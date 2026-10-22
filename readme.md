# Smart Water Management and Irrigation Optimization System Using C++

A C++-based Smart Irrigation System that simulates water distribution across 100 farm zones using sensor readings, priority-based allocation, and graph-based shortest-path routing.

## 📌 Project Overview

Traditional irrigation methods can lead to over-irrigation in some areas and under-irrigation in others. This project aims to optimize water distribution by identifying which farm zones need irrigation most urgently.

The system evaluates simulated soil moisture, temperature, and rainfall probability to calculate irrigation priority. It then uses a priority queue to determine the irrigation order and Dijkstra’s algorithm to find the shortest available route from the water tank to each zone.

**Note:** This project is currently a software simulation. It does not directly control physical sensors, pumps, or valves.

## 🎯 Objectives

- Manage 100 farm zones with crop and environmental information.
- Accept manual or randomly generated sensor readings.
- Process sensor readings in FIFO order.
- Calculate irrigation priority using environmental conditions.
- Allocate limited water based on zone requirements.
- Find shortest water-delivery routes using Dijkstra’s algorithm.
- Support adding, updating, and removing pipes.
- Maintain irrigation history and display allocation summaries.

## ✨ Key Features

- **Farm Zone Management:** Maintains information about 100 zones, including crop type, moisture, temperature, rainfall, water requirements, and priority.
- **Sensor Simulation:** Generates simulated sensor readings or accepts manual input.
- **FIFO Sensor Processing:** Processes readings in the order they enter the queue.
- **Priority-Based Irrigation:** Ranks zones according to their calculated irrigation priority.
- **Water Tank Management:** Tracks available water and allows additional water to be added.
- **Smart Irrigation Decisions:** Supports irrigation, partial irrigation, or skipping a zone based on configured conditions.
- **Graph-Based Pipe Network:** Represents the tank and farm zones as nodes connected by weighted pipes.
- **Shortest-Path Routing:** Uses Dijkstra’s algorithm to calculate the minimum-cost route.
- **Pipe Management:** Adds new pipes, updates existing connections, and removes pipes.
- **Irrigation History:** Records irrigation decisions, water supplied, routes, and pipe costs.

## 🧠 Data Structures and Algorithms

| Concept | Application |
|---|---|
| `struct` | Stores farm-zone and sensor-reading information. |
| `vector` | Stores zones, irrigation history, and graph adjacency lists. |
| `queue` | Processes sensor readings using FIFO order. |
| `priority_queue` | Selects zones according to irrigation priority. |
| Graph | Represents the water-pipe network. |
| Adjacency list | Stores connections and weights between nodes. |
| Dijkstra’s algorithm | Finds the shortest available route from the tank. |

## 📊 Irrigation Priority Calculation

The system calculates a weighted priority score using soil moisture, temperature, and rainfall probability.

The implemented formula is:

```text
Temperature Score = ((Temperature - 10) / 40) × 100

Priority =
    0.5 × (100 - Soil Moisture)
  + 0.3 × Temperature Score
  + 0.2 × (100 - Rainfall Probability)
```

The temperature score is restricted to the range 0–100.

The weights are:

- **50% — Soil moisture:** Lower moisture increases priority.
- **30% — Temperature:** Higher temperatures generally increase priority.
- **20% — Rainfall probability:** Lower rainfall probability increases priority.

A higher score generally indicates a greater need for irrigation.

## ⚙️ System Workflow

1. Initialize 100 farm zones and the water-pipe network.
2. Enter sensor readings manually or generate simulated readings.
3. Store incoming readings in a FIFO queue.
4. Process the queue and update environmental values.
5. Calculate the irrigation priority for each zone.
6. Arrange zones in a priority queue.
7. Run Dijkstra’s algorithm from the water tank to determine available routes.
8. Check water availability, rainfall, soil moisture, and route availability.
9. Allocate water fully or partially, or skip irrigation when the configured conditions require it.
10. Update tank water, soil moisture, and remaining water requirements.
11. Record irrigation activity and display a summary.

