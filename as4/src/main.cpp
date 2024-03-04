#include "raylib.h"
#include <stdlib.h> //rand() & srand()
#include <time.h>   //time()

#define MAX_ENEMIES 55
#define MAX_SHOTS 50
#define ENEMY_SHOT_COOLDOWN_MIN 30
#define ENEMY_SHOT_COOLDOWN_MAX 120
#define PLAYER_SHOT_COOLDOWN 20 
#define MAX_BARRICADES 4
#define BARRICADE_HEALTH 3
#define BARRICADE_DAMAGE_AMOUNT 2 //pixels removed when a barricade gets hit
#define LIGHTGREEN (Color){144, 238, 144, 255} //light green +10 points
#define GREEN (Color){0, 255, 0, 255}          //green +20 points
#define DARKGREEN (Color){0, 100, 0, 255}      //dark green +40 points

typedef struct{
    Vector2 position;
    bool active;
    int directionX; //1 for right, -1 for left
    int directionY; //1 for down, -1 for up
} Enemy;

void DrawBlinkingRectangle(Rectangle rect, Color color, bool isVisible); //to let player know when they've been hit

int main(){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Space Invaders Remake");

    enum GameState {
        MENU,
        GAMEPLAY,
        GAME_OVER
    } gameState = MENU;

    //load texture: alien image
    Texture2D alienTexture = LoadTexture("textures/textures/alien.png");

    //initialize player
    Rectangle player = { screenWidth / 2 - 20, screenHeight - 50, 40, 20 };
    int playerLives = 3;
    bool playerHit = false; //player was hit
    int playerBlinkFrames = 0; //player blink
    const int blinkTime = 30; //time for player to blink
    const int respawnTime = 60; //time for player respawn
    int respawnFrames = 0; //player respawn

    //initialize shots
    Rectangle shots[MAX_SHOTS] = { 0 };
    int shotCooldown = 0;

    //initialize enemy shots
    Rectangle enemyShots[MAX_SHOTS] = { 0 };
    int enemyShotCooldown = GetRandomValue(ENEMY_SHOT_COOLDOWN_MIN, ENEMY_SHOT_COOLDOWN_MAX);

    //initialize enemies
    Enemy enemies[MAX_ENEMIES] = { 0 };
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].position = (Vector2) { 50.0f + (i % 11) * 60.0f, 50.0f + (i / 11) * 40.0f };
        enemies[i].active = true;
        enemies[i].directionX = 1; //move right
        enemies[i].directionY = 1; //move down
    }

    //initialize big red alien
    Rectangle bigAlien = { screenWidth, 30, 60, 30 };
    bool bigAlienActive = false;
    int bigAlienDirection = 1; //1 for right, -1 for left
    int alienTimer = 10.0f; //timer for big red alien

    //initialize barricades
    Rectangle barricades[MAX_BARRICADES] = {
        { screenWidth / 5, screenHeight - 100, 50, 50 },
        { 2 * screenWidth / 5, screenHeight - 100, 50, 50 },
        { 3 * screenWidth / 5, screenHeight - 100, 50, 50 },
        { 4 * screenWidth / 5, screenHeight - 100, 50, 50 }
    };
    int barricadeHealth[MAX_BARRICADES] = { BARRICADE_HEALTH, BARRICADE_HEALTH, BARRICADE_HEALTH, BARRICADE_HEALTH };

    //initialize score
    int score = 0;

    bool gameover = false;
    bool restart = false;

    //random number generator
    srand(time(NULL));

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        switch (gameState){
            case MENU: {
                BeginDrawing();
                ClearBackground(BLACK);

                //start screen
                DrawText("SPACE INVADERS REMAKE", screenWidth / 2 - MeasureText("SPACE INVADERS REMAKE", 40) / 2, screenHeight / 2 - 50, 40, PURPLE);
                DrawText("PRESS ENTER TO START", screenWidth / 2 - MeasureText("PRESS ENTER TO START", 20) / 2, screenHeight / 2 + 20, 20, WHITE);

                EndDrawing();

                if (IsKeyPressed(KEY_ENTER)){
                    gameState = GAMEPLAY;
                } 

                break;
            }

            case GAMEPLAY: {
                if (IsKeyPressed(KEY_ENTER) && gameover){ //for game over (loss)
                    //reset game variables
                    playerLives = 3;
                    score = 0;
                    gameover = false;
                    restart = false;

                    //reset player position
                    player.x = screenWidth / 2 - 20;
                    player.y = screenHeight - 50;

                    //reactivate enemies and reset their positions
                    for (int i = 0; i < MAX_ENEMIES; i++){
                        enemies[i].position = (Vector2){50.0f + (i % 11) * 60.0f, 50.0f + (i / 11) * 40.0f};
                        enemies[i].active = true;
                        enemies[i].directionX = 1; 
                        enemies[i].directionY = 1; 
                    }

                    //reactivate big red alien
                    bigAlienActive = false;
                    bigAlien.x = screenWidth;
                    bigAlienDirection = 1; 

                    //reset barricade
                    for (int i = 0; i < MAX_BARRICADES; i++) {
                        barricadeHealth[i] = BARRICADE_HEALTH;
                    }
                }

                // Increment timer
                alienTimer++;

                if (!gameover && playerLives > 0) {
                    //player respawn countdown
                    if (respawnFrames > 0) {
                        respawnFrames--;
                        if (respawnFrames == 0) {
                            playerHit = false; 
                            player.x = screenWidth / 2 - 20;
                            player.y = screenHeight - 50;
                        }
                    }

                    //player movement
                    if (!playerHit) { 
                        if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= 5;
                        if (IsKeyDown(KEY_RIGHT) && player.x + player.width < screenWidth) player.x += 5;
                    }

                    //player shooting
                    if (!playerHit && IsKeyDown(KEY_SPACE) && shotCooldown <= 0){ 
                        for (int i = 0; i < MAX_SHOTS; i++) {
                            if (shots[i].height == 0) {
                                shots[i] = (Rectangle) { player.x + player.width / 2 - 1, player.y, 2, 10 };
                                shotCooldown = PLAYER_SHOT_COOLDOWN;
                                break;
                            }
                        }
                    }

                    //enemy movement and check collision with window edge
                    bool moveDown = false;
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) {
                            enemies[i].position.x += enemies[i].directionX * 1; //move horizontally
                            if (enemies[i].position.x <= 0 || enemies[i].position.x >= screenWidth - 40) {
                                moveDown = true;
                            }
                        }
                    }

                    if (moveDown) {
                        for (int i = 0; i < MAX_ENEMIES; i++) {
                            if (enemies[i].active) {
                                enemies[i].position.y += 10 * enemies[i].directionY; //move down slightly
                                enemies[i].directionX *= -1; //change direction horizontally
                                if (enemies[i].position.y >= screenHeight - 80) {
                                    gameover = true;
                                    restart = true;
                                } 
                            }
                        }
                    }

                    //big red alien movement
                    if (alienTimer >= 1800) { 
                        alienTimer = 0; //reset timer
                        if (!bigAlienActive) {
                            bigAlienActive = true;
                            bigAlien.x = screenWidth;
                            bigAlienDirection = -1; 
                        }
                    }

                    if (bigAlienActive) {
                        // Slowly scroll the alien across the screen
                        bigAlien.x += bigAlienDirection * 1;
                        if (bigAlien.x < -bigAlien.width) {
                            bigAlienActive = false;
                        }
                    }

                    //enemy shooting
                    if (enemyShotCooldown <= 0) {
                        for (int i = 0; i < MAX_ENEMIES; i++) {
                            if (enemies[i].active) {
                                if (GetRandomValue(0, 100) < 3) {
                                    //look for an available shot slot
                                    for (int j = 0; j < MAX_SHOTS; j++) {
                                        if (enemyShots[j].height == 0) {
                                            //create a shot and exit the loop
                                            enemyShots[j] = (Rectangle) { enemies[i].position.x + 20 - 1, enemies[i].position.y + 20, 2, 10 };
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        enemyShotCooldown = GetRandomValue(ENEMY_SHOT_COOLDOWN_MIN, ENEMY_SHOT_COOLDOWN_MAX); 
                    }

                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (shots[i].height > 0) {
                            shots[i].y -= 5;
                            if (shots[i].y + shots[i].height < 0) shots[i].height = 0;
                        }
                        if (enemyShots[i].height > 0) {
                            enemyShots[i].y += 3;
                            if (enemyShots[i].y > screenHeight) enemyShots[i].height = 0;
                        }
                    }

                    //check for collisions between player shots & enemies
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (shots[i].height > 0) {
                            for (int j = 0; j < MAX_ENEMIES; j++) {
                                if (enemies[j].active && CheckCollisionRecs(shots[i], (Rectangle) { enemies[j].position.x, enemies[j].position.y, 40, 20 })) {
                                    shots[i].height = 0;
                                    enemies[j].active = false;
                                    score += 10; //increment score when an enemy is destroyed
                                }
                            }
                        }
                    }

                    //check for collisions between player shots and big red alien
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (shots[i].height > 0 && CheckCollisionRecs(shots[i], bigAlien)) {
                            shots[i].height = 0;
                            bigAlienActive = false;
                            score += 100; //increment score when the big red alien is destroyed
                        }
                    }

                    //check collisions between player & enemy shots
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (enemyShots[i].height > 0 && CheckCollisionRecs(enemyShots[i], player)) {
                            enemyShots[i].height = 0;
                            playerLives--;
                            playerHit = true; 
                            playerBlinkFrames = blinkTime; 
                            respawnFrames = respawnTime; //respawn frames
                            if (playerLives == 0) {
                                gameover = true;
                                restart = true;
                            } //game over if player loses all lives
                        }
                    }

                    //check collisions between player & barricades
                    for (int i = 0; i < MAX_BARRICADES; i++) {
                        if (CheckCollisionRecs(player, barricades[i])) {
                            if (player.x < barricades[i].x) player.x = barricades[i].x - player.width;
                            else player.x = barricades[i].x + barricades[i].width;
                        }
                        for (int j = 0; j < MAX_SHOTS; j++) {
                            if (enemyShots[j].height > 0 && CheckCollisionRecs(enemyShots[j], barricades[i])) {
                                //decrease barricade health & reset enemy shot
                                enemyShots[j].height = 0;
                                barricadeHealth[i]--;
                                barricades[i].height -= BARRICADE_DAMAGE_AMOUNT; //decrease barricade height
                                barricades[i].y += BARRICADE_DAMAGE_AMOUNT; 
                            }
                            if (shots[j].height > 0 && CheckCollisionRecs(shots[j], barricades[i])) {
                                //destroy player shot & decrease barricade health
                                shots[j].height = 0;
                                barricadeHealth[i]--;
                                barricades[i].height -= BARRICADE_DAMAGE_AMOUNT; //decrease barricade height
                                barricades[i].y += BARRICADE_DAMAGE_AMOUNT; 
                            }
                        }
                        
                        if (!bigAlienActive && GetRandomValue(0, 1000) < 2){ 
                            bigAlienActive = true;
                            bigAlienDirection = 1; 
                        }
                    }
                }

                BeginDrawing();
                ClearBackground(BLACK);

                if (gameover) {
                    DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
                    DrawText("PRESS ENTER TO RESTART", screenWidth / 2 - MeasureText("PRESS ENTER TO RESTART", 20) / 2, screenHeight / 2 + 20, 20, WHITE);
                } else {
                    //blinking effect if hit
                    if (!playerHit || (playerHit && (playerBlinkFrames / 5) % 2 == 0)) {
                        DrawRectangleRec(player, WHITE);
                    }

                    //player shots
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (shots[i].height > 0) DrawRectangleRec(shots[i], WHITE);
                    }

                    //enemy shots
                    for (int i = 0; i < MAX_SHOTS; i++) {
                        if (enemyShots[i].height > 0) DrawRectangleRec(enemyShots[i], RED);
                    }

                    //enemies
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) {
                            Color enemyColor;
                            if (i >= 44) //bottom 2 rows
                                enemyColor = LIGHTGREEN;
                            else if (i >= 33) //middle rows
                                enemyColor = GREEN;
                            else //top row
                                enemyColor = DARKGREEN;
                            
                            // Draw the alien texture with adjusted size
                            DrawTexturePro(alienTexture, (Rectangle){0, 0, static_cast<float>(alienTexture.width), static_cast<float>(alienTexture.height)}, 
                                        (Rectangle){enemies[i].position.x, enemies[i].position.y, 40, 20}, 
                                        (Vector2){0, 0}, 0.0f, enemyColor);
                        }
                    }

                    //big red alien
                    if (bigAlienActive) DrawRectangleRec(bigAlien, RED);

                    //display barricades
                    for (int i = 0; i < MAX_BARRICADES; i++) {
                        DrawRectangleRec(barricades[i], GRAY);
                    }

                    //display score
                    DrawText(TextFormat("SCORE: %04i", score), 10, 10, 20, WHITE);

                    //displaylives
                    DrawText(TextFormat("LIVES: %i", playerLives), screenWidth - 100, 10, 20, WHITE);
                }

                EndDrawing();

                enemyShotCooldown--;
                shotCooldown--;

                //decrement player blink frames
                if (playerHit) {
                    playerBlinkFrames--;
                    if (playerBlinkFrames <= 0) {
                        playerHit = false; 
                    }
                }

                break;
            }

            //game over: loss
            case GAME_OVER: {
                BeginDrawing();
                ClearBackground(BLACK);

                DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, WHITE);
                DrawText("PRESS ENTER TO RESTART", screenWidth / 2 - MeasureText("PRESS ENTER TO RESTART", 20) / 2, screenHeight / 2 + 20, 20, WHITE);

                EndDrawing();

                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = GAMEPLAY;
                }

                break;
            }
        }
    }

    CloseWindow();

    //unload texture
    UnloadTexture(alienTexture);

    return 0;
}