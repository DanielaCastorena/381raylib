#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 2");

    // Camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 5.0f, -10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;

    // Set camera to be able to move freely
    SetCameraMode(camera, CAMERA_FREE);

    // Load textures for ground plane and skybox
    Texture2D groundTexture = LoadTexture("grass_texture.png");
    Texture2D skyTexture = LoadTexture("sky_texture.png");

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);

        // Draw skybox
        DrawCubeTexture(skyTexture, (Vector3){ 0.0f, 0.0f, 0.0f }, 100.0f, 100.0f, 100.0f, WHITE);

        // Draw ground plane
        DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 100.0f, 100.0f }, groundTexture, 1.0f, WHITE);

        // Draw airplane (simple rectangle for now)
        DrawCube((Vector3){ -5.0f, 1.0f, 0.0f }, 2.0f, 1.0f, 1.0f, RED); // Left side of the camera
        DrawCube((Vector3){ 5.0f, 1.0f, 0.0f }, 2.0f, 1.0f, 1.0f, GREEN); // Right side of the camera

        EndMode3D();

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(groundTexture);
    UnloadTexture(skyTexture);

    CloseWindow();

    return 0;
}




