#define SIZE 256

int* swap(int (&array)[SIZE], int value1, int value2) {
    int tmp;
    int lowest = array[value2];

    tmp = array[value1];
    array[value1] = lowest;
    array[value2] = tmp;

    return array;
}

int* selectionSort(int (&array)[SIZE], int n, int &lowest) {
    int lowestValue = array[n];
    int lowest_i = n;
    lowest = n;

    for (int i = n+1; i < SIZE; i++) {
        if (array[i] < lowestValue) {
            lowest = i;
            lowestValue = array[i];
            lowest_i = i;
        }
    }

    swap(array, lowest_i, n);

    return array;
}

int* bubbleSort(int (&array)[SIZE], int n) {
    for (int i = 0; i < SIZE - n - 1; i++) {
        if (array[i] > array[i+1]) {
            swap(array, i, i+1);
        }
    }
    return array;
}

int* insertionSort(int (&array)[SIZE], int n, int &current) {
    for (int i = n; i > 0; i--) {
        if (array[i] < array[i - 1]) {
            current = i;
            swap(array, i, i-1);
        } else
            return array;
    }
    return array;
}