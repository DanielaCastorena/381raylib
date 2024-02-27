#include "raylib.h"
#include "raymath.h"

#define VELOCITY_INCREMENT 0.001f

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 2");

    Camera camera = {0};
    camera.position = (Vector3){ 0.0f, 30.0f, -700.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model model1 = LoadModel("meshes/meshes/PolyPlane.glb");
    Model model2 = LoadModel("meshes/meshes/PolyPlane.glb");
    Model model3 = LoadModel("meshes/meshes/PolyPlane.glb");

    // Load skybox texture
    Texture2D skyboxTexture = LoadTexture("textures/textures/skybox.png");

    // Load grass texture
    Texture2D grassTexture = LoadTexture("textures/textures/grass.jpg");

    Vector3 position1 = { 0.0f, 0.0f, -200.0f };
    Vector3 position2 = { 100.0f, 0.0f, -200.0f };
    Vector3 position3 = { -100.0f, 0.0f, -200.0f };

    float velocity = 0.0f;
    float strafeVelocity = 0.0f;
    float verticalVelocity = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Handle keyboard input
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

        // Update positions based on velocity and camera direction
        Vector3 forwardDirection = Vector3Subtract(camera.target, camera.position);
        forwardDirection = Vector3Normalize(forwardDirection);

        Vector3 rightDirection = Vector3CrossProduct(camera.up, forwardDirection);
        rightDirection = Vector3Normalize(rightDirection);

        Vector3 upDirection = Vector3CrossProduct(forwardDirection, rightDirection);
        upDirection = Vector3Normalize(upDirection);

        position1.x += forwardDirection.x * velocity + rightDirection.x * strafeVelocity;
        position1.y += forwardDirection.y * velocity + rightDirection.y * strafeVelocity + upDirection.y * verticalVelocity;
        position1.z += forwardDirection.z * velocity + rightDirection.z * strafeVelocity;

        position2.x += forwardDirection.x * velocity + rightDirection.x * strafeVelocity;
        position2.y += forwardDirection.y * velocity + rightDirection.y * strafeVelocity + upDirection.y * verticalVelocity;
        position2.z += forwardDirection.z * velocity + rightDirection.z * strafeVelocity;

        position3.x += forwardDirection.x * velocity + rightDirection.x * strafeVelocity;
        position3.y += forwardDirection.y * velocity + rightDirection.y * strafeVelocity + upDirection.y * verticalVelocity;
        position3.z += forwardDirection.z * velocity + rightDirection.z * strafeVelocity;

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                // Draw the skybox
                DrawTexturePro(skyboxTexture, 
                               (Rectangle){0.0f, 0.0f, (float)skyboxTexture.width, -(float)skyboxTexture.height}, 
                               (Rectangle){-(float)screenWidth / 2, -(float)screenHeight / 2, (float)screenWidth, (float)screenHeight}, 
                               (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

                // Draw the models (planes)
                DrawModel(model1, position1, 2.0f, WHITE);
                DrawModel(model2, position2, 2.0f, WHITE);
                DrawModel(model3, position3, 2.0f, WHITE);

                // Calculate the position to draw the grass texture relative to the camera
                float grassPosX = camera.position.x - (grassTexture.width / 2);
                float grassPosY = camera.position.y - 1099; // Move the grass down by 200 units

                // Draw the grass texture
                DrawTextureRec(grassTexture, (Rectangle){ 0.0f, 0.0f, (float)grassTexture.width, (float)grassTexture.height }, (Vector2){ grassPosX, grassPosY }, WHITE);
            }
            EndMode3D();
        }
        EndDrawing();
    }

    UnloadModel(model1);
    UnloadModel(model2);
    UnloadModel(model3);
    UnloadTexture(skyboxTexture);
    UnloadTexture(grassTexture);
    CloseWindow();

    return 0;
}



