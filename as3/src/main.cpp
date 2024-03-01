#include "raylib.h"
#include "raymath.h"

#define VELOCITY_INCREMENT 0.01f
#define BOUNDING_BOX_SCALE_FACTOR 2.0f

typedef struct{
    Model model;
    Vector3 position;
    Vector3 velocity;
    float heading;
    float width;
    float height;
    float depth;
    Sound engineSound;
    bool isMoving;
} Plane;

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 3");

    Camera camera = {0};
    camera.position = (Vector3){ 0.0f, 30.0f, -700.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Texture2D skyboxTexture = LoadTexture("textures/textures/skybox.png");
    Texture2D grassTexture = LoadTexture("textures/textures/grass.jpg");

    //create and initialize planes
    Plane planes[3];
    float planeSpacing = 100.0f; // Increased spacing between planes
    float planeHeight = 5.0f; // Adjust the height of planes above the ground

    for (int i = 0; i < 3; i++){
        planes[i].model = LoadModel("meshes/meshes/PolyPlane.glb");
        planes[i].position = (Vector3){ -planeSpacing + i * planeSpacing, planeHeight, -200.0f }; // Adjusted initial positions with increased spacing and lower height
        planes[i].width = 10.0f;
        planes[i].height = 10.0f;
        planes[i].depth = 10.0f;
        planes[i].velocity = (Vector3){0.0f, 0.0f, 0.0f};
        planes[i].heading = 0.0f;
        planes[i].engineSound = LoadSound("sounds/engine.wav");
        planes[i].isMoving = false;
    }

    int selectedPlaneIndex = 0; 

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        if (IsKeyDown(KEY_W))
            planes[selectedPlaneIndex].velocity.x += VELOCITY_INCREMENT;
        else if (IsKeyDown(KEY_S))
            planes[selectedPlaneIndex].velocity.x -= VELOCITY_INCREMENT;

        if (IsKeyDown(KEY_D))
            planes[selectedPlaneIndex].heading -= VELOCITY_INCREMENT;
        else if (IsKeyDown(KEY_A))
            planes[selectedPlaneIndex].heading += VELOCITY_INCREMENT;

        if (IsKeyDown(KEY_SPACE)) {
            planes[selectedPlaneIndex].velocity = (Vector3){0.0f, 0.0f, 0.0f}; // Stop the selected plane
            planes[selectedPlaneIndex].isMoving = false; // Update moving flag
            StopSound(planes[selectedPlaneIndex].engineSound); // Stop engine sound
        }

        // Update positions based on velocity
        for (int i = 0; i < 3; i++){
            planes[i].position.x += planes[i].velocity.x;
            planes[i].position.y += planes[i].velocity.y;
            planes[i].position.z += planes[i].velocity.z;
        }

        // Update selected plane's position based on heading
        Vector3 forwardDirection = {sinf(planes[selectedPlaneIndex].heading), 0.0f, cosf(planes[selectedPlaneIndex].heading)};
        planes[selectedPlaneIndex].position.x += forwardDirection.x * planes[selectedPlaneIndex].velocity.x;
        planes[selectedPlaneIndex].position.z += forwardDirection.z * planes[selectedPlaneIndex].velocity.x;

        if (IsKeyPressed(KEY_TAB)){
            selectedPlaneIndex = (selectedPlaneIndex + 1) % 3; 
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                DrawTexturePro(skyboxTexture, 
                               (Rectangle){0.0f, 0.0f, (float)skyboxTexture.width, -(float)skyboxTexture.height}, 
                               (Rectangle){-(float)screenWidth / 2, -(float)screenHeight / 2, (float)screenWidth, (float)screenHeight}, 
                               (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

                for (int i = 0; i < 3; i++){
                    DrawModel(planes[i].model, planes[i].position, 2.0f, WHITE);
                }

                DrawBoundingBox((BoundingBox){
                    (Vector3){ planes[selectedPlaneIndex].position.x - planes[selectedPlaneIndex].width / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.y - planes[selectedPlaneIndex].height / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.z - planes[selectedPlaneIndex].depth / 1 * BOUNDING_BOX_SCALE_FACTOR },
                    (Vector3){ planes[selectedPlaneIndex].position.x + planes[selectedPlaneIndex].width / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.y + planes[selectedPlaneIndex].height / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.z + planes[selectedPlaneIndex].depth / 1 * BOUNDING_BOX_SCALE_FACTOR }
                }, RED);

                float grassPosX = camera.position.x - (grassTexture.width / 2);
                float grassPosY = camera.position.y - 1100; 
                DrawTextureRec(grassTexture, (Rectangle){ 0.0f, 0.0f, (float)grassTexture.width, (float)grassTexture.height }, (Vector2){ grassPosX, grassPosY }, WHITE);
            }
            EndMode3D();
        }
        EndDrawing();
    }

    for (int i = 0; i < 3; i++) {
        UnloadModel(planes[i].model);
        UnloadSound(planes[i].engineSound);
    }
    UnloadTexture(skyboxTexture);
    UnloadTexture(grassTexture);
    CloseWindow();

    return 0;
}

