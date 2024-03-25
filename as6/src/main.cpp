#include "raylib.h"
#include "raymath.h"

#define VELOCITY_INCREMENT 0.1f

typedef struct {
    Model model;
    Vector3 position;
    Vector3 velocity;
    float heading;
    float width;
    float height;
    float depth;
} Plane;

typedef struct {
    Model model;
    Vector3 position;
    Vector3 velocity;
    float heading;
    float width;
    float height;
    float depth;
    float scale;
    float maxSpeed;
    float acceleration;
    float turningRate;
} Ship;

typedef struct {
    Model model;
    Vector3 position;
    Vector3 velocity;
    float width;
    float height;
    float depth;
} Bird;

//ships
void increaseVelocityShip(Ship *ship);
void decreaseVelocityShip(Ship *ship);
void increaseHeadingShip(Ship *ship);
void decreaseHeadingShip(Ship *ship);
void resetVelocityShip(Ship *ship);

//planes
void increaseVelocityPlane(Plane *plane);
void decreaseVelocityPlane(Plane *plane);
void increaseHeadingPlane(Plane *plane);
void decreaseHeadingPlane(Plane *plane);
void resetVelocityPlane(Plane *plane);

//bounding box
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

//positions of ships and planes
void updateEntitiesPositions(Plane *planes, Ship *ships, Bird *bird) {
    for (int i = 0; i < 5; i++) {
        planes[i].position.x += planes[i].velocity.x;
        planes[i].position.z += planes[i].velocity.z;

        ships[i].position.x = planes[i].position.x;
        ships[i].position.z = planes[i].position.z;
    }
}

void updateBirdPosition(Bird *bird) {
    bird->position.x += bird->velocity.x;
    bird->position.y += bird->velocity.y;

    if (bird->position.x < -10) {
        bird->position.x = GetScreenWidth() + 10;
        bird->position.y = GetRandomValue(50, GetScreenHeight() - 50);
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 6");

    //bird model
    Bird bird;
    bird.model = LoadModel("meshes/meshes/bird.glb"); 
    bird.position = (Vector3){screenWidth + 10, static_cast<float>(GetRandomValue(50, screenHeight - 50)), 0};

    bird.velocity = (Vector3){-0.1f, 0, 0}; 
    bird.width = 5.0f; 
    bird.height = 5.0f; 
    bird.depth = 5.0f; 
    float birdScale = 2.0f;
    bird.model.transform = MatrixScale(birdScale, birdScale, birdScale);

    //initialize camera
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
    bool spaceBuffered = false;

    //textures
    Texture2D skyboxTexture = LoadTexture("textures/textures/skybox.png");
    Texture2D waterTexture = LoadTexture("textures/textures/water.jpg");

    //planes
    Plane planes[5]; //5 planes
    float planeSpacing = 100.0f;
    float planeHeight = -10.0f;

    for (int i = 0; i < 5; i++) {
        planes[i].model = LoadModel("meshes/meshes/PolyPlane.glb");
        planes[i].position = (Vector3){ -2 * planeSpacing + i * planeSpacing, planeHeight, -200.0f };
        planes[i].width = 10.0f;
        planes[i].height = 10.0f;
        planes[i].depth = 10.0f;
        planes[i].velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
        planes[i].heading = 0.0f;
    }

    //create and initialize ships
    Ship ships[5]; //5 ships
    float shipSpacing = 20.0f;
    float shipHeightOffset = -80.0f;

    float maxSpeeds[5] = {0.25f, 100.18f, 0.3f, 0.22f, 0.35f};
    float accelerations[5] = {0.02f, 0.015f, 0.025f, 0.018f, 0.03f};
    float turningRates[5] = {2.0f, 1.8f, 2.5f, 1.7f, 2.8f};

    for (int i = 0; i < 5; i++) {
        ships[i].maxSpeed = maxSpeeds[i];
        ships[i].acceleration = accelerations[i];
        ships[i].turningRate = turningRates[i];
    }

    //ship models
    const char* shipModelPaths[5] = {
        "meshes/meshes/ship5.glb",
        "meshes/meshes/ship4.glb",
        "meshes/meshes/ship3.glb",
        "meshes/meshes/ship2.glb",
        "meshes/meshes/ship1.glb"
    };

    float shipScales[5] = {0.4f, 1.0f, 0.1f, 0.003f, 6.0f}; 

    for (int i = 0; i < 5; i++) {
        ships[i].model = LoadModel(shipModelPaths[i]);
        ships[i].position = (Vector3){ planes[i].position.x, shipHeightOffset, planes[i].position.z };
        ships[i].width = 5.0f;
        ships[i].height = 5.0f;
        ships[i].depth = 5.0f;
        ships[i].scale = shipScales[i];
        ships[i].velocity = (Vector3){ 0.0f, 0.0f, 0.0f };

        if (i == 0){
            ships[i].model.transform = MatrixRotateX(-90 * DEG2RAD);
        } 
        
        if(i == 4) {
            ships[i].model.transform = MatrixRotateX(-90 * DEG2RAD); 
            ships[i].model.transform = MatrixMultiply(ships[i].model.transform, MatrixRotateY(-90 * DEG2RAD)); 
        }

        else if (i == 3) { 
            ships[i].model.transform = MatrixMultiply(ships[i].model.transform, MatrixRotateX(90 * DEG2RAD)); 
            ships[i].model.transform = MatrixMultiply(ships[i].model.transform, MatrixRotateY(180 * DEG2RAD)); 
        }
    }

    int selectedIndex = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) {
            selectedIndex++;
            if (selectedIndex >= 5) selectedIndex = 0; 
        }

        if (IsKeyDown(KEY_W)) {
            if (!wBuffered) {
                wBuffered = true;
                increaseVelocityPlane(&planes[selectedIndex]);
            }
        } else {
            wBuffered = false;
        }

        if (IsKeyDown(KEY_S)) {
            if (!sBuffered) {
                sBuffered = true;
                decreaseVelocityPlane(&planes[selectedIndex]);
            }
        } else {
            sBuffered = false;
        }

        if (IsKeyDown(KEY_A)) {
            if (!aBuffered) {
                aBuffered = true;
                increaseHeadingPlane(&planes[selectedIndex]);
            }
        } else {
            aBuffered = false;
        }

        if (IsKeyDown(KEY_D)) {
            if (!dBuffered) {
                dBuffered = true;
                decreaseHeadingPlane(&planes[selectedIndex]);
            }
        } else {
            dBuffered = false;
        }


        if (IsKeyPressed(KEY_SPACE)) {
            resetVelocityPlane(&planes[selectedIndex]);
        }

        updateEntitiesPositions(planes, ships, &bird); 

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawTexturePro(waterTexture, 
                        (Rectangle){0, 0, static_cast<float>(waterTexture.width), static_cast<float>(waterTexture.height - 50)}, 
                        (Rectangle){0, static_cast<float>(screenHeight) / 2 + 50, static_cast<float>(screenWidth), static_cast<float>(screenHeight) / 2 - 50},
                        (Vector2){0, 0}, 0, WHITE);

            BeginMode3D(camera);
            {
                float skyboxPosX = (screenWidth - skyboxTexture.width * 4) / 2;
                float skyboxPosY = (screenHeight - skyboxTexture.height * 4) / 2 + 200;

                DrawTexturePro(skyboxTexture, 
                            (Rectangle){0, 0, static_cast<float>(skyboxTexture.width), static_cast<float>(skyboxTexture.height)},
                            (Rectangle){skyboxPosX, skyboxPosY, 
                                        static_cast<float>(skyboxTexture.width * 4), 
                                        static_cast<float>(skyboxTexture.height * 4)}, 
                            (Vector2){0, static_cast<float>(skyboxTexture.height)}, 
                            0, WHITE); 

                //draw planes, ships, and bird
                for (int i = 0; i < 5; i++) {
                    // Draw planes
                    DrawModel(planes[i].model, planes[i].position, 2.0f, WHITE);

                    //draw ships
                    DrawModelEx(ships[4 - i].model, ships[4 - i].position, (Vector3){0, 1, 0}, -90.0f, Vector3Scale((Vector3){1, 1, 1}, ships[4 - i].scale), WHITE);

                    //draw bird
                    DrawModel(bird.model, bird.position, 1.0f, WHITE); 

                    //draw bounding boxes
                    if (i == selectedIndex) {
                        DrawBoundingBox(planes[i].position, planes[i].width * 8, planes[i].height * 2, planes[i].depth * 4, RED);
                        DrawBoundingBox(ships[i].position, ships[i].width * 14, ships[i].height * 4, ships[i].depth * 8, BLUE);
                    }
                }
            }
            EndMode3D();
        }
        EndDrawing();
    }

    for (int i = 0; i < 5; i++) {
        UnloadModel(planes[i].model);
        UnloadModel(ships[i].model);
    }
    UnloadTexture(skyboxTexture);
    UnloadTexture(waterTexture);

    CloseWindow(); 

    return 0;
}

