# C++ Algorithms & Computational Projects

A private personal archive of four C++ implementations completed as part of the **Coding for Everyone: C & C++ Specialization** (2026).

This repository preserves the source files and supporting walkthrough references together. The four programs are independent coursework implementations; they are not one integrated application.

## Projects

| Project | Main ideas | Source |
|---|---|---|
| Dijkstra's shortest path | Weighted graph, adjacency matrix, priority queue, shortest-path distances, random graph experiment | [`dijkstra/dijkstra.cpp`](dijkstra/dijkstra.cpp) |
| Prim's Minimum Spanning Tree | Greedy graph algorithm, priority queue, spanning-tree cost | [`prim-mst/MST.cpp`](prim-mst/MST.cpp) |
| Hex game | Board representation, legal moves, six-neighbour connectivity, BFS win detection | [`hex-game/Hex.cpp`](hex-game/Hex.cpp) |
| Monte Carlo Hex AI | Random playouts, simulated board evaluation, win-rate-based move selection | [`monte-carlo-hex-ai/Monte_Carlo_AI.cpp`](monte-carlo-hex-ai/Monte_Carlo_AI.cpp) |

## Build

Each source file has its own `main()` and should be compiled separately with a C++17-compatible compiler.

```bash
g++ -std=c++17 dijkstra/dijkstra.cpp -o dijkstra

g++ -std=c++17 prim-mst/MST.cpp -o prim-mst

g++ -std=c++17 hex-game/Hex.cpp -o hex-game

g++ -std=c++17 monte-carlo-hex-ai/Monte_Carlo_AI.cpp -o monte-carlo-hex-ai
```

On Windows, append `.exe` to the output names if desired.

## Video walkthroughs

The walkthroughs are personal recordings made while working through the implementations. They are currently set to **Private on YouTube**; the links below are retained for personal reference and may not be viewable by other accounts.

- **Dijkstra:** [source walkthrough — 17:39](https://youtu.be/MdPx0j1Wp4U?t=1059) · [recorded compile/run — 23:41](https://youtu.be/MdPx0j1Wp4U?t=1421)
- **Prim's MST:** [concept drawing — 02:54](https://youtu.be/5f4IYZVPZi8?t=174) · [brief source overview — 08:49](https://youtu.be/5f4IYZVPZi8?t=529). The recorded terminal attempt did not complete successfully because the expected input file was missing; this is retained as an early development record, not a successful demonstration.
- **Hex game:** [BFS and board code walkthrough — 11:49](https://youtu.be/eObpp_g4Wsk?t=709) · [board initialization — 15:48](https://youtu.be/eObpp_g4Wsk?t=948). This is an earlier two-player milestone; the recording's gameplay test is limited.
- **Monte Carlo Hex AI:** [rollout concept — 04:50](https://youtu.be/wBlbxEEEU1w?t=290) · [source walkthrough — 12:37](https://youtu.be/wBlbxEEEU1w?t=757) · [compile and gameplay demonstration — 17:51](https://youtu.be/wBlbxEEEU1w?t=1071).

## Notes

- Source files are preserved as supplied; this archive does not silently rewrite or refactor the original implementations.
- These projects are kept here as a personal coursework record. Do not make this repository public or share assessment solutions unless the course's sharing rules explicitly permit it.
- The Dijkstra source comments describe 1,000 unique random graphs, but the current implementation constructs each `Graph` with a default-seeded random engine. The simulation therefore needs review before its results are described as 1,000 independent graph samples.
- The Monte Carlo Hex implementation uses random playouts to estimate candidate-move win rates. It should not be labelled Monte Carlo Tree Search (MCTS).
