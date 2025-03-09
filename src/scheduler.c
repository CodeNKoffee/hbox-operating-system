#include "scheduler.h"
#include "threads.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables for thread management
static pthread_t *threads;
static pthread_attr_t *thread_attrs;
static struct sched_param *thread_params;
static PerformanceMetrics *thread_metrics;

// Function to initialize scheduler attributes
void init_scheduler(pthread_attr_t *attr, SchedulerConfig *config, int num_threads)
{
  for (int i = 0; i < num_threads; i++)
  {
    pthread_attr_init(&attr[i]);
    pthread_attr_setdetachstate(&attr[i], PTHREAD_CREATE_JOINABLE);
  }

  // Set scheduler policy if not default
  if (config->type != SCHED_TYPE_DEFAULT)
  {
    struct sched_param param[num_threads];
    for (int i = 0; i < num_threads; i++)
    {
      set_scheduler_policy(&attr[i], &param[i], config->type, config->priority);
    }
  }
}

// Function to set scheduler policy
int set_scheduler_policy(pthread_attr_t *attr, struct sched_param *param, SchedulerType type, int priority)
{
  int policy;

  // Map enum to actual scheduler policy
  switch (type)
  {
  case SCHED_TYPE_RR:
    policy = SCHED_RR;
    break;
  case SCHED_TYPE_FIFO:
    policy = SCHED_FIFO;
    break;
  default:
    policy = SCHED_OTHER;
    break;
  }

  // Set scheduling policy
  int result = pthread_attr_setschedpolicy(attr, policy);
  if (result != 0)
  {
    perror("Failed to set scheduling policy");
    return result;
  }

  // Set priority (only relevant for real-time policies)
  if (type != SCHED_TYPE_DEFAULT)
  {
    param->sched_priority = priority;
    result = pthread_attr_setschedparam(attr, param);
    if (result != 0)
    {
      perror("Failed to set scheduling parameters");
      return result;
    }

    // Set explicit scheduling attribute
    result = pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
    if (result != 0)
    {
      perror("Failed to set explicit scheduling");
      return result;
    }
  }

  return 0;
}

// Function to get scheduler name
const char *get_scheduler_name(SchedulerType type)
{
  switch (type)
  {
  case SCHED_TYPE_RR:
    return "SCHED_RR";
  case SCHED_TYPE_FIFO:
    return "SCHED_FIFO";
  case SCHED_TYPE_DEFAULT:
  default:
    return "SCHED_OTHER";
  }
}

// Thread creation function
int create_threads(pthread_t *threads, pthread_attr_t *attr, PerformanceMetrics *metrics, int num_threads)
{
  // Store global references
  thread_metrics = metrics;

  // Create threads
  int result = pthread_create(&threads[0], &attr[0], alphabet_thread, &metrics[0]);
  if (result != 0)
  {
    perror("Failed to create alphabet thread");
    return result;
  }

  result = pthread_create(&threads[1], &attr[1], print_thread, &metrics[1]);
  if (result != 0)
  {
    perror("Failed to create print thread");
    return result;
  }

  result = pthread_create(&threads[2], &attr[2], math_thread, &metrics[2]);
  if (result != 0)
  {
    perror("Failed to create math thread");
    return result;
  }

  return 0;
}

// Thread joining function
void join_threads(pthread_t *threads, int num_threads)
{
  for (int i = 0; i < num_threads; i++)
  {
    pthread_join(threads[i], NULL);
  }
}

// Function to run experiment with a specific scheduler
void run_experiment(SchedulerConfig *config, PerformanceMetrics *metrics, int num_threads)
{
  // Allocate memory for thread management
  threads = malloc(num_threads * sizeof(pthread_t));
  thread_attrs = malloc(num_threads * sizeof(pthread_attr_t));
  thread_params = malloc(num_threads * sizeof(struct sched_param));

  if (!threads || !thread_attrs || !thread_params)
  {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  printf("\n\nRunning with %s scheduling policy\n", config->name);

  // Initialize scheduler
  init_scheduler(thread_attrs, config, num_threads);

  // Initialize metrics
  for (int i = 0; i < num_threads; i++)
  {
    init_performance_metrics(&metrics[i]);
  }

  // Create threads
  if (create_threads(threads, thread_attrs, metrics, num_threads) != 0)
  {
    fprintf(stderr, "Failed to create threads\n");
    exit(EXIT_FAILURE);
  }

  // Wait for threads to finish
  join_threads(threads, num_threads);

  // Display performance metrics
  printf("\n--- Performance Metrics with %s ---\n", config->name);
  for (int i = 0; i < num_threads; i++)
  {
    char thread_name[20];
    sprintf(thread_name, "Thread %d", i + 1);
    print_performance_metrics(&metrics[i], thread_name, config->name);
  }

  // Export metrics to CSV
  char filename[100];
  sprintf(filename, "performance_metrics.csv");
  export_performance_metrics(metrics, num_threads, config->name, filename);

  // Clean up
  for (int i = 0; i < num_threads; i++)
  {
    pthread_attr_destroy(&thread_attrs[i]);
  }

  free(threads);
  free(thread_attrs);
  free(thread_params);
}