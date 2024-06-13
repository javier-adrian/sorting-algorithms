#include <iostream>
#include <chrono>

#define SIZE 10000

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void printArray(int (&array)[SIZE], int min, int max) {
    for (int value: array) {
        if (value == min)
            std::cout << "\033[1;32m" << value << "\033[0m" << ", ";
        else if (value == max)
            std::cout << "\033[1;31m" << value << "\033[0m" << ", ";
        else
            std::cout << value << ", ";
    }

    std::cout << '\b' << '\b';
    std::cout << std::endl;
}

int* swap(int (&array)[SIZE], int value1, int value2) {
    int tmp;
    int lowest = array[value2];

    tmp = array[value1];
    // printArray(array, lowest, tmp);
    array[value1] = lowest;
    array[value2] = tmp;
    // printArray(array, lowest, tmp);

    // std::cout << std::endl;

    return array;
}

int* selectionSort(int (&array)[SIZE]) {
    int tmp, lowest, lowest_i;

    for (int i = 0; i < SIZE - 1; i++) {
        lowest = array[i];
        lowest_i = i;

        for (int j = i+1; j < SIZE - 1; j++) {
            if (array[j] < lowest) {
                lowest = array[j];
                lowest_i = j;
            }
        }

        swap(array, lowest_i, i);
    }

    return array;
}

void populateArray(int (&array)[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }
}

int main() {
    int array[SIZE];
    populateArray(array);
    std::random_shuffle(std::begin(array), std::end(array));

    printArray(array, 0, 0);

    uint64_t time = timeSinceEpochMillisec();
    selectionSort(array);
    uint64_t duration = timeSinceEpochMillisec() - time;

    printArray(array, 0, 0);
    std::cout << duration << std::endl;

    return 0;
}
