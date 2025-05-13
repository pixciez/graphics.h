#include <graphics.h>
#include <conio.h>
#include <iostream>

using namespace std;

void drawBox(int left, int top, int right, int bottom, int color) {
    setcolor(color);
    rectangle(left, top, right, bottom);
}

void drawLine(int x1, int y1, int x2, int y2, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    
    float wxmin = 10, wxmax = 150, wymin = 10, wymax = 250;
    float vxmin = 200, vxmax = 600, vymin = 10, vymax = 250;
    int wx1 = 30, wy1 = 50, wx2 = 100, wy2 = 180; 

    cleardevice();

 
    drawBox(wxmin, wymin, wxmax, wymax, RED);
    drawLine(wx1, wy1, wx2, wy2, GREEN);

 
    float sx = (vxmax - vxmin) / (wxmax - wxmin);
    float sy = (vymax - vymin) / (wymax - wymin);

   
    float vx1 = sx * (wx1 - wxmin) + vxmin;
    float vy1 = sy * (wy1 - wymin) + vymin;
    float vx2 = sx * (wx2 - wxmin) + vxmin;
    float vy2 = sy * (wy2 - wymin) + vymin;

    
    drawBox(vxmin, vymin, vxmax, vymax, RED);
    drawLine((int)vx1, (int)vy1, (int)vx2, (int)vy2, GREEN);

    outtextxy(60, 260, "Window");
    outtextxy(360, 260, "Viewport");

    getch();
    closegraph();
    return 0;
}