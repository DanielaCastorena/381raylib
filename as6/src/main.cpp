#include "raylib.h"
#include "raymath.h"
#include <cstdio>

#define MAX_ENTITIES 10

// Entity types
typedef enum {
    PLANE,
    SHIP,
    BIRD
} EntityType;

// Entity structure
typedef struct {
    EntityType type;
    Model model;
    Vector3 position;
    Vector3 velocity;
    float heading;
    float width;
    float height;
    float depth;
    Color color;
    float maxSpeed;
    float acceleration;
    float turningRate;
} Entity;

// Function prototypes
void initializeEntity(Entity *entity, EntityType type, Model model, Vector3 position, Color color,
                      float width, float height, float depth, float maxSpeed, float acceleration, float turningRate);
void updateEntity(Entity *entity);
void drawEntity(Entity *entity);

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Entity-Component Architecture");

    // Load models
    Model planeModel = LoadModel("meshes/meshes/PolyPlane.glb");
    Model birdModel = LoadModel("meshes/meshes/bird.glb");
    Model shipModels[5];
    for (int i = 0; i < 5; i++) {
        char path[64];
        sprintf(path, "meshes/meshes/ship%d.glb", i + 1);
        shipModels[i] = LoadModel(path);
    }

    // Initialize entities
    Entity entities[MAX_ENTITIES];
    initializeEntity(&entities[0], PLANE, planeModel, (Vector3){-200.0f, -10.0f, -200.0f}, WHITE, 10.0f, 10.0f, 10.0f, 0.25f, 0.02f, 2.0f);
    initializeEntity(&entities[1], PLANE, planeModel, (Vector3){-100.0f, -10.0f, -200.0f}, WHITE, 10.0f, 10.0f, 10.0f, 0.4f, 0.015f, 1.8f);
    initializeEntity(&entities[2], PLANE, planeModel, (Vector3){0.0f, -10.0f, -200.0f}, WHITE, 10.0f, 10.0f, 10.0f, 0.55f, 0.025f, 2.5f);
    initializeEntity(&entities[3], PLANE, planeModel, (Vector3){100.0f, -10.0f, -200.0f}, WHITE, 10.0f, 10.0f, 10.0f, 0.7f, 0.018f, 1.7f);
    initializeEntity(&entities[4], PLANE, planeModel, (Vector3){200.0f, -10.0f, -200.0f}, WHITE, 10.0f, 10.0f, 10.0f, 0.85f, 0.03f, 2.8f);
    initializeEntity(&entities[5], BIRD, birdModel, (Vector3){screenWidth + 10, GetRandomValue(50, screenHeight - 50), 0.0f}, WHITE, 5.0f, 5.0f, 5.0f, 0.1f, 0.05f, 1.0f);

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 30.0f, -1000.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            updateEntity(&entities[i]);
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                for (int i = 0; i < MAX_ENTITIES; i++) {
                    drawEntity(&entities[i]);
                }
            }
            EndMode3D();
        }
        EndDrawing();
    }

    UnloadModel(planeModel);
    UnloadModel(birdModel);
    for (int i = 0; i < 5; i++) {
        UnloadModel(shipModels[i]);
    }

    CloseWindow(); 

    return 0;
}

// Initialize entity
void initializeEntity(Entity *entity, EntityType type, Model model, Vector3 position, Color color,
                      float width, float height, float depth, float maxSpeed, float acceleration, float turningRate) {
    entity->type = type;
    entity->model = model;
    entity->position = position;
    entity->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    entity->color = color;
    entity->width = width;
    entity->height = height;
    entity->depth = depth;
    entity->maxSpeed = maxSpeed;
    entity->acceleration = acceleration;
    entity->turningRate = turningRate;
    entity->heading = 0.0f;
}

// Update entity
void updateEntity(Entity *entity) {
    // Update position
    entity->position.x += entity->velocity.x;
    entity->position.z += entity->velocity.z;

    // Update heading (for planes)
    if (entity->type == PLANE) {
        entity->heading += entity->turningRate;
        if (entity->heading >= 360.0f) entity->heading -= 360.0f;
    }

    // Update velocity (oriented physics)
    float angle = DEG2RAD * entity->heading;
    Vector3 acceleration = {sinf(angle) * entity->acceleration, 0.0f, -cosf(angle) * entity->acceleration};

    entity->velocity.x += acceleration.x;
    entity->velocity.z += acceleration.z;

    // Limit velocity to maxSpeed
    float speed = Vector3Length(entity->velocity);
    if (speed > entity->maxSpeed) {
        entity->velocity = Vector3Scale(entity->velocity, entity->maxSpeed / speed);
    }
}

// Draw entity
void drawEntity(Entity *entity) {
    DrawModel(entity->model, entity->position, 1.0f, entity->color);
}
