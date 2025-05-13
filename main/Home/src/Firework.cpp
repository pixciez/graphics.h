#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define NUM_PARTICLES 300
#define TRAIL_PARTICLES 50
#define GRAVITY 0.15f

struct Particle {
    float x, y;
    float dx, dy;
    int life;
    COLORREF color;
    bool active;
};

Particle explosion[NUM_PARTICLES];
Particle trail[TRAIL_PARTICLES];
int trailIndex = 0;

COLORREF colors[] = {
    RGB(255, 255, 0),   // Yellow
    RGB(255, 0, 255),   // Magenta
    RGB(0, 255, 255),   // Cyan
    RGB(255, 165, 0),   // Orange
    RGB(255, 255, 255)  // White
};

void initExplosion(int cx, int cy) {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        float angle = (float)(rand() % 360) * 3.14159f / 180.0f;
        float speed = (float)(rand() % 5 + 2);
        explosion[i].x = cx;
        explosion[i].y = cy;
        explosion[i].dx = speed * cos(angle);
        explosion[i].dy = speed * sin(angle);
        explosion[i].life = rand() % 30 + 30;
        explosion[i].color = colors[rand() % 5];
        explosion[i].active = true;
    }
}

void updateExplosion() {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        if (explosion[i].active && explosion[i].life > 0) {
            explosion[i].x += explosion[i].dx;
            explosion[i].y += explosion[i].dy;
            explosion[i].dy += GRAVITY; // Gravity pulls downward
            explosion[i].life--;
        }
    }
}

void drawExplosion() {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        if (explosion[i].active && explosion[i].life > 0) {
            setcolor(explosion[i].color);
            putpixel((int)explosion[i].x, (int)explosion[i].y, explosion[i].color);
        }
    }
}

void addTrail(int x, int y) {
    trail[trailIndex].x = x;
    trail[trailIndex].y = y;
    trail[trailIndex].life = 15;
    trail[trailIndex].color = RGB(200, 200, 200);
    trail[trailIndex].active = true;
    trailIndex = (trailIndex + 1) % TRAIL_PARTICLES;
}

void updateTrail() {
    for (int i = 0; i < TRAIL_PARTICLES; ++i) {
        if (trail[i].active && trail[i].life > 0) {
            trail[i].life--;
        }
    }
}

void drawTrail() {
    for (int i = 0; i < TRAIL_PARTICLES; ++i) {
        if (trail[i].active && trail[i].life > 0) {
            int alpha = trail[i].life * 15;
            setcolor(RGB(alpha, alpha, alpha));
            putpixel((int)trail[i].x, (int)trail[i].y, trail[i].color);
        }
    }
}

int main() {
    initwindow(1000, 700, "Click Click Fireworks");
    srand(time(0));

    while (!kbhit()) {
        cleardevice();

        POINT mouse;
        GetCursorPos(&mouse);
        ScreenToClient(GetActiveWindow(), &mouse);
        addTrail(mouse.x, mouse.y);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            initExplosion(mouse.x, mouse.y);
        }

        updateTrail();
        updateExplosion();
        drawTrail();
        drawExplosion();

        delay(20);
    }

    closegraph();
    return 0;
}
