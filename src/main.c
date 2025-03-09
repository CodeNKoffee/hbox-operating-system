#include "threads.h"

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

int main()
{
  pthread_t threads[3];
  ThreadData thread_data[3];
  pthread_attr_t attr[3];
  struct sched_param param[3];

  // Initialize thread attributes
  for (int i = 0; i < 3; i++)
  {
    pthread_attr_init(&attr[i]);

    // Set thread as joinable
    pthread_attr_setdetachstate(&attr[i], PTHREAD_CREATE_JOINABLE);

    // Initialize thread data
    thread_data[i].thread_id = i + 1;
    thread_data[i].release_time = get_current_time();
  }

  // First run with default scheduling (SCHED_OTHER)
  printf("Running with default scheduling policy (SCHED_OTHER)\n");

  // Create threads
  pthread_create(&threads[0], &attr[0], alphabet_thread, &thread_data[0]);
  pthread_create(&threads[1], &attr[1], print_thread, &thread_data[1]);
  pthread_create(&threads[2], &attr[2], math_thread, &thread_data[2]);

  // Wait for threads to finish
  for (int i = 0; i < 3; i++)
  {
    pthread_join(threads[i], NULL);
  }

  // Display performance metrics
  printf("\n--- Performance Metrics with SCHED_OTHER ---\n");
  for (int i = 0; i < 3; i++)
  {
    printf("Thread %d:\n", thread_data[i].thread_id);
    printf("  Wait Time: %.2f ms\n", thread_data[i].wait_time);
    printf("  Response Time: %.2f ms\n", thread_data[i].response_time);
    printf("  Turnaround Time: %.2f ms\n", thread_data[i].turnaround_time);
    printf("\n");
  }

  // Reset thread data for second run
  for (int i = 0; i < 3; i++)
  {
    thread_data[i].release_time = get_current_time();

    // Set scheduling policy to SCHED_RR (Round Robin)
    pthread_attr_setschedpolicy(&attr[i], SCHED_RR);

    // Set priority (1-99 for real-time policies)
    param[i].sched_priority = 50;
    pthread_attr_setschedparam(&attr[i], &param[i]);

    // Set explicit scheduling attribute
    pthread_attr_setinheritsched(&attr[i], PTHREAD_EXPLICIT_SCHED);
  }

  printf("\n\nRunning with Round-Robin scheduling policy (SCHED_RR)\n");

  // Create threads with RR scheduling
  // Note: This might require root privileges on some systems
  pthread_create(&threads[0], &attr[0], alphabet_thread, &thread_data[0]);
  pthread_create(&threads[1], &attr[1], print_thread, &thread_data[1]);
  pthread_create(&threads[2], &attr[2], math_thread, &thread_data[2]);

  // Wait for threads to finish
  for (int i = 0; i < 3; i++)
  {
    pthread_join(threads[i], NULL);
  }

  // Display performance metrics
  printf("\n--- Performance Metrics with SCHED_RR ---\n");
  for (int i = 0; i < 3; i++)
  {
    printf("Thread %d:\n", thread_data[i].thread_id);
    printf("  Wait Time: %.2f ms\n", thread_data[i].wait_time);
    printf("  Response Time: %.2f ms\n", thread_data[i].response_time);
    printf("  Turnaround Time: %.2f ms\n", thread_data[i].turnaround_time);
    printf("\n");
  }

  // Clean up
  for (int i = 0; i < 3; i++)
  {
    pthread_attr_destroy(&attr[i]);
  }

  return 0;
}

// Thread 1: Display alphabet between two characters
void *alphabet_thread(void *arg)
{
  ThreadData *data = (ThreadData *)arg;
  data->start_time = get_current_time();
  data->response_time = time_diff_ms(data->release_time, data->start_time);
  data->wait_time = data->response_time; // For first execution, wait time equals response time

  char start, end;

  printf("Thread %d (ID: %p): Enter two alphabetic characters: ",
         data->thread_id, (void *)pthread_self());
  scanf(" %c %c", &start, &end);

  // Make sure characters are in the right order
  if (start > end)
  {
    char temp = start;
    start = end;
    end = temp;
  }

  // Convert to lowercase for consistency
  start = tolower(start);
  end = tolower(end);

  printf("Thread %d (ID: %p): Alphabet from %c to %c: ",
         data->thread_id, (void *)pthread_self(), start, end);

  for (char c = start; c <= end; c++)
  {
    printf("%c ", c);
  }
  printf("\n");

  data->end_time = get_current_time();
  data->turnaround_time = time_diff_ms(data->release_time, data->end_time);

  return NULL;
}

// Thread 2: Print statements
void *print_thread(void *arg)
{
  ThreadData *data = (ThreadData *)arg;
  data->start_time = get_current_time();
  data->response_time = time_diff_ms(data->release_time, data->start_time);
  data->wait_time = data->response_time;

  printf("Thread %d (ID: %p): This is the first print statement.\n",
         data->thread_id, (void *)pthread_self());
  sleep(1); // Simulate some work

  printf("Thread %d (ID: %p): This is the second print statement.\n",
         data->thread_id, (void *)pthread_self());
  sleep(1); // Simulate some work

  printf("Thread %d (ID: %p): This is the third print statement.\n",
         data->thread_id, (void *)pthread_self());

  data->end_time = get_current_time();
  data->turnaround_time = time_diff_ms(data->release_time, data->end_time);

  return NULL;
}

// Thread 3: Calculate sum, average, and product
void *math_thread(void *arg)
{
  ThreadData *data = (ThreadData *)arg;
  data->start_time = get_current_time();
  data->response_time = time_diff_ms(data->release_time, data->start_time);
  data->wait_time = data->response_time;

  int num1, num2;

  printf("Thread %d (ID: %p): Enter two integers: ",
         data->thread_id, (void *)pthread_self());
  scanf("%d %d", &num1, &num2);

  // Make sure numbers are in the right order
  if (num1 > num2)
  {
    int temp = num1;
    num1 = num2;
    num2 = temp;
  }

  // Calculate sum
  int sum = 0;
  for (int i = num1; i <= num2; i++)
  {
    sum += i;
  }

  // Calculate average
  double avg = (double)sum / (num2 - num1 + 1);

  // Calculate product
  long long product = 1;
  for (int i = num1; i <= num2; i++)
  {
    product *= i;
  }

  printf("Thread %d (ID: %p): Results for integers from %d to %d:\n",
         data->thread_id, (void *)pthread_self(), num1, num2);
  printf("  Sum: %d\n", sum);
  printf("  Average: %.2f\n", avg);
  printf("  Product: %lld\n", product);

  data->end_time = get_current_time();
  data->turnaround_time = time_diff_ms(data->release_time, data->end_time);

  return NULL;
}