//input component functions for ships
void increaseVelocityShip(Ship *ship) {
    ship->velocity.x += VELOCITY_INCREMENT * sinf(DEG2RAD * ship->heading);
    ship->velocity.z -= VELOCITY_INCREMENT * cosf(DEG2RAD * ship->heading);
}

void decreaseVelocityShip(Ship *ship) {
    ship->velocity.x -= VELOCITY_INCREMENT * sinf(DEG2RAD * ship->heading);
    ship->velocity.z += VELOCITY_INCREMENT * cosf(DEG2RAD * ship->heading);
}

void increaseHeadingShip(Ship *ship) {
    ship->heading += VELOCITY_INCREMENT;
    if (ship->heading > 360) ship->heading -= 360;
}

void decreaseHeadingShip(Ship *ship) {
    ship->heading -= VELOCITY_INCREMENT;
    if (ship->heading < 0) ship->heading += 360;
}

void resetVelocityShip(Ship *ship) {
    ship->velocity = (Vector3){0.0f, 0.0f, 0.0f};
}

//input component functions for planes
void increaseVelocityPlane(Plane *plane) {
    plane->velocity.x += VELOCITY_INCREMENT * sinf(DEG2RAD * plane->heading);
    plane->velocity.z -= VELOCITY_INCREMENT * cosf(DEG2RAD * plane->heading);
}

void decreaseVelocityPlane(Plane *plane) {
    plane->velocity.x -= VELOCITY_INCREMENT * sinf(DEG2RAD * plane->heading);
    plane->velocity.z += VELOCITY_INCREMENT * cosf(DEG2RAD * plane->heading);
}

void increaseHeadingPlane(Plane *plane) {
    plane->heading += VELOCITY_INCREMENT;
    if (plane->heading > 360) plane->heading -= 360;
}

void decreaseHeadingPlane(Plane *plane) {
    plane->heading -= VELOCITY_INCREMENT;
    if (plane->heading < 0) plane->heading += 360;
}

void resetVelocityPlane(Plane *plane) {
    plane->velocity = (Vector3){0.0f, 0.0f, 0.0f};
}

   

