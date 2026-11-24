# Dijkstra's Shortest Path

**Source:** [`dijkstra.cpp`](dijkstra.cpp)

This program defines a weighted undirected graph using an adjacency matrix, generates edges according to a specified density, and applies Dijkstra's algorithm from a selected start vertex. A `std::priority_queue` configured as a min-priority queue is used to process the next lowest tentative distance.

The program then runs a graph experiment for edge densities `0.2` and `0.4`, accumulating reachable shortest-path distances from vertex `0` across generated graphs.

## Build and run

```bash
g++ -std=c++17 dijkstra.cpp -o dijkstra
./dijkstra
```

On Windows, run `dijkstra.exe`.

## Walkthrough

- [Source walkthrough — 17:39](https://youtu.be/MdPx0j1Wp4U?t=1059)
- [Recorded compile/run — 23:41](https://youtu.be/MdPx0j1Wp4U?t=1421)
- [Hand-drawn algorithm trace — 02:32](https://youtu.be/MdPx0j1Wp4U?t=152)

## Review note

The current source constructs a new `Graph` inside each simulation iteration, and each graph's random engine is default-seeded. As a result, iterations may repeat the same generated graph rather than sample independently. Review and correct the random-engine seeding before interpreting the experiment as 1,000 unique graph trials. The source file is preserved unchanged in this archive.
