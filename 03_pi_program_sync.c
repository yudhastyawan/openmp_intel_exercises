#include <omp.h>
#include <stdio.h>

/**
 * integral (0 -> 1) of 4.0 / (1 + x * x) = pi value
 **/

static long num_steps = 100000;
double step;

#define NUM_THREADS 2

int main() {
    double start_time = omp_get_wtime();

    double pi = 0.0;
    step = 1.0 / (double)num_steps;

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x, sum;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        for (i = id, sum = 0.0; i < num_steps; i = i+nthrds) {
            x = (i+0.5)*step;
            sum += 4.0/(1.0 + x*x);
        }
        sum *= step;
        #pragma omp atomic
        pi += sum;
    }

    double run_time = omp_get_wtime() - start_time;
    printf("pi value by integral: %g in %g sec.\n", pi, run_time);
}