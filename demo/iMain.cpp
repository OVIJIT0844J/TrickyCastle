#define _CRT_SECURE_NO_WARNINGS
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * FILE: iMain.cpp
 * GAME DIRECTOR, THEORY & GRAPHICS LEAD: Ovijit Sharma (Student ID: 00725105101134)
 * LEAD SYSTEM INTEGRATION: Maheed Abrar (Student ID: 00725105101140)
 * CO-DEVELOPERS: Shahriar Rythm, Nabeel Saad Borno
 * ROLE & RESPONSIBILITY: Master Display Loop, System Bootstrap & Pipeline Orchestration
 *
 * ARCHITECTURE & DIRECTION BY OVIJIT SHARMA:
 *   - Master display routing pipeline via iDraw()
 *   - Game flow control: Intro story, carousel, levels, penalty mini-game, victory/death
 *   - Visual staging & aesthetic presentation coordination
 *
 * SYSTEM INTEGRATION BY MAHEED ABRAR:
 *   - Application entry point: main(int argc, char* argv[])
 *   - Window setup and OpenGL context bootstrap via iInitialize()
 *   - Texture asset pipeline: preloads 30+ PNG/JPG sprites and hero skins (iLoadImage)
 *   - Saved user progress loading & level 0 initial state setup
 *   - Audio system initialization & background music startup
 *   - 60 FPS fixed timer hook registration via iSetTimer(16, fixedUpdate)
 *   - Diagnostic test runner argument parser (--autocapture)
 *   - Starts iGraphics event loop via iStart()
 * DEPENDENCIES: All modular subsystem headers
 * =========================================================================== */
#include "GameDefines.h"
#include "AudioSystem.h"
#include "SaveSystem.h"
#include "RenderUtils.h"
#include "WorldObjects.h"
#include "CharacterRender.h"
#include "Levels.h"
#include "PenaltyGame.h"
#include "MenuScreens.h"
#include "GameLogic.h"
#include "InputHandler.h"

