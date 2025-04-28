# Game 21 - Multithreaded Simulation

This project is a multithreaded implementation of the popular card game "21". The game simulates two players attempting to reach a total score of 21 or as close as possible without exceeding it. The entire game logic is implemented using C++ and demonstrates the use of threads, synchronization primitives, and file I/O.

---

## Features

- **Multithreaded Execution**:
  - First thread generates random numbers (simulating card draws).
  - Second and third threads represent two players competing to reach 21.
  - Fourth thread logs the results of each game to a file.

- **Thread Synchronization**:
  - Implements `std::mutex` and `std::condition_variable` for thread-safe operations.
  
- **Customizable Gameplay**:
  - Simulates 10,000 games by default.
  - Results are written to a file (`results.txt`) for later review.

- **Game Rules**:
  - The player who exactly hits 21 or gets closest to it without exceeding wins.
  - If both players exceed 21, the round results in a draw.