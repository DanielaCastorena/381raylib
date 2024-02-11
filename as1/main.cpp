#include "raylib.h"
#include "raymath.h" // Include this for matrix math functions

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 1");

    // Define the camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 500.0f, 500.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;

    // Load models
    Model airplane = LoadModel("resources/PolyPlane.glb");
    Model ship = LoadModel("resources/SmitHouston_Tug.glb");

    // Set positions, scales, and rotations for airplanes and ships
    Vector3 airplanePos1 = { 0.0f, 0.0f, 0.0f };
    Vector3 airplanePos2 = { -100.0f, 100.0f, 0.0f };
    Vector3 shipPos1 = { -200.0f, 0.0f, 0.0f };
    Vector3 shipPos2 = { 200.0f, 0.0f, 0.0f };
    Vector3 shipPos3 = { 100.0f, 100.0f, 0.0f };

    // Main game loop
    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw airplanes
        DrawModel(airplane, airplanePos1, 1.0f, WHITE); // Default
        DrawModel(airplane, airplanePos2, 1.0f, WHITE); // Translated, scaled, and yawed

        // Draw ships
        DrawModel(ship, shipPos1, 1.0f, WHITE); // Default
        DrawModel(ship, shipPos2, 1.0f, WHITE); // Yawed
        DrawModel(ship, shipPos3, 1.0f, WHITE); // Translated, scaled, and yawed

        // Draw bounding boxes for airplanes
        for (int i = 0; i < airplane.meshCount; i++) {
            Mesh mesh = airplane.meshes[i];
            BoundingBox bbox = GetMeshBoundingBox(mesh);
            bbox.min = Vector3Add(bbox.min, i == 0 ? airplanePos1 : airplanePos2);
            bbox.max = Vector3Add(bbox.max, i == 0 ? airplanePos1 : airplanePos2);
            DrawBoundingBox(bbox, GREEN);
        }

        // Draw bounding boxes for ships
        for (int i = 0; i < ship.meshCount; i++) {
            Mesh mesh = ship.meshes[i];
            BoundingBox bbox = GetMeshBoundingBox(mesh);
            bbox.min = Vector3Add(bbox.min, i == 0 ? shipPos1 : (i == 1 ? shipPos2 : shipPos3));
            bbox.max = Vector3Add(bbox.max, i == 0 ? shipPos1 : (i == 1 ? shipPos2 : shipPos3));
            DrawBoundingBox(bbox, GREEN);
        }

        EndMode3D();

        EndDrawing();
    }

    // De-Initialization
    UnloadModel(airplane);
    UnloadModel(ship);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}









