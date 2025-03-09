#include "threads.h"
#include "metrics.h"

// Thread initialization function
void initialize_thread_data(PerformanceMetrics *metrics, int num_threads)
{
  for (int i = 0; i < num_threads; i++)
  {
    init_performance_metrics(&metrics[i]);
  }
}

// Thread 1: Display alphabet between two characters
void *alphabet_thread(void *arg)
{
  PerformanceMetrics *metrics = (PerformanceMetrics *)arg;

  // Start measuring performance
  start_performance_measurement(metrics);

  char start, end;

  printf("Thread 1 (ID: %p): Enter two alphabetic characters: ",
         (void *)pthread_self());
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

  printf("Thread 1 (ID: %p): Alphabet from %c to %c: ",
         (void *)pthread_self(), start, end);

  for (char c = start; c <= end; c++)
  {
    printf("%c ", c);
  }
  printf("\n");

  // End measuring performance
  end_performance_measurement(metrics);

  return NULL;
}

// Thread 2: Print statements
void *print_thread(void *arg)
{
  PerformanceMetrics *metrics = (PerformanceMetrics *)arg;

  // Start measuring performance
  start_performance_measurement(metrics);

  printf("Thread 2 (ID: %p): This is the first print statement.\n",
         (void *)pthread_self());
  sleep(1); // Simulate some work

  printf("Thread 2 (ID: %p): This is the second print statement.\n",
         (void *)pthread_self());
  sleep(1); // Simulate some work

  printf("Thread 2 (ID: %p): This is the third print statement.\n",
         (void *)pthread_self());

  // End measuring performance
  end_performance_measurement(metrics);

  return NULL;
}

// Thread 3: Calculate sum, average, and product
void *math_thread(void *arg)
{
  PerformanceMetrics *metrics = (PerformanceMetrics *)arg;

  // Start measuring performance
  start_performance_measurement(metrics);

  int num1, num2;

  printf("Thread 3 (ID: %p): Enter two integers: ",
         (void *)pthread_self());
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

  printf("Thread 3 (ID: %p): Results for integers from %d to %d:\n",
         (void *)pthread_self(), num1, num2);
  printf("  Sum: %d\n", sum);
  printf("  Average: %.2f\n", avg);
  printf("  Product: %lld\n", product);

  // End measuring performance
  end_performance_measurement(metrics);

  return NULL;
}