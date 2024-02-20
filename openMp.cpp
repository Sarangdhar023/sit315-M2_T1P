#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <omp.h>

using namespace std::chrono;

const int NEW_MATRIX_SIZE = 100;

int new_matrix1[NEW_MATRIX_SIZE][NEW_MATRIX_SIZE];
int new_matrix2[NEW_MATRIX_SIZE][NEW_MATRIX_SIZE];
int new_matrix3[NEW_MATRIX_SIZE][NEW_MATRIX_SIZE];

void fillRandomMatrix(int matrix[][NEW_MATRIX_SIZE]) {
    for (int i = 0; i < NEW_MATRIX_SIZE; ++i) {
        for (int j = 0; j < NEW_MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

int main() {
    srand(time(0));

    fillRandomMatrix(new_matrix1);
    fillRandomMatrix(new_matrix2);

    auto start = high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < NEW_MATRIX_SIZE; ++i) {
        for (int j = 0; j < NEW_MATRIX_SIZE; ++j) {
            new_matrix3[i][j] = 0;
            for (int k = 0; k < NEW_MATRIX_SIZE; ++k) {
                new_matrix3[i][j] += new_matrix1[i][k] * new_matrix2[k][j];
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    printf("Execution time: %d microseconds\n", duration.count());

    std::ofstream outputFile("Modified_OpenMP_Results.txt");
    for (int i = 0; i < NEW_MATRIX_SIZE; ++i) {
        for (int j = 0; j < NEW_MATRIX_SIZE; ++j) {
            outputFile << new_matrix3[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile << "Execution time: " << duration.count() << " microseconds";
    outputFile.close();

    return 0;
}
