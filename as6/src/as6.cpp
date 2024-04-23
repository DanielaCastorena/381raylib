#include "raylib.h"
#include "raymath.h"

#define VELOCITY_INCREMENT 0.1f

typedef struct {
    int entityId;
    void (*setup)(void *componentData);
    void (*tick)(void *componentData);
    void (*update)(void *componentData);
    void *data;
} Component;

typedef struct {
    int entityId;
    Component *components;
    int numComponents;
} Entity;

typedef struct {
    Vector3 position;
    Vector3 velocity;
    float heading;
} TransformComponent;

typedef struct {
    float width;
    float height;
    float depth;
} SizeComponent;

typedef struct {
    float maxSpeed;
    float acceleration;
    float turningRate;
} MovementComponent;

typedef struct {
    Model model;
    float scale;
} GraphicsComponent;

void transformSetup(void *componentData) {
    TransformComponent *transform = (TransformComponent *)componentData;
    transform->position = (Vector3){ 0 };
    transform->velocity = (Vector3){ 0 };
    transform->heading = 0.0f;
}

void transformTick(void *componentData) {
    // No per-frame logic for transform component
}

void transformUpdate(void *componentData) {
    TransformComponent *transform = (TransformComponent *)componentData;
    transform->position.x += transform->velocity.x;
    transform->position.z += transform->velocity.z;
}

void graphicsSetup(void *componentData) {
    GraphicsComponent *graphics = (GraphicsComponent *)componentData;
    graphics->model = LoadModel("meshes/PolyPlane.glb");
    graphics->scale = 2.0f;
}

void graphicsTick(void *componentData) {
    // No per-frame graphics logic
}

void graphicsUpdate(void *componentData) {
    GraphicsComponent *graphics = (GraphicsComponent *)componentData;
    DrawModel(graphics->model, graphics->position, graphics->scale, WHITE);
}

void movementSetup(void *componentData) {
    MovementComponent *movement = (MovementComponent *)componentData;
    movement->maxSpeed = 0.25f;
    movement->acceleration = 0.02f;
    movement->turningRate = 2.0f;
}

void movementTick(void *componentData) {
    // No per-frame movement logic
}

void movementUpdate(void *componentData) {
    MovementComponent *movement = (MovementComponent *)componentData;
    movement->velocity.x += movement->acceleration;
    movement->velocity.z += movement->acceleration;
    
    // Example: Limit velocity to maximum speed
    if (movement->velocity.x > movement->maxSpeed) {
        movement->velocity.x = movement->maxSpeed;
    }
    if (movement->velocity.z > movement->maxSpeed) {
        movement->velocity.z = movement->maxSpeed;
    }
}
void DrawBoundingBox(Vector3 position, float width, float height, float depth, Color color) {
    Vector3 corners[8];
    corners[0] = (Vector3){position.x - width / 2, position.y - height / 2, position.z - depth / 2};
    corners[1] = (Vector3){position.x + width / 2, position.y - height / 2, position.z - depth / 2};
    corners[2] = (Vector3){position.x + width / 2, position.y + height / 2, position.z - depth / 2};
    corners[3] = (Vector3){position.x - width / 2, position.y + height / 2, position.z - depth / 2};
    corners[4] = (Vector3){position.x - width / 2, position.y - height / 2, position.z + depth / 2};
    corners[5] = (Vector3){position.x + width / 2, position.y - height / 2, position.z + depth / 2};
    corners[6] = (Vector3){position.x + width / 2, position.y + height / 2, position.z + depth / 2};
    corners[7] = (Vector3){position.x - width / 2, position.y + height / 2, position.z + depth / 2};

    DrawLine3D(corners[0], corners[1], color);
    DrawLine3D(corners[1], corners[2], color);
    DrawLine3D(corners[2], corners[3], color);
    DrawLine3D(corners[3], corners[0], color);

    DrawLine3D(corners[4], corners[5], color);
    DrawLine3D(corners[5], corners[6], color);
    DrawLine3D(corners[6], corners[7], color);
    DrawLine3D(corners[7], corners[4], color);

    DrawLine3D(corners[0], corners[4], color);
    DrawLine3D(corners[1], corners[5], color);
    DrawLine3D(corners[2], corners[6], color);
    DrawLine3D(corners[3], corners[7], color);
}

