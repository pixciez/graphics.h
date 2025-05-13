#include <graphics.h>
#include <windows.h>

const int MAZE_SIZE = 20;
const int CELL_SIZE = 30;
const int OFFSET = 135;

int maze[MAZE_SIZE][MAZE_SIZE] = {0};
int playerX = 0, playerY = 0;
int endX = MAZE_SIZE - 1, endY = MAZE_SIZE - 1;

// A simple hardcoded complex maze generator (adjust this manually or use a generator later)
void generateMazeLayout() {
    int layout[MAZE_SIZE][MAZE_SIZE] = {
        {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,1,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,1,0,1},
        {1,0,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
        {1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,0,0,1,1,1,0,1,1,1,1,0,1,1,0,1,0,1},
        {1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1},
        {1,0,1,1,0,1,1,0,0,0,0,0,1,0,1,1,0,1,0,1},
        {1,0,1,1,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    };
    for (int y = 0; y < MAZE_SIZE; y++)
        for (int x = 0; x < MAZE_SIZE; x++)
            maze[y][x] = layout[y][x];
}

void drawMaze() {
    for (int y = 0; y < MAZE_SIZE; y++) {
        for (int x = 0; x < MAZE_SIZE; x++) {
            int x1 = OFFSET + x * CELL_SIZE;
            int y1 = OFFSET + y * CELL_SIZE;
            int x2 = x1 + CELL_SIZE;
            int y2 = y1 + CELL_SIZE;

            setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, maze[y][x] ? COLOR(30,30,40) : COLOR(10,10,10));
            bar(x1, y1, x2 - 1, y2 - 1);
        }
    }

    // Start and End nodes
    int sX = OFFSET + 0 * CELL_SIZE + CELL_SIZE / 2;
    int sY = OFFSET + 0 * CELL_SIZE + CELL_SIZE / 2;
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(sX, sY, 6, 6);

    int eX = OFFSET + endX * CELL_SIZE + CELL_SIZE / 2;
    int eY = OFFSET + endY * CELL_SIZE + CELL_SIZE / 2;
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(eX, eY, 6, 6);
}

void drawPlayer() {
    int px = OFFSET + playerX * CELL_SIZE + CELL_SIZE / 2;
    int py = OFFSET + playerY * CELL_SIZE + CELL_SIZE / 2;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, COLOR(255, 20, 147)); // Hot pink dot
    fillellipse(px, py, 5, 5);
}

void drawMiniMap() {
    int size = 4;
    int startX = 20, startY = 20;

    setcolor(WHITE);
    outtextxy(startX, startY - 20, "MiniMap");

    for (int y = 0; y < MAZE_SIZE; y++) {
        for (int x = 0; x < MAZE_SIZE; x++) {
            int x1 = startX + x * size;
            int y1 = startY + y * size;

            int color = maze[y][x] ? COLOR(30,30,50) : COLOR(100,100,120);
            setfillstyle(SOLID_FILL, color);
            bar(x1, y1, x1 + size - 1, y1 + size - 1);
        }
    }

    // player dot on minimap
    int px = startX + playerX * size;
    int py = startY + playerY * size;
    setfillstyle(SOLID_FILL, MAGENTA);
    bar(px, py, px + size - 1, py + size - 1);
}

bool isKey(int key) {
    return GetAsyncKeyState(key) & 0x8000;
}

void movePlayer(int dx, int dy) {
    int nx = playerX + dx;
    int ny = playerY + dy;

    if (nx >= 0 && ny >= 0 && nx < MAZE_SIZE && ny < MAZE_SIZE && maze[ny][nx] == 0) {
        playerX = nx;
        playerY = ny;
    }
}

int main() {
    initwindow(850, 800, "3D Maze");

    generateMazeLayout();

    while (true) {
        drawMaze();
        drawPlayer();
        drawMiniMap();

        if (isKey(VK_UP)) movePlayer(0, -1);
        if (isKey(VK_DOWN)) movePlayer(0, 1);
        if (isKey(VK_LEFT)) movePlayer(-1, 0);
        if (isKey(VK_RIGHT)) movePlayer(1, 0);
        if (isKey(VK_ESCAPE)) break;

        if (playerX == endX && playerY == endY) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            setcolor(LIGHTGREEN);
            outtextxy(OFFSET, OFFSET + MAZE_SIZE * CELL_SIZE + 20, "Destination Reached.");
        }

        delay(20);
    }

    closegraph();
    return 0;
}
