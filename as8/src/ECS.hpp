#include <raylib-cpp.hpp>
#include <memory>
#include <iostream>
#include <vector>

#include "ECS.hpp"
#include "skybox.hpp"

using ECS = cs381::Scene<cs381::SkiplistComponentStorage>;

struct VelocityComponent {
    float speed = 0;
    raylib::Degree heading = 0;
};

struct RenderingComponent {
    raylib::Model model;
};

bool ProcessInput(ECS& ecs, size_t selectedPlane);
raylib::Vector3 CalculateVelocity(float targetSpeed, raylib::Degree targetHeading, const VelocityComponent& velocity, float dt);
void DrawSystem(const ECS& ecs);

int main() {
    // Create window
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;
    raylib::Window window(screenWidth, screenHeight, "CS381 - Assignment 3");

    // Create camera
    auto camera = raylib::Camera(
        raylib::Vector3(0, 120, -500), // Position
        raylib::Vector3(0, 0, 300), // Target
        raylib::Vector3::Up(), // Up direction
        45.0f,
        CAMERA_PERSPECTIVE
    );

    // Create skybox
    cs381::SkyBox skybox("textures/skybox.png");

    // Create ECS instance
    ECS ecs;

    // Create ground
    auto mesh = raylib::Mesh::Plane(10000, 10000, 50, 50, 25);
    raylib::Model ground = ((raylib::Mesh*)&mesh)->LoadModelFrom();
    raylib::Texture grass("textures/grass.png");
    grass.SetFilter(TEXTURE_FILTER_BILINEAR);
    grass.SetWrap(TEXTURE_WRAP_REPEAT);
    ground.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grass;

    // Add ground to ECS
    auto entity = ecs.CreateEntity();
    ecs.AddComponent<RenderingComponent>(entity, {ground});

    // Main loop
    bool keepRunning = true;
    size_t selectedPlane = 0;
    while (!window.ShouldClose() && keepRunning) {
        // Updates
        keepRunning = ProcessInput(ecs, selectedPlane);

        // Apply physics to entities
        for (auto entity : cs381::SceneView<VelocityComponent, RenderingComponent>{ecs}) {
            auto [velocity, rendering] = *entity;
            raylib::Vector3 newVelocity = CalculateVelocity(velocity.speed, velocity.heading, velocity, window.GetFrameTime());
            raylib::Vector3 newPosition = rendering.model.transform.position + newVelocity * window.GetFrameTime();
            rendering.model.transform = rendering.model.transform.Translate(newPosition).RotateY(velocity.heading);
        }

        // Rendering
        window.BeginDrawing();
        {
            // Clear screen
            window.ClearBackground(BLACK);

            camera.BeginMode();
            {
                // Render skybox and ground
                skybox.Draw();
                DrawSystem(ecs);
            }
            camera.EndMode();

            // Measure our FPS
            DrawFPS(10, 10);
        }
        window.EndDrawing();
    }

    return 0;
}

bool ProcessInput(ECS& ecs, size_t selectedPlane) {
    // Add input handling logic here
    return true;
}

raylib::Vector3 CalculateVelocity(float targetSpeed, raylib::Degree targetHeading, const VelocityComponent& velocity, float dt) {
    // Add physics calculation logic here
    return {};
}

void DrawSystem(const ECS& ecs) {
    for (auto entity : cs381::SceneView<RenderingComponent>{ecs}) {
        auto [rendering] = *entity;
        rendering.model.Draw({});
    }
}