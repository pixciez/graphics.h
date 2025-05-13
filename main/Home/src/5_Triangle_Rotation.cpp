#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void rotate_anticlockwise() {
 int x1, y1, x2, y2, x3, y3;
 cout << "Enter (x1, y1): ";
 cin >> x1 >> y1;
 cout << "Enter (x2, y2): ";
 cin >> x2 >> y2;
 cout << "Enter (x3, y3): ";
 cin >> x3 >> y3;

 int Points_Array_1[] = {x1, y1, x2, y2, x3, y3, x1, y1};
 setcolor(GREEN);
 drawpoly(4, Points_Array_1);
 delay(1000);

 int cx = (x1 + x2 + x3) / 3, cy = (y1 + y2 + y3) / 3;
 float angle;
 cout << "Enter rotation angle (in degrees): ";
 cin >> angle;
 angle *= M_PI / 180.0;

 int nx1 = (x1 - cx) * cos(angle) + (y1 - cy) * sin(angle) + cx;
 int ny1 = -(x1 - cx) * sin(angle) + (y1 - cy) * cos(angle) + cy;
 int nx2 = (x2 - cx) * cos(angle) + (y2 - cy) * sin(angle) + cx;
 int ny2 = -(x2 - cx) * sin(angle) + (y2 - cy) * cos(angle) + cy;
 int nx3 = (x3 - cx) * cos(angle) + (y3 - cy) * sin(angle) + cx;
 int ny3 = -(x3 - cx) * sin(angle) + (y3 - cy) * cos(angle) + cy;

 cleardevice();
 int Points_Array_2[] = {nx1, ny1, nx2, ny2, nx3, ny3, nx1, ny1};
 setcolor(GREEN);
 drawpoly(4, Points_Array_2);
 getch();
}

void rotate_clockwise() {
 int x1, y1, x2, y2, x3, y3;
 cout << "Enter (x1, y1): ";
 cin >> x1 >> y1;
 cout << "Enter (x2, y2): ";
 cin >> x2 >> y2;
 cout << "Enter (x3, y3): ";
 cin >> x3 >> y3;

 int Points_Array_1[] = {x1, y1, x2, y2, x3, y3, x1, y1};
 setcolor(GREEN);
 drawpoly(4, Points_Array_1);
 delay(1000);

 int cx = (x1 + x2 + x3) / 3, cy = (y1 + y2 + y3) / 3;

 float angle;
 cout << "Enter rotation angle (in degrees): ";
 cin >> angle;
 angle *= M_PI / 180.0;

 int nx1 = (x1 - cx) * cos(angle) - (y1 - cy) * sin(angle) + cx;
 int ny1 = (x1 - cx) * sin(angle) + (y1 - cy) * cos(angle) + cy;
 int nx2 = (x2 - cx) * cos(angle) - (y2 - cy) * sin(angle) + cx;
 int ny2 = (x2 - cx) * sin(angle) + (y2 - cy) * cos(angle) + cy;
 int nx3 = (x3 - cx) * cos(angle) - (y3 - cy) * sin(angle) + cx;
 int ny3 = (x3 - cx) * sin(angle) + (y3 - cy) * cos(angle) + cy;

 cleardevice(); // Clear previous frame
 int Points_Array_2[] = {nx1, ny1, nx2, ny2, nx3, ny3, nx1, ny1};
 setcolor(GREEN);
 drawpoly(4, Points_Array_2);
 getch();
}

int main() {
 int gd = DETECT, gm;
 initgraph(&gd, &gm, "");

 int choice = 0;
 while (choice != 3) {
 cout << "\nChoose Rotation:\n";
 cout << "1. Anticlockwise Rotation\n";
 cout << "2. Clockwise Rotation\n";
 cout << "3. Exit\n";
 cout << "\nEnter choice: ";
 cin >> choice;

 if (choice == 1) {
 cleardevice();
 rotate_anticlockwise();
 } else if (choice == 2) {
 cleardevice();
 rotate_clockwise();
 }
 else if (choice == 3) { break; }
 else { cout << "Invalid choice!\n"; }
 }
 closegraph();
 return 0;
}
