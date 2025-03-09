#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Structure to pass arguments to threads
typedef struct
{
  int thread_id;
  struct timespec start_time;
  struct timespec end_time;
  struct timespec release_time;
  double wait_time;
  double response_time;
  double turnaround_time;
} ThreadData;

// Thread functions
void *alphabet_thread(void *arg);
void *print_thread(void *arg);
void *math_thread(void *arg);

// Helper function to get current time
struct timespec get_current_time();

// Helper function to calculate time difference in milliseconds
double time_diff_ms(struct timespec start, struct timespec end);

#endif // THREADS_H 