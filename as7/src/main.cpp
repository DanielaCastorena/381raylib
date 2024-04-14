#include "raylib.h"
#include <vector>
#include <ctime>
#include <string>
#include <queue>

const int screenWidth = 800;
const int screenHeight = 600;
const int gridSize = 20;
const int appleSize = 22;
const float zoomFactor = 1.2f;

enum class Direction { None, Up, Down, Left, Right };

class Entity {
public:
    Vector2 position;

    Entity(int x, int y) : position({ static_cast<float>(x), static_cast<float>(y) }) {}
};

class Apple : public Entity {
public:
    Apple(int x, int y) : Entity(x, y) {}
};

class SnakeSegment : public Entity {
public:
    SnakeSegment(int x, int y) : Entity(x, y) {}
};

class Snake {
public:
    std::vector<SnakeSegment> segments;
    Direction direction;
    bool ateApple;

    Snake() : direction(Direction::Right), ateApple(false) {
        segments.push_back({ screenWidth / 2 - screenWidth / 2 % gridSize, screenHeight / 2 - screenHeight / 2 % gridSize });
    }

    void Move() {
        Vector2 newPos = segments[0].position;
        switch (direction) {
            case Direction::Up:
                newPos.y -= gridSize;
                break;
            case Direction::Down:
                newPos.y += gridSize;
                break;
            case Direction::Left:
                newPos.x -= gridSize;
                break;
            case Direction::Right:
                newPos.x += gridSize;
                break;
            default:
                break;
        }
        segments.insert(segments.begin(), { static_cast<int>(newPos.x), static_cast<int>(newPos.y) });

        if (!ateApple) {
            segments.pop_back();
        } else {
            ateApple = false;
        }
    }

    bool CheckCollision(const Vector2& applePos) const {
        Rectangle snakeHeadRect = { segments[0].position.x, segments[0].position.y, static_cast<float>(gridSize / 2), static_cast<float>(gridSize) };
        Rectangle appleRect = { applePos.x, applePos.y, static_cast<float>(appleSize), static_cast<float>(appleSize) };
        return CheckCollisionRecs(snakeHeadRect, appleRect);
    }

    bool CheckCollision() const {
        Vector2 headPos = segments[0].position;
        for (size_t i = 1; i < segments.size(); ++i) {
            if (headPos.x == segments[i].position.x && headPos.y == segments[i].position.y) {
                return true;
            }
        }
        if (headPos.x < 0 || headPos.x >= screenWidth || headPos.y < 0 || headPos.y >= screenHeight) {
            return true;
        }
        return false;
    }

    void ChangeDirection(Direction newDir) {
        if ((newDir == Direction::Up && direction != Direction::Down) ||
            (newDir == Direction::Down && direction != Direction::Up) ||
            (newDir == Direction::Left && direction != Direction::Right) ||
            (newDir == Direction::Right && direction != Direction::Left)) {
            direction = newDir;
        }
    }

    int GetScore() const {
        return segments.size() - 1;
    }

    void Draw(Texture2D& headTexture, Texture2D& bodyTexture, float zoomFactor) {
        float rotation = 0.0f;
        switch (direction) {
            case Direction::Up:
                rotation = 270.0f;
                break;
            case Direction::Down:
                rotation = 90.0f;
                break;
            case Direction::Left:
                rotation = 180.0f;
                break;
            case Direction::Right:
                rotation = 0.0f;
                break;
            default:
                break;
        }

        DrawTexturePro(headTexture, Rectangle{ 0, 0, static_cast<float>(headTexture.width), static_cast<float>(headTexture.height) }, 
            Rectangle{ segments[0].position.x, segments[0].position.y, static_cast<float>(gridSize * zoomFactor), static_cast<float>(gridSize * zoomFactor) },
            Vector2{ static_cast<float>(gridSize * zoomFactor / 2), static_cast<float>(gridSize * zoomFactor / 2) }, rotation, WHITE);

        for (size_t i = 1; i < segments.size(); ++i) {
            float posX = segments[i].position.x;
            float posY = segments[i].position.y;
            float bodyRotation = 0.0f;
            if (i < segments.size() - 1) {
                Vector2 delta = { segments[i + 1].position.x - segments[i].position.x, segments[i + 1].position.y - segments[i].position.y };
                if (delta.x < 0) bodyRotation = 180.0f;
                else if (delta.x > 0) bodyRotation = 0.0f;
                else if (delta.y < 0) bodyRotation = 270.0f;
                else if (delta.y > 0) bodyRotation = 90.0f;
            } else {
                Vector2 delta = { segments[i].position.x - segments[i - 1].position.x, segments[i].position.y - segments[i - 1].position.y };
                if (delta.x < 0) bodyRotation = 180.0f;
                else if (delta.x > 0) bodyRotation = 0.0f;
                else if (delta.y < 0) bodyRotation = 270.0f;
                else if (delta.y > 0) bodyRotation = 90.0f;
            }

            DrawTexturePro(bodyTexture, Rectangle{ 0, 0, static_cast<float>(bodyTexture.width), static_cast<float>(bodyTexture.height) }, 
                Rectangle{ posX, posY, static_cast<float>(gridSize * zoomFactor), static_cast<float>(gridSize * zoomFactor) },
                Vector2{ static_cast<float>(gridSize * zoomFactor / 2), static_cast<float>(gridSize * zoomFactor / 2) }, bodyRotation, WHITE);
        }
    }
};

