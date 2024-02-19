#include "raylib.h"
#include "raymath.h"

#define VELOCITY_INCREMENT 0.001f

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 2");

    Camera camera = {0};
    camera.position = (Vector3){ 0.0f, 50.0f, -600.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model model = LoadModel("meshes/meshes/PolyPlane.glb");
    Texture2D texture = LoadTexture("textures/textures/skybox.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Vector3 position = { 0.0f, 0.0f, -200.0f };
    float velocity = 0.0f;
    float strafeVelocity = 0.0f;
    float verticalVelocity = 0.0f;

    Texture2D background = LoadTexture("textures/textures/skybox.png");

    // Adjust the skybox position to center it on the screen
    Vector3 skyboxPosition = {-(float)screenWidth / 2, -(float)screenHeight / 2, 10000.0f}; // Move the skybox further back

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

        // Update position based on velocity and camera direction
        Vector3 forwardDirection = Vector3Subtract(camera.target, camera.position);
        forwardDirection = Vector3Normalize(forwardDirection);

        Vector3 rightDirection = Vector3CrossProduct(camera.up, forwardDirection);
        rightDirection = Vector3Normalize(rightDirection);

        Vector3 upDirection = Vector3CrossProduct(forwardDirection, rightDirection);
        upDirection = Vector3Normalize(upDirection);

        position.x += forwardDirection.x * velocity + rightDirection.x * strafeVelocity;
        position.y += forwardDirection.y * velocity + rightDirection.y * strafeVelocity + upDirection.y * verticalVelocity;
        position.z += forwardDirection.z * velocity + rightDirection.z * strafeVelocity;

        model.transform = MatrixTranslate(position.x, position.y, position.z);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                // Draw the background quads (skybox) first
                DrawTexturePro(background, 
                               (Rectangle){0.0f, 0.0f, (float)background.width, -(float)background.height}, 
                               (Rectangle){skyboxPosition.x, skyboxPosition.y, (float)screenWidth, (float)screenHeight}, 
                               (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

                // Draw the plane model after the skybox
                DrawModel(model, position, 1.0f, WHITE);
            }
            EndMode3D();

            // Draw UI elements
            DrawRectangle(30, 370, 260, 90, Fade(BLACK, 0.5f));
            DrawRectangleLines(30, 370, 260, 100, Fade(WHITE, 0.5f));
            DrawText("In/Out: W | S", 40, 380, 10, WHITE);
            DrawText("Left/Right: A | D", 40, 400, 10, WHITE);
            DrawText("Up/Down: Q | E", 40, 420, 10, WHITE);
        }
        EndDrawing();
    }

    UnloadModel(model);
    UnloadTexture(background);
    CloseWindow();

    return 0;
}


















