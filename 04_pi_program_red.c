#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;

int main() {
    double start_time, run_time;
    start_time = omp_get_wtime();
    // omp_sched_t sched_id;

    double pi, sum = 0.0;

    step = 1.0/ (double) num_steps;

    #pragma omp parallel
    {
        int i;
        double x;
        #pragma omp for reduction(+:sum) schedule(auto)
        for (i = 0; i < num_steps; i++) {
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0 + x*x);
        }
    }
    pi = step * sum;

    run_time = omp_get_wtime() - start_time;
    printf("pi: %g in %g sec.\n", pi, run_time);
}