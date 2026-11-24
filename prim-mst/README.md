# Prim's Minimum Spanning Tree

**Source:** [`MST.cpp`](MST.cpp)

This program reads a weighted graph from standard input, represents it with an adjacency matrix, and applies Prim's greedy algorithm using a min-priority queue to accumulate the total weight of the spanning tree.

## Build and run

```bash
g++ -std=c++17 MST.cpp -o prim-mst
./prim-mst < graph.txt
```

The input format expected by the program is the number of vertices and edges, followed by one weighted edge per line. Check the source's `main()` for the exact input order before preparing `graph.txt`.

## Walkthrough

- [Prim's MST concept drawing — 02:54](https://youtu.be/5f4IYZVPZi8?t=174)
- [Source overview — 08:49](https://youtu.be/5f4IYZVPZi8?t=529)
- [Successful compilation — 13:08](https://youtu.be/rFx5ZxOR8CM?t=788)
- [Graph input — 13:15](https://youtu.be/rFx5ZxOR8CM?t=795)
- [MST output: 19 — 13:32](https://youtu.be/rFx5ZxOR8CM?t=812)

The later recording demonstrates successful execution using a connected four-vertex, five-edge weighted graph, producing the minimum spanning tree cost of 19.
