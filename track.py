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
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap" rel="stylesheet">
  <style>
    * {
      box-sizing: border-box;
    }
    
    body {
      font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      color: #2d3748;
      margin: 0;
      padding: 20px;
      min-height: 100vh;
      line-height: 1.6;
    }
    
    .container {
      max-width: 1000px;
      margin: 0 auto;
    }
    
    h1 {
      text-align: center;
      margin-bottom: 30px;
      font-size: 2.5rem;
      font-weight: 700;
      color: white;
      text-shadow: 0 2px 4px rgba(0,0,0,0.3);
      letter-spacing: -0.02em;
    }
    
    /* Card-style containers */
    .card {
      background: rgba(255, 255, 255, 0.95);
      backdrop-filter: blur(10px);
      border-radius: 16px;
      box-shadow: 0 8px 32px rgba(0, 0, 0, 0.12);
      border: 1px solid rgba(255, 255, 255, 0.2);
      transition: all 0.3s ease;
    }
    

    
    /* Date picker controls */
    .date-controls {
      text-align: center;
      margin-bottom: 25px;
      padding: 25px;
    }
    
    .date-controls label {
      display: block;
      margin-bottom: 15px;
      font-weight: 500;
      color: #4a5568;
      font-size: 1.1rem;
    }
    
    .date-controls input {
      padding: 12px 16px;
      margin: 8px;
      border-radius: 10px;
      border: 2px solid #e2e8f0;
      font-size: 1rem;
      font-family: inherit;
      transition: all 0.2s ease;
      background: white;
    }
    
    .date-controls input:focus {
      outline: none;
      border-color: #667eea;
      box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);
    }
    
    .date-controls button {
      padding: 12px 20px;
      margin: 8px;
      border-radius: 10px;
      border: none;
      font-size: 1rem;
      font-weight: 500;
      cursor: pointer;
      transition: all 0.2s ease;
      font-family: inherit;
    }
    
    .date-controls button:first-of-type {
      background: linear-gradient(135deg, #667eea, #764ba2);
      color: white;
    }
    
    .date-controls button:first-of-type:hover {
      transform: translateY(-1px);
      box-shadow: 0 4px 12px rgba(102, 126, 234, 0.4);
    }
    
    .date-controls button:last-of-type {
      background: #f7fafc;
      color: #4a5568;
      border: 2px solid #e2e8f0;
    }
    
    .date-controls button:last-of-type:hover {
      background: #edf2f7;
      border-color: #cbd5e0;
    }
    
    /* Heatmap Layout */
    .heatmap-card {
      padding: 30px 30px 25px 30px;
      margin-bottom: 25px;
      overflow-x: auto;
    }
    
    .heatmap-card::-webkit-scrollbar {
      height: 8px;
    }
    
    .heatmap-card::-webkit-scrollbar-track {
      background: #f1f5f9;
      border-radius: 4px;
      margin: 2px 8px 2px 8px;
    }
    
    .heatmap-card::-webkit-scrollbar-thumb {
      background: #cbd5e0;
      border-radius: 4px;
      border: 1px solid #f1f5f9;
    }
    
    .heatmap-card::-webkit-scrollbar-thumb:hover {
      background: #a0aec0;
    }
    
    #heatmap-container {
      position: relative;
      margin-bottom: 15px;
      min-width: fit-content;
      width: 100%;
      box-sizing: border-box;
    }
    
    /* Month labels */
    #month-labels {
      display: grid;
      grid-auto-flow: column;
      grid-gap: 4px;
      margin-left: 35px;
      margin-bottom: 8px;
    }
    
    #month-labels div {
      font-size: 11px;
      font-weight: 500;
      color: #718096;
      text-align: center;
    }
    
    /* Day labels */
    #day-labels {
      width: 35px;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      margin-right: 6px;
    }
    
    #day-labels div {
      font-size: 11px;
      font-weight: 500;
      color: #718096;
      height: 15px;
      line-height: 15px;
    }
    
    /* Heatmap grid */
    #heatmap {
      display: grid;
      grid-template-rows: repeat(7, 15px);
      grid-auto-flow: column;
      grid-gap: 4px;
    }
    
    .square {
      width: 15px;
      height: 15px;
      border-radius: 4px;
      cursor: pointer;
      transition: all 0.15s ease;
      border: 1px solid rgba(0,0,0,0.04);
    }
    

    
    .heat0 { background: #f1f5f9; }
    .heat1 { background: linear-gradient(135deg, #bbf7d0, #86efac); }
    .heat2 { background: linear-gradient(135deg, #86efac, #4ade80); }
    .heat3 { background: linear-gradient(135deg, #4ade80, #22c55e); }
    .heat4 { background: linear-gradient(135deg, #22c55e, #16a34a); }
    
    /* Statistics styles */
    .stats-card {
      padding: 30px;
      margin-bottom: 25px;
    }
    
    #stats {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
      gap: 25px;
    }
    
    .stat-item {
      text-align: center;
      padding: 20px;
      background: linear-gradient(135deg, #f8fafc, #f1f5f9);
      border-radius: 12px;
      transition: all 0.2s ease;
      border: 1px solid #e2e8f0;
    }
    
    .stat-item:hover {
      transform: translateY(-2px);
      box-shadow: 0 4px 12px rgba(0,0,0,0.1);
    }
    
    .stat-label {
      font-weight: 600;
      color: #4a5568;
      margin-bottom: 8px;
      font-size: 0.9rem;
      text-transform: uppercase;
      letter-spacing: 0.5px;
    }
    
    .stat-value {
      font-size: 2rem;
      font-weight: 700;
      background: linear-gradient(135deg, #667eea, #764ba2);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      background-clip: text;
    }
    
    /* Log container styles */
    .logs-card {
      padding: 30px;
    }
    
    .logs-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 25px;
      flex-wrap: wrap;
      gap: 15px;
    }
    
    .logs-header h3 {
      margin: 0;
      color: #2d3748;
      font-size: 1.5rem;
      font-weight: 600;
      position: relative;
    }
    
    .search-loading {
      display: inline-block;
      width: 12px;
      height: 12px;
      border: 2px solid #e2e8f0;
      border-top: 2px solid #667eea;
      border-radius: 50%;
      animation: spin 1s linear infinite;
      margin-left: 10px;
    }
    
    @keyframes spin {
      0% { transform: rotate(0deg); }
      100% { transform: rotate(360deg); }
    }
    
    .logs-content {
      position: relative;
    }
    
    .logs-overlay {
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background: rgba(255, 255, 255, 0.8);
      backdrop-filter: blur(2px);
      display: flex;
      align-items: center;
      justify-content: center;
      border-radius: 12px;
      z-index: 10;
    }
    
    .search-container {
      display: flex;
      gap: 10px;
      align-items: center;
    }
    
    .search-container input {
      padding: 10px 14px;
      border: 2px solid #e2e8f0;
      border-radius: 8px;
      font-size: 0.9rem;
      font-family: inherit;
      min-width: 200px;
      transition: all 0.2s ease;
    }
    
    .search-container input:focus {
      outline: none;
      border-color: #667eea;
      box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);
    }
    
    .search-container button {
      padding: 10px 16px;
      background: #f7fafc;
      color: #4a5568;
      border: 2px solid #e2e8f0;
      border-radius: 8px;
      font-size: 0.9rem;
      font-weight: 500;
      cursor: pointer;
      transition: all 0.2s ease;
      font-family: inherit;
    }
    
    .search-container button:hover {
      background: #edf2f7;
      border-color: #cbd5e0;
    }
    
    #log {
      max-height: 500px;
      overflow-y: auto;
      border-radius: 12px;
      margin-bottom: 20px;
    }
    
    /* Pagination styles */
    .pagination-container {
      display: flex;
      justify-content: center;
      align-items: center;
      gap: 10px;
      margin-top: 20px;
      padding: 15px 0;
    }
    
    .pagination-btn {
      padding: 8px 12px;
      background: #f7fafc;
      color: #4a5568;
      border: 2px solid #e2e8f0;
      border-radius: 6px;
      font-size: 0.9rem;
      font-weight: 500;
      cursor: pointer;
      transition: all 0.2s ease;
      font-family: inherit;
    }
    
    .pagination-btn:hover:not(:disabled) {
      background: #edf2f7;
      border-color: #cbd5e0;
    }
    
    .pagination-btn:disabled {
      opacity: 0.5;
      cursor: not-allowed;
    }
    
    .pagination-btn.active {
      background: linear-gradient(135deg, #667eea, #764ba2);
      color: white;
      border-color: #667eea;
    }
    
    .pagination-info {
      color: #718096;
      font-size: 0.9rem;
      margin: 0 10px;
    }
    
    .log-group:not(:last-child) {
      margin-bottom: 25px;
    }
    
    .log-date {
      font-size: 1.2rem;
      font-weight: 600;
      margin-bottom: 15px;
      padding: 15px 20px;
      background: linear-gradient(135deg, #f8fafc, #edf2f7);
      border-radius: 10px;
      color: #2d3748;
      border-left: 4px solid #667eea;
    }
    
    .log-entry {
      padding: 15px 20px;
      margin-bottom: 10px;
      background: white;
      border-radius: 10px;
      border: 1px solid #e2e8f0;
      display: flex;
      align-items: center;
      justify-content: space-between;
      transition: all 0.2s ease;
    }
    

    
    .log-info {
      display: flex;
      align-items: center;
      flex: 1;
    }
    
    .log-time {
      font-weight: 600;
      margin-right: 15px;
      color: #667eea;
      font-size: 0.9rem;
      padding: 4px 8px;
      background: rgba(102, 126, 234, 0.1);
      border-radius: 6px;
    }
    
    .log-message {
      color: #4a5568;
    }
    
    .delete-button {
      background: linear-gradient(135deg, #fed7d7, #feb2b2);
      border: none;
      color: #c53030;
      cursor: pointer;
      font-size: 0.85rem;
      font-weight: 500;
      padding: 6px 12px;
      border-radius: 8px;
      transition: all 0.2s ease;
      font-family: inherit;
    }
    
    .delete-button:hover {
      background: linear-gradient(135deg, #feb2b2, #fc8181);
      color: white;
      transform: scale(1.05);
    }
    
    /* Loading state */
    .loading {
      text-align: center;
      padding: 40px;
      color: #718096;
      font-style: italic;
    }
    
    /* Responsive design */
    @media (max-width: 768px) {
      body { padding: 15px; }
      h1 { font-size: 2rem; }
      .card { margin-bottom: 20px; }
      .date-controls, .heatmap-card, .stats-card, .logs-card { padding: 20px; }
      #stats { grid-template-columns: repeat(auto-fit, minmax(150px, 1fr)); gap: 15px; }
      .stat-item { padding: 15px; }
      .stat-value { font-size: 1.5rem; }
      .logs-header { flex-direction: column; align-items: stretch; }
      .search-container { justify-content: center; }
      .search-container input { min-width: 150px; }
      .pagination-container { flex-wrap: wrap; }
    }
    
    @media (max-width: 480px) {
      h1 { font-size: 1.75rem; }
      .date-controls input, .date-controls button { width: 100%; margin: 5px 0; }
      #stats { grid-template-columns: 1fr; }
      .search-container { flex-direction: column; gap: 8px; }
      .search-container input, .search-container button { width: 100%; }
      .pagination-btn { font-size: 0.8rem; padding: 6px 10px; }
      .pagination-info { font-size: 0.8rem; }
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>🔥 Activity Tracker</h1>
    
    <!-- Date picker controls -->
    <div class="card date-controls">
      <label for="datePicker">📅 Select end date for heatmap</label>
      <input type="date" id="datePicker">
      <button id="goDate">Go</button>
      <button id="resetDate">Reset to Today</button>
    </div>
    
    <!-- Heatmap container -->
    <div class="card heatmap-card">
      <div id="heatmap-container">
        <div id="month-labels"></div>
        <div style="display: flex;">
          <div id="day-labels"></div>
          <div id="heatmap"></div>
        </div>
      </div>
    </div>
    
    <!-- Statistics section -->
    <div class="card stats-card">
      <div id="stats" class="loading">Loading statistics...</div>
    </div>
    
    <!-- Log container -->
    <div class="card logs-card">
      <div class="logs-header">
        <h3>📊 Activity Logs</h3>
        <div class="search-container">
          <input type="text" id="searchInput" placeholder="🔍 Search logs..." />
          <button id="clearSearch">Clear</button>
        </div>
      </div>
      <div class="logs-content">
        <div id="log"></div>
        <div id="pagination" class="pagination-container"></div>
      </div>
    </div>
  </div>
  
  <script>
    // Global variables for filtering and current heatmap end date.
    let currentDayFilter = null;
    let currentEndDate = new Date(); // Defaults to today.
  
    // Initially loaded aggregated data from the server.
    window.aggregatedData = {{ aggregated_data|safe }};
  
    // Global variables for pagination and search
    let currentPage = 1;
    let currentSearch = "";
    const itemsPerPage = 20;
    
    document.addEventListener("DOMContentLoaded", function(){
        renderHeatmap();
        updateLog();
        updateStats();
        
        // Setup search functionality
        const searchInput = document.getElementById("searchInput");
        const clearSearchBtn = document.getElementById("clearSearch");
        
        let searchTimeout;
        searchInput.addEventListener("input", function(){
            clearTimeout(searchTimeout);
            
            // Show loading indicator immediately
            showSearchLoading(true);
            
            searchTimeout = setTimeout(() => {
                currentSearch = searchInput.value;
                currentPage = 1;
                updateLog(currentDayFilter);
            }, 200); // reduced from 300ms to 200ms
        });
        
        clearSearchBtn.addEventListener("click", function(){
            searchInput.value = "";
            currentSearch = "";
            currentPage = 1;
            showSearchLoading(false);
            updateLog(currentDayFilter);
        });
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
  
      // Normalize end date (set time to end of day to include today)
      let endDate = new Date(currentEndDate);
      endDate.setHours(23,59,59,999);
      // 365-day window ending on endDate.
      let startDate = new Date(endDate);
      startDate.setDate(endDate.getDate() - 364);
      startDate.setHours(0,0,0,0);
  
      // Calculate offset: number of blank cells to insert before the first valid date.
      const offset = startDate.getDay();
      const oneDay = 24 * 60 * 60 * 1000;
      const totalCells = offset + 366;  // Updated to account for the extra day
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
          labelDiv.style.fontSize = "11px";
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
      for (let i = 0; i <= 365; i++) {  // Changed to <= to include today
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
          
          // Highlight today's cell
          const today = new Date().toISOString().split("T")[0];
          if (dateStr === today) {
              square.style.border = "2px solid #667eea";
              square.style.boxShadow = "0 0 0 1px rgba(102, 126, 234, 0.3)";
          }
          
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
          dayDiv.style.fontSize = "11px";
          dayDiv.textContent = dayLabelsText[i] || "";
          dayLabelsEl.appendChild(dayDiv);
      }
    }
  
        // Show/hide search loading indicator
    function showSearchLoading(show) {
      const header = document.querySelector('.logs-header h3');
      const existingSpinner = header.querySelector('.search-loading');
      
      if (show && !existingSpinner) {
        const spinner = document.createElement('span');
        spinner.className = 'search-loading';
        header.appendChild(spinner);
      } else if (!show && existingSpinner) {
        existingSpinner.remove();
      }
    }
    
    // Show smooth loading overlay
    function showLogsOverlay(show) {
      const logsContent = document.querySelector('.logs-content');
      let overlay = logsContent.querySelector('.logs-overlay');
      
      if (show && !overlay) {
        overlay = document.createElement('div');
        overlay.className = 'logs-overlay';
        overlay.innerHTML = '<div class="search-loading"></div>';
        logsContent.appendChild(overlay);
      } else if (!show && overlay) {
        overlay.remove();
      }
    }

    // Fetch and display logs with pagination and search
    function updateLog(day) {
      currentDayFilter = day || null;
      const logContainer = document.getElementById("log");
      const paginationContainer = document.getElementById("pagination");
      
      // For initial load or when no existing content
      if (logContainer.innerHTML === "" || logContainer.innerHTML.includes("Loading logs...")) {
        logContainer.innerHTML = "<div class='loading'>Loading logs...</div>";
        paginationContainer.innerHTML = "";
      } else {
        // Show overlay for smoother experience when content exists
        showLogsOverlay(true);
      }

      let url = "/api/logs?page=" + currentPage + "&per_page=" + itemsPerPage;
      if (day) url += "&day=" + day;
      if (currentSearch) url += "&search=" + encodeURIComponent(currentSearch);
      
            fetch(url)
        .then(response => response.json())
        .then(data => {
           // Hide loading indicators
           showSearchLoading(false);
           showLogsOverlay(false);
           
           if (data.logs.length === 0) {
              logContainer.innerHTML = "<div class='loading'>No logs found.</div>";
              paginationContainer.innerHTML = "";
              return;
           }

           const groups = {};
           data.logs.forEach(entry => {
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
                  html += "<div class='log-info'><span class='log-time'>" + timePart + "</span><span class='log-message'>" + entry.message + "</span></div>";
                  html += "<button class='delete-button' data-logid='" + entry.id + "'>Delete</button>";
                  html += "</div>";
              });
              html += "</div>";
           });
           logContainer.innerHTML = html;

           // Render pagination
           renderPagination(data);

           document.querySelectorAll(".delete-button").forEach(button => {
              button.addEventListener("click", function(e) {
                  const logId = e.target.getAttribute("data-logid");
                  if (confirm("Are you sure you want to delete this log?")) {
                      deleteLog(logId);
                  }
              });
           });
        })
        .catch(err => {
           // Hide loading indicators on error
           showSearchLoading(false);
           showLogsOverlay(false);
           logContainer.innerHTML = "<div class='loading'>Error loading logs.</div>";
           paginationContainer.innerHTML = "";
        });
    }
    
    // Render pagination controls
    function renderPagination(data) {
      const paginationContainer = document.getElementById("pagination");
      if (data.total_pages <= 1) {
        paginationContainer.innerHTML = "";
        return;
      }
      
      let html = "";
      
      // Previous button
      html += `<button class="pagination-btn" ${currentPage === 1 ? 'disabled' : ''} onclick="changePage(${currentPage - 1})">← Previous</button>`;
      
      // Page numbers
      const startPage = Math.max(1, currentPage - 2);
      const endPage = Math.min(data.total_pages, currentPage + 2);
      
      if (startPage > 1) {
        html += `<button class="pagination-btn" onclick="changePage(1)">1</button>`;
        if (startPage > 2) html += `<span class="pagination-info">...</span>`;
      }
      
      for (let i = startPage; i <= endPage; i++) {
        html += `<button class="pagination-btn ${i === currentPage ? 'active' : ''}" onclick="changePage(${i})">${i}</button>`;
      }
      
      if (endPage < data.total_pages) {
        if (endPage < data.total_pages - 1) html += `<span class="pagination-info">...</span>`;
        html += `<button class="pagination-btn" onclick="changePage(${data.total_pages})">${data.total_pages}</button>`;
      }
      
      // Next button
      html += `<button class="pagination-btn" ${currentPage === data.total_pages ? 'disabled' : ''} onclick="changePage(${currentPage + 1})">Next →</button>`;
      
      // Info
      const start = (currentPage - 1) * itemsPerPage + 1;
      const end = Math.min(currentPage * itemsPerPage, data.total_count);
      html += `<span class="pagination-info">Showing ${start}-${end} of ${data.total_count}</span>`;
      
      paginationContainer.innerHTML = html;
    }
    
    // Change page function
    function changePage(page) {
      currentPage = page;
      updateLog(currentDayFilter);
    }
  
    // Fetch and display statistics.
    function updateStats(){
      fetch("/api/stats")
        .then(response => response.json())
        .then(data => {
           const statsContainer = document.getElementById("stats");
           let html = "";
           html += "<div class='stat-item'><div class='stat-label'>Max Streak (All Time)</div><div class='stat-value'>"+ data.max_streak_all_time +"</div></div>";
           html += "<div class='stat-item'><div class='stat-label'>Max Streak (Last Month)</div><div class='stat-value'>"+ data.max_streak_last_month +"</div></div>";
           html += "<div class='stat-item'><div class='stat-label'>Total Logs (All Time)</div><div class='stat-value'>"+ data.total_logs_all_time +"</div></div>";
           html += "<div class='stat-item'><div class='stat-label'>Total Logs (Last Month)</div><div class='stat-value'>"+ data.total_logs_last_month +"</div></div>";
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
             // Stay on current page, but go to page 1 if current page becomes empty
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
    search = request.args.get("search", "")
    page = int(request.args.get("page", 1))
    per_page = int(request.args.get("per_page", 20))
    
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    
    # Build the WHERE clause
    where_conditions = []
    params = []
    
    if day:
        where_conditions.append("DATE(datetime) = ?")
        params.append(day)
    
    if search:
        where_conditions.append("message LIKE ?")
        params.append(f"%{search}%")
    
    where_clause = ""
    if where_conditions:
        where_clause = "WHERE " + " AND ".join(where_conditions)
    
    # Get total count
    count_query = f"SELECT COUNT(*) FROM activities {where_clause}"
    cur.execute(count_query, params)
    total_count = cur.fetchone()[0]
    
    # Get paginated results
    offset = (page - 1) * per_page
    query = f"SELECT id, datetime, message FROM activities {where_clause} ORDER BY datetime DESC LIMIT ? OFFSET ?"
    cur.execute(query, params + [per_page, offset])
    rows = cur.fetchall()
    conn.close()
    
    logs = [{"id": row[0], "datetime": row[1], "message": row[2]} for row in rows]
    
    return jsonify({
        "logs": logs,
        "total_count": total_count,
        "page": page,
        "per_page": per_page,
        "total_pages": (total_count + per_page - 1) // per_page
    })

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
