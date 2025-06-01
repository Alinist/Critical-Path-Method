# Critical Path Finder using Topological Sorting (C++)

This project calculates the **Critical Path** of a set of tasks in a project using **topological sorting** and earliest/latest start-finish time analysis.

The Critical Path is the sequence of tasks that determines the **minimum total duration** of a project. Any delay in these tasks will delay the whole project.

## Table of Contents

- [Features](#features)
- [Algorithm Overview](#algorithm-overview)
- [Build & Run](#build--run)
- [Example](#example)
- [Code Structure](#code-structure)
- [Example Test Cases](#example-test-cases)
- [Notes](#notes)
- [Members](#members)

## Features

- Parses task dependencies and durations
- Computes:
    - Earliest Start & Finish Times
    - Latest Start & Finish Times
    - Critical Path(s)
- Displays the total time required to complete the project
- Handles multiple test cases (predefined in code)

## Algorithm Overview

The program uses **Topological Sorting** concepts and **Breadth-First Search (BFS)** to compute:
1. **Earliest Start/Finish Times** by traversing tasks from sources to sinks
2. **Latest Start/Finish Times** by traversing in reverse (from end to start)
3. **Critical Path** by finding tasks where `EarliestStart == LatestStart`

## Build & Run

### Requirements

- C++17 or above
- Any C++ compiler (e.g., `g++`)

### Compilation

```bash
g++ -std=c++17 -o critical_path critical_path.cpp
```

### Run

```bash
./critical_path
```

##  Example

Input is defined directly in the code:

```cpp
vector<Task> tasks = {
    {'A', 6, {}},
    {'B', 4, {'A'}},
    {'C', 4, {'A'}},
    {'D', 7, {'B', 'C'}},
    {'E', 6, {'C'}},
    {'F', 2, {'D', 'E'}},
};
```

### Output

```
Critical Path(s) : 

[1] A B D F 

Total Time: 19
```

## Code Structure

- `Task`: Struct containing task id, duration, and dependencies
- `calculateEarliestStartFinishTimes()`: Computes the earliest times
- `calculateLatestStartFinishTimes()`: Computes the latest times
- `calculateCriticalPath()`: Extracts and prints the critical path
- `main()`: Defines test cases and runs computations

## Example Test Cases

You can test different task configurations by commenting/uncommenting the appropriate blocks inside `main()`.

```cpp
// Test 1: Basic dependency chain
// Test 2: More complex DAG
// Test 3: Multiple starting tasks and longer path
```

## Notes

- This implementation assumes task IDs are unique single characters (e.g., A, B, C, etc.)
- No input file handling; tasks are defined directly in source code
- Aimed for educational purposes and extendable for real-world usage

## Members

| Name        | GitHub Profile                              |
| ----------- | ------------------------------------------- |
| Ali Ashraf Ibrahim Said | https://github.com/Alinist |
| Omar Amgad Ahmad Saaid | https://github.com/OmarAmgad220 |
| Hossam Ahmad Mohamed Tag El Deen | https://github.com/hosahmed |
| Zaid Hany Mohamed Salah El Deen | https://github.com/ElAlbany |
| Ali Amgad Ahmad Saaid   | https://github.com/aliamgad |
| Ahmad Ibrahim Mohamed Fathy | https://github.com/AhmadIbrahim2004 |
