#include <iostream>
#include <chrono>
#include "include/raylib-cpp.hpp"

#define SIZE 256
#define WIDTH 1280
#define HEIGHT 720

enum MODE {
    SELECTION,
    BUBBLE,
    INSERTION
};

void switchMode(
    int (&array)[SIZE],
    int &n,
    int &current,
    int &lowest,
    int &verified,
    MODE &mode,
    bool &paused,
    MODE newMode
    ) {
    std::random_shuffle(std::begin(array) + 1, std::end(array));

    n = 0;
    lowest = 0;
    current = 0;
    verified = 0;

    mode = newMode;

     paused = true;
}

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void populateArray(int (&array)[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }
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

void drawGraph(int (&array)[SIZE], int n, int lowest, int current, int verified, raylib::Window &window) {
    BeginDrawing();

    window.ClearBackground(BLACK);

    for (int i = 0; i < SIZE; i++) {
        Color color = RAYWHITE;

        if (i == lowest || i == current) color = RED;
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

void verify(int (&array)[SIZE], int &verified) {
    if (array[verified] == verified + 1)
        verified++;
}

int main() {
    int array[SIZE];
    populateArray(array);
    std::random_shuffle(std::begin(array) + 1, std::end(array));

    // ----------------------------------------------------------------------------------------------------------------

    int width = WIDTH;
    int height = HEIGHT;

    raylib::Window window(width, height, "raylib-cpp - basic window");

    SetTargetFPS(60);

    // ----------------------------------------------------------------------------------------------------------------

    int n = 0;

    int lowest = 0;
    int current = 0;
    int verified = 0;

    MODE mode = SELECTION;

    bool paused = false;

    while (!window.ShouldClose())
    {
        if (IsKeyReleased(KEY_SPACE))
            paused = !paused;
        if (IsKeyReleased(KEY_ONE))
            switchMode(array, n, current, lowest, verified, mode, paused, SELECTION);
        if (IsKeyReleased(KEY_TWO))
            switchMode(array, n, current, lowest, verified, mode, paused, BUBBLE);
        if (IsKeyReleased(KEY_THREE))
            switchMode(array, n, current, lowest, verified, mode, paused, INSERTION);


        if (n < SIZE) {
            if (!paused) {
                switch (mode) {
                    case SELECTION:
                        selectionSort(array, n, lowest);
                        break;
                    case BUBBLE:
                        bubbleSort(array, n);
                        break;
                    case INSERTION:
                        insertionSort(array, n, current);
                        break;
                    default:
                        selectionSort(array, n, lowest);
                        break;
                }
                n++;
            }
        }
        else {
            lowest = 0;
            current = 0;
            verify(array, verified);
        };
        drawGraph(array, n, lowest, current, verified, window);
    }

    CloseWindow();

    return 0;
}
