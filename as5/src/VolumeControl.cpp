#include "VolumeControl.h"
#include "raylib.h"  
#include "raygui.h" 

Sound sfxSound;
Sound musicSound;
Sound dialogueSound;

GuiVolumeControlState InitGuiVolumeControl(void){
    GuiVolumeControlState state = { 0 };
    state.anchor01 = (Vector2){ 24, 24 };
    state.SFXSliderValue = 0.0f;
    state.MusicSliderValue = 0.0f;
    state.DialogueSliderValue = 0.0f;

    //load sounds
    sfxSound = LoadSound("audio/audio/alarm.mp3");
    musicSound = LoadSound("audio/audio/spongebob.mp3");
    dialogueSound = LoadSound("audio/audio/hello!.mp3");

    return state;
}

void GuiVolumeControl(GuiVolumeControlState *state){
    const char *VolumeGroupText = "Volume Controls";
    const char *SFXGroupText = "SFXVolume";
    const char *MusicGroupText = "MusicVolume";
    const char *DialogueGroupText = "DialogueVolume";
    const char *PingButtonText = "Ping";

    //volume controls
    GuiGroupBox((Rectangle){ state->anchor01.x + 0, state->anchor01.y + 5, 256, 250 }, VolumeGroupText);

    //SFX volume group and slider
    GuiGroupBox((Rectangle){ state->anchor01.x + 24, state->anchor01.y + 29, 212, 56 }, SFXGroupText);
    GuiLabel((Rectangle){ state->anchor01.x + 35, state->anchor01.y + 45, 30, 24 }, TextFormat("%.0f%%", state->SFXSliderValue));
    state->SFXSliderValue = GuiSlider((Rectangle){ state->anchor01.x + 65, state->anchor01.y + 45, 150, 24 }, NULL, NULL, state->SFXSliderValue, 0, 100);

    //music volume group and slider
    GuiGroupBox((Rectangle){ state->anchor01.x + 24, state->anchor01.y + 105, 212, 56 }, MusicGroupText);
    GuiLabel((Rectangle){ state->anchor01.x + 35, state->anchor01.y + 121, 30, 24 }, TextFormat("%.0f%%", state->MusicSliderValue));
    state->MusicSliderValue = GuiSlider((Rectangle){ state->anchor01.x + 65, state->anchor01.y + 121, 150, 24 }, NULL, NULL, state->MusicSliderValue, 0, 100);

    //dialogue volume group and slider
    GuiGroupBox((Rectangle){ state->anchor01.x + 24, state->anchor01.y + 181, 212, 56 }, DialogueGroupText);
    GuiLabel((Rectangle){ state->anchor01.x + 35, state->anchor01.y + 197, 30, 24 }, TextFormat("%.0f%%", state->DialogueSliderValue));
    state->DialogueSliderValue = GuiSlider((Rectangle){ state->anchor01.x + 65, state->anchor01.y + 197, 150, 24 }, NULL, NULL, state->DialogueSliderValue, 0, 100);

    //"ping" button 
    if (GuiButton((Rectangle){ 24, 295, 256, 30 }, PingButtonText)){
        //play sounds when the "ping" button is pressed
        PlaySound(sfxSound); 
        PlaySound(musicSound);
        PlaySound(dialogueSound);
    }

    //if space key is pressed play sounds
    if (IsKeyPressed(KEY_SPACE)) {
        PlaySound(sfxSound); 
        PlaySound(musicSound);
        PlaySound(dialogueSound);
    }
}


