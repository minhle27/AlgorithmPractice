#!/usr/bin/env python3
import sys
import sqlite3
import datetime
import json
import threading
import webbrowser
from flask import Flask, request, jsonify, render_template_string

DB_FILE = "activities.db"

def init_db():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("""
      CREATE TABLE IF NOT EXISTS activities (
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          datetime TEXT NOT NULL,
          message TEXT NOT NULL
      )
    """)
    conn.commit()
    conn.close()

init_db()

app = Flask(__name__)

# Main HTML template with separate containers for month labels, day labels, and the heatmap grid.
TEMPLATE = """
<!doctype html>
<html>
<head>
  <title>Activity Tracker</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: Arial, sans-serif;
      background: #f4f7f6;
      color: #333;
      margin: 0;
      padding: 20px;
    }
    .container {
      max-width: 900px;
      margin: 0 auto;
    }
    h1 {
      text-align: center;
      margin-bottom: 20px;
    }
    /* Date picker controls */
    .date-controls {
      text-align: center;
      margin-bottom: 15px;
    }
    .date-controls input,
    .date-controls button {
      padding: 8px 12px;
      margin: 5px;
      border-radius: 4px;
      border: 1px solid #ccc;
      font-size: 1em;
    }
    .date-controls button {
      background: #30a14e;
      color: white;
      border: none;
      cursor: pointer;
    }
    .date-controls button:hover {
      background: #248737;
    }
    /* Heatmap Layout */
    #heatmap-container {
      position: relative;
      margin-bottom: 20px;
    }
    /* Month labels are displayed above the grid.
       The left margin accounts for day labels below. */
    #month-labels {
      display: grid;
      grid-auto-flow: column;
      grid-gap: 4px;
      margin-left: 30px;
      margin-bottom: 4px;
    }
    /* The day labels container appears to the left of the grid. */
    #day-labels {
      width: 30px;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      margin-right: 4px;
    }
    #day-labels div {
      font-size: 10px;
      height: 15px;
      line-height: 15px;
    }
    /* The heatmap grid itself */
    #heatmap {
      display: grid;
      grid-template-rows: repeat(7, 15px);
      grid-auto-flow: column;
      grid-gap: 4px;
    }
    .square {
      width: 15px;
      height: 15px;
      border-radius: 3px;
      cursor: pointer;
    }
    .heat0 { background-color: #ebedf0; }
    .heat1 { background-color: #c6e48b; }
    .heat2 { background-color: #7bc96f; }
    .heat3 { background-color: #239a3b; }
    .heat4 { background-color: #196127; }
    /* Statistics styles */
    #stats {
      border: 1px solid #ddd;
      background: #fff;
      padding: 10px;
      border-radius: 4px;
      margin-bottom: 20px;
      display: flex;
      justify-content: space-around;
      flex-wrap: wrap;
    }
    .stat-item {
      font-size: 1.1em;
      text-align: center;
      margin: 5px 20px;
    }
    .stat-label {
      font-weight: bold;
      color: #555;
      margin-bottom: 4px;
    }
    /* Log container styles */
    #log {
      background: #fff;
      border: 1px solid #ddd;
      padding: 10px;
      border-radius: 4px;
      max-height: 500px;
      overflow-y: auto;
    }
    .log-group:not(:last-child) {
      margin-bottom: 15px;
    }
    .log-date {
      font-size: 1.1em;
      font-weight: bold;
      margin-bottom: 5px;
      border-bottom: 1px solid #eee;
      padding-bottom: 5px;
    }
    .log-entry {
      padding-left: 15px;
      border-left: 2px solid #239a3b;
      margin-bottom: 5px;
      display: flex;
      align-items: center;
      justify-content: space-between;
    }
    .log-info {
      display: inline-block;
    }
    .log-time {
      font-weight: bold;
      margin-right: 5px;
    }
    .delete-button {
      background: none;
      border: none;
      color: #d00;
      cursor: pointer;
      font-size: 0.8em;
      margin-left: 10px;
    }
    .delete-button:hover {
      text-decoration: underline;
    }
    .reset-button {
      margin: 10px 0;
      padding: 8px 12px;
      background: #30a14e;
      color: white;
      border: none;
      border-radius: 4px;
      cursor: pointer;
    }
    .reset-button:hover {
      background: #248737;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Activity Tracker</h1>
    
    <!-- Date picker controls -->
    <div class="date-controls">
      <label for="datePicker">Select end date for heatmap:</label>
      <input type="date" id="datePicker">
      <button id="goDate">Go</button>
      <button id="resetDate">Reset to Today</button>
    </div>
    
    <!-- Heatmap container including month and day labels -->
    <div id="heatmap-container">
      <div id="month-labels"></div>
      <div style="display: flex;">
        <div id="day-labels"></div>
        <div id="heatmap"></div>
      </div>
    </div>
    
    <!-- Statistics section -->
    <div id="stats">Loading statistics...</div>
    
    <button class="reset-button" onclick="updateLog()">Show All Logs</button>
    <!-- Log container -->
    <div id="log"></div>
  </div>
  
  <script>
    // Global variables for filtering and current heatmap end date.
    let currentDayFilter = null;
    let currentEndDate = new Date(); // Defaults to today.
  
    // Initially loaded aggregated data from the server.
    window.aggregatedData = {{ aggregated_data|safe }};
  
    document.addEventListener("DOMContentLoaded", function(){
        renderHeatmap();
        updateLog();
        updateStats();
    });
  
    // Date-picker functionality.
    document.getElementById("goDate").addEventListener("click", function(){
        const picker = document.getElementById("datePicker");
        if (picker.value) {
            currentEndDate = new Date(picker.value);
            renderHeatmap();
        }
    });
    document.getElementById("resetDate").addEventListener("click", function(){
        currentEndDate = new Date();
        document.getElementById("datePicker").value = "";
        renderHeatmap();
    });
  
    // Refresh aggregated data from the server.
    function refreshHeatmapData(callback) {
      fetch("/api/aggregation")
        .then(response => response.json())
        .then(data => {
           window.aggregatedData = data;
           renderHeatmap();
           if (callback) callback();
        });
    }
    
    // Render the heatmap with month and day labels.
    function renderHeatmap() {
      // Retrieve container elements
      const heatmapEl = document.getElementById('heatmap');
      const monthLabelsEl = document.getElementById('month-labels');
      const dayLabelsEl = document.getElementById('day-labels');
      heatmapEl.innerHTML = "";
      monthLabelsEl.innerHTML = "";
  
      // Normalize end date (set time to midnight)
      let endDate = new Date(currentEndDate);
      endDate.setHours(0,0,0,0);
      // 365-day window ending on endDate.
      let startDate = new Date(endDate);
      startDate.setDate(endDate.getDate() - 364);
  
      // Calculate offset: number of blank cells to insert before the first valid date.
      const offset = startDate.getDay();
      const oneDay = 24 * 60 * 60 * 1000;
      const totalCells = offset + 365;
      const columnCount = Math.ceil(totalCells / 7);
  
      // Compute month labels for each week (column)
      const monthLabels = new Array(columnCount).fill("");
      let prevMonth = null;
      for (let i = 0; i < columnCount; i++) {
          // Find the first valid cell in this column.
          for (let j = 0; j < 7; j++) {
              let cellIndex = i * 7 + j;
              if (cellIndex < offset) continue;
              let dayIndex = cellIndex - offset;
              let cellDate = new Date(startDate.getTime() + dayIndex * oneDay);
              let currentMonth = cellDate.getMonth();
              if (i === 0 || currentMonth !== prevMonth) {
                  const monthNames = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
                  monthLabels[i] = monthNames[currentMonth];
                  prevMonth = currentMonth;
              }
              break;
          }
      }
  
      // Render month labels.
      monthLabelsEl.style.display = "grid";
      monthLabelsEl.style.gridAutoFlow = "column";
      monthLabelsEl.style.gridGap = "4px";
      for (let i = 0; i < columnCount; i++) {
          const labelDiv = document.createElement("div");
          labelDiv.style.width = "15px";
          labelDiv.style.textAlign = "center";
          labelDiv.style.fontSize = "10px";
          labelDiv.textContent = monthLabels[i];
          monthLabelsEl.appendChild(labelDiv);
      }
  
      // Build cells for the heatmap grid.
      const cells = [];
      for (let i = 0; i < offset; i++) {
          const blank = document.createElement("div");
          blank.classList.add("square");
          blank.style.visibility = "hidden";
          cells.push(blank);
      }
      let date = new Date(startDate);
      for (let i = 0; i < 365; i++) {
          let cellDate = new Date(date);
          const dateStr = cellDate.toISOString().split("T")[0];
          const count = window.aggregatedData[dateStr] || 0;
          let level = "heat0";
          if (count === 1) { level = "heat1"; }
          else if (count === 2) { level = "heat2"; }
          else if (count === 3) { level = "heat3"; }
          else if (count >= 4) { level = "heat4"; }
          const square = document.createElement("div");
          square.classList.add("square", level);
          square.setAttribute("data-date", dateStr);
          square.title = dateStr + " (" + count + (count === 1 ? " activity)" : " activities)");
          square.addEventListener("click", function(){
              currentDayFilter = dateStr;
              updateLog(dateStr);
          });
          cells.push(square);
          date.setDate(date.getDate() + 1);
      }
  
      heatmapEl.style.display = "grid";
      heatmapEl.style.gridTemplateRows = "repeat(7, 15px)";
      heatmapEl.style.gridAutoFlow = "column";
      heatmapEl.style.gridGap = "4px";
      cells.forEach(cell => heatmapEl.appendChild(cell));
  
      // Render day labels (only show "Mon", "Wed", "Fri")
      dayLabelsEl.innerHTML = "";
      dayLabelsEl.style.display = "flex";
      dayLabelsEl.style.flexDirection = "column";
      dayLabelsEl.style.justifyContent = "space-between";
      const dayLabelsText = {1: "Mon", 3: "Wed", 5: "Fri"};
      for (let i = 0; i < 7; i++) {
          const dayDiv = document.createElement("div");
          dayDiv.style.height = "15px";
          dayDiv.style.fontSize = "10px";
          dayDiv.textContent = dayLabelsText[i] || "";
          dayLabelsEl.appendChild(dayDiv);
      }
    }
  
    // Fetch and display logs; grouped by date.
    function updateLog(day) {
      currentDayFilter = day || null;
      const logContainer = document.getElementById("log");
      logContainer.innerHTML = "<p>Loading logs...</p>";
  
      let url = "/api/logs";
      if (day) { url += "?day=" + day; }
      fetch(url)
        .then(response => response.json())
        .then(data => {
           if (data.length === 0) {
              logContainer.innerHTML = "<p>No logs found.</p>";
              return;
           }
  
           const groups = {};
           data.forEach(entry => {
              let dateKey = entry.datetime.split(" ")[0];
              if (!groups[dateKey]) { groups[dateKey] = []; }
              groups[dateKey].push(entry);
           });
  
           const dates = Object.keys(groups).sort((a, b) => new Date(b) - new Date(a));
           let html = "";
           dates.forEach(dateKey => {
              html += "<div class='log-group'>";
              html += "<div class='log-date'>" + dateKey + " (" + groups[dateKey].length + " log" + (groups[dateKey].length > 1 ? "s" : "") + ")</div>";
              const logsSorted = groups[dateKey].sort((a, b) => new Date(b.datetime) - new Date(a.datetime));
              logsSorted.forEach(entry => {
                  const timePart = entry.datetime.split(" ")[1];
                  html += "<div class='log-entry'>";
                  html += "<span class='log-info'><span class='log-time'>" + timePart + "</span> - " + entry.message + "</span>";
                  html += "<button class='delete-button' data-logid='" + entry.id + "'>Delete</button>";
                  html += "</div>";
              });
              html += "</div>";
           });
           logContainer.innerHTML = html;
  
           document.querySelectorAll(".delete-button").forEach(button => {
              button.addEventListener("click", function(e) {
                  const logId = e.target.getAttribute("data-logid");
                  if (confirm("Are you sure you want to delete this log?")) {
                      deleteLog(logId);
                  }
              });
           });
        });
    }
  
    // Fetch and display statistics.
    function updateStats(){
      fetch("/api/stats")
        .then(response => response.json())
        .then(data => {
           const statsContainer = document.getElementById("stats");
           let html = "";
           html += "<div class='stat-item'><div class='stat-label'>Max Streak (All Time)</div><div>"+ data.max_streak_all_time +"</div></div>";
           html += "<div class='stat-item'><div class='stat-label'>Max Streak (Last Month)</div><div>"+ data.max_streak_last_month +"</div></div>";
           html += "<div class='stat-item'><div class='stat-label'>Total Logs (All Time)</div><div>"+ data.total_logs_all_time +"</div></div>";
           html += "<div class='stat-item'><div class='stat-label'>Total Logs (Last Month)</div><div>"+ data.total_logs_last_month +"</div></div>";
           statsContainer.innerHTML = html;
        });
    }
  
    // Delete a log entry.
    function deleteLog(logId) {
      fetch("/api/delete", {
         method: "DELETE",
         headers: { "Content-Type": "application/json" },
         body: JSON.stringify({ id: logId })
      })
      .then(response => response.json())
      .then(data => {
         if (data.status === "success") {
             updateLog(currentDayFilter);
             refreshHeatmapData();
             updateStats();
         } else {
             alert("Error deleting log: " + data.message);
         }
      })
      .catch(err => { alert("Error deleting log."); });
    }
  </script>
</body>
</html>
"""

