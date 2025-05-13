#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <cmath>

using namespace std;

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, nullptr);
    
    setbkcolor(BLACK);
    cleardevice();

    int x1 = 150, y1 = 200;
    int x2 = 200, y2 = 100;
    int x3 = 250, y3 = 200;
    
    int choice, tx, ty, sx, sy;
    float angle;

    drawTriangle(x1, y1, x2, y2, x3, y3, RED);

    cout << "Choose transformation:\n";
    cout << "1. Translation\n2. Scaling\n3. Rotation\nEnter your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        cout << "Enter translation values (tx, ty): ";
        cin >> tx >> ty;
        drawTriangle(x1 + tx, y1 + ty, x2 + tx, y2 + ty, x3 + tx, y3 + ty, GREEN);
    } 
    else if (choice == 2) {
        cout << "Enter scaling values (sx, sy): ";
        cin >> sx >> sy;
        drawTriangle(x1 * sx, y1 * sy, x2 * sx, y2 * sy, x3 * sx, y3 * sy, GREEN);
    } 
    else if (choice == 3) {
        cout << "Enter rotation angle (degrees): ";
        cin >> angle;
        angle = angle * M_PI / 180.0;
        
        float cx = (x1 + x2 + x3) / 3.0;
        float cy = (y1 + y2 + y3) / 3.0;

        int nx1 = cx + (x1 - cx) * cos(angle) - (y1 - cy) * sin(angle);
        int ny1 = cy + (x1 - cx) * sin(angle) + (y1 - cy) * cos(angle);

        int nx2 = cx + (x2 - cx) * cos(angle) - (y2 - cy) * sin(angle);
        int ny2 = cy + (x2 - cx) * sin(angle) + (y2 - cy) * cos(angle);

        int nx3 = cx + (x3 - cx) * cos(angle) - (y3 - cy) * sin(angle);
        int ny3 = cy + (x3 - cx) * sin(angle) + (y3 - cy) * cos(angle);

        drawTriangle(nx1, ny1, nx2, ny2, nx3, ny3, GREEN);
    } 
    else {
        cout << "Invalid choice!";
    }

    getch();
    closegraph();
    return 0;
}