#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std::chrono;

const int SIZE = 500;

// Fill a matrix with random values
void fillRandomArray(int array[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            array[i][j] = rand() % 100;
}

// Multiply two matrices
void multiplyArrays(const int array1[][SIZE], const int array2[][SIZE], int resultArray[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            resultArray[i][j] = 0;
            for (int k = 0; k < SIZE; ++k)
                resultArray[i][j] += array1[i][k] * array2[k][j];
        }
    }
}

int main()
{
    srand(time(nullptr));

    int array1[SIZE][SIZE];
    int array2[SIZE][SIZE];
    int resultArray[SIZE][SIZE];

    // Fill matrices with random values
    fillRandomArray(array1);
    fillRandomArray(array2);

    auto startTime = high_resolution_clock::now();
    // Perform matrix multiplication
    multiplyArrays(array1, array2, resultArray);
    auto stopTime = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    std::cout << "Multiplication completed in: " << duration.count() << " microseconds" << std::endl;

    // Write result to file
    std::ofstream outputFile("Modified_Results.txt");
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
            outputFile << resultArray[i][j] << "\t";
        outputFile << std::endl;
    }
    outputFile << "Execution time: " << duration.count() << " microseconds";
    outputFile.close();

    return 0;
}
