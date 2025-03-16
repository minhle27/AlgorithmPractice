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

# Main HTML template (includes heatmap, statistics, and logs)
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
    /* Date picker controls above heatmap */
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
    #heatmap {
      margin-bottom: 20px;
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
    
    <!-- Date picker controls for adjusting heatmap window -->
    <div class="date-controls">
      <label for="datePicker">Select end date for heatmap:</label>
      <input type="date" id="datePicker">
      <button id="goDate">Go</button>
      <button id="resetDate">Reset to Today</button>
    </div>
    
    <!-- Heatmap container -->
    <div id="heatmap"></div>
    
    <!-- Statistics section -->
    <div id="stats">Loading statistics...</div>
    
    <button class="reset-button" onclick="updateLog()">Show All Logs</button>
    <!-- Log container -->
    <div id="log"></div>
  </div>
  
  <script>
    // Global variables for filtering and the current heatmap end date.
    let currentDayFilter = null;
    let currentEndDate = new Date(); // Defaults to today.
  
    // Initially loaded aggregated data from server.
    window.aggregatedData = {{ aggregated_data|safe }};
  
    document.addEventListener("DOMContentLoaded", function(){
        renderHeatmap();
        updateLog();
        updateStats();
    });
  
    // Date picker functionality.
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
  
    // Refresh aggregated data from the server and then update the heatmap.
    function refreshHeatmapData(callback) {
      fetch("/api/aggregation")
        .then(response => response.json())
        .then(data => {
           window.aggregatedData = data;
           renderHeatmap();
           if (callback) callback();
        });
    }
  
    // Render the heatmap for a 365-day window ending on currentEndDate.
    function renderHeatmap() {
      const heatmapContainer = document.getElementById('heatmap');
      heatmapContainer.innerHTML = '';
  
      const aggregatedData = window.aggregatedData;
      let endDate = new Date(currentEndDate);
      // Create window: 365 days ending with endDate.
      let startDate = new Date(endDate);
      startDate.setDate(endDate.getDate() - 364);
  
      // Calculate offset so that the first date aligns to the correct day of week.
      const offset = startDate.getDay();
      const daysElements = [];
      // Insert blank squares for offset.
      for (let i = 0; i < offset; i++) {
          const blank = document.createElement("div");
          blank.classList.add("square");
          blank.style.visibility = "hidden";
          daysElements.push(blank);
      }
      
      let date = new Date(startDate);
      for (let i = 0; i < 365; i++) {
          let cellDate = new Date(date);
          const dateStr = cellDate.toISOString().split("T")[0];
          const count = aggregatedData[dateStr] || 0;
          let level = "heat0";
          if (count === 1) { level = "heat1"; }
          else if (count === 2) { level = "heat2"; }
          else if (count === 3) { level = "heat3"; }
          else if (count >= 4) { level = "heat4"; }
          
          const square = document.createElement("div");
          square.classList.add("square", level);
          square.setAttribute("data-date", dateStr);
          // Tooltip displays date and count.
          square.title = dateStr + " (" + count + (count === 1 ? " activity)" : " activities)");
          square.addEventListener("click", function(){
              currentDayFilter = dateStr;
              updateLog(dateStr);
          });
          daysElements.push(square);
          date.setDate(date.getDate() + 1);
      }
  
      // Arrange the cells in a grid (53 columns, roughly one per week).
      heatmapContainer.style.display = "grid";
      heatmapContainer.style.gridTemplateColumns = "repeat(53, 15px)";
      heatmapContainer.style.gridGap = "4px";
      
      daysElements.forEach(cell => heatmapContainer.appendChild(cell));
    }
  
    // Fetch logs and group them by date (newer dates first).
    function updateLog(day) {
      currentDayFilter = day || null;
      const logContainer = document.getElementById("log");
      logContainer.innerHTML = "<p>Loading logs...</p>";
  
      let url = "/api/logs";
      if (day) {
         url += "?day=" + day;
      }
      fetch(url)
        .then(response => response.json())
        .then(data => {
           if (data.length === 0) {
              logContainer.innerHTML = "<p>No logs found.</p>";
              return;
           }
  
           // Group logs by date.
           const groups = {};
           data.forEach(entry => {
              let dateKey = entry.datetime.split(" ")[0];
              if (!groups[dateKey]) {
                  groups[dateKey] = [];
              }
              groups[dateKey].push(entry);
           });
  
           // Sort dates descending (most recent first).
           const dates = Object.keys(groups).sort((a, b) => new Date(b) - new Date(a));
           let html = "";
  
           dates.forEach(dateKey => {
              html += "<div class='log-group'>";
              html += "<div class='log-date'>" + dateKey + " (" + groups[dateKey].length + " log" + (groups[dateKey].length > 1 ? "s" : "") + ")</div>";
              // Sort logs by time descending.
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
  
           // Attach deletion event handlers.
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
  
    // Fetch stats from the server and update the statistics section.
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
  
    // Delete log entry (calls backend DELETE endpoint).
    function deleteLog(logId) {
      fetch("/api/delete", {
         method: "DELETE",
         headers: {
             "Content-Type": "application/json"
         },
         body: JSON.stringify({ id: logId })
      })
      .then(response => response.json())
      .then(data => {
         if (data.status === "success") {
             // Refresh logs, heatmap, and statistics.
             updateLog(currentDayFilter);
             refreshHeatmapData();
             updateStats();
         } else {
             alert("Error deleting log: " + data.message);
         }
      })
      .catch(err => {
         alert("Error deleting log.");
      });
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
    # Retrieve aggregated counts (by day).
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
        # All-time streak: from the earliest recorded date to the latest.
        all_dates = sorted(aggregated.keys())
        min_date = datetime.date.fromisoformat(all_dates[0])
        max_date = datetime.date.fromisoformat(all_dates[-1])
        max_streak_all_time = calculate_max_streak(min_date, max_date, aggregated)
    else:
        max_streak_all_time = 0
  
    today = datetime.date.today()
    last_month_start = today - datetime.timedelta(days=29)  # last 30 days including today
    max_streak_last_month = calculate_max_streak(last_month_start, today, aggregated)
  
    # Total logs: sum of all counts.
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
