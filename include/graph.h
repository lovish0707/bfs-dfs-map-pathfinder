#pragma once
// ─────────────────────────────────────────────────────────────────────────────
//  graph.h  |  Road-network graph representation
//  Nodes = road intersections  |  Edges = road segments (undirected, weighted)
// ─────────────────────────────────────────────────────────────────────────────
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <limits>
#include <stdexcept>

// ── Data types ────────────────────────────────────────────────────────────────

struct Node {
    long long id   = 0;
    double    lat  = 0.0;
    double    lon  = 0.0;
    float     x    = 0.f;   // screen-space X (set by Renderer)
    float     y    = 0.f;   // screen-space Y (set by Renderer)
    std::string name;
};

struct Edge {
    int    to;              // index into Graph::nodes
    double weight;          // Haversine distance in kilometres
};

struct POI {
    std::string name;
    double lat = 0.0;
    double lon = 0.0;
    float x = 0.f;
    float y = 0.f;
};

// ── Graph ─────────────────────────────────────────────────────────────────────

class Graph {
public:
    std::unordered_map<long long, int> nodeIndex; // OSM id → vector index
    std::vector<Node>                  nodes;
    std::vector<std::vector<Edge>>     adj;
    std::vector<POI>                   pois;

    // Add a node (ignores duplicates)
    void addNode(long long id, double lat, double lon, const std::string& name = "");

    // Add an undirected edge between two OSM node IDs
    // Returns false if either ID is not in the graph
    bool addEdge(long long fromId, long long toId);

    int  size() const { return static_cast<int>(nodes.size()); }
    bool empty() const { return nodes.empty(); }

    // Haversine distance (km) between two node indices
    double distance(int i, int j) const;

    // Haversine formula: great-circle distance between two lat/lon points (km)
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    // Bounding box of all nodes
    void bounds(double& minLat, double& maxLat,
                double& minLon, double& maxLon) const;
};
