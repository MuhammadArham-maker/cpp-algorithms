# Monte Carlo Hex AI

**Source:** [`Monte_Carlo_AI.cpp`](Monte_Carlo_AI.cpp)

This program extends the terminal Hex game with an AI move evaluator based on Monte Carlo random playouts. For each legal candidate move, it creates simulated board states, randomly fills the remaining empty cells, checks the simulated result using BFS connectivity, and estimates the candidate's win rate from the fraction of successful trials. The program selects a move based on those estimated rates.

The implementation includes a configurable trial count (default `1000`) and an interactive human-versus-AI game loop.

## Build and run

```bash
g++ -std=c++17 Monte_Carlo_AI.cpp -o monte-carlo-hex-ai
./monte-carlo-hex-ai
```

On Windows, run `monte-carlo-hex-ai.exe`.

## Walkthrough

- [Monte Carlo rollout concept — 04:50](https://youtu.be/wBlbxEEEU1w?t=290)
- [Source walkthrough — 12:37](https://youtu.be/wBlbxEEEU1w?t=757)
- [Compilation and gameplay demonstration — 17:51](https://youtu.be/wBlbxEEEU1w?t=1071)

The recording includes a source walkthrough and a recorded human-versus-AI match. This is a random-playout evaluator; not Monte Carlo Tree Search (MCTS).