/* -------------------- MAIN DISPLAY FUNCTION (iDraw) -------------------- */
void iDraw()
{
    iClear();

    // ---------------- STATE: CINEMATIC STORY INTRO (IMAGE 3 CLONE) ----------------
    if (gameState == STATE_INTRO)
    {
        // 2D Stylized Nocturnal Castle Dungeon Background
        if (introBgTex != -1)
            iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, introBgTex);
        else if (levelBgTextures[0] != -1)
            iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelBgTextures[0]);

        // Atmospheric Dark Vignette Overlay
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.02f, 0.03f, 0.06f, 0.55f);
        iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glDisable(GL_BLEND);

        // Top-Left: Diamond "?"
        drawDiamond(60, 585, 26, 0.16f, 0.20f, 0.28f, 0.95f);
        drawDiamondOutline(60, 585, 26, 0.95f, 0.95f, 0.98f, 2.0f);
        drawSharpText(53, 576, "?", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

        // Top-Right: Diamond "||"
        drawDiamond(960, 585, 26, 0.16f, 0.20f, 0.28f, 0.95f);
        drawDiamondOutline(960, 585, 26, 0.95f, 0.95f, 0.98f, 2.0f);
        drawSharpText(953, 576, "||", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

        // Poetic Story Narrative from Screenshot 3
        drawSharpText(340, 390, "...I came a long way to get here", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);
        drawSharpText(320, 270, "There were dozens of traps", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);
        drawSharpText(300, 235, "hundreds of puzzles on my way", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

        // Radiant Glowing "TAP ANYWHERE OR PRESS ANY KEY TO ENTER" prompt
        double glowPulse = sin(introTimer * 0.05) * 0.35 + 0.65;
        drawGlowingText(340, 80, "TAP ANYWHERE TO ENTER", GLUT_BITMAP_HELVETICA_18, 251, 191, 36, glowPulse);

        // Warm torch embers drifting gently
        if (rand() % 2 == 0)
        {
            spawnParticle(rand() % SCREEN_WIDTH, 40 + (rand() % 160), ((rand() % 20) - 10) / 20.0, 0.8, 251, 191, 36, 2.0, 20, 1);
        }

        drawToastNotification();
        return;
    }

    if (gameState == STATE_MENU)
    {
        drawWorldSelectMenu();
        if (showChapter3ComingSoon || showChapter5ComingSoon)
            drawChapter5ComingSoonModal();
        if (showRenoSirCollabModal)
            drawRenoSirCollabModal();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_EVENTS)
    {
        drawEventsScreen();
        if (showRenoSirCollabModal)
            drawRenoSirCollabModal();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_PENALTY_GAME)
    {
        drawPenaltyGame();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_CHARACTER_SELECT)
    {
        drawCharacterSelectScreen();
        if (showRenoSirCollabModal)
            drawRenoSirCollabModal();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_LEVEL_SELECT)
    {
        drawLevelSelectScreen();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_CHAPTER2_SELECT)
    {
        drawChapter2SelectScreen();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_CHAPTER3_SELECT)
    {
        drawChapter3SelectScreen();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_CHAPTER4_SELECT)
    {
        drawChapter4SelectScreen();
        drawToastNotification();
        return;
    }

    if (gameState == STATE_SETTINGS)
    {
        drawSettingsMenu();
        drawToastNotification();
        return;
    }

    // ---------------- STATE: PLAYING & IN-GAME RENDERING ----------------
    if (screenShakeTimer > 0)
    {
        glPushMatrix();
        double ox = ((rand() % 100) - 50) / 50.0 * screenShakeIntensity;
        double oy = ((rand() % 100) - 50) / 50.0 * screenShakeIntensity;
        glTranslated(ox, oy, 0);
    }

    // 1. Level Background Image
    int bgTex = levelBgTextures[currentLevel];
    if (bgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgTex);

    // 2. Base Floor Line with textured stone bevels and joint seams
    iSetColor(51, 65, 85);
    iFilledRectangle(0, 0, SCREEN_WIDTH, GROUND_HEIGHT);
    iSetColor(71, 85, 105);
    iFilledRectangle(0, GROUND_HEIGHT - 6, SCREEN_WIDTH, 6);
    iSetColor(30, 41, 59);
    iRectangle(0, 0, SCREEN_WIDTH, GROUND_HEIGHT);
    for (int tx = 0; tx < SCREEN_WIDTH; tx += 64)
    {
        iLine(tx, 0, tx, GROUND_HEIGHT);
    }

    // 3. ALL PLATFORMS & BRIDGES
    drawPlatforms();

    // 4. ALL INTERACTIVE BACKGROUND OBJECTS (RENDERED IN FRONT OF BACKGROUND!)
    for (int i = 0; i < bgObjectCount; i++)
    {
        BgObject& obj = bgObjects[i];
        if (obj.type == BG_PULL_CHAIN)
            drawPullChain(obj.x, obj.y, obj.w, obj.h, obj.state);
        else if (obj.type == BG_TORCH_SCONCE)
            drawWallTorch(obj.x, obj.y, obj.hasTorch);
        else if (obj.type == BG_WALL_LEVER)
            drawWallLever(obj.x, obj.y, obj.state);
        else if (obj.type == BG_CLIMB_IVY)
            drawClimbIvy(obj.x, obj.y, obj.w, obj.h);
        else if (obj.type == BG_PUSH_CRATE)
            drawPushCrate(obj.x, obj.y, obj.w, obj.h);
        else if (obj.type == BG_SPRING_PAD)
            drawSpringPad(obj.x, obj.y, obj.w, obj.h, springCompressTimer > 0);
        else if (obj.type == BG_COGWHEEL_LEVER)
            drawRotatingCogwheel(obj.x, obj.y, 60, cogwheelAngle);
        else if (obj.type == BG_WARP_PORTAL)
            drawWarpPortal(obj.x, obj.y, obj.w, obj.h, false);
        else if (obj.type == BG_WINCH_DRAWBRIDGE)
            drawFortressWinch(obj.x, obj.y, obj.w, obj.h);
        else if (obj.type == BG_GRAVITY_PAD || obj.type == BG_GRAVITY_RETURN_PAD)
        {
            // Arcane glowing purple gravity runes
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            float gPulse = (float)(sin(levelTimer * 0.15) * 0.2 + 0.8);
            glColor4f(0.58f, 0.20f, 0.92f, gPulse);
            iFilledRectangle(obj.x, obj.y, obj.w, obj.h);
            glColor4f(0.75f, 0.52f, 0.98f, 1.0f);
            iRectangle(obj.x, obj.y, obj.w, obj.h);
            glDisable(GL_BLEND);
        }
    }

    // 5. Spikes
    for (int i = 0; i < spikeCount; i++)
    {
        SpikeTrap s = spikes[i];
        if (s.lethal)
            drawSpikes(s.x, s.y, s.w, s.h, s.ceiling);
    }

    // 5b. Authentic Tricky Castle 3D Red Button (Floors 5, 9, 12, 14, etc.)
    if (buttonX > 0)
    {
        drawRedButton(buttonX, buttonY, buttonPressed);
    }

    // 5c. Heavy Ceiling Crusher Trap (Floor 9)
    if (currentLevel == 8)
    {
        drawCrusher(420, crusherY, 140, 36);
    }

    // 5d. Floor 11: Mirror Dimension Central Obsidian Frame & Reflection Pedestal
    if (currentLevel == 10)
    {
        // Central obsidian mirror pillar & enchanted silver frame
        iSetColor(30, 41, 59);
        iFilledRectangle(506, GROUND_HEIGHT, 12, 480);
        iSetColor(148, 163, 184);
        iRectangle(506, GROUND_HEIGHT, 12, 480);

        // Glowing reflection pedestal on the right
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        float rPulse = (float)(sin(globalAnimTimer * 0.1) * 0.2 + 0.7);
        glColor4f(0.22f, 0.74f, 0.97f, 0.5f * rPulse);
        iFilledRectangle(740, GROUND_HEIGHT, 60, 12);
        glColor4f(0.56f, 0.90f, 1.0f, 0.9f);
        iRectangle(740, GROUND_HEIGHT, 60, 12);
        glDisable(GL_BLEND);
        drawSharpText(745, GROUND_HEIGHT + 18, "REFLECT", GLUT_BITMAP_HELVETICA_10, 56, 189, 248);

        // Spectral reflection clone
        mirrorPlayerX = 512 + (512 - (int)playerX) - PLAYER_WIDTH;
        drawCharacterGraphics(mirrorPlayerX, (int)playerY, -facing, invertedGravity, selectedHero);
    }

    // 5e. Floor 13: Flashing Decoy Key
    if (currentLevel == 12 && hasDecoyKey)
    {
        float decoyPulse = (float)(sin(globalAnimTimer * 0.2) * 0.25 + 0.75);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.95f, 0.25f, 0.25f, 0.45f * decoyPulse);
        iFilledCircle(decoyKeyX + 16, decoyKeyY + 16, 24);
        glDisable(GL_BLEND);
        drawKey(decoyKeyX, decoyKeyY);
    }

    // 5f. Floor 14: Swinging Pendulum Blade Trap & Safety Bridge
    if (currentLevel == 13)
    {
        // Lowered Iron Safety Walkway across the spike pit when locked
        if (pendulumLocked)
        {
            int brX = 400, brY = GROUND_HEIGHT, brW = 340, brH = 26;
            // Steel bridge base
            iSetColor(47, 53, 66);
            iFilledRectangle(brX, brY, brW, brH);
            iSetColor(148, 163, 184);
            iRectangle(brX, brY, brW, brH);

            // Safety hazard stripes and green runes
            for (int sx = brX + 16; sx < brX + brW - 12; sx += 32)
            {
                iSetColor(74, 222, 128);
                iFilledRectangle(sx, brY + 4, 12, brH - 8);
                iSetColor(34, 197, 94);
                iFilledCircle(sx + 6, brY + brH / 2, 3);
            }

            // Sturdy iron safety railing
            iSetColor(100, 116, 139);
            iLine(brX, brY + brH + 12, brX + brW, brY + brH + 12);
            for (int rx = brX + 10; rx <= brX + brW; rx += 40)
                iLine(rx, brY + brH, rx, brY + brH + 12);

            drawSharpText(brX + 90, brY + brH + 16, "[ SAFE WALKWAY LOWERED ]", GLUT_BITMAP_HELVETICA_10, 74, 222, 128);
        }

        int pivX = 520, pivY = 560;
        double rad = pendulumAngle * 3.14159265 / 180.0;
        int blX = pivX + (int)(sin(rad) * 340.0);
        int blY = pivY - (int)(cos(rad) * 340.0);

        // Pivot mount on ceiling
        iSetColor(51, 65, 85);
        iFilledCircle(pivX, pivY, 18);
        iSetColor(148, 163, 184);
        iCircle(pivX, pivY, 18);
        iSetColor(203, 213, 225);
        iFilledCircle(pivX, pivY, 6);

        // Heavy steel arm rod
        iSetColor(100, 116, 139);
        iLine(pivX - 2, pivY, blX - 2, blY);
        iLine(pivX + 2, pivY, blX + 2, blY);
        iLine(pivX, pivY, blX, blY);

        // Crescent curved battle blade
        if (!pendulumLocked)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(0.95f, 0.2f, 0.2f, 0.35f);
            iFilledCircle(blX, blY, 36);
            glDisable(GL_BLEND);

            iSetColor(226, 232, 240); // Silver steel blade
            iFilledCircle(blX, blY, 28);
            iSetColor(15, 23, 42);
            iFilledCircle(blX, blY - 14, 22); // Cutout to form crescent
            iSetColor(239, 68, 68); // Razor red glowing edge
            iCircle(blX, blY, 28);
        }
        else
        {
            // Blade safely locked / clamped
            iSetColor(148, 163, 184);
            iFilledCircle(blX, blY, 28);
            iSetColor(15, 23, 42);
            iFilledCircle(blX, blY - 14, 22);
            iSetColor(74, 222, 128); // Green safe edge
            iCircle(blX, blY, 28);

            // Safety clamp
            iSetColor(251, 191, 36);
            iFilledRectangle(blX - 16, blY - 8, 32, 16);
            iSetColor(30, 41, 59);
            iRectangle(blX - 16, blY - 8, 32, 16);
            drawSharpText(blX - 18, blY + 34, "LOCKED", GLUT_BITMAP_HELVETICA_10, 74, 222, 128);
        }
    }

    // 5g. Floor 15: Shifting Castle Stone Wall
    if (currentLevel == 14)
    {
        int wx = 500, wy = shiftingWallY, ww = 90, wh = 480;
        iSetColor(51, 65, 85);
        iFilledRectangle(wx, wy, ww, wh);
        iSetColor(30, 41, 59);
        iRectangle(wx, wy, ww, wh);

        // Chiseled fortress stone blocks pattern
        iSetColor(100, 116, 139);
        for (int by = wy + 20; by < wy + wh; by += 40)
        {
            iLine(wx, by, wx + ww, by);
            int offset = ((by / 40) % 2 == 0) ? 0 : 30;
            iLine(wx + offset + 30, by - 40, wx + offset + 30, by);
        }

        // Iron ring handle
        iSetColor(203, 213, 225);
        iCircle(wx + ww / 2, wy + 80, 14);
        iFilledCircle(wx + ww / 2, wy + 80, 5);

        if (!shiftingWallOpen)
        {
            drawSharpText(wx - 25, wy + 110, "[CLICK OR SHIFT]", GLUT_BITMAP_HELVETICA_12, 251, 191, 36);
        }
    }

    // 5h. Floor 16: Stepped Solid Floating Words Bridge
    if (currentLevel == 15)
    {
        double wPulse = sin(globalAnimTimer * 0.08) * 0.2 + 0.8;

        // Floating mystical aura under the stepped words
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.22f, 0.74f, 0.97f, (float)(0.30f * wPulse));
        iFilledRectangle(120, 130, 115, 26);
        iFilledRectangle(260, 190, 80, 26);
        iFilledRectangle(365, 245, 465, 26);
        glDisable(GL_BLEND);

        drawGlowingText(130, 136, "W  A  L  K", GLUT_BITMAP_TIMES_ROMAN_24, 56, 189, 248, wPulse);
        drawGlowingText(275, 196, "O  N", GLUT_BITMAP_TIMES_ROMAN_24, 56, 189, 248, wPulse);
        drawGlowingText(380, 251, "T  H  E      S  O  L  I  D      W  O  R  D  S", GLUT_BITMAP_TIMES_ROMAN_24, 56, 189, 248, wPulse);
    }
    // Floor 18: Witch's Cauldron & Arcane Flame
    else if (currentLevel == 17)
    {
        int cX = 500, cY = 240;
        // Draw iron witch cauldron
        iSetColor(30, 41, 59);
        iFilledRectangle(cX - 25, cY, 50, 30);
        iCircle(cX, cY + 15, 25);

        // If door is not opened, cauldron burns with blue witchflame
        if (!doorOpen)
        {
            double fPulse = sin(globalAnimTimer * 0.25) * 0.25 + 0.75;
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(0.22f, 0.74f, 0.97f, (float)(0.60f * fPulse));
            iFilledCircle(cX, cY + 35, 18);
            glColor4f(0.58f, 0.20f, 0.92f, (float)(0.80f * fPulse));
            iFilledCircle(cX, cY + 45, 12);
            glDisable(GL_BLEND);
            drawSharpText(cX - 45, cY + 65, "[BLUE WITCHFLAME]", GLUT_BITMAP_HELVETICA_10, 56, 189, 248);
        }
    }

    // 6. Chests (Floor 3)
    for (int i = 0; i < chestCount; i++)
    {
        Chest c = chests[i];
        drawChest(c.x, c.y, c.opened);
    }

    // 7. Exit Door
    drawDoor(doorX, doorY, doorOpen);

    // 8. Key
    if (keyActive && !hasKey)
        drawKey(keyX, keyY);

    // 9. Falling Key (Floor 5)
    if (fallingKeyActive)
        drawKey(520, fallingKeyY);

    // 10. Ghost
    if (ghost.active)
        drawGhost(ghost.x, ghost.y);

    // 11. Glowing Animated Secret Star
    if (starActive)
        drawStar(starX, starY);

    // 12. Castle Guard Captain Messi (Floor 10)
    if (currentLevel == 9)
    {
        if (guardTex != -1)
            iShowImageAlpha(guardX - 4, guardY, 82, 102, guardTex, 1.0f);
        if (guardAsleep)
        {
            drawSharpText(guardX + 25, guardY + 108, "Z z z...", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);
        }
        else
        {
            drawSharpText(guardX + 8, guardY + 108, "CAPTAIN MESSI", GLUT_BITMAP_HELVETICA_10, 251, 191, 36);
        }
    }

    // 13. Protagonist Hero (with special animation effects & proper facing)
    drawCharacterGraphics((int)playerX, (int)playerY, facing, invertedGravity, selectedHero);

    // 14. Particles
    for (int i = 0; i < particleCount; i++)
    {
        Particle p = particles[i];
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(p.r / 255.0f, p.g / 255.0f, p.b / 255.0f, (float)p.a);
        iFilledCircle((int)p.x, (int)p.y, (int)p.size);
        glDisable(GL_BLEND);
    }

    // 15. Floating Texts
    for (int i = 0; i < floatingTextCount; i++)
    {
        FloatingText& ft = floatingTexts[i];
        drawSharpText((int)ft.x, (int)ft.y, ft.text, GLUT_BITMAP_HELVETICA_18, ft.r, ft.g, ft.b);
    }

    // 16. Active Interactive Prompt
    if (activeInteractionIndex >= 0 && activeInteractionIndex < bgObjectCount)
    {
        BgObject& obj = bgObjects[activeInteractionIndex];
        int promptX = (int)playerX - 85;
        if (promptX < 20) promptX = 20;
        if (promptX > SCREEN_WIDTH - 290) promptX = SCREEN_WIDTH - 290;
        int promptY = (int)playerY + PLAYER_HEIGHT + 20;

        drawMetallicButton(promptX, promptY, 270, 40, obj.prompt, true, 0);
    }

    // 17. HUD On-screen touch controls (Matching Reference Image)
    drawOnScreenTouchControls();

    // 18. Top Riddle Banner
    drawMetallicCard(262, 570, 500, 48, 14, 0.12f, 0.16f, 0.24f, 0.88f, 0.98f, 0.82f, 0.25f, 2);
    int clueLen = (int)strlen(levels[currentLevel].clue);
    int ctx = 262 + (500 - clueLen * 9) / 2;
    drawSharpText(ctx, 586, levels[currentLevel].clue, GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // ---------------- IN-GAME HINT MODAL ----------------
    if (showHintAdModal)
    {
        drawHintAdModal();
    }

    // ---------------- PAUSE MENU ----------------
    if (gameState == STATE_PAUSED)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.05f, 0.08f, 0.14f, 0.78f);
        iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glDisable(GL_BLEND);

        int cardX = 312;
        int cardY = 120;
        int cardW = 400;
        int cardH = 420;

        drawMetallicCard(cardX, cardY, cardW, cardH, 24, 0.98f, 0.98f, 0.99f, 1.0f, 0.32f, 0.36f, 0.44f, 4);
        drawSharpText(cardX + 145, cardY + 365, "PAUSED", GLUT_BITMAP_TIMES_ROMAN_24, 30, 41, 59);

        drawMetallicButton(cardX + 50, cardY + 280, 300, 50, "RESUME [P]", false, 0);
        drawMetallicButton(cardX + 50, cardY + 210, 300, 50, "RESTART [R]", false, 1);
        drawMetallicButton(cardX + 50, cardY + 140, 300, 50, "CHANGE HERO [C]", false, 2);
        drawMetallicButton(cardX + 50, cardY + 70, 300, 50, "LEVEL MAP [L]", false, 2);
    }

    // ---------------- GAME OVER: TRICKY CASTLE ANGEL GHOST ----------------
    if (gameState == STATE_GAME_OVER)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.05f, 0.08f, 0.14f, 0.82f);
        iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glDisable(GL_BLEND);

        int gx = (int)angelGhostX;
        int gy = (int)angelGhostY;

        iSetColor(251, 191, 36);
        iEllipse(gx + 25, gy + 85, 16, 6);

        iSetColor(241, 245, 249);
        iFilledCircle(gx + 25, gy + 56, 18);
        iFilledRectangle(gx + 7, gy + 36, 36, 20);

        double wingFlap = sin(angelGhostTimer * 0.25) * 9.0;
        iSetColor(255, 255, 255);
        double w1x[] = { (double)(gx + 7), (double)(gx - 16), (double)(gx + 5) };
        double w1y[] = { (double)(gy + 50), (double)(gy + 64 + wingFlap), (double)(gy + 40) };
        iFilledPolygon(w1x, w1y, 3);
        double w2x[] = { (double)(gx + 43), (double)(gx + 66), (double)(gx + 45) };
        double w2y[] = { (double)(gy + 50), (double)(gy + 64 + wingFlap), (double)(gy + 40) };
        iFilledPolygon(w2x, w2y, 3);

        int cardX = 262;
        int cardY = 140;
        int cardW = 500;
        int cardH = 280;

        drawMetallicCard(cardX, cardY, cardW, cardH, 24, 0.98f, 0.98f, 0.99f, 1.0f, 0.32f, 0.36f, 0.44f, 4);

        drawSharpText(cardX + 90, cardY + 225, "YOU FELL FOR THE TRICK!", GLUT_BITMAP_TIMES_ROMAN_24, 220, 38, 38);
        drawSharpText(cardX + 50, cardY + 175, levels[currentLevel].deathQuote, GLUT_BITMAP_HELVETICA_12, 71, 85, 105);

        drawMetallicButton(cardX + 100, cardY + 100, 300, 48, "PLAY AGAIN [R]", false, 0);
        drawMetallicButton(cardX + 100, cardY + 40, 300, 48, "GET HINT [H]", false, 1);
    }

    // ---------------- LEVEL CLEAR: STARS & SCORE ----------------
    if (gameState == STATE_LEVEL_CLEAR)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.05f, 0.08f, 0.14f, 0.78f);
        iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glDisable(GL_BLEND);

        int cardX = 282;
        int cardY = 160;
        int cardW = 460;
        int cardH = 320;

        drawMetallicCard(cardX, cardY, cardW, cardH, 24, 0.98f, 0.98f, 0.99f, 1.0f, 0.32f, 0.36f, 0.44f, 4);

        if (currentLevel == 11)
            drawSharpText(cardX + 45, cardY + 265, "CHAPTER 1 CLEARED! CITADEL UNLOCKED!", GLUT_BITMAP_TIMES_ROMAN_24, 34, 197, 94);
        else if (currentLevel == 15)
            drawSharpText(cardX + 35, cardY + 265, "CHAPTER 2 CLEARED! WITCH TOWER UNLOCKED!", GLUT_BITMAP_TIMES_ROMAN_24, 56, 189, 248);
        else if (currentLevel == 19)
            drawSharpText(cardX + 30, cardY + 265, "CHAPTER 3 CLEARED! DRAGON KEEP UNLOCKED!", GLUT_BITMAP_TIMES_ROMAN_24, 251, 191, 36);
        else
            drawSharpText(cardX + 115, cardY + 265, "FLOOR CLEARED!", GLUT_BITMAP_TIMES_ROMAN_24, 34, 197, 94);

        for (int s = 0; s < 3; s++)
        {
            if (s < levelStars[currentLevel]) iSetColor(251, 191, 36);
            else iSetColor(148, 163, 184);
            drawStar(cardX + 175 + s * 55, cardY + 205);
        }

        char scoreInfo[64];
        sprintf(scoreInfo, "Room Score: %d PTS", levelScores[currentLevel]);
        drawSharpText(cardX + 140, cardY + 145, scoreInfo, GLUT_BITMAP_HELVETICA_18, 30, 41, 59);

        drawMetallicButton(cardX + 80, cardY + 50, 300, 50, "NEXT FLOOR [ENTER]", false, 0);
    }

    if (screenShakeTimer > 0)
        glPopMatrix();
}

