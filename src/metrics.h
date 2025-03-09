#ifndef METRICS_H
#define METRICS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

// Structure to store performance metrics
typedef struct {
    // Time metrics
    struct timespec release_time;
    struct timespec start_time;
    struct timespec end_time;
    double wait_time;
    double response_time;
    double turnaround_time;
    
    // CPU metrics
    double cpu_time_user;
    double cpu_time_system;
    double cpu_utilization;
    double cpu_useful_work;
    
    // Memory metrics
    long memory_usage_kb;
    long peak_memory_kb;
} PerformanceMetrics;

// Helper function to get current time
struct timespec get_current_time();

// Helper function to calculate time difference in milliseconds
double time_diff_ms(struct timespec start, struct timespec end);

// Function to initialize performance metrics
void init_performance_metrics(PerformanceMetrics *metrics);

// Function to start measuring performance
void start_performance_measurement(PerformanceMetrics *metrics);

// Function to end measuring performance and calculate metrics
void end_performance_measurement(PerformanceMetrics *metrics);

// Function to get CPU utilization
double get_cpu_utilization();

// Function to get memory usage in KB
long get_memory_usage();

// Function to calculate CPU useful work
double calculate_cpu_useful_work(PerformanceMetrics *metrics);

// Function to print performance metrics
void print_performance_metrics(PerformanceMetrics *metrics, const char *thread_name, const char *scheduler_name);

// Function to export performance metrics to a CSV file
void export_performance_metrics(PerformanceMetrics *metrics, int num_threads, const char *scheduler_name, const char *filename);

#endif // METRICS_H 