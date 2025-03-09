# Thread Scheduling Demonstration

This project demonstrates different thread scheduling policies in a POSIX-compliant operating system. It creates three threads with different functionalities and compares their performance metrics under different scheduling policies.

## Features

- Three concurrent threads with different functionalities:
  - Thread 1: Displays the alphabet between two user-provided characters
  - Thread 2: Prints three statements with delays in between
  - Thread 3: Performs mathematical operations on user-provided integers

- Comparison of two scheduling policies:
  - SCHED_OTHER (default)
  - SCHED_RR (Round Robin)

- Performance metrics for each thread:
  - Wait time
  - Response time
  - Turnaround time

## Project Structure

```
MS_01_Team_m/
├── CMakeLists.txt
├── src/
│   ├── main.c
│   └── threads.h
├── README.md
└── docs/
    └── report.md
```

## Building the Project

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
```

### Using GCC directly

```bash
gcc src/main.c -o scheduler -pthread
```

## Running the Program

```bash
./scheduler
```

Note: Running with SCHED_RR scheduling policy may require root privileges on some systems.

## Requirements

- POSIX-compliant operating system (Linux, macOS, etc.)
- GCC or compatible C compiler
- CMake (optional, for build system)
- pthread library

## License

This project is provided for educational purposes.
