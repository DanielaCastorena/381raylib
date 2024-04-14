#include "raylib.h"
#include <stdlib.h> // rand() & srand()
#include <time.h>   // time()

#define MAX_ENEMIES 55
#define MAX_SHOTS 50
#define ENEMY_SHOT_COOLDOWN_MIN 30
#define ENEMY_SHOT_COOLDOWN_MAX 120
#define PLAYER_SHOT_COOLDOWN 40 // Adjusted to slow down player shot frequency
#define MAX_BARRICADES 4
#define BARRICADE_HEALTH 3
#define BARRICADE_DAMAGE_AMOUNT 2 // pixels removed when a barricade gets hit

void PlayShotSound();

typedef struct {
    Vector2 position;
    bool active;
    int directionX; // 1 for right, -1 for left
    int directionY; // 1 for down, -1 for up
} Enemy;

// Define shotSound as a global variable
Sound shotSound;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Space Invaders Remake");
    InitAudioDevice();

    enum GameState {
        MENU,
        GAMEPLAY,
        GAME_OVER,
        YOU_WIN,
        YOU_WIN_CONTINUE
    } gameState = MENU;

    // Load textures
    Texture2D alienTexture1 = LoadTexture("textures/textures/alien1.png");
    Texture2D alienTexture2 = LoadTexture("textures/textures/alien2.png");
    Texture2D alienTexture3 = LoadTexture("textures/textures/alien3.png");
    Texture2D spaceshipTexture = LoadTexture("textures/textures/spaceship.png");

    // Load background music
    Music backgroundMusic = LoadMusicStream("sounds/sounds/background.mp3");
    PlayMusicStream(backgroundMusic);

    // Load shot sound
    shotSound = LoadSound("sounds/sounds/weird.wav");

    // Initialize player
    Rectangle player = {screenWidth / 2 - 20, screenHeight - 50, 40, 20};
    int playerLives = 3;
    int playerBlinkFrames = 0;
    const int blinkTime = 30;
    const int respawnTime = 60;
    int respawnFrames = 0;
    bool playerHit = false;

    // Initialize shots
    Rectangle shots[MAX_SHOTS] = {0};
    int shotCooldown = 0;

    // Initialize enemy shots
    Rectangle enemyShots[MAX_SHOTS] = {0};
    int enemyShotCooldown = GetRandomValue(ENEMY_SHOT_COOLDOWN_MIN, ENEMY_SHOT_COOLDOWN_MAX);

    // Initialize enemies
    Enemy enemies[MAX_ENEMIES] = {0};
    int activeEnemies = MAX_ENEMIES;
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

    // Random number generator
    srand(time(NULL));

    SetTargetFPS(60);

    // Alien movement speed
    float alienMovementSpeed = 1.0f;

    while (!WindowShouldClose()) {

        UpdateMusicStream(backgroundMusic);

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

                    // Reset player position
                    player.x = screenWidth / 2 - 20;
                    player.y = screenHeight - 50;

                    // Reactivate enemies and reset their positions
                    activeEnemies = MAX_ENEMIES;
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

                    gameState = GAMEPLAY; // Switch back to gameplay state
                }

                // Increment timer
                if (!gameover && playerLives > 0) {
                    // Player respawn countdown
                    if (respawnFrames > 0) {
                        respawnFrames--;
                        if (respawnFrames == 0) {
                            player.x = screenWidth / 2 - 20;
                            player.y = screenHeight - 50;
                        }
                    }

                    // Player movement
                    if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= 5;
                    if (IsKeyDown(KEY_RIGHT) && player.x + player.width < screenWidth) player.x += 5;

                    // Player shooting
                    if (!playerHit && IsKeyDown(KEY_SPACE) && shotCooldown <= 0) {
                        for (int i = 0; i < MAX_SHOTS; i++) {
                            if (shots[i].height == 0) {
                                shots[i] = (Rectangle){player.x + player.width / 2 - 1, player.y, 2, 10}; // Set the shot's height to 10
                                shotCooldown = PLAYER_SHOT_COOLDOWN; // Reset cooldown
                                // Play shot sound
                                PlaySound(shotSound);
                                break;
                            }
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

                    // Decrement player shot cooldown
                    if (shotCooldown > 0) {
                        shotCooldown--;
                    }

                    // Enemy movement and check collision with window edge
                    bool moveDown = false;
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) {
                            enemies[i].position.x += enemies[i].directionX * alienMovementSpeed; // Move horizontally
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

// Update enemy shots
for (int i = 0; i < MAX_SHOTS; i++) {
    if (enemyShots[i].height > 0) {
        enemyShots[i].y += 5; // Move the enemy shot downwards

        // Flag to track if the shot collided with anything
        bool shotCollided = false;

        // Check if the shot collides with any barricade
        for (int j = 0; j < MAX_BARRICADES; j++) {
            if (barricadeHealth[j] > 0 && CheckCollisionRecs(enemyShots[i], barricades[j])) {
                // Reset the enemy shot and reduce barricade health
                enemyShots[i].height = 0;
                barricadeHealth[j] -= BARRICADE_DAMAGE_AMOUNT;
                shotCollided = true; // Set flag to true
                break; // Exit the barricade loop
            }
        }

        // Check if the shot collides with the player
        if (!shotCollided && CheckCollisionRecs(enemyShots[i], player)) {
            enemyShots[i].height = 0; // Reset the enemy shot
            playerLives--; // Decrement player lives
            respawnFrames = respawnTime; // Start respawn countdown
            if (playerLives <= 0) {
                gameover = true;
            }
            continue; // Skip further processing if shot collided with the player
        }

        // Check if the shot is out of bounds
        if (enemyShots[i].y > screenHeight) {
            enemyShots[i].height = 0; // Reset the enemy shot if it's out of bounds
        }
    }
}





                    // Check collisions between player shots & enemies
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (shots[i].height > 0) {
                            for (int j = 0; j < MAX_ENEMIES; j++) {
                                if (enemies[j].active && CheckCollisionRecs(shots[i], (Rectangle){enemies[j].position.x, enemies[j].position.y, 40, 20})) {
                                    shots[i].height = 0;
                                    enemies[j].active = false;
                                    // Increment score based on the type of alien destroyed
                                    if (j >= 0 && j < 22) {
                                        score += 50; // Alien1.png is worth 50 points
                                    } else if (j >= 22 && j < 44) {
                                        score += 25; // Alien2.png is worth 25 points
                                    } else {
                                        score += 10; // Alien3.png is worth 10 points
                                    }
                                    activeEnemies--; // Decrement activeEnemies
                                }
                            }
                        }
                    }


                    // Check collisions between player and enemy shots
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (enemyShots[i].height > 0 && CheckCollisionRecs(enemyShots[i], player)) {
                            enemyShots[i].height = 0; // Reset the enemy shot
                            playerLives--; // Decrement player lives
                            respawnFrames = respawnTime; // Start respawn countdown
                            if (playerLives <= 0) {
                                gameover = true;
                            }
                            break; // Exit the loop after one collision
                        }
                    }

// Check collisions between player shots & barriers
for (int i = 0; i < MAX_SHOTS; i++) {
    if (shots[i].height > 0) {
        for (int j = 0; j < MAX_BARRICADES; j++) {
            if (barricadeHealth[j] > 0 && CheckCollisionRecs(shots[i], barricades[j])) {
                shots[i].height = 0; // Reset the player shot
                barricadeHealth[j] -= BARRICADE_DAMAGE_AMOUNT; // Reduce barricade health
                break; // Exit the loop after one collision
            }
        }
    }
}

// Check collisions between enemy shots & barriers
for (int i = 0; i < MAX_SHOTS; i++) {
    if (enemyShots[i].height > 0) {
        for (int j = 0; j < MAX_BARRICADES; j++) {
            if (barricadeHealth[j] > 0 && CheckCollisionRecs(enemyShots[i], barricades[j])) {
                enemyShots[i].height = 0; // Reset the enemy shot
                enemyShots[i].y = screenHeight + 1; // Move the shot off-screen to remove it from the game world
                barricadeHealth[j] -= BARRICADE_DAMAGE_AMOUNT; // Reduce barricade health
                break; // Exit the loop after one collision
            }
        }
    }
}
                    // Check if all enemies are destroyed
                    if (activeEnemies == 0) {
                        gameState = YOU_WIN;
                    }

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
                }

                BeginDrawing();
                ClearBackground(BLACK);

                if (gameover) {
                    DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
                    DrawText("PRESS ENTER TO RESTART", screenWidth / 2 - MeasureText("PRESS ENTER TO RESTART", 20) / 2, screenHeight / 2 + 20, 20, WHITE);
                } else if (gameState == YOU_WIN) {
                    DrawText("YOU WIN", screenWidth / 2 - MeasureText("YOU WIN", 40) / 2, screenHeight / 2 - 20, 40, GREEN);
                    DrawText("PRESS ENTER TO CONTINUE", screenWidth / 2 - MeasureText("PRESS ENTER TO CONTINUE", 20) / 2, screenHeight / 2 + 20, 20, WHITE);
                } else {
                    // Blinking effect if hit
                    if ((respawnFrames / 5) % 2 == 0) {
                        DrawTextureEx(spaceshipTexture, (Vector2){player.x, player.y}, 0, 0.08f, WHITE);
                    }

                    // Player shots
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (shots[i].height > 0) {
                            DrawRectangleRec(shots[i], WHITE); // Draw the shot
                        }
                    }

                    // Enemy shots
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (enemyShots[i].height > 0) {
                            DrawRectangleRec(enemyShots[i], RED); // Draw the enemy shot
                        }
                    }

                    // Enemies
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) {
                            if (i >= 0 && i < 22) {
                                DrawTexturePro(alienTexture1, (Rectangle){0, 0, (float)alienTexture1.width, (float)alienTexture1.height}, (Rectangle){enemies[i].position.x, enemies[i].position.y, 40, 20}, (Vector2){0, 0}, 0.0f, WHITE);
                            } else if (i >= 22 && i < 44) {
                                DrawTexturePro(alienTexture2, (Rectangle){0, 0, (float)alienTexture2.width, (float)alienTexture2.height}, (Rectangle){enemies[i].position.x, enemies[i].position.y, 40, 20}, (Vector2){0, 0}, 0.0f, WHITE);
                            } else {
                                DrawTexturePro(alienTexture3, (Rectangle){0, 0, (float)alienTexture3.width, (float)alienTexture3.height}, (Rectangle){enemies[i].position.x, enemies[i].position.y, 40, 20}, (Vector2){0, 0}, 0.0f, WHITE);
                            }
                        }
                    }

                }

                EndDrawing();

                break;
            }

            case YOU_WIN: {
                BeginDrawing();
                ClearBackground(BLACK);
                
                DrawText("YOU WIN", screenWidth / 2 - MeasureText("YOU WIN", 40) / 2, screenHeight / 2 - 20, 40, GREEN);
                DrawText("PRESS ENTER TO CONTINUE", screenWidth / 2 - MeasureText("PRESS ENTER TO CONTINUE", 20) / 2, screenHeight / 2 + 20, 20, WHITE);
                
                EndDrawing();

                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = YOU_WIN_CONTINUE;
                }

                break;
            }

            case YOU_WIN_CONTINUE: {
                // Preserve the score and number of lives
                int prevScore = score;
                int prevLives = playerLives;

                // Reset game variables except the score and lives
                gameover = false;
                player.x = screenWidth / 2 - 20;
                player.y = screenHeight - 50;
                activeEnemies = MAX_ENEMIES;
                for (int i = 0; i < MAX_ENEMIES; i++) {
                    enemies[i].position = (Vector2){50.0f + (i % 11) * 60.0f, 50.0f + (i / 11) * 40.0f};
                    enemies[i].active = true;
                    enemies[i].directionX = 1;
                    enemies[i].directionY = 1;
                }
                for (int i = 0; i < MAX_BARRICADES; i++) {
                    barricadeHealth[i] = BARRICADE_HEALTH;
                }

                // Restore the score and lives
                score = prevScore;
                playerLives = prevLives;

                // Increase the alien movement speed
                alienMovementSpeed += 0.2f;

                gameState = GAMEPLAY; // Switch back to gameplay state
                break;
            }
            default:
                break;
        }

        // Update timers
        if (shotCooldown > 0) shotCooldown--;
        if (enemyShotCooldown > 0) enemyShotCooldown--;

        // Transition from YOU_WIN to GAMEPLAY
        if (gameState == YOU_WIN && IsKeyPressed(KEY_ENTER)) {
            // Reset game variables
            playerLives = 3;
            score = 0;
            gameover = false;

            // Reset player position
            player.x = screenWidth / 2 - 20;
            player.y = screenHeight - 50;

            // Reactivate enemies and reset their positions
            activeEnemies = MAX_ENEMIES;
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

            gameState = GAMEPLAY; // Switch back to gameplay state
        }
    }

    UnloadTexture(alienTexture1);
    UnloadTexture(alienTexture2);
    UnloadTexture(alienTexture3);
    UnloadTexture(spaceshipTexture);
    UnloadMusicStream(backgroundMusic);
    UnloadSound(shotSound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
