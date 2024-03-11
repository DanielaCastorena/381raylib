#include "raylib.h"
#include "raygui.h"

#define RAYGUI_IMPLEMENTATION

// Function declarations
void LoadAudio();
void UnloadAudio();
void UpdateVolume();

// Global variables
Sound fxSound;
Music music;

float fxVolume = 0.5f;
float musicVolume = 0.5f;

int main() {
    // Initialize window
    InitWindow(300, 350, "CS381 - Assignment 5");
    SetTargetFPS(60);

    // Load audio files
    LoadAudio();

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        UpdateVolume();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw GUI
        fxVolume = GuiSlider((Rectangle){10, 10, 150, 20}, "Sound Effect", nullptr, fxVolume, 0.0f, 1.0f);
        musicVolume = GuiSlider((Rectangle){10, 40, 150, 20}, "Music", nullptr, musicVolume, 0.0f, 1.0f);

        if (GuiButton((Rectangle){10, 70, 100, 30}, "Play Sound Effect")) {
            PlaySound(fxSound);
        }

        EndDrawing();
    }

    // Unload resources
    UnloadAudio();
    CloseWindow();

    return 0;
}

void LoadAudio() {
    fxSound = LoadSound("sound_effect.wav");
    music = LoadMusicStream("background_music.mp3");

    PlayMusicStream(music);
}

void UnloadAudio() {
    UnloadSound(fxSound);
    UnloadMusicStream(music);
}

void UpdateVolume() {
    SetSoundVolume(fxSound, fxVolume);
    SetMusicVolume(music, musicVolume);

    UpdateMusicStream(music);
}


