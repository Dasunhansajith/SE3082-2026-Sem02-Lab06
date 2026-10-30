#include <stdio.h>
#include <omp.h>

#define N 1000
#define MAX_ITER 1000

int main() {

    for (int threads = 1; threads <= 4; threads++) {

        omp_set_num_threads(threads);

        long long inside = 0;

        double start = omp_get_wtime();

        #pragma omp parallel for reduction(+:inside)
        for (int i = 0; i < N; i++) {

            for (int j = 0; j < N; j++) {

                double x = -2.0 + 3.0 * i / N;
                double y = -1.5 + 3.0 * j / N;

                double zr = 0.0;
                double zi = 0.0;

                int iteration = 0;

                while (zr * zr + zi * zi <= 4.0 &&
                       iteration < MAX_ITER) {

                    double temp = zr * zr - zi * zi + x;

                    zi = 2.0 * zr * zi + y;
                    zr = temp;

                    iteration++;
                }

                if (iteration == MAX_ITER) {
                    inside++;
                }
            }
        }

        double end = omp_get_wtime();

        double area = 9.0 * inside / (N * N);

        printf("Threads: %d | Area: %.6f | Time: %.6f seconds\n",
               threads, area, end - start);
    }

    return 0;
}