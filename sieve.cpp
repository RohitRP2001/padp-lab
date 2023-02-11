#include <iostream>
#include <cstring>
#include <cmath>
#include <omp.h>
using namespace std;

const int N = 10000000;
bool primes[N];

// Cache Unfriendly Sieve of Eratosthenes
void unfriendlySieve() {
    memset(primes, true, sizeof(primes));
    int limit = sqrt(N);

    for (int i = 2; i <= limit; i++) {
        if (primes[i]) {
            for (int j = i * i; j <= N; j += i) {
                primes[j] = false;
            }
        }
    }
}

// Cache Friendly Sieve of Eratosthenes
void friendlySieve() {
    memset(primes, true, sizeof(primes));
    int limit = sqrt(N);

    #pragma omp parallel for
    for (int i = 2; i <= limit; i++) {
        if (primes[i]) {
            int start = i * i;
            int inc = 2 * i;

            for (int j = start; j <= N; j += inc) {
                primes[j] = false;
            }
        }
    }
}

int main() {
    cout << "Cache Unfriendly Sieve of Eratosthenes: " << endl;
    double start = omp_get_wtime();
    unfriendlySieve();
    double end = omp_get_wtime();
    cout << "Time taken: " << end - start << "s" << endl;

    cout << "Cache Friendly Sieve of Eratosthenes: " << endl;
    start = omp_get_wtime();
    friendlySieve();
    end = omp_get_wtime();
    cout << "Time taken: " << end - start << "s" << endl;

    return 0;
}
/*
The unfriendlySieve() function implements the traditional cache unfriendly Sieve of Eratosthenes algorithm. 
The friendlySieve() function implements the cache friendly version of the algorithm. 
The difference between the two lies in the loop structure and the way they access memory.
The cache friendly version uses OpenMP's #pragma omp parallel for directive to parallelize the computation, 
making it faster than the cache unfriendly version.

*/
