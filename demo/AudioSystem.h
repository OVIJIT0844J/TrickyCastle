#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: AudioSystem.h
 * DEVELOPER: Maheed Abrar (Student ID: 00725105101140)
 * ROLE & RESPONSIBILITY: Complete Audio Subsystem & Sound FX Integration
 *
 * FEATURES IMPLEMENTED:
 *   - Background Music (BGM) streaming via Windows MCI commands (playBgm, stopBgm)
 *   - Continuous BGM playback looping with alias handling
 *   - Asynchronous sound effects playback via PlaySoundA (playSfx)
 *   - Dynamic sound enable/disable toggle & audio state management
 * DEPENDENCIES: GameDefines.h (winmm.lib, mciSendStringA, PlaySoundA)
 * =========================================================================== */
#include "GameDefines.h"

/* -------------------- AUDIO SYSTEM -------------------- */
void playBgm(const char* file)
{
    if (!soundEnabled) return;
    char cmd[512];
    mciSendStringA("close bgm", NULL, 0, NULL);
    sprintf(cmd, "open \"%s\" type mpegvideo alias bgm", file);
    mciSendStringA(cmd, NULL, 0, NULL);
    mciSendStringA("play bgm repeat", NULL, 0, NULL);
}

void stopBgm()
{
    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);
}

void playSfx(const char* file)
{
    if (!soundEnabled) return;
    PlaySoundA(file, NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT);
}

void toggleSound()
{
    soundEnabled = !soundEnabled;
    if (soundEnabled)
    {
        playBgm("Audios\\background.mp3");
        playSfx("Audios\\key.wav");
    }
    else
    {
        stopBgm();
    }
}

