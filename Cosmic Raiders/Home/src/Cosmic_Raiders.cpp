#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function prototypes
void drawSpaceship(int x, int y);
void drawAlien(int x, int y);
void drawPlayerBullet(int x, int y);
void drawAlienBullet(int x, int y);
bool checkHit(int bulletX, int bulletY, int targetX, int targetY, int targetWidth, int targetHeight);
void drawExplosion(int x, int y);
void displayScore(int score);
void displayLives(int lives);
void drawBackground();
void displayMenu();
void displayHighScores();
void drawTitle();
void drawMenuOptions();
void drawStars();

void drawSpaceship(int x, int y) {
    int p = 4;

    // Core Body (Steel Gray)
    setcolor(COLOR(100, 100, 100));
    setfillstyle(SOLID_FILL, COLOR(100, 100, 100));
    bar(x + 4*p, y + 0*p, x + 5*p, y + 1*p);
    bar(x + 3*p, y + 1*p, x + 6*p, y + 2*p);
    bar(x + 3*p, y + 2*p, x + 6*p, y + 3*p);
    bar(x + 2*p, y + 3*p, x + 7*p, y + 4*p);
    bar(x + 2*p, y + 4*p, x + 7*p, y + 5*p);
    bar(x + 1*p, y + 5*p, x + 8*p, y + 6*p);
    bar(x + 1*p, y + 6*p, x + 8*p, y + 7*p);
    bar(x + 2*p, y + 7*p, x + 7*p, y + 8*p);

    // Cockpit Dome (Cyan/Glass Look)
    setcolor(CYAN);
    setfillstyle(SOLID_FILL, CYAN);
    bar(x + 4*p, y + 3*p, x + 5*p, y + 5*p);
    setcolor(LIGHTCYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(x + 4*p, y + 2*p, x + 5*p, y + 3*p); // cockpit shine

    // Left Wing (Vibrant green tint)
    setcolor(COLOR(0, 255, 0));
    setfillstyle(SOLID_FILL, COLOR(0, 255, 0));
    bar(x + 0*p, y + 5*p, x + 1*p, y + 6*p);
    bar(x + 0*p, y + 6*p, x + 1*p, y + 7*p);
    bar(x + 0*p, y + 7*p, x + 2*p, y + 8*p);

    // Right Wing
    bar(x + 8*p, y + 5*p, x + 9*p, y + 6*p);
    bar(x + 8*p, y + 6*p, x + 9*p, y + 7*p);
    bar(x + 7*p, y + 7*p, x + 9*p, y + 8*p);

    // Engine Ports (Gunmetal)
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(x + 3*p, y + 8*p, x + 4*p, y + 9*p);
    bar(x + 5*p, y + 8*p, x + 6*p, y + 9*p);

    // Booster Core (Middle Exhaust)
    setcolor(COLOR(120, 0, 0)); // deep red
    setfillstyle(SOLID_FILL, COLOR(120, 0, 0));
    bar(x + 4*p, y + 8*p, x + 5*p, y + 10*p);

    // Flame Animation - Alternating Flicker (Call this in a loop with frame variation)
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(x + 3*p, y + 9*p, x + 4*p, y + 10*p);
    bar(x + 5*p, y + 9*p, x + 6*p, y + 10*p);

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    bar(x + 4*p, y + 10*p, x + 5*p, y + 11*p);

    // Optional Details: tail fins or rear sensors
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x + 2*p, y + 8*p, x + 3*p, y + 9*p);
    bar(x + 6*p, y + 8*p, x + 7*p, y + 9*p);
}


