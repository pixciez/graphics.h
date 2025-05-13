#include <iostream>
#include <graphics.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\turboc3\\bgi");

    setbkcolor(BLACK);
    cleardevice();

    setcolor(GREEN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    // First row
    circle(150, 100, 50);
    outtextxy(110, 90, "CIRCLE");

    rectangle(250, 60, 400, 140);
    outtextxy(265, 90, "RECTANGLE");

    ellipse(500, 100, 0, 360, 60, 40);
    outtextxy(453, 90, "ELLIPSE");

    // Second row
    arc(150, 300, 0, 180, 50);
    outtextxy(130, 310, "ARC");

    line(250, 320, 450, 320);   // Triangle base
    line(350, 220, 250, 320);   // Triangle left side
    line(350, 220, 450, 320);   // Triangle right side

    outtextxy(295, 280, "TRIANGLE");

    line(480, 300, 580, 300);
    outtextxy(500, 310, "LINE");

    getch();
    closegraph();

    return 0;
}
