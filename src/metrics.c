#include "metrics.h"

// Helper function to get current time
struct timespec get_current_time()
{
  struct timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  return time;
}

// Helper function to calculate time difference in milliseconds
double time_diff_ms(struct timespec start, struct timespec end)
{
  return (end.tv_sec - start.tv_sec) * 1000.0 +
        (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

// Function to initialize performance metrics
void init_performance_metrics(PerformanceMetrics *metrics)
{
  metrics->release_time = get_current_time();
  metrics->wait_time = 0.0;
  metrics->response_time = 0.0;
  metrics->turnaround_time = 0.0;
  metrics->cpu_time_user = 0.0;
  metrics->cpu_time_system = 0.0;
  metrics->cpu_utilization = 0.0;
  metrics->cpu_useful_work = 0.0;
  metrics->memory_usage_kb = 0;
  metrics->peak_memory_kb = 0;
}

// Function to start measuring performance
void start_performance_measurement(PerformanceMetrics *metrics)
{
  struct rusage usage;

  // Get current time
  metrics->start_time = get_current_time();

  // Calculate response time
  metrics->response_time = time_diff_ms(metrics->release_time, metrics->start_time);

  // For first execution, wait time equals response time
  metrics->wait_time = metrics->response_time;

  // Get initial CPU usage
  getrusage(RUSAGE_SELF, &usage);
  metrics->cpu_time_user = usage.ru_utime.tv_sec * 1000.0 + usage.ru_utime.tv_usec / 1000.0;
  metrics->cpu_time_system = usage.ru_stime.tv_sec * 1000.0 + usage.ru_stime.tv_usec / 1000.0;

  // Get initial memory usage
  metrics->memory_usage_kb = usage.ru_maxrss;
  metrics->peak_memory_kb = usage.ru_maxrss;
}

// Function to end measuring performance and calculate metrics
void end_performance_measurement(PerformanceMetrics *metrics)
{
  struct rusage usage;

  // Get end time
  metrics->end_time = get_current_time();

  // Calculate turnaround time
  metrics->turnaround_time = time_diff_ms(metrics->release_time, metrics->end_time);

  // Get final CPU usage
  getrusage(RUSAGE_SELF, &usage);
  double end_cpu_time_user = usage.ru_utime.tv_sec * 1000.0 + usage.ru_utime.tv_usec / 1000.0;
  double end_cpu_time_system = usage.ru_stime.tv_sec * 1000.0 + usage.ru_stime.tv_usec / 1000.0;

  // Calculate CPU time used
  double cpu_time_user_used = end_cpu_time_user - metrics->cpu_time_user;
  double cpu_time_system_used = end_cpu_time_system - metrics->cpu_time_system;

  // Update CPU metrics
  metrics->cpu_time_user = cpu_time_user_used;
  metrics->cpu_time_system = cpu_time_system_used;

  // Calculate CPU utilization (percentage of time spent on CPU)
  double total_time = time_diff_ms(metrics->start_time, metrics->end_time);
  if (total_time > 0)
  {
    metrics->cpu_utilization = ((cpu_time_user_used + cpu_time_system_used) / total_time) * 100.0;
  }

  // Calculate CPU useful work (percentage of CPU time spent on user code vs system code)
  metrics->cpu_useful_work = calculate_cpu_useful_work(metrics);

  // Get final memory usage
  long current_memory = usage.ru_maxrss;
  metrics->memory_usage_kb = current_memory;

  // Update peak memory if current is higher
  if (current_memory > metrics->peak_memory_kb)
  {
    metrics->peak_memory_kb = current_memory;
  }
}

// Function to get CPU utilization
double get_cpu_utilization()
{
  // This is a simplified version - for more accurate measurements,
  // you would need to sample CPU usage over time
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);

  double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1000000.0;
  double system_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1000000.0;

  return user_time + system_time;
}

// Function to get memory usage in KB
long get_memory_usage()
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  return usage.ru_maxrss;
}

// Function to calculate CPU useful work
double calculate_cpu_useful_work(PerformanceMetrics *metrics)
{
  double total_cpu_time = metrics->cpu_time_user + metrics->cpu_time_system;

  if (total_cpu_time > 0)
  {
    // Useful work is the percentage of CPU time spent in user code
    return (metrics->cpu_time_user / total_cpu_time) * 100.0;
  }

  return 0.0;
}

// Function to print performance metrics
void print_performance_metrics(PerformanceMetrics *metrics, const char *thread_name, const char *scheduler_name)
{
  printf("\n--- Performance Metrics for %s with %s ---\n", thread_name, scheduler_name);
  printf("  Wait Time: %.2f ms\n", metrics->wait_time);
  printf("  Response Time: %.2f ms\n", metrics->response_time);
  printf("  Turnaround Time: %.2f ms\n", metrics->turnaround_time);
  printf("  CPU Time (User): %.2f ms\n", metrics->cpu_time_user);
  printf("  CPU Time (System): %.2f ms\n", metrics->cpu_time_system);
  printf("  CPU Utilization: %.2f%%\n", metrics->cpu_utilization);
  printf("  CPU Useful Work: %.2f%%\n", metrics->cpu_useful_work);
  printf("  Memory Usage: %ld KB\n", metrics->memory_usage_kb);
  printf("  Peak Memory Usage: %ld KB\n", metrics->peak_memory_kb);
  printf("\n");
}

// Function to export performance metrics to a CSV file
void export_performance_metrics(PerformanceMetrics *metrics, int num_threads, const char *scheduler_name, const char *filename)
{
  FILE *file;
  int file_exists = access(filename, F_OK) != -1;

  file = fopen(filename, "a");
  if (file == NULL)
  {
    perror("Error opening file");
    return;
  }

  // Write header if file is new
  if (!file_exists)
  {
    fprintf(file, "Scheduler,Thread,Wait Time (ms),Response Time (ms),Turnaround Time (ms),CPU Time User (ms),CPU Time System (ms),CPU Utilization (%%),CPU Useful Work (%%),Memory Usage (KB),Peak Memory (KB)\n");
  }

  // Write data for each thread
  for (int i = 0; i < num_threads; i++)
  {
    fprintf(file, "%s,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%ld,%ld\n",
            scheduler_name,
            i + 1,
            metrics[i].wait_time,
            metrics[i].response_time,
            metrics[i].turnaround_time,
            metrics[i].cpu_time_user,
            metrics[i].cpu_time_system,
            metrics[i].cpu_utilization,
            metrics[i].cpu_useful_work,
            metrics[i].memory_usage_kb,
            metrics[i].peak_memory_kb);
  }

  fclose(file);
  printf("Performance metrics exported to %s\n", filename);
}