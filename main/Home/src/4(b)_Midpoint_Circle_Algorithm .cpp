#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <cmath>

#define roundOff(a) ((int)(a + 0.5))  // Rename macro to avoid conflict

using namespace std;

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");  // Change path if needed

    setbkcolor(BLACK);  // Set background color to black
    cleardevice();      // Apply background color
    setcolor(GREEN);    // Set circle color to green

    // METHOD 1: Using Trigonometry
    int xc = 100, yc = 150, r = 50;
    float x, y;

    for (int i = 0; i <= 45; i++) {
        double ang = i * (M_PI / 180);  // Use M_PI from <cmath>
        x = r * cos(ang);
        y = r * sin(ang);

        putpixel(xc + roundOff(x), yc + roundOff(y), GREEN);
        putpixel(xc - roundOff(x), yc + roundOff(y), GREEN);
        putpixel(xc + roundOff(x), yc - roundOff(y), GREEN);
        putpixel(xc - roundOff(x), yc - roundOff(y), GREEN);
        putpixel(xc + roundOff(y), yc + roundOff(x), GREEN);
        putpixel(xc - roundOff(y), yc + roundOff(x), GREEN);
        putpixel(xc + roundOff(y), yc - roundOff(x), GREEN);
        putpixel(xc - roundOff(y), yc - roundOff(x), GREEN);

        delay(50);
    }

    // METHOD 2: Using Pythagorean Theorem
    xc = 300, yc = 150;
    x = 0, y = r;

    for (x = 0; x < y; x++) {
        y = sqrt((r * r) - (x * x));

        putpixel(xc + roundOff(x), yc + roundOff(y), GREEN);
        putpixel(xc - roundOff(x), yc + roundOff(y), GREEN);
        putpixel(xc + roundOff(x), yc - roundOff(y), GREEN);
        putpixel(xc - roundOff(x), yc - roundOff(y), GREEN);
        putpixel(xc + roundOff(y), yc + roundOff(x), GREEN);
        putpixel(xc - roundOff(y), yc + roundOff(x), GREEN);
        putpixel(xc + roundOff(y), yc - roundOff(x), GREEN);
        putpixel(xc - roundOff(y), yc - roundOff(x), GREEN);

        delay(50);
    }

    getch();
    closegraph();
    return 0;
}