/* -------------------- ENTRY POINT -------------------- */
int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "--autocapture") == 0)
    {
        autoCaptureStep = 0;
    }

    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, (char*)"Tricky Castle - Dream Deluxe Edition", 16);

    // Load 6 High-Resolution Champions
    characters[HERO_WILLIAM].skinTexID   = iLoadImage((char*)"Images//chibi_william.png");
    characters[HERO_CR7].skinTexID       = iLoadImage((char*)"Images//chibi_cr7_devil.png");
    characters[HERO_NEYMAR].skinTexID    = iLoadImage((char*)"Images//chibi_neymar.png");
    characters[HERO_ELENA].skinTexID     = iLoadImage((char*)"Images//chibi_elena.png");
    characters[HERO_THORGAR].skinTexID   = iLoadImage((char*)"Images//chibi_thorgar.png");
    characters[HERO_SAHA_RENO].skinTexID = iLoadImage((char*)"Images//chibi_reno_sir.png");

    // Load CR7 Multi-Skins
    cr7DevilTex    = characters[HERO_CR7].skinTexID;
    cr7MadridTex   = iLoadImage((char*)"Images//chibi_cr7_madrid.png");
    cr7JuventusTex = iLoadImage((char*)"Images//chibi_cr7_juventus.png");

    // Intro, Menu, Banner, Guard, and Chapter 2 Textures
    guardTex               = iLoadImage((char*)"Images//castle_guard.png");
    introBgTex             = iLoadImage((char*)"Images//bg_intro_tricky_castle.jpg");
    menuBgTex              = iLoadImage((char*)"Images//bg_tricky_menu.jpg");
    eventBannerTex         = iLoadImage((char*)"Images//banner_cr7_event.jpg");
    renoSirCollabBannerTex = iLoadImage((char*)"Images//banner_reno_sir_collab.jpg");
    gearSketchTex          = iLoadImage((char*)"Images//btn_setting_gear.png");
    introCr7Tex            = iLoadImage((char*)"Images//intro_cr7_william.png");
    chapter2BgTex          = iLoadImage((char*)"Images//bg_chapter2_citadel.jpg");
    chapter3BgTex          = iLoadImage((char*)"Images//bg_castle_runes.jpg");
    chapter4BgTex          = iLoadImage((char*)"Images//castle_dungeon.jpg");
    eventCollabThumbTex    = iLoadImage((char*)"Images//thumb_collab_saha_reno.jpg");

    // Custom Characters for Penalty Game (Exclusive to Penalty Derby!)
    penaltyMessiTex   = iLoadImage((char*)"Images//penalty_messi_gk.png");
    penaltyCr7BackTex = iLoadImage((char*)"Images//penalty_cr7_back.png");
    penaltyCr7SiuTex  = iLoadImage((char*)"Images//penalty_cr7_siu.png");

    // Segmented Articulated Limbs for Dynamic Leg & Body Animations
    penaltyCr7TorsoTex   = iLoadImage((char*)"Images//penalty_cr7_torso.png");
    penaltyCr7LegLTex    = iLoadImage((char*)"Images//penalty_cr7_leg_l.png");
    penaltyCr7LegRTex    = iLoadImage((char*)"Images//penalty_cr7_leg_r.png");
    penaltyMessiTorsoTex = iLoadImage((char*)"Images//penalty_messi_torso.png");
    penaltyMessiLegLTex  = iLoadImage((char*)"Images//penalty_messi_leg_l.png");
    penaltyMessiLegRTex  = iLoadImage((char*)"Images//penalty_messi_leg_r.png");

    // Level Backgrounds
    for (int i = 0; i < LEVEL_COUNT; i++)
    {
        levelBgTextures[i] = iLoadImage((char*)levels[i].bgFile);
    }

    loadProgress();
    loadLevel(0);

    if (soundEnabled)
    {
        playBgm("Audios\\background.mp3");
    }

    // 60 FPS Platformer Logic & Animation Loop (16ms)
    iSetTimer(16, fixedUpdate);

    iStart();
    return 0;
}

