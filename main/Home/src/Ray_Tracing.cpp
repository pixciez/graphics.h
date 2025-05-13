#include <graphics.h>
#include <cmath>
#include <iostream>
using namespace std;

struct Vec2 {
    float x, y;
    Vec2() : x(0), y(0) {}
    Vec2(float a, float b) : x(a), y(b) {}

    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator*(float f) const { return Vec2(x * f, y * f); }
    float dot(const Vec2& v) const { return x * v.x + y * v.y; }
    float length() const { return sqrt(x * x + y * y); }
    Vec2 normalize() const {
        float len = length();
        return Vec2(x / len, y / len);
    }
};

void drawRayWithShadow(Vec2 origin, Vec2 light, Vec2 obj, float radius) {
    setcolor(YELLOW);
    line(origin.x, origin.y, obj.x, obj.y);
    
    Vec2 lightDir = (light - obj).normalize();
    Vec2 shadowEnd = obj + lightDir * 200;
    setcolor(DARKGRAY);
    line(obj.x, obj.y, shadowEnd.x, shadowEnd.y);
}

void drawScene() {
    Vec2 camera(100, 300);
    Vec2 light(500, 100);
    Vec2 object(300, 300);
    float radius = 30;

    setcolor(WHITE);
    circle(object.x, object.y, radius);

    setcolor(RED);
    circle(light.x, light.y, 5);
    outtextxy(light.x + 10, light.y, (char*)"Light Source");

    setcolor(GREEN);
    circle(camera.x, camera.y, 5);
    outtextxy(camera.x - 50, camera.y, (char*)"Camera");

    drawRayWithShadow(camera, light, object, radius);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    setbkcolor(BLACK);
    cleardevice();

    drawScene();

    getch();
    closegraph();
    return 0;
}