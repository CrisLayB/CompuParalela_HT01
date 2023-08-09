#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define A 1
#define B 40
#define N 10e6
#define DEFAULT_THREADS 4

double f(double x);
double trapezoides(double a, double b, int n, int thread_count);

int main(int argc, char* argv[]) 
{
  double integral;
  double a = A, b = B;
  int n = N;
  double h;
  int thread_count = DEFAULT_THREADS;

  if(argc > 1) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    thread_count = strtol(argv[3], NULL, 10);
  }

  integral = trapezoides(a, b, n, thread_count);

  printf("Con n = %d trapezoides, nuestra aproximacion \n",n);
  printf("de la integral de %f a %f es = %.10f\n", a,b,integral);

  return 0;
}

double trapezoides(double a, double b, int n, int thread_count) 
{
  double integral, h;
  int k;

  h = (b-a)/n;

  integral = (f(a) + f(b)) / 2.0;

  #pragma omp parallel for reduction(+: integral) num_threads(thread_count)  
  for(k = 1; k <= n-1; k++) 
  {
    integral += f(a + k*h);
  }
  
  integral = integral * h;

  return integral;
}

double f(double x) 
{
  return x * x;
}
