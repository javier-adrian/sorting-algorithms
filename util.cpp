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

void populateArray(int (&array)[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }
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
    }

    EndDrawing();
}

void verify(int (&array)[SIZE], int &verified) {
    if (array[verified] == verified + 1)
        verified++;
}
