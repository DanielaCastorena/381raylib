#include "raylib.h"
#include <vector>

//Input buffers
std::vector<int> keyBuffer;
std::vector<int> mouseBuffer;

// Define components struct
struct TransformComponent {
    Vector2 position;
};

struct ColliderComponent {
    Rectangle collider;
};

struct MovementComponent {
    Vector2 velocity;
};

// Entity struct
struct Entity {
    TransformComponent transform;
    ColliderComponent collider;
    MovementComponent movement;
    Color color;
};

// Initialize entities
std::vector<Entity> InitializeEntities(int screenWidth, int screenHeight) {
    std::vector<Entity> entities;

    // Initialize paddle
    Entity paddle;
    paddle.transform.position = { static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) - 50 };
    paddle.collider.collider = { paddle.transform.position.x - 50, paddle.transform.position.y, 100, 20 };
    paddle.movement.velocity = { 5, 0 };
    paddle.color = RED;
    entities.push_back(paddle);

    // Initialize ball
    Entity ball;
    ball.transform.position = { static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2 };
    ball.collider.collider = { ball.transform.position.x - 10, ball.transform.position.y - 10, 20, 20 };
    ball.movement.velocity = { 3, -3 };
    ball.color = BLUE;
    entities.push_back(ball);

    // Initialize blocks
    int blockSize = 40;
    int blockRows = 3;
    int blockCols = 10;
    Color blockColor = GREEN;

    for (int i = 0; i < blockRows; i++) {
        for (int j = 0; j < blockCols; j++) {
            Entity block;
            block.transform.position = { static_cast<float>(j * blockSize * 2 + 50), static_cast<float>(i * blockSize + 50) };
            block.collider.collider = { block.transform.position.x, block.transform.position.y, static_cast<float>(blockSize), static_cast<float>(blockSize) };
            block.color = blockColor;
            entities.push_back(block);
        }
    }

    return entities;
}

// Start screen
void DrawStartScreen(int screenWidth, int screenHeight) {
    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
    DrawText("Arkanoid", screenWidth / 2 - MeasureText("Arkanoid", 40) / 2, screenHeight / 4, 40, WHITE);
    DrawText("Press Enter to Start", screenWidth / 2 - MeasureText("Press Enter to Start", 20) / 2, screenHeight / 2, 20, WHITE);
}

// Winning screen
void DrawYouWonScreen(int screenWidth, int screenHeight) {
    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
    DrawText("You Won!", screenWidth / 2 - MeasureText("You Won!", 40) / 2, screenHeight / 4, 40, WHITE);
    DrawText("Click here to play again", screenWidth / 2 - MeasureText("Click here to play again", 20) / 2, screenHeight / 2, 20, WHITE);
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "CS 381 - Assignment 9");
    InitAudioDevice();

    SetTargetFPS(60);

    Music backgroundMusic = LoadMusicStream("sounds/background.mp3");
    PlayMusicStream(backgroundMusic);

    std::vector<Entity> entities;
    bool gameStarted = false;
    bool gameOver = false;
    bool gameWon = false;
    Rectangle restartButton = { screenWidth / 2 - 100, screenHeight / 2 - 25, 200, 50 };

// Main game loop
while (!WindowShouldClose()) {
    // Update
    if (!gameStarted) {
        if (IsKeyPressed(KEY_ENTER)) {
            gameStarted = true;
            entities = InitializeEntities(screenWidth, screenHeight);
        }
    } else {
        if (!gameOver && !gameWon) {
            // Paddle movement
            if (IsKeyDown(KEY_LEFT) && entities[0].transform.position.x > 0) {
                entities[0].transform.position.x -= entities[0].movement.velocity.x;
                entities[0].collider.collider.x = entities[0].transform.position.x;
            }
            if (IsKeyDown(KEY_RIGHT) && entities[0].transform.position.x + entities[0].collider.collider.width < screenWidth) {
                entities[0].transform.position.x += entities[0].movement.velocity.x;
                entities[0].collider.collider.x = entities[0].transform.position.x;
            }

            // Move ball
            Entity& ball = entities[1];
            ball.transform.position.x += ball.movement.velocity.x;
            ball.transform.position.y += ball.movement.velocity.y;
            ball.collider.collider.x = ball.transform.position.x - ball.collider.collider.width / 2;
            ball.collider.collider.y = ball.transform.position.y - ball.collider.collider.height / 2;

            // Check collisions with walls for the ball
            if (ball.transform.position.x - ball.collider.collider.width / 2 <= 0 || ball.transform.position.x + ball.collider.collider.width / 2 >= screenWidth) {
                ball.movement.velocity.x = -ball.movement.velocity.x;
            }
            if (ball.transform.position.y - ball.collider.collider.height / 2 <= 0) {
                ball.movement.velocity.y = -ball.movement.velocity.y;
            }

            // Check if ball falls out of the window
            if (ball.transform.position.y + ball.collider.collider.height / 2 >= screenHeight) {
                gameOver = true;
            }

            // Check collisions with paddle
            if (CheckCollisionRecs(ball.collider.collider, entities[0].collider.collider)) {
                ball.movement.velocity.y = -ball.movement.velocity.y;
            }

            // Check collisions with blocks
            auto it = entities.begin() + 2; // Skip paddle and ball
            while (it != entities.end()) {
                if (CheckCollisionRecs(ball.collider.collider, it->collider.collider)) {
                    it = entities.erase(it);
                    ball.movement.velocity.y = -ball.movement.velocity.y;
                } else {
                    ++it;
                }
            }

            // Check for game over condition
            if (entities.size() <= 2) {
                gameWon = true;
            }
        }
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!gameStarted) {
        DrawStartScreen(screenWidth, screenHeight);
    } else {
        if (gameWon) {
            DrawYouWonScreen(screenWidth, screenHeight);

            // Check if continue button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), restartButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                gameWon = false;
                entities = InitializeEntities(screenWidth, screenHeight);
            }
        } else {
            // Draw entities
            for (const auto& entity : entities) {
                DrawRectangleRec(entity.collider.collider, entity.color);
            }

            // Draw game over screen if game over
            if (gameOver) {
                DrawRectangle(screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2, BLACK);
                DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 40) / 2, screenHeight / 4 + 20, 40, WHITE);
                DrawRectangleLines(restartButton.x, restartButton.y, restartButton.width, restartButton.height, WHITE);
                DrawText("Restart", restartButton.x + 50, restartButton.y + 15, 20, WHITE);

                // Check if restart button is clicked
                if (CheckCollisionPointRec(GetMousePosition(), restartButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    gameOver = false;
                    entities = InitializeEntities(screenWidth, screenHeight);
                }
            }
        }
    }

    EndDrawing();
}


    CloseWindow();
    
    StopMusicStream(backgroundMusic);
    UnloadMusicStream(backgroundMusic);

    CloseAudioDevice();

    return 0;
}
