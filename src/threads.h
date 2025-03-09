#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "metrics.h"

// Thread functions
void *alphabet_thread(void *arg);
void *print_thread(void *arg);
void *math_thread(void *arg);

// Thread initialization function
void initialize_thread_data(PerformanceMetrics *metrics, int num_threads);

#endif // THREADS_H 