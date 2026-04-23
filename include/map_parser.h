#pragma once
// ─────────────────────────────────────────────────────────────────────────────
//  map_parser.h  |  Lightweight OpenStreetMap XML parser
//  Reads .osm files exported from www.openstreetmap.org or Overpass API
// ─────────────────────────────────────────────────────────────────────────────
#include "graph.h"
#include <string>

// Parses an OSM XML file and populates the graph.
// Only way elements tagged highway=* are added (road network only).
// Returns true on success, false if file could not be opened.
bool parseOSM(const std::string& filename, Graph& g);

// Build a small demo graph for testing (10×10 grid, no OSM file needed)
void buildDemoGraph(Graph& g);
