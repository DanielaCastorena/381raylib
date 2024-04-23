#include "raylib.h"
#include "raymath.h"

#define VELOCITY_INCREMENT 0.1f

typedef struct {
    Model model;
    Vector3 position;
    Vector3 velocity;
    float heading;
    float pitch; //new variable for 3D physics
    float width;
    float height;
    float depth;
    float turningRate; 
    float roll; 
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
void increaseYawPlane(Plane *plane);
void decreaseYawPlane(Plane *plane);
void increaseRollPlane(Plane *plane);
void decreaseRollPlane(Plane *plane);


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
void updateEntitiesPositions(Plane *planes, Ship *ships) {
    for (int i = 0; i < 5; i++) {
        planes[i].position.x += planes[i].velocity.x;
        planes[i].position.z += planes[i].velocity.z;

        ships[i].position.x = planes[i].position.x;
        ships[i].position.z = planes[i].position.z;
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 8");

    //initialize camera
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 30.0f, -1000.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    //textures
    Texture2D skyboxTexture = LoadTexture("textures/skybox.png");
    Texture2D waterTexture = LoadTexture("textures/water.jpg");

    //planes
    Plane planes[5]; //5 planes
    float planeSpacing = 100.0f;
    float planeHeight = -10.0f;

    for (int i = 0; i < 5; i++) {
        planes[i].model = LoadModel("meshes/PolyPlane.glb");
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

    float maxSpeeds[5] = {0.25f, 0.4f, 0.55f, 0.7f, 0.85f}; 
    float accelerations[5] = {0.02f, 0.015f, 0.025f, 0.018f, 0.03f};
    float turningRates[5] = {2.0f, 1.8f, 2.5f, 1.7f, 2.8f};

    for (int i = 0; i < 5; i++) {
        ships[i].maxSpeed = maxSpeeds[i];
        ships[i].acceleration = accelerations[i];
        ships[i].turningRate = turningRates[i];
    }

    //ship models
    const char* shipModelPaths[5] = {
        "meshes/ship5.glb",
        "meshes/ship4.glb",
        "meshes/ship3.glb",
        "meshes/ship2.glb",
        "meshes/ship1.glb"
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

bool wBuffered[5] = { false };
bool sBuffered[5] = { false };
bool aBuffered[5] = { false };
bool dBuffered[5] = { false };
bool qBuffered[5] = { false };
bool eBuffered[5] = { false };
bool rBuffered[5] = { false };
bool fBuffered[5] = { false };
bool spaceBuffered[5] = { false };

while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_TAB)) {
        selectedIndex++;
        if (selectedIndex >= 5) selectedIndex = 0; 
    }

if (IsKeyPressed(KEY_W)) {
    if (!wBuffered[selectedIndex]) {
        wBuffered[selectedIndex] = true;
        increaseVelocityPlane(&planes[selectedIndex]);
    }
} else if (IsKeyReleased(KEY_W)) {
    wBuffered[selectedIndex] = false;
}

if (IsKeyPressed(KEY_S)) {
    if (!sBuffered[selectedIndex]) {
        sBuffered[selectedIndex] = true;
        decreaseVelocityPlane(&planes[selectedIndex]);
    }
} else if (IsKeyReleased(KEY_S)) {
    sBuffered[selectedIndex] = false;
}

if (IsKeyPressed(KEY_A)) {
    if (!aBuffered[selectedIndex]) {
        aBuffered[selectedIndex] = true;
        increaseHeadingPlane(&planes[selectedIndex]);
    }
} else if (IsKeyReleased(KEY_A)) {
    aBuffered[selectedIndex] = false;
}

if (IsKeyPressed(KEY_D)) {
    if (!dBuffered[selectedIndex]) {
        dBuffered[selectedIndex] = true;
        decreaseYawPlane(&planes[selectedIndex]);
    }
} else if (IsKeyReleased(KEY_D)) {
    dBuffered[selectedIndex] = false;
}

if (IsKeyPressed(KEY_Q)) {
    if (!qBuffered[selectedIndex]) {
        qBuffered[selectedIndex] = true;
        increaseRollPlane(&planes[selectedIndex]);
    }
} else if (IsKeyReleased(KEY_Q)) {
    qBuffered[selectedIndex] = false;
}

if (IsKeyPressed(KEY_E)) {
    if (!eBuffered[selectedIndex]) {
        eBuffered[selectedIndex] = true;
        decreaseRollPlane(&planes[selectedIndex]);
    }
} else if (IsKeyReleased(KEY_E)) {
    eBuffered[selectedIndex] = false;
}

if (IsKeyPressed(KEY_SPACE)) {
    if (!spaceBuffered[selectedIndex]) {
        spaceBuffered[selectedIndex] = true;
        resetVelocityPlane(&planes[selectedIndex]);
    }
} else if (IsKeyReleased(KEY_SPACE)) {
    spaceBuffered[selectedIndex] = false;
}
        updateEntitiesPositions(planes, ships); 

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

                //draw planes and ships
                for (int i = 0; i < 5; i++) {
                    // Draw planes
                    DrawModel(planes[i].model, planes[i].position, 2.0f, WHITE);

                    //draw ships
                    DrawModelEx(ships[4 - i].model, ships[4 - i].position, (Vector3){0, 1, 0}, -90.0f, Vector3Scale((Vector3){1, 1, 1}, ships[4 - i].scale), WHITE);

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

//input component functions for ships 2d
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

//input component functions for planes 3d
void increaseVelocityPlane(Plane *plane) {
    plane->velocity.x += VELOCITY_INCREMENT * sinf(DEG2RAD * plane->heading);
    plane->velocity.z -= VELOCITY_INCREMENT * cosf(DEG2RAD * plane->heading);
    plane->velocity.y += VELOCITY_INCREMENT * sinf(DEG2RAD * plane->pitch); // New line for 3D physics
}

void decreaseVelocityPlane(Plane *plane) {
    plane->velocity.x -= VELOCITY_INCREMENT * sinf(DEG2RAD * plane->heading);
    plane->velocity.z += VELOCITY_INCREMENT * cosf(DEG2RAD * plane->heading);
    plane->velocity.y -= VELOCITY_INCREMENT * sinf(DEG2RAD * plane->pitch); 
}

void increaseHeadingPlane(Plane *plane) {
    plane->heading += plane->turningRate * GetFrameTime(); 
    if (plane->heading > 360) plane->heading -= 360;
}

void decreaseHeadingPlane(Plane *plane) {
    plane->heading -= VELOCITY_INCREMENT;
    if (plane->heading < 0) plane->heading += 360;
}

void resetVelocityPlane(Plane *plane) {
    plane->velocity = (Vector3){0.0f, 0.0f, 0.0f};
}
//input component functions for planes 3d
void increaseYawPlane(Plane *plane) {
    plane->heading += VELOCITY_INCREMENT * plane->turningRate;
    if (plane->heading > 360) plane->heading -= 360;
}

void decreaseYawPlane(Plane *plane) {
    plane->heading -= VELOCITY_INCREMENT * plane->turningRate;
    if (plane->heading < 0) plane->heading += 360;
}

void increaseRollPlane(Plane *plane) {
    plane->roll += VELOCITY_INCREMENT * plane->turningRate;
    if (plane->roll > 360) plane->roll -= 360;
}

void decreaseRollPlane(Plane *plane) {
    plane->roll -= VELOCITY_INCREMENT * plane->turningRate;
    if (plane->roll < 0) plane->roll += 360;
}

void increasePitchPlane(Plane *plane) {
    plane->pitch += VELOCITY_INCREMENT * plane->turningRate;
    if (plane->pitch > 360) plane->pitch -= 360;
}

void decreasePitchPlane(Plane *plane) {
    plane->pitch -= VELOCITY_INCREMENT * plane->turningRate;
    if (plane->pitch < 0) plane->pitch += 360;
}