@app.route("/")
def index():
    # Aggregate counts per day.
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("SELECT DATE(datetime) as log_date, COUNT(*) as count FROM activities GROUP BY log_date")
    rows = cur.fetchall()
    aggregated = {row[0]: row[1] for row in rows}
    conn.close()
    return render_template_string(TEMPLATE, aggregated_data=json.dumps(aggregated))

@app.route("/api/logs")
def get_logs():
    day = request.args.get("day", None)
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    if day:
        cur.execute("SELECT id, datetime, message FROM activities WHERE DATE(datetime)=? ORDER BY datetime DESC", (day,))
    else:
        cur.execute("SELECT id, datetime, message FROM activities ORDER BY datetime DESC")
    rows = cur.fetchall()
    conn.close()
    logs = [{"id": row[0], "datetime": row[1], "message": row[2]} for row in rows]
    return jsonify(logs)

@app.route("/api/aggregation")
def aggregation():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("SELECT DATE(datetime) as log_date, COUNT(*) as count FROM activities GROUP BY log_date")
    rows = cur.fetchall()
    aggregated = {row[0]: row[1] for row in rows}
    conn.close()
    return jsonify(aggregated)

@app.route("/api/stats")
def get_stats():
    # Retrieve aggregated counts per day.
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("SELECT DATE(datetime) as log_date, COUNT(*) as count FROM activities GROUP BY log_date")
    rows = cur.fetchall()
    aggregated = {row[0]: row[1] for row in rows}
    conn.close()
  
    def calculate_max_streak(start, end, aggregated):
        current = start
        streak = 0
        max_streak = 0
        while current <= end:
            s = current.isoformat()
            if aggregated.get(s, 0) > 0:
                streak += 1
            else:
                max_streak = max(max_streak, streak)
                streak = 0
            current += datetime.timedelta(days=1)
        max_streak = max(max_streak, streak)
        return max_streak
  
    if aggregated:
        all_dates = sorted(aggregated.keys())
        min_date = datetime.date.fromisoformat(all_dates[0])
        max_date = datetime.date.fromisoformat(all_dates[-1])
        max_streak_all_time = calculate_max_streak(min_date, max_date, aggregated)
    else:
        max_streak_all_time = 0
  
    today = datetime.date.today()
    last_month_start = today - datetime.timedelta(days=29)  # Last 30 days including today.
    max_streak_last_month = calculate_max_streak(last_month_start, today, aggregated)
  
    total_logs_all_time = sum(aggregated.values())
    total_logs_last_month = 0
    for i in range(30):
        d = (today - datetime.timedelta(days=i)).isoformat()
        total_logs_last_month += aggregated.get(d, 0)
  
    stats = {
        "max_streak_all_time": max_streak_all_time,
        "max_streak_last_month": max_streak_last_month,
        "total_logs_all_time": total_logs_all_time,
        "total_logs_last_month": total_logs_last_month
    }
    return jsonify(stats)

@app.route("/api/delete", methods=["DELETE"])
def delete_log():
    data = request.get_json()
    log_id = data.get("id")
    if not log_id:
        return jsonify({"status": "error", "message": "No ID provided"}), 400
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("DELETE FROM activities WHERE id=?", (log_id,))
    conn.commit()
    conn.close()
    return jsonify({"status": "success"})

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: ./app.py [add \"activity message\" | view]")
        sys.exit(1)
  
    command = sys.argv[1]
  
    if command == "add":
        if len(sys.argv) < 3:
            print("Please provide an activity message.")
            sys.exit(1)
        message = sys.argv[2]
        conn = sqlite3.connect(DB_FILE)
        cur = conn.cursor()
        now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        cur.execute("INSERT INTO activities (datetime, message) VALUES (?, ?)", (now, message))
        conn.commit()
        conn.close()
        print("Activity added.")
  
    elif command == "view":
        def open_browser():
            webbrowser.open("http://127.0.0.1:5000", new=2)
        threading.Timer(1, open_browser).start()
        app.run()
    else:
        print("Unknown command. Use 'add' or 'view'.")
        sys.exit(1)
