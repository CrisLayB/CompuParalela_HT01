#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define A 1
#define B 40
#define N 10e6
#define DEFAULT_THREADS 4

double f(double x);
void trapezoides(double a, double b, int n, double* global_sum);

double global_sum = 0.0;

int main(int argc, char* argv[]) 
{
  double a = A, b = B;
  int n = N;

  if(argc > 1) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    // thread_count = strtol(argv[3], NULL, 10);
  }

  trapezoides(a, b, n, &global_sum);

  printf("Con n = %d trapezoides, nuestra aproximacion \n",n);
  printf("de la integral de %f a %f es = %.10f\n", a, b, global_sum);

  return 0;
}

void trapezoides(double a, double b, int n, double* global_sum) 
{
  double integral, h, x, local_sum;
  double local_a, local_b;
  int i, local_n;
  int thread_ID = omp_get_thread_num();
  int thread_count = omp_get_num_threads();

  h = (b-a)/n;

  local_n = n / thread_count;
  local_a = a + thread_ID*local_n * h;
  local_b = local_a + local_n * h;
  local_sum = (f(local_a) + f(local_b)) / 2.0;

  integral = (f(a) + f(b)) / 2.0;

  #pragma omp parallel for reduction(+: integral) num_threads(thread_count)  
  for(i = 1; i <= n-1; i++) 
  {
    x = local_a + i * h;
    local_sum += f(x);
  }
  
  local_sum = local_sum * h;

  #pragma omp critical
  *global_sum += local_sum;
}

double f(double x) 
{
  return x * x;
}
