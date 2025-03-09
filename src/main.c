#include "threads.h"
#include "metrics.h"
#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3
#define NUM_SCHEDULERS 2

int main()
{
  // Define scheduler configurations
  SchedulerConfig schedulers[NUM_SCHEDULERS] = {
      {SCHED_TYPE_DEFAULT, 0, "SCHED_OTHER (Default)"},
      {SCHED_TYPE_RR, 50, "SCHED_RR (Round Robin)"}};

  // Allocate memory for performance metrics
  PerformanceMetrics *metrics = malloc(NUM_THREADS * sizeof(PerformanceMetrics));
  if (!metrics)
  {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }

  printf("Thread Scheduling Demonstration\n");
  printf("===============================\n");
  printf("This program demonstrates different thread scheduling policies.\n");
  printf("It creates three threads with different functionalities and compares\n");
  printf("their performance metrics under different scheduling policies.\n\n");

  // Run experiments with different schedulers
  for (int i = 0; i < NUM_SCHEDULERS; i++)
  {
    run_experiment(&schedulers[i], metrics, NUM_THREADS);
  }

  // Generate report
  printf("\nPerformance metrics have been exported to performance_metrics.csv\n");
  printf("You can use this data to complete the report in docs/report.md\n");

  // Clean up
  free(metrics);

  return EXIT_SUCCESS;
}