## 🛠️ Technology Stack

- **Programming Language:** C++
- **Libraries:** `iostream`, `vector`, `queue`, `string`, `iomanip`, `climits`, and `cstdlib`, as applicable to individual source files.
- **Development Tools:** A C++ compiler such as GCC or MinGW.
- **Version Control:** Git and GitHub.

## 🚀 Getting Started

### Prerequisites

Install a C++ compiler that supports standard C++ features, such as GCC.

Check whether GCC is installed:

```bash
g++ --version
```

### Project Structure

The project documentation identifies the following source files:

```text
Smart-Irrigation-system/
├── main.cpp
├── farm.cpp
├── graph.cpp
└── README.md
```

- `main.cpp` — Main menu, program flow, module integration, irrigation execution, and water management.
- `farm.cpp` — Farm-zone data, sensor readings, FIFO queue processing, and priority calculation.
- `graph.cpp` — Graph representation, pipe management, Dijkstra’s algorithm, route reconstruction, and network display.
- `README.md` — Project documentation.

### Compilation

If all three source files contain the required definitions and declarations, compile them together:

```bash
g++ -std=c++17 main.cpp farm.cpp graph.cpp -o irrigation
```

### Run the Program

On Linux or macOS:

```bash
./irrigation
```

On Windows:

```bash
irrigation.exe
```

**Important:** The code snippets must be integrated with the complete project, including the shared global variables, function declarations, and main menu, before compilation. The compilation command assumes these files are present and correctly integrated.

## 💧 Water Network

The network contains 101 nodes:

- Node `0` represents the water tank.
- Nodes `1–100` represent the farm zones.
- Each pipe has a positive weight representing distance or cost.
- Connections are bidirectional in the current implementation.

The graph supports pipe addition, weight updates, and removal. Dijkstra’s algorithm calculates the minimum total pipe weight from the tank to each reachable zone.

## 🧪 Testing

The project documentation identifies the following major testing areas:

- Creation of all 100 farm zones.
- Manual and simulated sensor input.
- FIFO queue processing.
- Priority-score calculation.
- Water-tank management.
- Shortest-path routing.
- Pipe addition, updating, and removal.
- Irrigation decisions and partial allocation.
- Irrigation-history generation.
- Disconnected routes and invalid-input handling.

Further edge-case testing and final validation are part of the remaining project work.

## ⚠️ Limitations

- Sensor readings are simulated or entered manually.
- Irrigation priority uses a simplified weighted formula, not a complete agricultural prediction model.
- Pump and valve actions are represented by console messages.
- The application does not currently communicate with physical irrigation hardware.
- Real-world deployment would require hardware integration, real sensor data, and additional validation.

## 👥 Team Members

**Team Name:** aquacode  
**Team ID:** DSCPP-III-2026-T294  
**Project Domain:** Smart Water Management

- **Akanksha Katiyar** — Team Lead; main program, integration, irrigation execution, and water management.
- **Pragya Anand** — Graph module, pipe management, Dijkstra’s algorithm, and route reconstruction.
- **Shivendra Kumar Sahani** — Farm-zone management, sensor simulation, FIFO queue processing, and priority calculation.

## 🔮 Future Enhancements

- Integrate real soil-moisture, temperature, and rainfall sensors.
- Connect the software to physical pumps and automated valves.
- Develop a live dashboard for monitoring irrigation conditions.
- Improve water allocation using real-time weather forecasts.
- Add more comprehensive validation and performance testing.
- Evaluate the system under real farming conditions.

## 📚 References

- C++ Standard Library documentation.
- Documentation for queues, priority queues, vectors, and graph representations.
- Standard references on Dijkstra’s shortest-path algorithm.
- Course notes and prescribed Data Structures and Algorithms materials.
- Food and Agriculture Organization (FAO) resources on agricultural water management.

---

**Project:** Smart Water Management and Irrigation Optimization System Using C++  
**Institution:** Graphic Era (Deemed to be University), Dehradun  
**Academic Session:** 2026–27

