# C++ Algorithms & Computational Projects

This repository contains four standalone C++ implementations exploring graph algorithms and computational game problems. Developed through hands-on C++ coursework and practice in 2026, these programs demonstrate different approaches to graph traversal, shortest-path computation, minimum spanning trees and simulation-based game AI.

## Projects

| Project | What it covers | Source |
|---|---|---|
| Dijkstra's shortest path | Weighted undirected graphs, adjacency matrices, priority queues and a graph-density experiment | [`dijkstra/dijkstra.cpp`](dijkstra/dijkstra.cpp) |
| Prim's Minimum Spanning Tree | Greedy graph algorithms, priority queues and spanning-tree cost | [`prim-mst/MST.cpp`](prim-mst/MST.cpp) |
| Hex game | Terminal board representation, legal moves, six-neighbour connectivity and BFS win detection | [`hex-game/Hex.cpp`](hex-game/Hex.cpp) |
| Monte Carlo Hex AI | Random playouts, simulated board evaluation and win-rate-based move selection | [`monte-carlo-hex-ai/Monte_Carlo_AI.cpp`](monte-carlo-hex-ai/Monte_Carlo_AI.cpp) |

## Build

Each source file has its own `main()` function. Compile one program at a time with a C++17-compatible compiler.

```bash
g++ -std=c++17 dijkstra/dijkstra.cpp -o dijkstra
g++ -std=c++17 prim-mst/MST.cpp -o prim-mst
g++ -std=c++17 hex-game/Hex.cpp -o hex-game
g++ -std=c++17 monte-carlo-hex-ai/Monte_Carlo_AI.cpp -o monte-carlo-hex-ai
```

On Windows, the generated executable can be run with its `.exe` extension. Prim's MST program reads graph data from standard input; see its folder README and `main()` for the expected input format.

## Video walkthroughs

The recordings document the implementation process, code walkthroughs and selected execution demonstrations.

- **Dijkstra:** [Source walkthrough — 17:39](https://youtu.be/MdPx0j1Wp4U?t=1059) · [Compile and run — 23:41](https://youtu.be/MdPx0j1Wp4U?t=1421)
- **Prim's MST:** [Concept drawing — 02:54](https://youtu.be/5f4IYZVPZi8?t=174) · [Source overview — 08:49](https://youtu.be/5f4IYZVPZi8?t=529). The recorded terminal attempt is incomplete and is not presented as a successful run.
- **Hex game:** [BFS and board code walkthrough — 11:49](https://youtu.be/eObpp_g4Wsk?t=709) · [Board initialization — 15:48](https://youtu.be/eObpp_g4Wsk?t=948). This recording covers the earlier two-player version, before the AI extension.
- **Monte Carlo Hex AI:** [Random-playout concept — 04:50](https://youtu.be/wBlbxEEEU1w?t=290) · [Source walkthrough — 12:37](https://youtu.be/wBlbxEEEU1w?t=757) · [Compile and gameplay demonstration — 17:51](https://youtu.be/wBlbxEEEU1w?t=1071)

## Implementation notes

- The four programs are independent implementations rather than components of one integrated application.
- The Dijkstra experiment currently constructs each graph with a default-seeded random engine. Repeated trials may therefore reuse the same generated graph; the random-engine setup needs revision before the averages can be interpreted as independent samples.
- The Prim implementation assumes a connected input graph and does not currently report that an MST is unavailable when the graph is disconnected.
- The Hex AI uses Monte Carlo random playouts to estimate candidate-move win rates. It is a random-playout evaluator, not Monte Carlo Tree Search (MCTS).
