#include "raylib.h"
#include "VolumeControl.h"

int main(){
    //resize window
    const int screenWidth = 300;
    const int screenHeight = 350;

    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 5");
    SetTargetFPS(60);

    //load audio files
    Sound soundEffect = LoadSound("audio/audio/alarm.mp3");
    Sound dialogueTrack = LoadSound("audio/audio/hello!.mp3");
    Music backgroundMusic = LoadMusicStream("audio/audio/spongebob.mp3");
    PlayMusicStream(backgroundMusic);

    //Load Volume Control GUI
    GuiVolumeControlState volumeControlState = InitGuiVolumeControl();

    //main loop
    while (!WindowShouldClose()) {
        //update music stream
        UpdateMusicStream(backgroundMusic);

        //if the space key is pressed to play sounds
        if (IsKeyPressed(KEY_SPACE)) {
            PlaySound(soundEffect);
            PlaySound(dialogueTrack);
        }

        //begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Draw Volume Control GUI
        GuiVolumeControl(&volumeControlState);

        //end drawing
        EndDrawing();
    }

    //unload audio files
    UnloadSound(soundEffect);
    UnloadSound(dialogueTrack);
    UnloadMusicStream(backgroundMusic);

    //close window
    CloseWindow();

    return 0;
}