void updateEntitiesPositions(Entity *planes, Entity *ships) {
    for (int i = 0; i < 5; i++) {
        // Update planes' positions
        for (int j = 0; j < planes[i].numComponents; j++) {
            if (planes[i].components[j].update != NULL) {
                planes[i].components[j].update(planes[i].components[j].data, &planes[i]);
            }
        }
        // Update ships' positions
        for (int j = 0; j < ships[i].numComponents; j++) {
            if (ships[i].components[j].update != NULL) {
                ships[i].components[j].update(ships[i].components[j].data, &ships[i]);
            }
        }
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 8");

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 30.0f, -1000.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    bool wBuffered = false;
    bool sBuffered = false;
    bool aBuffered = false;
    bool dBuffered = false;

    Texture2D skyboxTexture = LoadTexture("textures/skybox.png");
    Texture2D waterTexture = LoadTexture("textures/water.jpg");

    Entity planes[5];
    Entity ships[5];

    for (int i = 0; i < 5; i++) {
        planes[i].entityId = i;
        planes[i].numComponents = 2;
        planes[i].components = malloc(sizeof(Component) * planes[i].numComponents);

        planes[i].components[0].setup = transformSetup;
        planes[i].components[0].tick = transformTick;
        planes[i].components[0].update = transformUpdate;
        planes[i].components[0].data = malloc(sizeof(TransformComponent));

        planes[i].components[1].setup = graphicsSetup;
        planes[i].components[1].tick = graphicsTick;
        planes[i].components[1].update = graphicsUpdate;
        planes[i].components[1].data = malloc(sizeof(GraphicsComponent));

        for (int j = 0; j < planes[i].numComponents; j++) {
            planes[i].components[j].setup(planes[i].components[j].data);
        }
    }

// Similar setup for ships
for (int i = 0; i < 5; i++) {
    ships[i].entityId = i;
    ships[i].numComponents = 2; // Assuming ships have similar components as planes
    ships[i].components = malloc(sizeof(Component) * ships[i].numComponents);

    ships[i].components[0].setup = transformSetup;
    ships[i].components[0].tick = transformTick;
    ships[i].components[0].update = transformUpdate;
    ships[i].components[0].data = malloc(sizeof(TransformComponent));

    ships[i].components[1].setup = graphicsSetup;
    ships[i].components[1].tick = graphicsTick;
    ships[i].components[1].update = graphicsUpdate;
    ships[i].components[1].data = malloc(sizeof(GraphicsComponent));

    for (int j = 0; j < ships[i].numComponents; j++) {
        ships[i].components[j].setup(ships[i].components[j].data);
    }
}

while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_TAB)) {
        // Switch selected index
    }

    if (IsKeyPressed(KEY_W)) {
        // Handle key press
    }

    // Similar handling for other keys

    updateEntitiesPositions(planes, ships);

    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        // Draw water texture
        DrawTexturePro(waterTexture, 
                    (Rectangle){0, 0, static_cast<float>(waterTexture.width), static_cast<float>(waterTexture.height - 50)}, 
                    (Rectangle){0, static_cast<float>(screenHeight) / 2 + 50, static_cast<float>(screenWidth), static_cast<float>(screenHeight) / 2 - 50},
                    (Vector2){0, 0}, 0, WHITE);

        BeginMode3D(camera);
        {
            // Draw skybox texture
            float skyboxPosX = (screenWidth - skyboxTexture.width * 4) / 2;
            float skyboxPosY = (screenHeight - skyboxTexture.height * 4) / 2 + 200;

            DrawTexturePro(skyboxTexture, 
                        (Rectangle){0, 0, static_cast<float>(skyboxTexture.width), static_cast<float>(skyboxTexture.height)},
                        (Rectangle){skyboxPosX, skyboxPosY, 
                                    static_cast<float>(skyboxTexture.width * 4), 
                                    static_cast<float>(skyboxTexture.height * 4)}, 
                        (Vector2){0, static_cast<float>(skyboxTexture.height)}, 
                        0, WHITE);

                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < planes[i].numComponents; j++) {
                        planes[i].components[j].update(planes[i].components[j].data);
                    }

                    // Draw bounding boxes
                    DrawBoundingBox(*(Vector3 *)(planes[i].components[0].data),
                                    ((TransformComponent *)(planes[i].components[0].data))->position.x * 8,
                                    ((TransformComponent *)(planes[i].components[0].data))->position.y * 2,
                                    ((TransformComponent *)(planes[i].components[0].data))->position.z * 4,
                                    RED);
                }
            }
            EndMode3D();
        }
        EndDrawing();
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < planes[i].numComponents; j++) {
            free(planes[i].components[j].data);
        }
        free(planes[i].components);
    }

    // Unload resources
    for (int i = 0; i < 5; i++) {
        UnloadModel(((GraphicsComponent *)(planes[i].components[1].data))->model);
    }
    UnloadTexture(skyboxTexture);
    UnloadTexture(waterTexture);

    CloseWindow();

    return 0;
}
