#include "algorithms.cpp"
#include "util.cpp"

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

    // ----------------------------------------------------------------------------------------------------------------

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

    // ----------------------------------------------------------------------------------------------------------------

    CloseWindow();

    return 0;
}
