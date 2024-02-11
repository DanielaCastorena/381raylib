#include <raylib.h>
#include <raymath.h>
#include <cfloat>

//ambda function to translate models
auto translateModel = [](Model& model, Vector3 translation) {
    model.transform = MatrixMultiply(model.transform, MatrixTranslate(translation.x, translation.y, translation.z));
};

//lambda function to rotate models
auto rotateModel = [](Model& model, Vector3 axis, float angle) {
    model.transform = MatrixMultiply(model.transform, MatrixRotateXYZ(axis));
};

//bounding box 
BoundingBox CalculateModelBoundingBox(Model model, float expansionFactor) {
    BoundingBox box = { 0 };

    for (int i = 0; i < model.meshCount; i++) {
        //mesh data
        Mesh mesh = model.meshes[i];

        //calculate min & max vertices
        Vector3 minVertex = { FLT_MAX, FLT_MAX, FLT_MAX };
        Vector3 maxVertex = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

        for (int j = 0; j < mesh.vertexCount; j++) {
            Vector3 vertex = { mesh.vertices[j * 3], mesh.vertices[j * 3 + 1], mesh.vertices[j * 3 + 2] };
            minVertex = Vector3Min(minVertex, vertex);
            maxVertex = Vector3Max(maxVertex, vertex);
        }

        minVertex = Vector3Subtract(minVertex, (Vector3){expansionFactor, expansionFactor, expansionFactor});
        maxVertex = Vector3Add(maxVertex, (Vector3){expansionFactor, expansionFactor, expansionFactor});

        //expand bounding box
        box.min = Vector3Min(box.min, minVertex);
        box.max = Vector3Max(box.max, maxVertex);
    }

    return box;
}

int main() {
    //initialize window
    InitWindow(800, 600, "CS381 - Assignment 1");

    //load models
    Model airplane = LoadModel("resources/SmitHouston_Tug.glb");
    Model ship = LoadModel("resources/SmitHouston_Tug.glb");

    //scale airplane
    airplane.transform = MatrixMultiply(airplane.transform, MatrixScale(3, 3, 3));

    //rotate ship
    ship.transform = MatrixMultiply(ship.transform, MatrixRotateXYZ((Vector3){90, 0, 90}));

    //camera function
    Camera camera = { (Vector3){ 0.0f, 120.0f, -500.0f }, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

    //rotation speeds 
    float airplaneRotationSpeed = -10.0f;
    float shipRotationSpeed = -10.0f;

    //main loop
    while (!WindowShouldClose()) {

        //rotate models
        rotateModel(airplane, (Vector3){0, 1, 0}, airplaneRotationSpeed * GetFrameTime());
        rotateModel(ship, (Vector3){0, 1, 0}, shipRotationSpeed * GetFrameTime());

        //draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //begin 3D mode
        BeginMode3D(camera);

        //draw airplanes
        translateModel(airplane, (Vector3){ -100, 100, 0 });
        DrawModel(airplane, (Vector3){ 0, 0, 0 }, 1.0f, WHITE); 
        BoundingBox airplaneBox1 = CalculateModelBoundingBox(airplane, 2.5f); 
        DrawBoundingBox(airplaneBox1, GREEN);

        translateModel(airplane, (Vector3){ 100, -100, 0 }); 
        DrawModel(airplane, (Vector3){ 0, 0, 0 }, 1.0f, WHITE); 
        BoundingBox airplaneBox2 = CalculateModelBoundingBox(airplane, 2.5f); 
        DrawBoundingBox(airplaneBox2, GREEN);

        //draw ships
        translateModel(ship, (Vector3){ -200, 0, 0 });
        DrawModel(ship, (Vector3){ 0, 0, 0 }, 1.0f, WHITE);
        BoundingBox shipBox1 = CalculateModelBoundingBox(ship, 2.5f); 
        DrawBoundingBox(shipBox1, GREEN);

        translateModel(ship, (Vector3){ 200, 0, 0 }); 
        DrawModel(ship, (Vector3){ 0, 0, 0 }, 1.0f, WHITE);
        BoundingBox shipBox2 = CalculateModelBoundingBox(ship, 2.5f); 
        DrawBoundingBox(shipBox2, GREEN);

        //end 3D mode
        EndMode3D();

        EndDrawing();
    }

    //cleanup
    CloseWindow();
    UnloadModel(airplane);
    UnloadModel(ship);

    return 0;
}