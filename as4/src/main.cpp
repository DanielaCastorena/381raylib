#include "raylib.h"
#include <stdlib.h> // rand() & srand()
#include <time.h>   // time()

#define MAX_ENEMIES 55
#define MAX_SHOTS 50
#define ENEMY_SHOT_COOLDOWN_MIN 30
#define ENEMY_SHOT_COOLDOWN_MAX 120
#define PLAYER_SHOT_COOLDOWN 20 
#define MAX_BARRICADES 4
#define BARRICADE_HEALTH 3
#define BARRICADE_DAMAGE_AMOUNT 2 // pixels removed when a barricade gets hit

typedef struct {
    Vector2 position;
    bool active;
    int directionX; // 1 for right, -1 for left
    int directionY; // 1 for down, -1 for up
} Enemy;

void DrawBlinkingRectangle(Rectangle rect, Color color, bool isVisible); // to let player know when they've been hit

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Space Invaders Remake");

    enum GameState {
        MENU,
        GAMEPLAY,
        GAME_OVER
    } gameState = MENU;

    // Load textures
    Texture2D alienTexture1 = LoadTexture("textures/textures/alien1.png");
    Texture2D alienTexture2 = LoadTexture("textures/textures/alien2.png");
    Texture2D alienTexture3 = LoadTexture("textures/textures/alien3.png");
    Texture2D spaceshipTexture = LoadTexture("textures/textures/spaceship.png");

    // Initialize player
    Rectangle player = {screenWidth / 2 - 20, screenHeight - 50, 40, 20};
    int playerLives = 3;
    bool playerHit = false;
    int playerBlinkFrames = 0;
    const int blinkTime = 30;
    const int respawnTime = 60;
    int respawnFrames = 0;

    // Initialize shots
    Rectangle shots[MAX_SHOTS] = {0};
    int shotCooldown = 0;

    // Initialize enemy shots
    Rectangle enemyShots[MAX_SHOTS] = {0};
    int enemyShotCooldown = GetRandomValue(ENEMY_SHOT_COOLDOWN_MIN, ENEMY_SHOT_COOLDOWN_MAX);

    // Initialize enemies
    Enemy enemies[MAX_ENEMIES] = {0};
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].position = (Vector2){50.0f + (i % 11) * 60.0f, 50.0f + (i / 11) * 40.0f};
        enemies[i].active = true;
        enemies[i].directionX = 1; // move right
        enemies[i].directionY = 1; // move down
    }

    // Initialize barricades
    Rectangle barricades[MAX_BARRICADES] = {
        {screenWidth / 5, screenHeight - 100, 50, 50},
        {2 * screenWidth / 5, screenHeight - 100, 50, 50},
        {3 * screenWidth / 5, screenHeight - 100, 50, 50},
        {4 * screenWidth / 5, screenHeight - 100, 50, 50}};
    int barricadeHealth[MAX_BARRICADES] = {BARRICADE_HEALTH, BARRICADE_HEALTH, BARRICADE_HEALTH, BARRICADE_HEALTH};

    // Initialize score
    int score = 0;

    bool gameover = false;
    bool restart = false;

    // Random number generator
    srand(time(NULL));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        switch (gameState) {
            case MENU: {
                BeginDrawing();
                ClearBackground(BLACK);

                // Start screen
                DrawText("SPACE INVADERS REMAKE", screenWidth / 2 - MeasureText("SPACE INVADERS REMAKE", 40) / 2, screenHeight / 2 - 50, 40, PURPLE);
                DrawText("PRESS ENTER TO START", screenWidth / 2 - MeasureText("PRESS ENTER TO START", 20) / 2, screenHeight / 2 + 20, 20, WHITE);

                EndDrawing();

                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = GAMEPLAY;
                }

                break;
            }

            case GAMEPLAY: {
                if (IsKeyPressed(KEY_ENTER) && gameover) { // for game over (loss)
                    // Reset game variables
                    playerLives = 3;
                    score = 0;
                    gameover = false;
                    restart = false;

                    // Reset player position
                    player.x = screenWidth / 2 - 20;
                    player.y = screenHeight - 50;

                    // Reactivate enemies and reset their positions
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        enemies[i].position = (Vector2){50.0f + (i % 11) * 60.0f, 50.0f + (i / 11) * 40.0f};
                        enemies[i].active = true;
                        enemies[i].directionX = 1;
                        enemies[i].directionY = 1;
                    }

                    // Reset barricade
                    for (int i = 0; i < MAX_BARRICADES; i++) {
                        barricadeHealth[i] = BARRICADE_HEALTH;
                    }
                }

                // Increment timer
                if (!gameover && playerLives > 0) {
                    // Player respawn countdown
                    if (respawnFrames > 0) {
                        respawnFrames--;
                        if (respawnFrames == 0) {
                            playerHit = false;
                            player.x = screenWidth / 2 - 20;
                            player.y = screenHeight - 50;
                        }
                    }

                    // Player movement
                    if (!playerHit) {
                        if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= 5;
                        if (IsKeyDown(KEY_RIGHT) && player.x + player.width < screenWidth) player.x += 5;
                    }

// Player shooting
if (!playerHit && IsKeyDown(KEY_SPACE) && shotCooldown <= 0) {
    for (int i = 0; i < MAX_SHOTS; i++) {
        if (shots[i].height == 0) {
            shots[i] = (Rectangle){player.x + player.width / 2 - 1, player.y, 2, 10}; // Set the shot's height to 10
            shotCooldown = PLAYER_SHOT_COOLDOWN; // Reset cooldown
            break;
        }
    }
}


// Decrement player shot cooldown
if (shotCooldown > 0) {
    shotCooldown--;
}


                    // Enemy movement and check collision with window edge
                    bool moveDown = false;
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) {
                            enemies[i].position.x += enemies[i].directionX * 1; // Move horizontally
                            if (enemies[i].position.x <= 0 || enemies[i].position.x >= screenWidth - 40) {
                                moveDown = true;
                            }
                        }
                    }

                    if (moveDown) {
                        for (int i = 0; i < MAX_ENEMIES; i++) {
                            if (enemies[i].active) {
                                enemies[i].position.y += 10 * enemies[i].directionY; // Move down slightly
                                enemies[i].directionX *= -1; // Change direction horizontally
                                if (enemies[i].position.y >= screenHeight - 80) {
                                    gameover = true;
                                    restart = true;
                                }
                            }
                        }
                    }

                    // Enemy shooting
                    if (enemyShotCooldown <= 0) {
                        for (int i = 0; i < MAX_ENEMIES; i++) {
                            if (enemies[i].active) {
                                if (GetRandomValue(0, 100) < 3) {
                                    // Look for an available shot slot
                                    for (int j = 0; j < MAX_SHOTS; j++) {
                                        if (enemyShots[j].height == 0) {
                                            // Create a shot and exit the loop
                                            enemyShots[j] = (Rectangle){enemies[i].position.x + 20 - 1, enemies[i].position.y + 20, 2, 10};
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        enemyShotCooldown = GetRandomValue(ENEMY_SHOT_COOLDOWN_MIN, ENEMY_SHOT_COOLDOWN_MAX);
                    }

                    // Check collisions between player shots & enemies
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (shots[i].height > 0) {
                            for (int j = 0; j < MAX_ENEMIES; j++) {
                                if (enemies[j].active && CheckCollisionRecs(shots[i], (Rectangle){enemies[j].position.x, enemies[j].position.y, 40, 20})) {
                                    shots[i].height = 0;
                                    enemies[j].active = false;
                                    score += 10; // Increment score when an enemy is destroyed
                                }
                            }
                        }
                    }

                    // Check collisions between player and enemy shots
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (enemyShots[i].height > 0 && CheckCollisionRecs(enemyShots[i], player)) {
                            enemyShots[i].height = 0; // Reset the enemy shot
                            playerHit = true; // Set player hit flag
                            playerLives--; // Decrement player lives
                            respawnFrames = respawnTime; // Start respawn countdown
                            break; // Exit the loop after one collision
                        }
                    }

                    // Check collisions between player shots and barricades (Not included for now)

                    // Display barricades
                    for (int i = 0; i < MAX_BARRICADES; i++) {
                        DrawRectangleRec(barricades[i], GRAY);
                    }

                    // Display score
                    DrawText(TextFormat("SCORE: %04i", score), 10, 10, 20, WHITE);

                    // Display lives
                    DrawText(TextFormat("LIVES: %i", playerLives), screenWidth - 100, 10, 20, WHITE);
                } else {
                    // Game over: loss
                    gameover = true;
                    restart = true;
                }

                BeginDrawing();
                ClearBackground(BLACK);

                if (gameover) {
                    DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
                    DrawText("PRESS ENTER TO RESTART", screenWidth / 2 - MeasureText("PRESS ENTER TO RESTART", 20) / 2, screenHeight / 2 + 20, 20, WHITE);
                } else {
                    // Blinking effect if hit
                    if (!playerHit || (playerHit && (playerBlinkFrames / 5) % 2 == 0)) {
                        DrawTextureEx(spaceshipTexture, (Vector2){player.x, player.y}, 0, 0.08f, WHITE);
                    }
            // Player shots
for (int i = 0; i < MAX_SHOTS; i++) {
    if (shots[i].height > 0) {
        DrawRectangleRec(shots[i], WHITE); // Draw the shot
    }
}


// Update player shots
for (int i = 0; i < MAX_SHOTS; i++) {
    if (shots[i].height > 0) {
        shots[i].y -= 5; // Move the shot upwards

        // Check if the shot is out of bounds
        if (shots[i].y + shots[i].height < 0) {
            shots[i].height = 0; // Reset the shot if it's out of bounds
        }
    }
}


// Update enemy shots
for (int i = 0; i < MAX_SHOTS; i++) {
    if (enemyShots[i].height > 0) {
        enemyShots[i].y += 5; // Move the enemy shot downwards

        // Check if the shot is out of bounds
        if (enemyShots[i].y > screenHeight) {
            enemyShots[i].height = 0; // Reset the enemy shot if it's out of bounds
        }
    }
}


                    // Enemies
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) {
                            // Draw the alien texture with adjusted size
                            if (i >= 0 && i < 22) {
                                DrawTexturePro(alienTexture1, (Rectangle){0, 0, static_cast<float>(alienTexture1.width), static_cast<float>(alienTexture1.height)},
                                               (Rectangle){enemies[i].position.x, enemies[i].position.y, 40, 20}, (Vector2){0, 0}, 0.0f, WHITE);
                            } else if (i >= 22 && i < 44) {
                                DrawTexturePro(alienTexture2, (Rectangle){0, 0, static_cast<float>(alienTexture2.width), static_cast<float>(alienTexture2.height)},
                                               (Rectangle){enemies[i].position.x, enemies[i].position.y, 40, 20}, (Vector2){0, 0}, 0.0f, WHITE);
                            } else {
                                DrawTexturePro(alienTexture3, (Rectangle){0, 0, static_cast<float>(alienTexture3.width), static_cast<float>(alienTexture3.height)},
                                               (Rectangle){enemies[i].position.x, enemies[i].position.y, 40, 20}, (Vector2){0, 0}, 0.0f, WHITE);
                            }
                        }
                    }
                }

                EndDrawing();

                break;
            }

            default:
                break;
        }

        // Update timers
        if (shotCooldown > 0) shotCooldown--;
        if (enemyShotCooldown > 0) enemyShotCooldown--;
        if (playerHit) {
            playerBlinkFrames++;
            if (playerBlinkFrames >= blinkTime * 2) {
                playerBlinkFrames = 0;
            }
        }
    }

    // Unload textures
    UnloadTexture(alienTexture1);
    UnloadTexture(alienTexture2);
    UnloadTexture(alienTexture3);
    UnloadTexture(spaceshipTexture);

    CloseWindow();

    return 0;
}
