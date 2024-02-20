#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <pthread.h>

using namespace std::chrono;

const int SIZE = 500;
#define MAX_THREADS 16

int array1[SIZE][SIZE];
int array2[SIZE][SIZE];
int resultArray[SIZE][SIZE];
int threadCounter = 0;
int partitionSize = SIZE / MAX_THREADS;

void fillRandomArray(int array[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            array[i][j] = rand() % 100;
        }
    }
}

void *multiplyArrays(void *args) {
    int threadID = threadCounter++;

    for (int i = threadID * partitionSize; i < (threadID + 1) * partitionSize; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            resultArray[i][j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                resultArray[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    srand(time(0));

    fillRandomArray(array1);
    fillRandomArray(array2);

    auto start = high_resolution_clock::now();

    pthread_t threadArray[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&threadArray[i], NULL, &multiplyArrays, NULL);
    }

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threadArray[i], NULL);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    printf("Execution time: %d microseconds", duration.count());

    std::ofstream outputFile("Modified_PThread_Results.txt");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            outputFile << resultArray[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile << "Execution time: " << duration.count() << " microseconds";
    outputFile.close();

    return 0;
}
