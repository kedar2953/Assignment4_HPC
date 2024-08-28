#include <omp.h>
#include <stdio.h>
#include <stdint.h>

long long int pfib(int n) {
    if (n < 2) return n;    //Base
    long long int x, y;

    #pragma omp parallel sections
    {
        #pragma omp section
        x = pfib(n - 1);
        
        #pragma omp section
        y = pfib(n - 2);
    }

    //OpenMP runtime ensures that all sections are complete before moving past the parallel region

    return x + y;
}

long long int sequential_fib(int n) {
    if (n < 2) return n;

    long long int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n; 
    long long int result;  
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sequential Execution\n");

    double sstime = omp_get_wtime();  

    result = sequential_fib(n);

    double setime = omp_get_wtime(); 
    double stime = setime - sstime;  
    
    printf("Fibonacci number F(%d) = %lld\n", n, result);
    printf("Time taken (sequential): %f seconds\n", stime);

    printf("Parallel Execution\n");
    double pstime = omp_get_wtime();
    
    result = pfib(n);
    double petime = omp_get_wtime();
    double ptime = petime - pstime;
    
    printf("Fibonacci number F(%d) = %lld\n", n, result);
    printf("Time taken (parallel): %f seconds\n", ptime);

    double speedup = stime / ptime;
    printf("Speed Up: %f\n", speedup);

    return 0;
}