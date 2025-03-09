# Thread Scheduling Demonstration

This project demonstrates different thread scheduling policies in a POSIX-compliant operating system. It creates three threads with different functionalities and compares their performance metrics under different scheduling policies.

## Features

- Three concurrent threads with different functionalities:
  - Thread 1: Displays the alphabet between two user-provided characters
  - Thread 2: Prints three statements with delays in between
  - Thread 3: Performs mathematical operations on user-provided integers

- Comparison of scheduling policies:
  - SCHED_OTHER (default)
  - SCHED_RR (Round Robin)

- Comprehensive performance metrics:
  - **Time Metrics**: Wait time, Response time, Turnaround time
  - **CPU Metrics**: CPU time (user/system), CPU utilization, CPU useful work
  - **Memory Metrics**: Memory usage, Peak memory usage

- Data export to CSV for further analysis

## Project Structure

```text
MS_01_Team_m/
├── CMakeLists.txt
├── src/
│   ├── main.c          - Main program entry point
│   ├── threads.h       - Thread function declarations
│   ├── threads.c       - Thread function implementations
│   ├── metrics.h       - Performance metrics declarations
│   ├── metrics.c       - Performance metrics implementations
│   ├── scheduler.h     - Scheduler policy declarations
│   └── scheduler.c     - Scheduler policy implementations
├── README.md
└── docs/
    └── report.md       - Performance analysis report
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
gcc src/main.c src/threads.c src/metrics.c src/scheduler.c -o scheduler -pthread
```

## Running the Program

```bash
./scheduler
```

Note: Running with SCHED_RR scheduling policy may require root privileges on some systems.

## Performance Metrics

The program collects and reports the following performance metrics for each thread:

### Time Metrics

- **Wait Time**: Time between thread creation and the start of execution
- **Response Time**: Time between thread creation and the first response
- **Turnaround Time**: Total time from thread creation to completion

### CPU Metrics

- **CPU Time (User)**: Time spent executing user code
- **CPU Time (System)**: Time spent executing system code
- **CPU Utilization**: Percentage of time spent on CPU
- **CPU Useful Work**: Percentage of CPU time spent on user code vs system code

### Memory Metrics

- **Memory Usage**: Memory consumption in KB
- **Peak Memory Usage**: Maximum memory consumption in KB

## Requirements

- POSIX-compliant operating system (Linux, macOS, etc.)
- GCC or compatible C compiler
- CMake (optional, for build system)
- pthread library

## License

This project is provided for educational purposes.
