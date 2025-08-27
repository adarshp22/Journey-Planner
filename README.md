# 🚇 Metro Route Planner

A simple **command-line application** written in **C++** to find the shortest distance and path between stations in a metro network.  
This project uses **Dijkstra's Algorithm** to efficiently calculate routes in a weighted graph representing the metro map.

---

## ✨ Features
- 📍 **List All Stations**: View a complete list of all metro stations available in the network.  
- 🗺️ **Display Metro Map**: See the direct connections and distances between stations.  
- 📏 **Shortest Distance**: Calculate the shortest travel distance (in KM) between any two stations.  
- ⏱️ **Shortest Time**: Estimate the travel time based on the shortest distance.  
- 🚆 **Shortest Path**: Display the exact sequence of stations to take for the quickest route.  

---

## 🛠️ How to Run

### Prerequisites
- A **C++ compiler** (e.g., `g++`)

### Compilation
Open your terminal/command prompt and run:

```bash
g++ -o metro_app main.cpp
