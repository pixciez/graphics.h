#include <iostream>
#include <graphics.h>

using namespace std;

const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

// Function to compute region code
int computeCode(int x, int y, int xmin, int ymin, int xmax, int ymax) {
    int code = INSIDE;

    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;

    return code;
}

// Cohen-Sutherland Line Clipping Algorithm
bool cohenSutherlandClip(int &x1, int &y1, int &x2, int &y2, int xmin, int ymin, int xmax, int ymax) {
    int code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
    int code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) { // Completely inside
            accept = true;
            break;
        } else if (code1 & code2) { // Completely outside
            break;
        } else { // Partially inside
            int codeOut;
            int x, y;

            if (code1 != 0) codeOut = code1; 
            else codeOut = code2;

            if (codeOut & TOP) { // Top intersection
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) { // Bottom intersection
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) { // Right intersection
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) { // Left intersection
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
            }
        }
    }
    return accept;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, nullptr);

    int xmin, ymin, xmax, ymax;
    int x1, y1, x2, y2;

    // Get Clipping Window
    cout << "Enter the bottom-left corner of clipping window (xmin ymin): ";
    cin >> xmin >> ymin;
    cout << "Enter the top-right corner of clipping window (xmax ymax): ";
    cin >> xmax >> ymax;

    // Get Line Endpoints
    cout << "Enter the coordinates of the line (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    // Draw Clipping Window in Red
    setcolor(RED);
    rectangle(xmin, ymin, xmax, ymax);

    // Draw Original Line in White
    setcolor(WHITE);
    line(x1, y1, x2, y2);

    int code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
    int code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);

    // Check if line is completely inside, outside, or partially inside
    if (code1 == 0 && code2 == 0) {
        cout << "Line (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ") is COMPLETELY inside the clipping window.\n";
    } else if (code1 & code2) {
        cout << "Line (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ") is COMPLETELY outside the clipping window.\n";
    } else {
        cout << "Line (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ") is PARTIALLY inside the clipping window.\n";
    }

    // Wait for 'C' to clip the line
    cout << "Press 'C' to clip the line...";
    while (true) {
        if (getch() == 'C' || getch() == 'c') break;
    }

    cleardevice();
    setcolor(RED);
    rectangle(xmin, ymin, xmax, ymax);

    if (cohenSutherlandClip(x1, y1, x2, y2, xmin, ymin, xmax, ymax)) {
        cout << "Clipped Line Coordinates: (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")\n";
        setcolor(10);
        line(x1, y1, x2, y2);
    } else {
        cout << "Line was completely outside and removed.\n";
    }

    getch();
    closegraph();
    return 0;
}
