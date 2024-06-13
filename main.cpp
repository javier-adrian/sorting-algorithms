#include <iostream>
#include <chrono>
#include "include/raylib-cpp.hpp"

#define SIZE 256
#define WIDTH 1280
#define HEIGHT 720

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void drawGraph(int (&array)[SIZE], int n, int lowest, int verified, raylib::Window &window) {
    BeginDrawing();

    window.ClearBackground(BLACK);

    for (int i = 0; i < SIZE; i++) {
        Color color = RAYWHITE;

        if (i == lowest) color = RED;
        if (i == n || i < verified) color = GREEN;

        int barHeight = (HEIGHT) * array[i] / SIZE;
        int barWidth = WIDTH / SIZE;

        int barPosX = (barWidth) * i + (WIDTH - barWidth * SIZE) / 2; // last two terms center the graph
        int barPosY = HEIGHT - barHeight;

        DrawRectangle(barPosX, barPosY, barWidth - 1, barHeight, color);
        window.DrawFPS();
    }

    EndDrawing();
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

int* selectionSort(int (&array)[SIZE], int n, int &lowest) {
    int tmp;

    int lowestValue = array[n];
    int lowest_i = n;

    for (int j = n+1; j < SIZE; j++) {
        if (array[j] < lowestValue) {
            lowest = j;
            lowestValue = array[j];
            lowest_i = j;
        }
    }

    swap(array, lowest_i, n);

    return array;
}

void verify(int (&array)[SIZE], int &verified) {
    if (array[verified] == verified + 1)
        verified++;
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

    // ----------------------------------------------------------------------------------------------------------------

    int width = WIDTH;
    int height = HEIGHT;

    raylib::Window window(width, height, "raylib-cpp - basic window");

    SetTargetFPS(60);

    // ----------------------------------------------------------------------------------------------------------------

    int n = 0;

    int lowest = 0;
    int verified = 0;

    while (!window.ShouldClose())
    {
        if (n < SIZE) {
            selectionSort(array, n, lowest);
            n++;
        }
        else {
            lowest = SIZE;
            verify(array, verified);
        };
        drawGraph(array, n, lowest, verified, window);
    }

    CloseWindow();

    // uint64_t time = timeSinceEpochMillisec();
    // selectionSort(array);
    // uint64_t duration = timeSinceEpochMillisec() - time;

    return 0;
}
