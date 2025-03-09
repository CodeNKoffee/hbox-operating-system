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
| 1      | 0.04          | 0.04              | 16527.21            | 0.08              | 0.33                | 0.00              | 20.39             | 1179648         | 1179648         |
| 2      | 0.08          | 0.08              | 2009.79             | 0.03              | 0.13                | 0.01              | 20.62             | 1163264         | 1163264         |
| 3      | 0.08          | 0.08              | 16527.31            | 0.10              | 0.37                | 0.00              | 22.25             | 1179648         | 1179648         |

### SCHED_RR (Round Robin Policy)

| Thread | Wait Time (ms) | Response Time (ms) | Turnaround Time (ms) | CPU Time User (ms) | CPU Time System (ms) | CPU Utilization (%) | CPU Useful Work (%) | Memory Usage (KB) | Peak Memory (KB) |
|--------|---------------|-------------------|---------------------|-------------------|---------------------|-------------------|-------------------|-----------------|-----------------|
| 1      | 0.04          | 0.04              | 0.09                | 0.03              | 0.10                | 238.46            | 20.16             | 1294336         | 1294336         |
| 2      | 0.05          | 0.05              | 2002.24             | 0.08              | 0.26                | 0.02              | 23.82             | 1310720         | 1310720         |
| 3      | 0.10          | 0.10              | 14740.90            | 0.10              | 0.33                | 0.00              | 22.88             | 1310720         | 1310720         |

## Analysis

### Time Metrics Analysis

1. **Wait Time and Response Time**:
   - Both scheduling policies show very low wait and response times (all under 0.10ms), indicating efficient thread creation and initial scheduling.
   - SCHED_OTHER shows slightly better response times for Thread 1 (0.04ms vs 0.04ms), identical for Thread 2, and slightly worse for Thread 3 (0.08ms vs 0.10ms).
   - The differences are minimal, suggesting that both policies handle initial thread scheduling efficiently.

2. **Turnaround Time**:
   - Significant differences are observed in turnaround times between the two policies.
   - Thread 1 shows a dramatic improvement under SCHED_RR (16527.21ms vs 0.09ms), suggesting that Round Robin scheduling prioritized this thread.
   - Thread 2 shows similar turnaround times under both policies (2009.79ms vs 2002.24ms), likely due to its sleep operations which dominate execution time.
   - Thread 3 shows improved performance under SCHED_RR (16527.31ms vs 14740.90ms), but the improvement is less dramatic than for Thread 1.

### CPU Performance Analysis

1. **CPU Time**:
   - Under SCHED_OTHER, Thread 3 (Math Thread) consumed the most CPU time (0.10ms user + 0.37ms system = 0.47ms total), which aligns with its computational nature.
   - Under SCHED_RR, Thread 3 still consumed the most total CPU time (0.43ms), but Thread 2 showed increased CPU usage compared to SCHED_OTHER.
   - All threads show a higher ratio of system time to user time, indicating significant kernel overhead.

2. **CPU Utilization**:
   - Thread 1 under SCHED_RR shows an anomalously high CPU utilization (238.46%), which may indicate a measurement error or a specific behavior of the Round Robin scheduler.
   - Other threads show very low CPU utilization (≤0.02%), suggesting that they spend most of their time waiting for I/O or sleeping.

3. **CPU Useful Work**:
   - All threads show similar CPU useful work percentages (20-24%), indicating that approximately one-fifth of CPU time is spent on user code.
   - Thread 3 shows slightly higher useful work under both policies, consistent with its computational nature.
   - The low percentages overall suggest significant system overhead, possibly due to thread management and I/O operations.

### Memory Usage Analysis

1. **Memory Consumption**:
   - Memory usage is significantly higher under SCHED_RR (1294336-1310720 KB) compared to SCHED_OTHER (1163264-1179648 KB).
   - This suggests that the Round Robin scheduler requires additional memory resources for time-slice management.
   - Thread 2 under SCHED_OTHER shows slightly lower memory usage than the other threads, possibly due to its simpler execution pattern.

2. **Peak Memory**:
   - Peak memory usage equals current memory usage for all threads, indicating stable memory consumption throughout execution.
   - No memory leaks or significant fluctuations in memory usage were observed.

## Conclusion

The comparison of SCHED_OTHER and SCHED_RR scheduling policies reveals several key insights:

1. **Performance Trade-offs**:
   - SCHED_RR significantly improves turnaround time for Thread 1 but at the cost of increased memory consumption.
   - SCHED_OTHER provides more consistent performance across all threads but may lead to longer turnaround times for certain thread types.

2. **Resource Utilization**:
   - Both scheduling policies show low CPU utilization for most threads, suggesting that the workload is not CPU-bound.
   - Memory usage is higher with SCHED_RR, indicating a resource trade-off for improved scheduling.

3. **Thread Characteristics**:
   - Thread 2, with its sleep operations, shows similar performance under both policies, suggesting that I/O-bound or sleeping threads are less affected by scheduling policy changes.
   - Thread 3, with its computational nature, shows more consistent CPU usage across policies.

4. **Practical Implications**:
   - For systems where response time is critical, SCHED_RR may be preferred despite its higher resource consumption.
   - For systems with limited memory resources, SCHED_OTHER provides a more memory-efficient option with acceptable performance for most threads.
   - The choice between scheduling policies should consider the specific characteristics of the workload and the system constraints.

In summary, this experiment demonstrates that thread scheduling policies can significantly impact performance metrics, particularly turnaround time and memory usage. The appropriate choice depends on the specific requirements and constraints of the application and system.

## References

1. Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). Operating System Concepts. Wiley.
2. Love, R. (2013). Linux Kernel Development. Addison-Wesley Professional.
3. Tanenbaum, A. S., & Bos, H. (2014). Modern Operating Systems. Pearson.

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
