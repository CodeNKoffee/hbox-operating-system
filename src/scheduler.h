#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <pthread.h>
#include <sched.h>
#include "metrics.h"

// Enum for scheduler types
typedef enum {
    SCHED_TYPE_DEFAULT,
    SCHED_TYPE_RR,
    SCHED_TYPE_FIFO
} SchedulerType;

// Structure to hold scheduler configuration
typedef struct {
    SchedulerType type;
    int priority;
    const char *name;
} SchedulerConfig;

// Function to initialize scheduler attributes
void init_scheduler(pthread_attr_t *attr, SchedulerConfig *config, int num_threads);

// Function to set scheduler policy
int set_scheduler_policy(pthread_attr_t *attr, struct sched_param *param, SchedulerType type, int priority);

// Function to get scheduler name
const char* get_scheduler_name(SchedulerType type);

// Function to run experiment with a specific scheduler
void run_experiment(SchedulerConfig *config, PerformanceMetrics *metrics, int num_threads);

#endif // SCHEDULER_H 