Vector2 SpawnApple(const std::vector<SnakeSegment>& segments) {
    Vector2 applePos;
    bool validPos = false;
    while (!validPos) {
        int gridX = GetRandomValue(1, (screenWidth - gridSize) / gridSize);
        int gridY = GetRandomValue(1, (screenHeight - gridSize) / gridSize);
        float offsetX = static_cast<float>(GetRandomValue(gridSize / 4, gridSize * 3 / 4));
        float offsetY = static_cast<float>(GetRandomValue(gridSize / 4, gridSize * 3 / 4));
        
        applePos.x = gridX * gridSize + offsetX - appleSize / 2;
        applePos.y = gridY * gridSize + offsetY - appleSize / 2;

        bool collision = false;
        for (const auto& segment : segments) {
            if (CheckCollisionCircles(applePos, appleSize / 2, segment.position, gridSize / 2)) {
                collision = true;
                break;
            }
        }

        if (!collision) {
            validPos = true;
        }
    }
    return applePos;
}

void DrawGameOverScreen(int score) {
    DrawText("Game Over!", screenWidth / 2 - MeasureText("Game Over!", 40) / 2, screenHeight / 2 - 20, 40, RED);
    int scoreTextWidth = MeasureText("Score: ", 20);
    DrawText(("Score: " + std::to_string(score)).c_str(), screenWidth / 2 - scoreTextWidth / 2, screenHeight / 2 + 40, 20, BLACK);
    int restartTextWidth = MeasureText("Press Enter to Restart", 20);
    DrawText("Press Enter to Restart", screenWidth / 2 - restartTextWidth / 2, screenHeight / 2 + 80, 20, BLACK);
}

void DrawStartScreen() {
    DrawText("Snake", screenWidth / 2 - MeasureText("Snake", 60) / 2, screenHeight / 2 - 50, 60, BLACK);
    DrawText("Press Enter to Start", screenWidth / 2 - MeasureText("Press Enter to Start", 20) / 2, screenHeight / 2 + 50, 20, BLACK);
}

void DrawGame(Snake& snake, Apple& apple, Texture2D& snakeHeadTexture, Texture2D& snakeBodyTexture, Texture2D& appleTexture) {
    for (int x = 0; x <= screenWidth; x += gridSize * zoomFactor) {
        DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
    }
    for (int y = 0; y <= screenHeight; y += gridSize * zoomFactor) {
        DrawLine(0, y, screenWidth, y, LIGHTGRAY);
    }

    DrawText(("Score: " + std::to_string(snake.GetScore())).c_str(), 20 * zoomFactor, 20 * zoomFactor, 20 * zoomFactor, BLACK);

    const float scaleFactor = static_cast<float>(gridSize * zoomFactor) / static_cast<float>(appleTexture.width);
    DrawTextureEx(appleTexture, { apple.position.x, apple.position.y }, 0.0f, scaleFactor, WHITE);

    snake.Draw(snakeHeadTexture, snakeBodyTexture, zoomFactor);
}

int main() {
    InitWindow(screenWidth, screenHeight, "Snake");
    InitAudioDevice();
    
    //custom textures
    Texture2D snakeHeadTexture = LoadTexture("textures/textures/snakehead.png");
    Texture2D snakeBodyTexture = LoadTexture("textures/textures/snakebody.png");
    Texture2D appleTexture = LoadTexture("textures/textures/apple.gif");

    Music backgroundMusic = LoadMusicStream("path/to/your/background_music.mp3");
    PlayMusicStream(backgroundMusic);

    Snake snake;
    Apple apple = Apple(SpawnApple(snake.segments).x, SpawnApple(snake.segments).y);

    SetTargetFPS(10);

    bool gameOver = false;
    bool gameStarted = false;

    while (!WindowShouldClose()) {
        if (!gameOver) {
            if (!gameStarted) {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawStartScreen();

                EndDrawing();

                if (IsKeyPressed(KEY_ENTER)) {
                    gameStarted = true;
                }

                continue;
            }

            Direction nextDir = Direction::None;

            if (IsKeyPressed(KEY_UP)) nextDir = Direction::Up;
            else if (IsKeyPressed(KEY_DOWN)) nextDir = Direction::Down;
            else if (IsKeyPressed(KEY_LEFT)) nextDir = Direction::Left;
            else if (IsKeyPressed(KEY_RIGHT)) nextDir = Direction::Right;

            if (nextDir != Direction::None) {
                snake.ChangeDirection(nextDir);
            }

            snake.Move();

            if (snake.CheckCollision()) {
                gameOver = true;
            }

            if (snake.CheckCollision(apple.position)) {
                apple = Apple(SpawnApple(snake.segments).x, SpawnApple(snake.segments).y);
                snake.ateApple = true;
            }
        } else {
            DrawGameOverScreen(snake.GetScore());

            if (IsKeyPressed(KEY_ENTER)) {
                snake = Snake();
                apple = Apple(SpawnApple(snake.segments).x, SpawnApple(snake.segments).y);
                gameOver = false;
                gameStarted = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameOver) {
            DrawGame(snake, apple, snakeHeadTexture, snakeBodyTexture, appleTexture);
        } else {
            DrawGameOverScreen(snake.GetScore());
        }

        EndDrawing();
    }

    UnloadTexture(snakeHeadTexture);
    UnloadTexture(snakeBodyTexture);
    UnloadTexture(appleTexture);

    StopMusicStream(backgroundMusic);
    UnloadMusicStream(backgroundMusic);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