// Pixel art style alien drawing function
void drawAlien(int x, int y) {
    int pixelSize = 4; // Size of each "pixel"
    
    // Alien head - simple pixel art style
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    
    // Antenna
    bar(x + 6*pixelSize, y, x + 7*pixelSize, y + pixelSize);
    
    // Upper Head
    for (int i = 1; i < 3; i++) {
        for (int j = 5; j < 8; j++) {
            bar(x + j*pixelSize, y + i*pixelSize, 
                x + (j+1)*pixelSize, y + (i+1)*pixelSize);
        }
    }
    
    // Middle Head (wider)
    for (int j = 4; j < 9; j++) {
        bar(x + j*pixelSize, y + 3*pixelSize, 
            x + (j+1)*pixelSize, y + 4*pixelSize);
    }
    
    // Eyes
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    bar(x + 5*pixelSize, y + 3*pixelSize, x + 6*pixelSize, y + 4*pixelSize);
    bar(x + 7*pixelSize, y + 3*pixelSize, x + 8*pixelSize, y + 4*pixelSize);
    
    // Body - blocky shape
    setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    for (int i = 4; i < 6; i++) {
        for (int j = 3; j < 10; j++) {
            bar(x + j*pixelSize, y + i*pixelSize, 
                x + (j+1)*pixelSize, y + (i+1)*pixelSize);
        }
    }
    
    // Tentacles/arms
    for (int j = 2; j < 11; j+=2) {
        bar(x + j*pixelSize, y + 6*pixelSize, 
            x + (j+1)*pixelSize, y + 7*pixelSize);
    }
}

// Pixel art style player bullet
void drawPlayerBullet(int x, int y) {
    int pixelSize = 3; // Smaller pixels for bullet
    
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    // Bullet body
    bar(x, y, x + pixelSize, y + 2*pixelSize);
    
    // Bullet tip
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    bar(x, y - pixelSize, x + pixelSize, y);
}

// Pixel art style alien bullet
void drawAlienBullet(int x, int y) {
    int pixelSize = 3; // Smaller pixels for bullet
    
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    // Bullet body
    bar(x, y, x + pixelSize, y + 2*pixelSize);
    
    // Bullet tip
    setcolor(LIGHTRED);
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(x, y + 2*pixelSize, x + pixelSize, y + 3*pixelSize);
}

// Check if a bullet hit a target
bool checkHit(int bulletX, int bulletY, int targetX, int targetY, int targetWidth, int targetHeight) {
    return (bulletX >= targetX && bulletX <= targetX + targetWidth &&
            bulletY >= targetY && bulletY <= targetY + targetHeight);
}

// Pixel art style explosion
void drawExplosion(int x, int y) {
    int pixelSize = 4;
    int frame = 0;
    
    for (frame = 0; frame < 3; frame++) {
        // Clear previous frame
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        bar(x - 5*pixelSize, y - 5*pixelSize, 
            x + 7*pixelSize, y + 7*pixelSize);
            
        // Draw new explosion frame
        // Frame pattern changes with each iteration
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        
        // Middle pixel always present
        bar(x, y, x + pixelSize, y + pixelSize);
        
        // Pattern depends on frame
        if (frame == 0) {
            // Small pattern
            bar(x - pixelSize, y, x, y + pixelSize);
            bar(x + pixelSize, y, x + 2*pixelSize, y + pixelSize);
            bar(x, y - pixelSize, x + pixelSize, y);
            bar(x, y + pixelSize, x + pixelSize, y + 2*pixelSize);
        } 
        else if (frame == 1) {
            // Medium pattern - star shape
            bar(x - 2*pixelSize, y, x - pixelSize, y + pixelSize);
            bar(x + 2*pixelSize, y, x + 3*pixelSize, y + pixelSize);
            bar(x, y - 2*pixelSize, x + pixelSize, y - pixelSize);
            bar(x, y + 2*pixelSize, x + pixelSize, y + 3*pixelSize);
            bar(x - pixelSize, y - pixelSize, x, y);
            bar(x + pixelSize, y - pixelSize, x + 2*pixelSize, y);
            bar(x - pixelSize, y + pixelSize, x, y + 2*pixelSize);
            bar(x + pixelSize, y + pixelSize, x + 2*pixelSize, y + 2*pixelSize);
        } 
        else {
            // Large pattern - scattered pixels
            setcolor(RED);
            setfillstyle(SOLID_FILL, RED);
            
            // Outer ring of explosion
            bar(x - 3*pixelSize, y, x - 2*pixelSize, y + pixelSize);
            bar(x + 3*pixelSize, y, x + 4*pixelSize, y + pixelSize);
            bar(x, y - 3*pixelSize, x + pixelSize, y - 2*pixelSize);
            bar(x, y + 3*pixelSize, x + pixelSize, y + 4*pixelSize);
            bar(x - 2*pixelSize, y - 2*pixelSize, x - pixelSize, y - pixelSize);
            bar(x + 2*pixelSize, y - 2*pixelSize, x + 3*pixelSize, y - pixelSize);
            bar(x - 2*pixelSize, y + 2*pixelSize, x - pixelSize, y + 3*pixelSize);
            bar(x + 2*pixelSize, y + 2*pixelSize, x + 3*pixelSize, y + 3*pixelSize);
            
            // Inner pattern in white
            setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
            bar(x - pixelSize, y, x, y + pixelSize);
            bar(x + pixelSize, y, x + 2*pixelSize, y + pixelSize);
            bar(x, y - pixelSize, x + pixelSize, y);
            bar(x, y + pixelSize, x + pixelSize, y + 2*pixelSize);
        }
        
        // Update display after each explosion frame
        delay(100);  // Slow down animation for visibility
        swapbuffers(); // Added to ensure explosion frames are visible
    }
}

