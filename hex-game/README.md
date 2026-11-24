# Hex Game with BFS Win Detection

**Source:** [`Hex.cpp`](Hex.cpp)

This is an interactive two-player Hex game implemented in C++. It defines a `HexBoard` class, displays the board in the terminal, validates moves, identifies each cell's six neighbouring positions, and uses breadth-first search (BFS) to test whether a player's stones connect the required opposing board edges.

## Build and run

```bash
g++ -std=c++17 Hex.cpp -o hex-game
./hex-game
```

On Windows, run `hex-game.exe`.

## Walkthrough

- [BFS and `HexBoard` code walkthrough — 11:49](https://youtu.be/eObpp_g4Wsk?t=709)
- [Compilation and board initialization — 15:48](https://youtu.be/eObpp_g4Wsk?t=948)

This recording documents the earlier two-player Hex implementation, which was subsequently extended with a Monte Carlo-based AI move evaluator.
