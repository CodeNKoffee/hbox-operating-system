# Thread Scheduling Performance Report

## Introduction

This report documents the performance comparison of different thread scheduling policies in a POSIX-compliant operating system. The experiment involves three threads with different functionalities, and measures their performance under two scheduling policies: SCHED_OTHER (default) and SCHED_RR (Round Robin).

## Experiment Setup

### Hardware Configuration

- CPU: [CPU model]
- RAM: [RAM size]
- Operating System: [OS name and version]

### Thread Descriptions

1. **Thread 1 (Alphabet Thread)**: Displays the alphabet between two user-provided characters.
2. **Thread 2 (Print Thread)**: Prints three statements with 1-second delays in between.
3. **Thread 3 (Math Thread)**: Performs mathematical operations (sum, average, product) on a range of integers.

## Performance Metrics

The following metrics were collected for each thread under both scheduling policies:

### Time Metrics
1. **Wait Time**: Time between thread creation and the start of execution.
2. **Response Time**: Time between thread creation and the first response.
3. **Turnaround Time**: Total time from thread creation to completion.

### CPU Metrics
4. **CPU Time (User)**: Time spent executing user code.
5. **CPU Time (System)**: Time spent executing system code.
6. **CPU Utilization**: Percentage of time spent on CPU.
7. **CPU Useful Work**: Percentage of CPU time spent on user code vs system code.

### Memory Metrics
8. **Memory Usage**: Memory consumption in KB.
9. **Peak Memory Usage**: Maximum memory consumption in KB.

## Results

### SCHED_OTHER (Default Policy)

| Thread | Wait Time (ms) | Response Time (ms) | Turnaround Time (ms) | CPU Time User (ms) | CPU Time System (ms) | CPU Utilization (%) | CPU Useful Work (%) | Memory Usage (KB) | Peak Memory (KB) |
|--------|---------------|-------------------|---------------------|-------------------|---------------------|-------------------|-------------------|-----------------|-----------------|
| 1      |               |                   |                     |                   |                     |                   |                   |                 |                 |
| 2      |               |                   |                     |                   |                     |                   |                   |                 |                 |
| 3      |               |                   |                     |                   |                     |                   |                   |                 |                 |

### SCHED_RR (Round Robin Policy)

| Thread | Wait Time (ms) | Response Time (ms) | Turnaround Time (ms) | CPU Time User (ms) | CPU Time System (ms) | CPU Utilization (%) | CPU Useful Work (%) | Memory Usage (KB) | Peak Memory (KB) |
|--------|---------------|-------------------|---------------------|-------------------|---------------------|-------------------|-------------------|-----------------|-----------------|
| 1      |               |                   |                     |                   |                     |                   |                   |                 |                 |
| 2      |               |                   |                     |                   |                     |                   |                   |                 |                 |
| 3      |               |                   |                     |                   |                     |                   |                   |                 |                 |

## Analysis

[Provide analysis of the results, comparing the performance of the two scheduling policies]

### Time Metrics Analysis
[Analyze wait time, response time, and turnaround time differences between scheduling policies]

### CPU Performance Analysis
[Analyze CPU utilization and useful work differences between scheduling policies]

### Memory Usage Analysis
[Analyze memory consumption differences between scheduling policies]

## Conclusion

[Summarize findings and draw conclusions about the effectiveness of different scheduling policies]

## References

1. [Reference 1]
2. [Reference 2]
3. [Reference 3]

## Appendix: How to Run the Experiment

To run the experiment and generate the performance metrics:

1. Build the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. Run the scheduler program:
   ```bash
   ./scheduler
   ```

3. Follow the prompts to input data for each thread.

4. The program will export the performance metrics to a CSV file named `performance_metrics.csv`.

5. Use the data from the CSV file to complete this report.

## Appendix: Video Documentation

A video demonstration of the experiment is available at [link to video]. The video includes:

1. An overview of the project and its objectives
2. A demonstration of running the experiment
3. An explanation of the results and analysis
4. Conclusions and insights gained from the experiment