// Display score on screen
void displayScore(int score) {
    char scoreText[50];
    sprintf(scoreText, "SCORE: %d", score);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(10, 10, scoreText);
}

void drawHeart(int x, int y, int pixelSize, bool filled) {
    int color = filled ? RED : LIGHTGRAY; // RED if life remains, GREY otherwise
    setcolor(color);
    setfillstyle(SOLID_FILL, color);

    // Left half of heart
    bar(x, y + pixelSize, x + pixelSize, y + 3 * pixelSize);
    bar(x + pixelSize, y, x + 2 * pixelSize, y + 2 * pixelSize);
    bar(x + 2 * pixelSize, y, x + 3 * pixelSize, y + 2 * pixelSize);
    bar(x + 3 * pixelSize, y + pixelSize, x + 4 * pixelSize, y + 3 * pixelSize);

    // Right half of heart
    bar(x + 4 * pixelSize, y + pixelSize, x + 5 * pixelSize, y + 3 * pixelSize);
    bar(x + 5 * pixelSize, y, x + 6 * pixelSize, y + 2 * pixelSize);
    bar(x + 6 * pixelSize, y, x + 7 * pixelSize, y + 2 * pixelSize);
    bar(x + 7 * pixelSize, y + pixelSize, x + 8 * pixelSize, y + 3 * pixelSize);

    // Bottom triangle of heart
    bar(x + 2 * pixelSize, y + 3 * pixelSize, x + 6 * pixelSize, y + 5 * pixelSize);
}

void displayLives(int lives) {
    int pixelSize = 3; // Adjust as necessary
    int startX = SCREEN_WIDTH - 100; // Position from right
    int startY = 10; // Position from top

    for (int i = 0; i < 3; i++) { // Always draw 3 hearts
        bool filled = (i < lives); // Fill red if life available, else grey
        drawHeart(startX + i * (10 * pixelSize), startY, pixelSize, filled);
    }
}


void clearLivesArea() {
    int pixelSize = 3;
    int startX = SCREEN_WIDTH - 100;
    int startY = 10;
    int width = 3 * (10 * pixelSize); // Width to clear 3 hearts
    int height = 6 * pixelSize; // Height of heart

    setcolor(BLACK); // Background color
    setfillstyle(SOLID_FILL, BLACK);
    bar(startX, startY, startX + width, startY + height);
}



// Draw stars in background
void drawBackground() {
    for (int i = 0; i < 100; i++) {
        putpixel(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, WHITE);
    }
}

// Debug function to display coordinates
void displayDebugInfo(int x, int y, const char* label) {
    char debugText[100];
    sprintf(debugText, "%s: X=%d, Y=%d", label, x, y);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(10, SCREEN_HEIGHT - 20, debugText);  // Display at bottom of screen

}

