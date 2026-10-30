#include <stdio.h>
#include <omp.h>

int fib(int n) {
    if (n < 2)
        return n;

    int i, j;

    #pragma omp task shared(i) if(n > 10)
    i = fib(n - 1);

    #pragma omp task shared(j) if(n > 10)
    j = fib(n - 2);

    #pragma omp taskwait

    return i + j;
}

int main() {
    int n = 10;
    int result = 0;

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    printf("Fibonacci(%d) = %d\n", n, result);

    return 0;
}