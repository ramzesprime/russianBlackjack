# Game 21 - Multithreaded Simulation

This is finished simulation program, witch simulate game between two players in russian version of popular card game called `balck jack`.

---

## Features

- **Realesed by using C++**
- **Used intel from book -> `anthony williams c++ concurrency in action`**

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