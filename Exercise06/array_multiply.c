#include <stdio.h>
#include <omp.h>

#define N 1000000
#define BLOCK_SIZE 1000

float A[N], B[N], C[N];

int main() {

    for (int i = 0; i < N; i++) {
        A[i] = 2.0f;
        B[i] = 3.0f;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int block = 0; block < N; block += BLOCK_SIZE) {

        int end = block + BLOCK_SIZE;

        if (end > N)
            end = N;

        #pragma omp simd
        for (int i = block; i < end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    double finish = omp_get_wtime();

    printf("Array size: %d\n", N);
    printf("C[0] = %.2f\n", C[0]);
    printf("C[999999] = %.2f\n", C[N - 1]);
    printf("Execution Time: %f seconds\n", finish - start);

    return 0;
}