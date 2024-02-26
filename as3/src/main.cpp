#include "raylib.h"

#define MAX_PLANES 3

struct Airplane {
    Model model;
    Vector3 position;
    Vector3 velocity;
    float heading; // Angle in radians
    BoundingBox bounds;
};

Airplane planes[MAX_PLANES];
int selectedPlaneIndex = 0;

void UpdateAirplane(Airplane *plane, float dt) {
    // Update position based on velocity
    plane->position.x += plane->velocity.x * dt;
    plane->position.y += plane->velocity.y * dt;
    plane->position.z += plane->velocity.z * dt;

    // Update bounding box position
    // For simplicity, just set the min and max corners directly based on the position
    plane->bounds.min = { plane->position.x - 1.0f, plane->position.y - 1.0f, plane->position.z - 1.0f };
    plane->bounds.max = { plane->position.x + 1.0f, plane->position.y + 1.0f, plane->position.z + 1.0f };
}

void Init() {
    // Load airplane models
    for (int i = 0; i < MAX_PLANES; ++i) {
        planes[i].model = LoadModel("path_to_airplane_model.obj"); // Example path to airplane model
        planes[i].position = { i * 10.0f, 0.0f, 0.0f }; // Example position
        planes[i].velocity = { 0.0f, 0.0f, 0.0f };
        planes[i].heading = 0.0f; // Initial heading
        // Define bounding box based on position
        planes[i].bounds.min = { planes[i].position.x - 1.0f, planes[i].position.y - 1.0f, planes[i].position.z - 1.0f };
        planes[i].bounds.max = { planes[i].position.x + 1.0f, planes[i].position.y + 1.0f, planes[i].position.z + 1.0f };
    }
}

void Update(float dt) {
    // Update all airplanes
    for (int i = 0; i < MAX_PLANES; ++i) {
        UpdateAirplane(&planes[i], dt);
    }
}

void Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw skybox
    // Note: You need to provide a skybox texture and replace "path_to_skybox_texture.dds"
    // with the actual file path
    DrawCubeTexture(planes[selectedPlaneIndex].model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture, {0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, WHITE);

    // Draw airplanes
    for (int i = 0; i < MAX_PLANES; ++i) {
        DrawModel(planes[i].model, planes[i].position, 1.0f, WHITE);
    }

    // Draw bounding box of selected plane
    DrawBoundingBox(planes[selectedPlaneIndex].bounds, RED);

    EndDrawing();
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const float dt = 1.0f / 60.0f; // Delta time

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 3");

    SetTargetFPS(60);

    Init();

    while (!WindowShouldClose()) {
        Update(dt);
        Draw();
    }

    CloseWindow();

    return 0;
}



