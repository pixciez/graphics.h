#include <iostream>
#include <graphics.h>

using namespace std;

// Function to draw red clipping boundary lines
void drawClippingWindow(int xmin, int ymin, int xmax, int ymax) {
    setcolor(RED);
    line(xmin, 0, xmin, getmaxy());   // Left boundary
    line(xmax, 0, xmax, getmaxy());   // Right boundary
    line(0, ymax, getmaxx(), ymax);   // Top boundary
    line(0, ymin, getmaxx(), ymin);   // Bottom boundary
}

// Function to compute the 4-bit region code
int computeRegionCode(int x, int y, int xmin, int ymin, int xmax, int ymax) {
    int code = 0;
    if (y < ymin) code |= 1;  // Below bottom
    if (y > ymax) code |= 2;  // Above top
    if (x > xmax) code |= 4;  // Right of window
    if (x < xmin) code |= 8;  // Left of window
    return code;
}

// Function to display the binary form of the region code
void printRegionCode(int code) {
    for (int i = 3; i >= 0; i--) {
        cout << ((code >> i) & 1);
    }
}

void analyzeLinePosition(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax) {
    int code1 = computeRegionCode(x1, y1, xmin, ymin, xmax, ymax);
    int code2 = computeRegionCode(x2, y2, xmin, ymin, xmax, ymax);

    cout << "\nRegion Code for Point (" << x1 << ", " << y1 << "): ";
    printRegionCode(code1);
    cout << endl;

    cout << "Region Code for Point (" << x2 << ", " << y2 << "): ";
    printRegionCode(code2);
    cout << endl;

    if (code1 == 0 && code2 == 0) {
        cout << "Line (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ") is COMPLETELY inside the clipping window.\n";
    } else if ((code1 & code2) != 0) {
        cout << "Line (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ") is COMPLETELY outside the clipping window.\n";
    } else {
        cout << "Line (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ") is PARTIALLY inside the clipping window.\n";
        
        // Check which points are inside
        if (code1 == 0 && code2 != 0) {
            cout << "Point (" << x1 << ", " << y1 << ") is INSIDE the window.\n";
        } else if (code2 == 0 && code1 != 0) {
            cout << "Point (" << x2 << ", " << y2 << ") is INSIDE the window.\n";
        } else {
            cout << "Both endpoints are outside, but part of the line may be inside.\n";
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, nullptr);

    int xmin = 200, ymin = 150, xmax = 400, ymax = 300;
    drawClippingWindow(xmin, ymin, xmax, ymax);

    int x1, y1, x2, y2;
    cout << "Enter the coordinates of the line (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    setcolor(GREEN);
    line(x1, y1, x2, y2);

    analyzeLinePosition(x1, y1, x2, y2, xmin, ymin, xmax, ymax);

    getch();
    closegraph();
    return 0;
}
