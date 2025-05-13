#include <graphics.h>
#include <cmath>
#include <conio.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Wave layer structure
struct WaveLayer {
    int amplitude;
    float frequency;
    float speed;
    int color;
    float phase;
};

// Initialize wave layers
WaveLayer waves[] = {
    {40, 0.015f, 0.07f, CYAN, 0},
    {25, 0.02f, 0.12f, LIGHTCYAN, 2},
    {15, 0.025f, 0.18f, WHITE, 4}
};

const int numWaves = sizeof(waves) / sizeof(waves[0]);

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    setbkcolor(BLACK);
    cleardevice();

    while (!kbhit()) {
        cleardevice();

        for (int w = 0; w < numWaves; ++w) {
            setcolor(waves[w].color);
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                int y = SCREEN_HEIGHT / 2 +
                        int(waves[w].amplitude * sin(waves[w].frequency * x + waves[w].phase));
                putpixel(x, y, waves[w].color);
            }
            waves[w].phase += waves[w].speed;
        }

        delay(30);
    }

    getch();
    closegraph();
    return 0;
}
