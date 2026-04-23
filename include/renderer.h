#pragma once
// ─────────────────────────────────────────────────────────────────────────────
//  renderer.h  |  SFML-based interactive visualizer for BFS & DFS
// ─────────────────────────────────────────────────────────────────────────────
#include "graph.h"
#include "pathfinding.h"
#include <SFML/Graphics.hpp>
#include <string>

// Application states (simple state machine)
enum class AppState {
    IDLE,             // Waiting for source selection
    SOURCE_SELECTED,  // Source chosen, waiting for destination
    READY,            // Both selected, press B or D to run
    ANIMATING,        // Algorithm running, animation playing
    DONE              // Animation complete, showing result
};

class Renderer {
public:
    Renderer(Graph& graph, int width, int height);
    void run();  // Main event loop – blocks until window is closed

private:
    // ── References ────────────────────────────────────────────────────────────
    Graph& g;
    int    winW, winH;

    // ── State ─────────────────────────────────────────────────────────────────
    AppState  state  = AppState::IDLE;
    int       srcIdx = -1;   // selected source node index
    int       dstIdx = -1;   // selected destination node index
    PathResult lastResult;
    bool      isBFS  = true; // true = BFS last run, false = DFS

    // ── Place names (resolved for source and destination) ─────────────────────
    std::string srcName;     // resolved name for the source node
    std::string dstName;     // resolved name for the destination node

    // ── Animation ─────────────────────────────────────────────────────────────
    int animStep  = 0;   // how many visited nodes revealed so far
    int animSpeed = 3;   // visited nodes to reveal per frame tick
    sf::Clock animClock;

    // ── Camera (zoom & pan) ───────────────────────────────────────────────────
    sf::View   mapView;          // the zoomable/pannable view for the map
    float      zoomLevel = 1.f;  // current zoom (1=fit, <1=zoomed in)
    bool       isPanning = false;
    sf::Vector2i lastMousePos;   // last mouse position for pan drag

    // ── Space+Drag panning ────────────────────────────────────────────────────
    bool       spaceHeld       = false;
    bool       spaceWasDragging = false;

    // ── Fullscreen toggle ─────────────────────────────────────────────────────
    bool       isFullscreen      = false;
    bool       fullscreenToggled = false;

    // ── Font (class member – survives window recreation on fullscreen toggle) ─
    sf::Font   font;
    bool       fontOK = false;

    // ── Search overlay ────────────────────────────────────────────────────────
    bool        isSearching = false;
    bool        ignoreNextText = false;
    std::string searchQuery;
    std::vector<int> searchResults; // indices into g.pois
    int         searchSelectedIndex = 0;

    // ── Pre-built geometry (for fast rendering) ───────────────────────────────
    sf::VertexArray edgeVA;      // all road edges (grey lines)

    // ── Helpers ───────────────────────────────────────────────────────────────
    void projectNodes();
    void buildEdgeArray();
    int  findNearestNode(float mx, float my, bool enforceThreshold = true) const;
    void startAlgorithm(bool useBFS);
    void update();
    void render(sf::RenderWindow& win);
    void drawHUD(sf::RenderWindow& win);
    void drawWorldLabels(sf::RenderWindow& win);
    void drawNode(sf::RenderWindow& win, int idx, sf::Color col, float r);
    void drawNodeHighlight(sf::RenderWindow& win, int idx, sf::Color col, float r);
    void handleEvents(sf::RenderWindow& win);
    void handleClick(sf::RenderWindow& win, float mx, float my);
    void handleKey(sf::Keyboard::Key key);
    void updateSearchResults();

    // Resolve a human-readable name for the given node index
    // Checks: node.name → nearest POI within 300 m → "Unnamed road node"
    std::string resolveNodeName(int nodeIdx) const;

    // Convert window pixel coords → map world coords (respects zoom/pan)
    sf::Vector2f windowToWorld(sf::RenderWindow& win, int px, int py) const;

    // ── Colour palette ────────────────────────────────────────────────────────
    static constexpr float NODE_RADIUS = 4.f;
    static sf::Color colBG()       { return sf::Color(15,  15,  26 ); }
    static sf::Color colEdge()     { return sf::Color(50,  55,  80 ); }
    static sf::Color colNode()     { return sf::Color(80,  85, 110 ); }
    static sf::Color colSrc()      { return sf::Color( 0, 255, 127 ); }
    static sf::Color colDst()      { return sf::Color(255,  68,  68 ); }
    static sf::Color colVisitBFS() { return sf::Color(255, 165,   0, 200); }
    static sf::Color colVisitDFS() { return sf::Color(155,  89, 182, 200); }
    static sf::Color colPathBFS()  { return sf::Color(  0, 229, 255 ); }
    static sf::Color colPathDFS()  { return sf::Color(224,  64, 251 ); }
};
