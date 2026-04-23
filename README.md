# BFS & DFS Map Pathfinder

A C++ application that loads **real OpenStreetMap data** and lets you visually compare **Breadth-First Search** vs **Depth-First Search** pathfinding on an actual road network.

---

## 🗂️ Project Structure
```
DAA project/
├── CMakeLists.txt          ← Build system
├── build.bat               ← One-click Windows build
├── download_map.bat        ← Downloads real map from OpenStreetMap
├── data/
│   └── map.osm             ← Map data (download with download_map.bat)
├── include/
│   ├── graph.h             ← Graph data structure
│   ├── pathfinding.h       ← BFS/DFS result types
│   ├── map_parser.h        ← OSM XML parser
│   └── renderer.h          ← SFML visualizer
├── src/
│   ├── main.cpp
│   ├── graph.cpp
│   ├── map_parser.cpp
│   ├── bfs.cpp
│   ├── dfs.cpp
│   ├── renderer.cpp
│   └── test_algorithms.cpp ← Unit tests (no SFML needed)
└── SFML/                   ← Place SFML here (see Step 1)
```

---

## ⚙️ Setup (Windows)

### Step 1 — Install CMake
Download from https://cmake.org/download/ and add to PATH.

### Step 2 — Install MinGW (C++ compiler)
Download MinGW-w64 from https://www.mingw-w64.org/ and add to PATH.
Verify with: `g++ --version`

### Step 3 — Download SFML
1. Go to https://sfml-dev.org/download.php
2. Download **SFML 2.6.x** → Windows → GCC (MinGW) 64-bit
3. Extract and **rename the folder to `SFML`**
4. Place it inside the project root:
   ```
   DAA project/
   └── SFML/
       ├── include/
       ├── lib/
       └── bin/
   ```

### Step 4 — Download the Map Data
```bat
download_map.bat
```
This downloads the Connaught Place (New Delhi) road network (~2 km²) from OpenStreetMap.
> ℹ️ If you skip this, the app launches in **Demo mode** with an 8×8 grid graph.

### Step 5 — Build
```bat
build.bat
```
The executable is created at `bin\DAA_Pathfinder.exe`.

---

## ▶️ Running

```bat
bin\DAA_Pathfinder.exe           ← Real map mode (needs data\map.osm)
bin\DAA_Pathfinder.exe --demo   ← Demo grid mode (no map needed)
```

### Controls
| Key / Action | Effect |
|---|---|
| **Click** node | Select **source** (green), then **destination** (red) |
| **B** | Run **BFS** and animate |
| **D** | Run **DFS** and animate |
| **+** / **-** | Increase / decrease animation speed |
| **R** | Reset selection |
| **Esc** | Quit |

---

## 🧪 Running Tests (No SFML required)
```bat
bin\test_algorithms.exe
```
Verifies BFS finds the shortest path and DFS finds a valid path across 5 test cases.

---

## 🔬 Algorithm Comparison

| Property | BFS | DFS |
|---|---|---|
| Guarantees shortest? | ✅ Yes (fewest hops) | ❌ No |
| Data structure | Queue | Stack |
| Traversal pattern | Level by level (rings) | Deep dive first (snake) |
| Nodes visited | Fewer (usually) | More (usually) |
| Time complexity | O(V + E) | O(V + E) |

> The visual animation makes this difference very clear! BFS fans out evenly; DFS zigzags deep before backtracking.

---

## 📡 Map Data
Uses the **Overpass API** to download freely available **OpenStreetMap** data.
Only `highway=*` tagged ways (roads) are loaded into the graph.
Nodes = intersections, Edges = road segments with real Haversine distances.
