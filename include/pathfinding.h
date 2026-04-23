#pragma once
// ─────────────────────────────────────────────────────────────────────────────
//  pathfinding.h  |  Common result type + BFS and DFS declarations
// ─────────────────────────────────────────────────────────────────────────────
#include "graph.h"
#include <vector>

// Result returned by both BFS and DFS
struct PathResult {
    bool              found       = false;
    double            totalDist   = 0.0;  // km along final path
    int               nodesVisited = 0;   // total nodes explored
    std::vector<int>  path;               // node indices: src → ... → dst
    std::vector<int>  visitOrder;         // all nodes in exploration order (for animation)
};

// BFS: guarantees shortest path (fewest hops)
PathResult bfs(const Graph& g, int src, int dst);

// DFS: guarantees a valid path (not necessarily shortest)
PathResult dfs(const Graph& g, int src, int dst);

// Shared utility: compute total distance along a path
double pathDistance(const Graph& g, const std::vector<int>& path);
