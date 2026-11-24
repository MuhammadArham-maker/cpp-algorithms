# Prim's Minimum Spanning Tree

**Source:** [`MST.cpp`](MST.cpp)

This program reads a weighted graph from standard input, represents it with an adjacency matrix, and applies Prim's greedy algorithm using a min-priority queue to accumulate the total weight of the spanning tree.

## Build and run

```bash
g++ -std=c++17 MST.cpp -o prim-mst
./prim-mst < graph.txt
```

The input format expected by the program is the number of vertices and edges, followed by one weighted edge per line. Check the source's `main()` for the exact input order before preparing `graph.txt`.

## Walkthrough archive

- [Prim's MST concept drawing — 02:54](https://youtu.be/5f4IYZVPZi8?t=174)
- [Brief source overview — 08:49](https://youtu.be/5f4IYZVPZi8?t=529)

The recording is currently Private on YouTube. Its recorded terminal attempt did not complete successfully because the expected input file was missing. This video is preserved as a development record, not presented as a successful live demonstration.

## Review note

The implementation should be checked for disconnected graphs before being relied on as a general MST routine. The current source file is preserved unchanged in this archive.
