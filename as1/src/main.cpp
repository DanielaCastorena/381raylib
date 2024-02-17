//#include "raylib.h"
//#include "raymath.h" 
#include "raylib-cpp.hpp"
#include "rlgl.h"

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 1");

    // Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 300.0f, 300.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;

    // Load models
    Model airplane = LoadModel("meshes/meshes/PolyPlane.glb");
    Model ship = LoadModel("meshes/meshes/SmitHouston_Tug.glb");

    // Initial positions for airplanes & ships per instructions
    Vector3 airplanePos1 = { 0.0f, 0.0f, 0.0f };
    Vector3 airplanePos2 = { -100.0f, 100.0f, 0.0f };
    Vector3 shipPos1 = { -200.0f, 0.0f, 0.0f };
    Vector3 shipPos2 = { 200.0f, 0.0f, 0.0f };
    Vector3 shipPos3 = { 100.0f, 100.0f, 0.0f };

    // Extra credit: "flying" animation!
    float airplaneSpeed = 20.0f; 
    float airplaneHeight = 50.0f; 
    float airplaneDirection1 = 1.0f; 
    float airplaneDirection2 = -1.0f; 
    float airplaneY1 = 0.0f;
    float airplaneY2 = 0.0f;

    // Extra credit: rotation animation!
    float shipRotationSpeed = 10.0f; 

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        airplaneY1 += airplaneSpeed * airplaneDirection1 * GetFrameTime();
        airplaneY2 += airplaneSpeed * airplaneDirection2 * GetFrameTime();

        if (airplaneY1 >= airplaneHeight || airplaneY1 <= 0){
            airplaneDirection1 *= -1; 
        }

        if (airplaneY2 >= airplaneHeight || airplaneY2 <= 0){
            airplaneDirection2 *= -1; 
        }

        // Rotation speed
        Matrix rotation = MatrixRotateY(DEG2RAD * shipRotationSpeed * GetFrameTime());
        ship.transform = MatrixMultiply(ship.transform, rotation);

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);

        // Airplanes
        DrawModel(airplane, (Vector3){ airplanePos1.x, airplaneY1, airplanePos1.z }, 1.0f, WHITE); 
        DrawModel(airplane, (Vector3){ airplanePos2.x, airplaneY2, airplanePos2.z }, 1.0f, WHITE); 

        // Ships
        DrawModel(ship, shipPos1, 1.0f, WHITE); 
        DrawModel(ship, shipPos2, 1.0f, WHITE); 
        DrawModel(ship, shipPos3, 1.0f, WHITE); 

        // Bounding boxes for airplanes
        BoundingBox bbox1 = GetMeshBoundingBox(airplane.meshes[0]);
        bbox1.min = Vector3Add(bbox1.min, (Vector3){ airplanePos1.x, airplaneY1, airplanePos1.z });
        bbox1.max = Vector3Add(bbox1.max, (Vector3){ airplanePos1.x, airplaneY1, airplanePos1.z });
        DrawBoundingBox(bbox1, WHITE);

        BoundingBox bbox2 = GetMeshBoundingBox(airplane.meshes[0]);
        bbox2.min = Vector3Add(bbox2.min, (Vector3){ airplanePos2.x, airplaneY2, airplanePos2.z });
        bbox2.max = Vector3Add(bbox2.max, (Vector3){ airplanePos2.x, airplaneY2, airplanePos2.z });
        DrawBoundingBox(bbox2, WHITE);

        // Bounding boxes for ships
        BoundingBox bbox3 = GetMeshBoundingBox(ship.meshes[0]);
        bbox3.min = Vector3Subtract(bbox3.min, (Vector3){ 20.0f, 20.0f, 20.0f }); // Scale the bounding box to make it bigger
        bbox3.max = Vector3Add(bbox3.max, (Vector3){ 20.0f, 20.0f, 20.0f }); // Scale the bounding box to make it bigger
        bbox3.min = Vector3Add(bbox3.min, shipPos1);
        bbox3.max = Vector3Add(bbox3.max, shipPos1);
        DrawBoundingBox(bbox3, WHITE);

        BoundingBox bbox4 = GetMeshBoundingBox(ship.meshes[0]);
        bbox4.min = Vector3Subtract(bbox4.min, (Vector3){ 20.0f, 20.0f, 20.0f }); 
        bbox4.max = Vector3Add(bbox4.max, (Vector3){ 15.0f, 20.0f, 15.0f }); 
        bbox4.min = Vector3Add(bbox4.min, shipPos2);
        bbox4.max = Vector3Add(bbox4.max, shipPos2);
        DrawBoundingBox(bbox4, WHITE);

        BoundingBox bbox5 = GetMeshBoundingBox(ship.meshes[0]);
        bbox5.min = Vector3Subtract(bbox5.min, (Vector3){ 20.0f, 20.0f, 20.0f }); 
        bbox5.max = Vector3Add(bbox5.max, (Vector3){ 20.0f, 20.0f, 20.0f }); 
        bbox5.min = Vector3Add(bbox5.min, shipPos3);
        bbox5.max = Vector3Add(bbox5.max, shipPos3);
        DrawBoundingBox(bbox5, WHITE);

        EndMode3D();

        EndDrawing();
    }

    // Unload resources
    UnloadModel(airplane);
    UnloadModel(ship);

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}





