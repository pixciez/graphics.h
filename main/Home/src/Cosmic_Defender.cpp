#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Player {
public:
    int x, y;
    int width, height;
    int lives;
    int score;

    Player() {
        width = 50;
        height = 50;
        x = SCREEN_WIDTH / 2 - width / 2;
        y = SCREEN_HEIGHT - 100;
        lives = 3;
        score = 0;
    }

    void draw() {
        setcolor(CYAN);
        rectangle(x, y, x + width, y + height);
        floodfill(x + width/2, y + height/2, CYAN);
    }

    void move(bool left) {
        if (left && x > 0) 
            x -= 10;
        else if (!left && x < SCREEN_WIDTH - width) 
            x += 10;
    }
};

class Bullet {
public:
    int x, y;
    bool isActive;

    Bullet() : isActive(false) {}

    void shoot(int startX, int startY) {
        x = startX;
        y = startY;
        isActive = true;
    }

    void update() {
        if (isActive) {
            y -= 10;
            if (y < 0) isActive = false;
        }
    }

    void draw() {
        if (isActive) {
            setcolor(YELLOW);
            rectangle(x, y, x + 5, y + 10);
            floodfill(x + 2, y + 5, YELLOW);
        }
    }
};

class Enemy {
public:
    int x, y;
    int width, height;
    bool isActive;

    Enemy() : isActive(false) {}

    void spawn() {
        width = 40;
        height = 40;
        x = rand() % (SCREEN_WIDTH - width);
        y = 0;
        isActive = true;
    }

    void update() {
        if (isActive) {
            y += 3;
            if (y > SCREEN_HEIGHT) isActive = false;
        }
    }

    void draw() {
        if (isActive) {
            setcolor(RED);
            rectangle(x, y, x + width, y + height);
            floodfill(x + width/2, y + height/2, RED);
        }
    }
};

class Game {
private:
    Player player;
    std::vector<Bullet> playerBullets;
    std::vector<Enemy> enemies;
    int gameState; // 0 = menu, 1 = playing, 2 = game over
    
    void drawMenu() {
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        setcolor(CYAN);
        outtextxy(SCREEN_WIDTH/2 - textwidth("COSMIC DEFENDER")/2, 200, "COSMIC DEFENDER");
        
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(WHITE);
        outtextxy(SCREEN_WIDTH/2 - textwidth("Press ENTER to Start")/2, 300, "Press ENTER to Start");
    }

    void drawGameOver() {
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        setcolor(RED);
        outtextxy(SCREEN_WIDTH/2 - textwidth("GAME OVER")/2, 200, "GAME OVER");
        
        char scoreText[50];
        sprintf(scoreText, "Score: %d", player.score);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);
        outtextxy(SCREEN_WIDTH/2 - textwidth(scoreText)/2, 300, scoreText);
        
        outtextxy(SCREEN_WIDTH/2 - textwidth("Press R to Restart")/2, 350, "Press R to Restart");
    }

    void spawnEnemies() {
        static int enemySpawnTimer = 0;
        enemySpawnTimer++;
        
        if (enemySpawnTimer > 50) {
            for (auto& enemy : enemies) {
                if (!enemy.isActive) {
                    enemy.spawn();
                    break;
                }
            }
            enemySpawnTimer = 0;
        }
    }

    void checkCollisions() {
        // Player bullets vs Enemies
        for (auto& bullet : playerBullets) {
            for (auto& enemy : enemies) {
                if (bullet.isActive && enemy.isActive &&
                    bullet.x >= enemy.x && bullet.x <= enemy.x + enemy.width &&
                    bullet.y >= enemy.y && bullet.y <= enemy.y + enemy.height) {
                    
                    bullet.isActive = false;
                    enemy.isActive = false;
                    player.score += 10;
                }
            }
        }

        // Enemies vs Player
        for (auto& enemy : enemies) {
            if (enemy.isActive &&
                enemy.x < player.x + player.width &&
                enemy.x + enemy.width > player.x &&
                enemy.y < player.y + player.height &&
                enemy.y + enemy.height > player.y) {
                
                player.lives--;
                enemy.isActive = false;
                
                if (player.lives <= 0) {
                    gameState = 2; // Game Over
                }
            }
        }
    }

    void drawScore() {
        char scoreText[50];
        sprintf(scoreText, "Score: %d  Lives: %d", player.score, player.lives);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(WHITE);
        outtextxy(10, 10, scoreText);
    }

public:
    Game() {
        initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cosmic Defender");
        srand(time(NULL));
        
        // Initialize enemy array
        enemies.resize(20);
        playerBullets.resize(10);
        
        gameState = 0; // Start in menu
    }

    void run() {
        while (true) {
            // Clear screen
            cleardevice();

            if (gameState == 0) { // Menu
                drawMenu();
                
                if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                    // Reset game state
                    player = Player();
                    enemies.clear();
                    enemies.resize(20);
                    playerBullets.clear();
                    playerBullets.resize(10);
                    gameState = 1;
                }
            }
            else if (gameState == 1) { // Playing
                // Player movement
                if (GetAsyncKeyState(VK_LEFT) & 0x8000)
                    player.move(true);
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
                    player.move(false);

                // Shooting
                if (GetAsyncKeyState('X') & 0x8000) {
                    for (auto& bullet : playerBullets) {
                        if (!bullet.isActive) {
                            bullet.shoot(player.x + player.width/2, player.y);
                            break;
                        }
                    }
                }

                // Spawn and update enemies
                spawnEnemies();
                
                for (auto& enemy : enemies)
                    enemy.update();
                
                for (auto& bullet : playerBullets)
                    bullet.update();

                // Collision detection
                checkCollisions();

                // Drawing
                player.draw();
                
                for (auto& enemy : enemies)
                    enemy.draw();
                
                for (auto& bullet : playerBullets)
                    bullet.draw();

                // Draw score
                drawScore();
            }
            else if (gameState == 2) { // Game Over
                drawGameOver();
                
                if (GetAsyncKeyState('R') & 0x8000) {
                    gameState = 0; // Back to menu
                }
            }

            // Exit game
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
                break;

            // Delay to control game speed
            delay(50);
        }

        // Close graphics window
        closegraph();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}