void drawTitle() {
    setcolor(CYAN);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
    outtextxy(SCREEN_WIDTH / 2 - textwidth("COSMIC RAIDERS") / 2, SCREEN_HEIGHT / 2 - 200, "COSMIC RAIDERS");

    // Glow effect
    for (int i = 1; i <= 3; i++) {
        setcolor(CYAN + i);
        outtextxy(SCREEN_WIDTH / 2 - textwidth("COSMIC RAIDERS") / 2 - i, SCREEN_HEIGHT / 2 - 200 - i, "COSMIC RAIDERS");
        outtextxy(SCREEN_WIDTH / 2 - textwidth("COSMIC RAIDERS") / 2 + i, SCREEN_HEIGHT / 2 - 200 + i, "COSMIC RAIDERS");
    }
}

void drawMenuOptions() {
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    // Center the menu options
    outtextxy(SCREEN_WIDTH / 2 - textwidth("1. Play") / 2, SCREEN_HEIGHT / 2 - 50, "1. Play");
    outtextxy(SCREEN_WIDTH / 2 - textwidth("2. High Scores") / 2, SCREEN_HEIGHT / 2, "2. High Scores");
    outtextxy(SCREEN_WIDTH / 2 - textwidth("3. Exit") / 2, SCREEN_HEIGHT / 2 + 50, "3. Exit");
}

void drawStars() {
    for (int i = 0; i < 150; i++) {
        int color = (rand() % 2 == 0) ? WHITE : LIGHTGRAY; // Randomize star colors
        putpixel(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, color);
    }
}

void displayMenu() {
    cleardevice();
    setbkcolor(BLACK);
    drawStars();
    drawTitle();
    drawMenuOptions();

    // Add a footer for instructions
    setcolor(LIGHTGRAY);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(SCREEN_WIDTH / 2 - textwidth("Use Arrow Keys to Navigate, Enter to Select") / 2, SCREEN_HEIGHT - 50, "Use Arrow Keys to Navigate, Enter to Select");

    swapbuffers();
}

void displayHighScores() {
    cleardevice();
    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, "HIGH SCORES");

    // Placeholder for high scores
    outtextxy(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "1. 1000");
    outtextxy(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 50, "2. 800");
    outtextxy(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 100, "3. 600");

    outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 200, "Press any key to return to menu");

    swapbuffers();
    getch();
}

