#include <iostream>
#include <chrono>
#include <omp.h>

int main() {
    int size;
    std::cout << "Enter the size of the matrix: ";
    std::cin >> size;

    // Allocate memory for the matrices
    float *A = new float[size * size];
    float *B = new float[size * size];
    float *C = new float[size * size];

    // Initialize the matrices with some values
    for (int i = 0; i < size * size; ++i) {
        A[i] = i + 1;
        B[i] = i + 1;
    }

    // Get the start time of the calculation
    auto start = std::chrono::high_resolution_clock::now();

    // Perform matrix multiplication in parallel using OpenMP
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            float sum = 0;
            for (int k = 0; k < size; ++k) {
                sum += A[i * size + k] * B[k * size + j];
            }
            C[i * size + j] = sum;
        }
    }

    // Get the end time of the calculation
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print the time taken to perform the calculation
    std::cout << "Time taken: " << duration.count() << "ms" << std::endl;

    // Deallocate the memory
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
