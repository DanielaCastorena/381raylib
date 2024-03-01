#include "raylib.h"
#include "raymath.h"

#define VELOCITY_INCREMENT 0.001f
#define BOUNDING_BOX_SCALE_FACTOR 2.0f

typedef struct{
    Model model;
    Vector3 position;
    float width;
    float height;
    float depth;
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

    //skybox texture
    Texture2D skyboxTexture = LoadTexture("textures/textures/skybox.png");

    //grass texture
    Texture2D grassTexture = LoadTexture("textures/textures/grass.jpg");

    //create and initialize planes
    Plane planes[3];
    planes[0].model = LoadModel("meshes/meshes/PolyPlane.glb");
    planes[1].model = LoadModel("meshes/meshes/PolyPlane.glb");
    planes[2].model = LoadModel("meshes/meshes/PolyPlane.glb");

    planes[0].position = (Vector3){ 0.0f, 0.0f, -200.0f };
    planes[1].position = (Vector3){ 100.0f, 0.0f, -200.0f };
    planes[2].position = (Vector3){ -100.0f, 0.0f, -200.0f };

    for (int i = 0; i < 3; i++){
        planes[i].width = 10.0f;
        planes[i].height = 10.0f;
        planes[i].depth = 10.0f;
    }

    float velocity = 0.0f;
    float strafeVelocity = 0.0f;
    float verticalVelocity = 0.0f;

    int selectedPlaneIndex = 0; 

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        //keyboard input
        if (IsKeyDown(KEY_W))
            velocity += VELOCITY_INCREMENT;
        else if (IsKeyDown(KEY_S))
            velocity -= VELOCITY_INCREMENT;

        if (IsKeyDown(KEY_D))
            strafeVelocity -= VELOCITY_INCREMENT;
        else if (IsKeyDown(KEY_A))
            strafeVelocity += VELOCITY_INCREMENT;

        if (IsKeyDown(KEY_Q))
            verticalVelocity += VELOCITY_INCREMENT;
        else if (IsKeyDown(KEY_E))
            verticalVelocity -= VELOCITY_INCREMENT;

        //selection when tab key is pressed
        if (IsKeyPressed(KEY_TAB)){
            selectedPlaneIndex = (selectedPlaneIndex + 1) % 3; 
        }

        Vector3 forwardDirection = Vector3Subtract(camera.target, camera.position);
        forwardDirection = Vector3Normalize(forwardDirection);

        Vector3 rightDirection = Vector3CrossProduct(camera.up, forwardDirection);
        rightDirection = Vector3Normalize(rightDirection);

        Vector3 upDirection = Vector3CrossProduct(forwardDirection, rightDirection);
        upDirection = Vector3Normalize(upDirection);

        planes[selectedPlaneIndex].position.x += forwardDirection.x * velocity + rightDirection.x * strafeVelocity;
        planes[selectedPlaneIndex].position.y += forwardDirection.y * velocity + rightDirection.y * strafeVelocity + upDirection.y * verticalVelocity;
        planes[selectedPlaneIndex].position.z += forwardDirection.z * velocity + rightDirection.z * strafeVelocity;

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                //skybox
                DrawTexturePro(skyboxTexture, 
                               (Rectangle){0.0f, 0.0f, (float)skyboxTexture.width, -(float)skyboxTexture.height}, 
                               (Rectangle){-(float)screenWidth / 2, -(float)screenHeight / 2, (float)screenWidth, (float)screenHeight}, 
                               (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

                //planes
                for (int i = 0; i < 3; i++){
                    DrawModel(planes[i].model, planes[i].position, 2.0f, WHITE);
                }

                //bounding box around the selected plane
                DrawBoundingBox((BoundingBox){
                    (Vector3){ planes[selectedPlaneIndex].position.x - planes[selectedPlaneIndex].width / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.y - planes[selectedPlaneIndex].height / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.z - planes[selectedPlaneIndex].depth / 1 * BOUNDING_BOX_SCALE_FACTOR },
                    (Vector3){ planes[selectedPlaneIndex].position.x + planes[selectedPlaneIndex].width / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.y + planes[selectedPlaneIndex].height / 1 * BOUNDING_BOX_SCALE_FACTOR,
                               planes[selectedPlaneIndex].position.z + planes[selectedPlaneIndex].depth / 1 * BOUNDING_BOX_SCALE_FACTOR }
                }, RED);

                //grass texture positioning
                float grassPosX = camera.position.x - (grassTexture.width / 2);
                float grassPosY = camera.position.y - 1100; 
                DrawTextureRec(grassTexture, (Rectangle){ 0.0f, 0.0f, (float)grassTexture.width, (float)grassTexture.height }, (Vector2){ grassPosX, grassPosY }, WHITE);
            }
            EndMode3D();
        }
        EndDrawing();
    }

    //unload resources
    for (int i = 0; i < 3; i++) {
        UnloadModel(planes[i].model);
    }
    UnloadTexture(skyboxTexture);
    UnloadTexture(grassTexture);
    CloseWindow();

    return 0;
}
