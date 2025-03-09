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

1. **Wait Time**: Time between thread creation and the start of execution.
2. **Response Time**: Time between thread creation and the first response.
3. **Turnaround Time**: Total time from thread creation to completion.

## Results

### SCHED_OTHER (Default Policy)

| Thread | Wait Time (ms) | Response Time (ms) | Turnaround Time (ms) |
|--------|---------------|-------------------|---------------------|
| 1      |               |                   |                     |
| 2      |               |                   |                     |
| 3      |               |                   |                     |

### SCHED_RR (Round Robin Policy)

| Thread | Wait Time (ms) | Response Time (ms) | Turnaround Time (ms) |
|--------|---------------|-------------------|---------------------|
| 1      |               |                   |                     |
| 2      |               |                   |                     |
| 3      |               |                   |                     |

## Analysis

[Provide analysis of the results, comparing the performance of the two scheduling policies]

## Conclusion

[Summarize findings and draw conclusions about the effectiveness of different scheduling policies]

## References

1. [Reference 1]
2. [Reference 2]
3. [Reference 3]
