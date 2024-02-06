#include "raylib.h"
#include <cmath>

const char* textToDisplay = "Hi, my name is Daniela!";

//changing colors function
Color LerpColor(Color a, Color b, float t) {
    return (Color){
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        (unsigned char)(a.a + (b.a - a.a) * t)
    };
}

int main(){
    int screenWidth = 800;
    int screenHeight = 600;

    //window resizing
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 0");
    SetTargetFPS(60);

    //ttf font & convert it to raylib font
    Font font = LoadFont("resources/cursive.ttf");

    //background image
    Texture2D background = LoadTexture("resources/background.jpg"); 

    float textScale = 1.0f;

    while (!WindowShouldClose()){
        if (IsWindowResized()){
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            SetWindowSize(screenWidth, screenHeight);
        }

        //extra credit! text animation
        textScale = 20.0f + 5.0f * sinf(GetTime());

        //center text on screen
        Vector2 textSize = MeasureTextEx(font, textToDisplay, textScale, 0);
        Vector2 textPosition = {(float)(screenWidth - textSize.x) / 2, (float)(screenHeight - textSize.y) / 2};

        //extra credit! change text color between 3 colors 
        float t = 0.5f + 0.5f * sinf(GetTime()); 
        Color textColor = LerpColor(LerpColor(PURPLE, BLUE, t), PINK, t);

        BeginDrawing();
        
        //background image
        DrawTexture(background, 0, 0, WHITE);

        ClearBackground(RAYWHITE);

        //ttf font
        DrawTextEx(font, textToDisplay, textPosition, textScale, 0, textColor);

        EndDrawing();
    }

    UnloadFont(font);
    UnloadTexture(background);

    CloseWindow();
    return 0;
}







