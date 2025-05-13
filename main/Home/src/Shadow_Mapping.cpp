#include <graphics.h>

void drawPretty3DBlock() {
    int x = 300, y = 250, size = 100, depth = 40;

    // Front face
    setcolor(CYAN);
    setfillstyle(SOLID_FILL, CYAN);
    rectangle(x, y, x + size, y + size);
    floodfill(x + 5, y + 5, CYAN);

    // Top face
    setcolor(LIGHTBLUE);
    line(x, y, x + depth, y - depth);
    line(x + size, y, x + size + depth, y - depth);
    line(x + depth, y - depth, x + size + depth, y - depth);
    line(x, y, x + size, y);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    floodfill(x + 10, y - 10, LIGHTBLUE);

    // Right face
    setcolor(LIGHTCYAN);
    line(x + size, y, x + size + depth, y - depth);
    line(x + size, y + size, x + size + depth, y + size - depth);
    line(x + size + depth, y - depth, x + size + depth, y + size - depth);
    line(x + size, y, x + size, y + size);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    floodfill(x + size + 10, y + 10, LIGHTCYAN);

    // Shadow (soft and stylized)
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    line(x + size, y + size, x + size + 60, y + size + 30);
    line(x, y + size, x + 60, y + size + 30);
    line(x + 60, y + size + 30, x + size + 60, y + size + 30);
    line(x, y + size, x + size, y + size);
    floodfill(x + size - 10, y + size + 10, DARKGRAY);

    // Labels
    setcolor(WHITE);
    settextstyle(8, 0, 2);
    outtextxy(x + 20, y + 40, "3D Block");
    outtextxy(x + size + 25, y + size + 15, "Shadow");
}

int main() {
    initwindow(900, 650, "Pretty 3D Block with Shadow");
    setbkcolor(BLACK);
    cleardevice();

    drawPretty3DBlock();

    getch();
    closegraph();
    return 0;
}
