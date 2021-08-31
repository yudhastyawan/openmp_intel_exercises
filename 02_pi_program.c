#include <omp.h>
#include <stdio.h>

/**
 * integral (0 -> 1) of 4.0 / (1 + x * x) = pi value
 **/

static long num_steps = 100000;
double step;

#define NUM_THREADS 2
#define PAD 8 // assume 64 byte L1 cache line size

int main() {
    double start_time = omp_get_wtime();

    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];
    step = 1.0 / (double)num_steps;

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;

        for (i = id, sum[id][0]= 0.0; i < num_steps; i = i+nthrds) {
            x = (i+0.5)*step;
            sum[id][0] += 4.0/(1.0 + x*x);
        }
    }

    for (i = 0, pi = 0.0; i < nthreads; i++) pi += sum[i][0] * step;
    // int thread_num = omp_get_num_threads();
    // printf("number of threads: %d\n", thread_num);

    // double pi, sum = 0.0;

    // step = 1.0 / (double)num_steps;

    // #pragma omp parallel
    // for (int i = 0; i < num_steps; i++) {
    //     double x = (i + 0.5) * step; // the center of seqment multiplied by step
    //     sum = sum + 4.0 / (1.0 + x * x);
    // }
    // double wtime = omp_get_wtime();
    // printf("wtime: %g\n", wtime);

    // pi = step * sum;
    double run_time = omp_get_wtime() - start_time;
    printf("pi value by integral: %g in %g sec.\n", pi, run_time);
}