int main() {
    int gd = DETECT, gm;
    
    // Initialize graphics with explicit window size
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cosmic Raiders");
    
    srand(time(NULL));
    
    setbkcolor(BLACK);
    cleardevice();
    
    bool inMenu = true;
    while (inMenu) {
        displayMenu();
        char choice = getch();
        switch (choice) {
            case '1':
                inMenu = false;
                break;
            case '2':
                displayHighScores();
                break;
            case '3':
                closegraph();
                return 0;
            default:
                break;
        }
    }
    
    int spaceshipX = SCREEN_WIDTH/2 - 25;  // Center the spaceship
    int spaceshipY = SCREEN_HEIGHT - 100;  // Position near bottom but visible
    int alienX = 50, alienY = 100;
    int playerBulletX = -1, playerBulletY = -1;
    int alienBulletX = -1, alienBulletY = -1;
    bool playerBulletFired = false;
    bool alienBulletFired = false;
    bool gameRunning = true;
    int alienDir = 5; // Alien movement direction
    int spaceshipDir = 0; // Spaceship movement direction
    int score = 0;
    int lives = 3;
    int alienShootTimer = 0;
    
    // Draw initial frame
    drawBackground();
    drawSpaceship(spaceshipX, spaceshipY);
    drawAlien(alienX, alienY);
    displayScore(score);
    displayLives(lives);
    outtextxy(SCREEN_WIDTH/2 - 150, 10, "Use arrow keys to move, X to shoot");
    
    // Initial message to confirm graphics are working
    setcolor(GREEN);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, "READY!");
    delay(1000);
    
    while (gameRunning) {
        cleardevice();
        
        drawBackground();
        
        // Display score and lives
        displayScore(score);
        displayLives(lives);
        
        // Debug info to show spaceship position
        displayDebugInfo(spaceshipX, spaceshipY, "Ship");
        
        // Draw spaceship and alien
        drawSpaceship(spaceshipX, spaceshipY);
        drawAlien(alienX, alienY);
        
        // Move alien
        alienX += alienDir;
        if (alienX > SCREEN_WIDTH - 55 || alienX < 0) {
            alienDir = -alienDir;
            alienY += 10; // Move alien down when it hits screen edge
        }
        
        // Check if alien reached bottom
        if (alienY > spaceshipY - 30) {
            setcolor(RED);
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
            outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, "GAME OVER!");
            swapbuffers(); // Make sure game over message is visible
            delay(2000);
            gameRunning = false;
        }
        
        // Move spaceship
        if (spaceshipDir != 0) {
            spaceshipX += spaceshipDir;
            spaceshipDir = 0; // Reset direction after move
        }
        if (spaceshipX < 0) spaceshipX = 0;
        if (spaceshipX > SCREEN_WIDTH - 55) spaceshipX = SCREEN_WIDTH - 55;
        
        // Move player bullet
        if (playerBulletFired) {
            playerBulletY -= 15;
            drawPlayerBullet(playerBulletX, playerBulletY);
            if (playerBulletY < 0) {
                playerBulletFired = false;
            } else if (checkHit(playerBulletX, playerBulletY, alienX, alienY, 50, 30)) {
                drawExplosion(alienX + 25, alienY + 15); // Center explosion on alien
                playerBulletFired = false;
                score += 100;
                
                // Respawn alien at a random position at the top
                alienX = rand() % (SCREEN_WIDTH - 100);
                alienY = 50;
                // Increase alien speed as score increases
                if (alienDir > 0) alienDir = 5 + score/500;
                else alienDir = -5 - score/500;
            }
        }
        
        // Alien shooting logic
        alienShootTimer++;
        if (!alienBulletFired && alienShootTimer > 50) {
            if (rand() % 10 == 0) { // 10% chance to shoot
                alienBulletX = alienX + 25;
                alienBulletY = alienY + 30;
                alienBulletFired = true;
                alienShootTimer = 0;
            }
        }
        
        // Move alien bullet
        if (alienBulletFired) {
            alienBulletY += 10;
            drawAlienBullet(alienBulletX, alienBulletY);
            if (alienBulletY > SCREEN_HEIGHT) {
                alienBulletFired = false;
            } else if (checkHit(alienBulletX, alienBulletY, spaceshipX, spaceshipY, 50, 30)) {
                drawExplosion(spaceshipX + 25, spaceshipY + 15); // Center explosion on spaceship
                alienBulletFired = false;
                lives--;
                displayLives(lives); // Update lives display immediately
                
                if (lives <= 0) {
                    displayLives(lives); // Ensure last heart turns grey
                    setcolor(RED);
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
                    outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, "GAME OVER!");
                    swapbuffers(); // Make sure game over message is visible
                    delay(2000);
                    gameRunning = false;
                } else {
                    // Reset player position after being hit
                    spaceshipX = SCREEN_WIDTH/2 - 25;
                    spaceshipY = SCREEN_HEIGHT - 100;
                    delay(1000);
                }
            }
        }
        
        // Handle user input
        if (kbhit()) {
            char ch = getch();
            if (ch == 'x' || ch == 'X' || ch == ' ') {
                if (!playerBulletFired) {
                    playerBulletX = spaceshipX + 25;
                    playerBulletY = spaceshipY;
                    playerBulletFired = true;
                }
            }
            else if (ch == 0 || ch == 224) { // Arrow keys prefix
                ch = getch(); // Get the actual arrow key code
                if (ch == 75) { // Left arrow
                    spaceshipDir = -10;
                } else if (ch == 77) { // Right arrow
                    spaceshipDir = 10;
                }
            }
            else if (ch == 27) { // ESC key
                gameRunning = false;
            }
        }
        
        // Show instructions
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(WHITE);
        outtextxy(SCREEN_WIDTH/2 - 150, 10, "Use arrow keys to move, X shoot");
        
        // Critical: Ensure frame is displayed before delay
        swapbuffers();
        delay(50); // Increased from 30 to 50 for better visibility
    }
    
    // Game over screen
    cleardevice();
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    outtextxy(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 50, "GAME OVER");
    
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    char finalScore[50];
    sprintf(finalScore, "Final Score: %d", score);
    outtextxy(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, finalScore);
    
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2 + 50, "Press any key to restart...");
    
    swapbuffers(); // Make sure the game over screen is visible
    getch();
    closegraph();
    
    return 0;
}