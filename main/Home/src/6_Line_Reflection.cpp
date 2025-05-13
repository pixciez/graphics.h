#include <iostream>
#include <graphics.h>

using namespace std;

// Function to draw X and Y axes
void draw_axes(int width, int height) {
    setcolor(4); // Red color for axes
    line(width / 2, 0, width / 2, height); // Y-axis
    line(0, height / 2, width, height / 2); // X-axis
}

// Function to reflect a line along the X-axis
void reflect_x(int &x1, int &y1, int &x2, int &y2, int height) {
    int y1_reflected = height - y1; // Reflect across X-axis
    int y2_reflected = height - y2;
    
    setcolor(3); // Cyan color for X-axis reflection
    line(x1, y1_reflected, x2, y2_reflected);
    outtextxy(x1, y1_reflected + 10, "Reflection along X-axis");
}

// Function to reflect a line along the Y-axis
void reflect_y(int &x1, int &y1, int &x2, int &y2, int width) {
    int x1_reflected = width - x1; // Reflect across Y-axis
    int x2_reflected = width - x2;

    setcolor(9); // Blue color for Y-axis reflection
    line(x1_reflected, y1, x2_reflected, y2);
    outtextxy(x1_reflected - 20, y1 + 10, "Reflection along Y-axis");
}

int main() {
    // Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Get screen size
    int width = getmaxx();
    int height = getmaxy();

    // User input for line coordinates
    int x1, y1, x2, y2;
    cout << "Enter the coordinates of the line (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    // Draw original line
    setcolor(6); // Yellow color
    line(x1, y1, x2, y2);
    outtextxy(x1, y1 + 10, "Original Object");

    // Draw coordinate axes
    draw_axes(width, height);

    // Perform reflections
    reflect_x(x1, y1, x2, y2, height / 2);
    reflect_y(x1, y1, x2, y2, width / 2);

    // Wait for user input before closing
    cin.get();
    cin.get();
    closegraph();

    return 0;
}