#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <dos.h>

#define PI 3.14159265

void koch(int x1, int y1, int x2, int y2, int iter) {
    if (iter == 0) {
        line(x1, y1, x2, y2);
    } else {
        int x3 = (2 * x1 + x2) / 3;
        int y3 = (2 * y1 + y2) / 3;
        int x4 = (x1 + 2 * x2) / 3;
        int y4 = (y1 + 2 * y2) / 3;

        int x = x3 + (x4 - x3) / 2 - (int)((sqrt(3) * (y4 - y3)) / 2);
        int y = y3 + (y4 - y3) / 2 + (int)((sqrt(3) * (x4 - x3)) / 2);

        koch(x1, y1, x3, y3, iter - 1);
        koch(x3, y3, x, y, iter - 1);
        koch(x, y, x4, y4, iter - 1);
        koch(x4, y4, x2, y2, iter - 1);
    }
}

void drawKochTriangle(int cx, int cy, float length, int depth) {
    int x1 = (int)(cx - length / 2);
    int y1 = (int)(cy + length * sqrt(3) / 6);

    int x2 = (int)(cx + length / 2);
    int y2 = y1;

    int x3 = (int)(cx);
    int y3 = (int)(cy - length * sqrt(3) / 3);

    koch(x1, y1, x2, y2, depth);
    koch(x2, y2, x3, y3, depth);
    koch(x3, y3, x1, y1, depth);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    setbkcolor(BLACK);
    cleardevice();

    int cx = getmaxx() / 2;
    int cy = getmaxy() / 2;

    float zoom = 1.0f;
    float zoomStep = 0.97f;
    float baseLength = 400;
    int depth = 2;

    while (!kbhit()) {
        cleardevice();

        float currentLength = baseLength;

        // Draw nested Koch snowflakes with blue gradient
        for (int i = 0; i < 8; i++) {
            int color;
            switch (i % 5) {
                case 0: color = LIGHTCYAN; break;
                case 1: color = CYAN; break;
                case 2: color = LIGHTBLUE; break;
                case 3: color = BLUE; break;
                case 4: color = BLUE + i % 2; break;
            }
            setcolor(color);
            drawKochTriangle(cx, cy, currentLength * zoom, depth);
            currentLength *= 0.6f;
        }

        zoom /= zoomStep;
        if (zoom > 10000) zoom = 1.0f;

        delay(60);
    }

    getch();
    closegraph();
    return 0;
}
