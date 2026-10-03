#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: MenuScreens.h
 * DEVELOPER: Nabeel Saad Borno (Student ID: 00725105101135)
 * ROLE & RESPONSIBILITY: User Interface Design, Menu Navigation & Score System
 *
 * FEATURES IMPLEMENTED:
 *   - Interactive 3D World Select Carousel with card scaling and smooth selection
 *   - Costumes / Hero Selection screen: 6 champion cards, stats, and perk descriptions
 *   - Chapter Level Selection grids with star ratings and locked/cleared status
 *   - Events & 7-Day Daily Login Reward modal with claiming mechanics
 *   - RenoSir LLM Collab Modal with banner presentation and 1-level trial activation
 *   - Pause dialog and Settings menu (sound toggle, tutorial hints, controls help)
 *   - Victory win screen with dynamic star awards and Game Over angel ghost screen
 * DEPENDENCIES: GameDefines.h, RenderUtils.h, CharacterRender.h, AudioSystem.h, SaveSystem.h
 * =========================================================================== */
#include "GameDefines.h"
#include "RenderUtils.h"
#include "CharacterRender.h"
#include "AudioSystem.h"
#include "SaveSystem.h"

/* -------------------- 1. STATE_MENU: WORLD SELECT CAROUSEL (IMAGE 1 MATCH) -------------------- */
void drawWorldSelectMenu()
{
    if (menuBgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgTex);
    else if (levelBgTextures[1] != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelBgTextures[1]);

    // Top Header Bar
    // 1. ADS Button (Orange diamond with white border and text)
    drawDiamond(60, 585, 26, 0.93f, 0.44f, 0.16f, 0.98f);
    drawDiamondOutline(60, 585, 26, 1.0f, 1.0f, 1.0f, 2.5f);
    drawSharpText(45, 578, "ADS", GLUT_BITMAP_HELVETICA_12, 255, 255, 255);

    // 2. Rate Button (Pill-shaped dark rounded container with crisp white border)
    int rateX = 115, rateY = 565, rateW = 110, rateH = 40;
    drawFilledSmoothRect((float)rateX, (float)rateY, (float)rateW, (float)rateH, 20, 0.16f, 0.20f, 0.28f, 0.95f);
    drawSmoothRectOutline((float)rateX, (float)rateY, (float)rateW, (float)rateH, 20, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f);
    drawSharpText(rateX + 35, rateY + 13, "Rate", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // 3. 3D Metallic Cog Gear Settings Button (Top Right)
    bool gearHov = (hoveredCarouselCard == -2);
    double cogSpin = gearHov ? (globalAnimTimer * 4.0) : (globalAnimTimer * 0.4);
    drawMetallicCogGear(960, 585, 22, cogSpin, gearHov);

    // Carousel Cards (Costumes, Events, Ch1 Princess Castle, Ch2 Citadel, Ch3 Witch Tower, Ch4 Dragon Keep, Ch5 Astral Spire)
    int cardW = 126;
    int cardH = 310;
    int startX = 32;
    int cardSpacing = 138;
    int baseCardY = 165;

    // CARD 0: COSTUMES (1 / 12)
    {
        int cx = startX;
        bool hov = (hoveredCarouselCard == 0);
        int cy = baseCardY + (hov ? 10 : 0);

        drawMetallicCard(cx, cy, cardW, cardH, 20, 0.88f, 0.25f, 0.15f, 0.95f, 0.98f, 0.82f, 0.25f, 4, hov);
        drawFilledSmoothRect((float)(cx + 8), (float)(cy + 55), (float)(cardW - 16), (float)(cardH - 68), 14, 0.95f, 0.42f, 0.15f, 0.92f);

        // Alert Badge "!" (Top-Left)
        iSetColor(239, 68, 68);
        iFilledCircle(cx + 18, cy + cardH - 18, 12);
        iSetColor(255, 255, 255);
        iCircle(cx + 18, cy + cardH - 18, 12);
        drawSharpText(cx + 15, cy + cardH - 24, "!", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

        // Clothes Hanger Icon at top
        int hx = cx + cardW / 2;
        int hy = cy + cardH - 36;
        iSetColor(254, 240, 138);
        iLine(hx - 20, hy - 14, hx + 20, hy - 14);
        iLine(hx - 20, hy - 14, hx, hy);
        iLine(hx + 20, hy - 14, hx, hy);
        iCircle(hx, hy + 6, 5);

        // Hero Preview Sprite
        int tex = characters[selectedHero].skinTexID;
        if (tex != -1)
        {
            if (selectedHero == HERO_SAHA_RENO)
                iShowImageAlphaFlipped(cx + 10, cy + 68, 106, 140, tex, 1.0f);
            else
                iShowImageAlpha(cx + 10, cy + 68, 106, 140, tex, 1.0f);
        }

        // 1 / 12 Badge
        drawFilledSmoothRect((float)(cx + 18), (float)(cy + 18), (float)(cardW - 36), 24, 8, 0.12f, 0.15f, 0.22f, 0.85f);
        drawSharpText(cx + 34, cy + 24, "1 / 12", GLUT_BITMAP_HELVETICA_12, 255, 255, 255);

        drawSharpText(cx + 20, cy - 30, "Costumes", GLUT_BITMAP_HELVETICA_18, 251, 191, 36);
    }

    // CARD 1: EVENTS (SAHA RENO COLLABORATION THUMBNAIL)
    {
        int cx = startX + cardSpacing;
        bool hov = (hoveredCarouselCard == 1);
        int cy = baseCardY + (hov ? 10 : 0);

        // BIG RED FONT "COMING SOON" DIRECTLY ABOVE THE THUMBNAIL CARD
        float redPulse = (float)(sin(globalAnimTimer * 0.12f) * 0.25f + 0.75f);
        const char* soonStr = "COMING SOON";
        int textW = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)soonStr);
        int tagPadX = 14;
        int tagW = textW + tagPadX * 2;
        int tagH = 34;
        int tagX = cx + (cardW - tagW) / 2;
        int tagY = cy + cardH + 12;

        // Elegant dark ruby glass pill backing with pulsing red border
        drawFilledSmoothRect((float)tagX, (float)tagY, (float)tagW, (float)tagH, 10, 0.08f, 0.02f, 0.03f, 0.94f);
        drawSmoothRectOutline((float)tagX, (float)tagY, (float)tagW, (float)tagH, 10, 0.95f, 0.20f, 0.20f, 0.95f * redPulse, 2.0f);

        // Big Vibrant Red Font: COMING SOON
        drawBigRedText(tagX + tagPadX, tagY + 8, soonStr, GLUT_BITMAP_TIMES_ROMAN_24, redPulse);

        drawMetallicCard(cx, cy, cardW, cardH, 20, 0.10f, 0.14f, 0.24f, 0.98f, 0.98f, 0.82f, 0.25f, 4, hov);
        drawFilledSmoothRect((float)(cx + 6), (float)(cy + 48), (float)(cardW - 12), (float)(cardH - 58), 12, 0.06f, 0.08f, 0.14f, 0.95f);

        if (eventCollabThumbTex != -1)
            iShowImageAlpha(cx + 6, cy + 48, cardW - 12, cardH - 58, eventCollabThumbTex, 1.0f);
        else if (characters[HERO_SAHA_RENO].skinTexID != -1)
            iShowImageAlphaFlipped(cx + 10, cy + 68, 106, 140, characters[HERO_SAHA_RENO].skinTexID, 1.0f);

        float pulse = (float)(sin(globalAnimTimer * 0.10) * 0.2 + 0.8);
        drawSmoothRectOutline((float)(cx + 6), (float)(cy + 48), (float)(cardW - 12), (float)(cardH - 58), 12, 0.22f * pulse, 0.74f * pulse, 0.97f, 0.90f, 2.0f);

        // Bottom Pill Banner: "RENOSIR x TRICKY"
        drawFilledSmoothRect((float)(cx + 8), (float)(cy + 14), (float)(cardW - 16), 26, 8, 0.10f, 0.16f, 0.26f, 0.95f);
        drawSmoothRectOutline((float)(cx + 8), (float)(cy + 14), (float)(cardW - 16), 26, 8, 0.22f, 0.74f, 0.97f, 0.90f, 1.5f);
        drawSharpText(cx + 12, cy + 20, "RENOSIR x TRICKY", GLUT_BITMAP_HELVETICA_10, 56, 189, 248);

        drawSharpText(cx + 10, cy - 30, "Renosir Collab", GLUT_BITMAP_HELVETICA_18, 251, 191, 36);
    }

    // CARD 2: PRINCESS CASTLE (CHAPTER 1)
    {
        int cx = startX + cardSpacing * 2;
        bool hov = (hoveredCarouselCard == 2);
        int cy = baseCardY + (hov ? 10 : 0);

        drawMetallicCard(cx, cy, cardW, cardH, 20, 0.18f, 0.22f, 0.32f, 0.95f, 0.98f, 0.82f, 0.25f, 4, hov);
        drawFilledSmoothRect((float)(cx + 8), (float)(cy + 55), (float)(cardW - 16), (float)(cardH - 68), 14, 0.24f, 0.38f, 0.44f, 0.92f);

        int kx = cx + cardW / 2;
        int ky = cy + cardH - 35;
        drawStarShape(kx, ky, 10.0, 5.0, 251, 191, 36, true);

        if (levelBgTextures[0] != -1)
            iShowImageAlpha(cx + 10, cy + 85, cardW - 20, 145, levelBgTextures[0], 0.95f);

        int ch1Stars = 0;
        for (int s = 0; s < 12; s++) ch1Stars += levelStars[s];
        char starTxt[32];
        sprintf(starTxt, "%d / 36 Stars", ch1Stars);
        drawFilledSmoothRect((float)(cx + 14), (float)(cy + 18), (float)(cardW - 28), 24, 8, 0.10f, 0.14f, 0.20f, 0.85f);
        drawSharpText(cx + 20, cy + 24, starTxt, GLUT_BITMAP_HELVETICA_10, 251, 191, 36);

        drawSharpText(cx + 12, cy - 30, "Ch.1 Castle", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);
    }

    // CARD 3: THE CITADEL (CHAPTER 2, FLOORS 13 - 16)
    {
        int cx = startX + cardSpacing * 3;
        bool hov = (hoveredCarouselCard == 3);
        int cy = baseCardY + (hov ? 10 : 0);
        bool ch2Unlocked = (unlockedLevels >= 13);

        if (ch2Unlocked)
        {
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.18f, 0.28f, 0.42f, 0.95f, 0.38f, 0.82f, 0.98f, 4, hov);
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + 55), (float)(cardW - 16), (float)(cardH - 68), 14, 0.14f, 0.22f, 0.36f, 0.92f);

            if (chapter2BgTex != -1)
                iShowImageAlpha(cx + 10, cy + 85, cardW - 20, 145, chapter2BgTex, 0.95f);

            int ch2Stars = 0;
            for (int s = 12; s < 16; s++) ch2Stars += levelStars[s];
            char starTxt[32];
            sprintf(starTxt, "%d / 12 Stars", ch2Stars);
            drawFilledSmoothRect((float)(cx + 14), (float)(cy + 18), (float)(cardW - 28), 24, 8, 0.10f, 0.14f, 0.20f, 0.85f);
            drawSharpText(cx + 20, cy + 24, starTxt, GLUT_BITMAP_HELVETICA_10, 56, 189, 248);
        }
        else
        {
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.15f, 0.18f, 0.25f, 0.92f, 0.40f, 0.45f, 0.55f, 2, hov);
            iSetColor(148, 163, 184);
            iFilledRectangle(cx + cardW / 2 - 16, cy + cardH / 2 - 18, 32, 28);
            iCircle(cx + cardW / 2, cy + cardH / 2 + 12, 13);
            iSetColor(30, 41, 59);
            iFilledCircle(cx + cardW / 2, cy + cardH / 2 - 2, 4);
            iLine(cx + cardW / 2, cy + cardH / 2 - 2, cx + cardW / 2, cy + cardH / 2 - 10);
            drawSharpText(cx + 28, cy + 30, "Floor 13+", GLUT_BITMAP_HELVETICA_10, 148, 163, 184);
        }

        drawSharpText(cx + 12, cy - 30, "Ch.2 Citadel", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);
    }

    // CARD 4: WITCH TOWER (CHAPTER 3, FLOORS 17 - 20)
    {
        int cx = startX + cardSpacing * 4;
        bool hov = (hoveredCarouselCard == 4);
        int cy = baseCardY + (hov ? 10 : 0);
        bool ch3Unlocked = (unlockedLevels >= 17);

        if (ch3Unlocked)
        {
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.26f, 0.18f, 0.42f, 0.95f, 0.75f, 0.52f, 0.98f, 4, hov);
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + 55), (float)(cardW - 16), (float)(cardH - 68), 14, 0.20f, 0.12f, 0.32f, 0.92f);

            if (levelBgTextures[6] != -1)
                iShowImageAlpha(cx + 10, cy + 85, cardW - 20, 145, levelBgTextures[6], 0.95f);

            int ch3Stars = 0;
            for (int s = 16; s < 20; s++) ch3Stars += levelStars[s];
            char starTxt[32];
            sprintf(starTxt, "%d / 12 Stars", ch3Stars);
            drawFilledSmoothRect((float)(cx + 14), (float)(cy + 18), (float)(cardW - 28), 24, 8, 0.10f, 0.14f, 0.20f, 0.85f);
            drawSharpText(cx + 20, cy + 24, starTxt, GLUT_BITMAP_HELVETICA_10, 192, 132, 252);
        }
        else
        {
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.15f, 0.18f, 0.25f, 0.92f, 0.40f, 0.45f, 0.55f, 2, hov);
            iSetColor(148, 163, 184);
            iFilledRectangle(cx + cardW / 2 - 16, cy + cardH / 2 - 18, 32, 28);
            iCircle(cx + cardW / 2, cy + cardH / 2 + 12, 13);
            iSetColor(30, 41, 59);
            iFilledCircle(cx + cardW / 2, cy + cardH / 2 - 2, 4);
            iLine(cx + cardW / 2, cy + cardH / 2 - 2, cx + cardW / 2, cy + cardH / 2 - 10);
            drawSharpText(cx + 28, cy + 30, "Floor 17+", GLUT_BITMAP_HELVETICA_10, 148, 163, 184);
        }

        drawSharpText(cx + 10, cy - 30, "Ch.3 Witch", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);
    }

    // CARD 5: DRAGON'S KEEP (CHAPTER 4, FLOORS 21 - 24)
    {
        int cx = startX + cardSpacing * 5;
        bool hov = (hoveredCarouselCard == 5);
        int cy = baseCardY + (hov ? 10 : 0);
        bool ch4Unlocked = (unlockedLevels >= 21);

        if (ch4Unlocked)
        {
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.38f, 0.16f, 0.14f, 0.95f, 0.98f, 0.65f, 0.25f, 4, hov);
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + 55), (float)(cardW - 16), (float)(cardH - 68), 14, 0.28f, 0.10f, 0.10f, 0.92f);

            if (levelBgTextures[0] != -1)
                iShowImageAlpha(cx + 10, cy + 85, cardW - 20, 145, levelBgTextures[0], 0.95f);

            int ch4Stars = 0;
            for (int s = 20; s < 24; s++) ch4Stars += levelStars[s];
            char starTxt[32];
            sprintf(starTxt, "%d / 12 Stars", ch4Stars);
            drawFilledSmoothRect((float)(cx + 14), (float)(cy + 18), (float)(cardW - 28), 24, 8, 0.10f, 0.14f, 0.20f, 0.85f);
            drawSharpText(cx + 20, cy + 24, starTxt, GLUT_BITMAP_HELVETICA_10, 251, 146, 60);
        }
        else
        {
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.15f, 0.18f, 0.25f, 0.92f, 0.40f, 0.45f, 0.55f, 2, hov);
            iSetColor(148, 163, 184);
            iFilledRectangle(cx + cardW / 2 - 16, cy + cardH / 2 - 18, 32, 28);
            iCircle(cx + cardW / 2, cy + cardH / 2 + 12, 13);
            iSetColor(30, 41, 59);
            iFilledCircle(cx + cardW / 2, cy + cardH / 2 - 2, 4);
            iLine(cx + cardW / 2, cy + cardH / 2 - 2, cx + cardW / 2, cy + cardH / 2 - 10);
            drawSharpText(cx + 28, cy + 30, "Floor 21+", GLUT_BITMAP_HELVETICA_10, 148, 163, 184);
        }

        drawSharpText(cx + 10, cy - 30, "Ch.4 Dragon", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);
    }

    // CARD 6: ASTRAL SPIRE (CHAPTER 5 - COMING SOON!)
    {
        int cx = startX + cardSpacing * 6;
        bool hov = (hoveredCarouselCard == 6);
        int cy = baseCardY + (hov ? 10 : 0);

        drawMetallicCard(cx, cy, cardW, cardH, 20, 0.12f, 0.18f, 0.32f, 0.98f, 0.98f, 0.82f, 0.25f, 4, hov);
        drawFilledSmoothRect((float)(cx + 8), (float)(cy + 55), (float)(cardW - 16), (float)(cardH - 68), 14, 0.08f, 0.12f, 0.22f, 0.92f);

        // Pulsing Astral Star
        float aPulse = (float)(sin(globalAnimTimer * 0.12) * 2.0 + 10.0);
        drawStarShape(cx + cardW / 2, cy + cardH / 2 + 30, aPulse, aPulse * 0.45, 251, 191, 36, true);

        // 3D Glowing "SOON" Pill Badge
        int snW = 76, snH = 24;
        int snX = cx + (cardW - snW) / 2, snY = cy + cardH / 2 - 25;
        drawFilledSmoothRect((float)snX, (float)snY, (float)snW, (float)snH, 6, 0.88f, 0.22f, 0.18f, 0.95f);
        drawSmoothRectOutline((float)snX, (float)snY, (float)snW, (float)snH, 6, 0.98f, 0.82f, 0.25f, 1.0f, 1.2f);
        drawSharpText(snX + 16, snY + 6, "SOON!", GLUT_BITMAP_HELVETICA_10, 254, 240, 138);

        drawFilledSmoothRect((float)(cx + 12), (float)(cy + 18), (float)(cardW - 24), 24, 8, 0.10f, 0.14f, 0.22f, 0.85f);
        drawSharpText(cx + 20, cy + 24, "V3.0 UPDATE", GLUT_BITMAP_HELVETICA_10, 56, 189, 248);

        drawSharpText(cx + 10, cy - 30, "Ch.5 Astral", GLUT_BITMAP_HELVETICA_18, 251, 191, 36);
    }
}

/* -------------------- 2. STATE_EVENTS: DAILY LOGIN REWARDS & CR7 x TRICKY CASTLE EVENT -------------------- */
void drawEventsScreen()
{
    if (menuBgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgTex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.04f, 0.06f, 0.12f, 0.78f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    // Top-Left: 3D Diamond Return Button "<"
    drawDiamond(60, 585, 28, 0.12f, 0.16f, 0.24f, 0.98f);
    drawDiamondOutline(60, 585, 28, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(52, 576, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    // Top-Right: 3D Currency Display Capsules (Multi-faceted 3D Gems & Stamped 3D Gold Coins)
    draw3DCurrencyCapsule(710, 564, 136, 42, 0, playerGems);
    draw3DCurrencyCapsule(862, 564, 136, 42, 1, playerCoins);

    // ---------------- 3D CR7 x TRICKY CASTLE CURRENT EVENT BANNER ----------------
    int banX = 142, banY = 375, banW = 740, banH = 175;
    draw3DBannerChassis(banX, banY, banW, banH, eventBannerTex);

    // ---------------- CR7 EVENT CHALLENGES & SKINS HUB ----------------
    drawSharpText(285, 350, "★ CR7 x TRICKY CASTLE EVENT CHALLENGES ★", GLUT_BITMAP_TIMES_ROMAN_24, 251, 191, 36);

    int qCardW = 236;
    int qCardH = 92;
    int qCardY = 248;

    // Challenge 1: Real Madrid CR7 Skin
    {
        int qx = 142;
        bool isDone = questMadridClaimed || cr7MadridUnlocked;
        bool canClaim = (unlockedLevels >= 6) && !isDone;
        drawFilledSmoothRect((float)qx, (float)qCardY, (float)qCardW, (float)qCardH, 12, 0.10f, 0.14f, 0.22f, 0.95f);
        drawSmoothRectOutline((float)qx, (float)qCardY, (float)qCardW, (float)qCardH, 12, isDone ? 0.13f : (canClaim ? 0.98f : 0.35f), isDone ? 0.77f : (canClaim ? 0.82f : 0.42f), isDone ? 0.36f : 0.25f, 0.9f, 1.8f);

        if (cr7MadridTex != -1)
            iShowImageAlpha(qx + 8, qCardY + 14, 58, 64, cr7MadridTex, 1.0f);

        drawSharpText(qx + 72, qCardY + 68, "REAL MADRID CR7", GLUT_BITMAP_HELVETICA_12, 254, 240, 138);
        int flrs = (unlockedLevels - 1 > 5) ? 5 : (unlockedLevels - 1);
        char progStr[32];
        sprintf(progStr, "Clear 5 Floors (%d/5)", flrs);
        drawSharpText(qx + 72, qCardY + 48, progStr, GLUT_BITMAP_HELVETICA_10, 148, 163, 184);

        if (isDone)
        {
            drawFilledSmoothRect((float)(qx + 72), (float)(qCardY + 12), (float)(qCardW - 84), 24, 6, 0.08f, 0.38f, 0.18f, 0.90f);
            drawSharpText(qx + 88, qCardY + 18, "✓ UNLOCKED", GLUT_BITMAP_HELVETICA_10, 220, 252, 231);
        }
        else if (canClaim)
        {
            draw3DButton(qx + 72, qCardY + 10, qCardW - 84, 26, "CLAIM SKIN!", true, 0);
        }
        else
        {
            drawFilledSmoothRect((float)(qx + 72), (float)(qCardY + 12), (float)(qCardW - 84), 24, 6, 0.14f, 0.18f, 0.26f, 0.85f);
            drawSharpText(qx + 86, qCardY + 18, "[LOCKED - 5 FLRS]", GLUT_BITMAP_HELVETICA_10, 148, 163, 184);
        }
    }

    // Challenge 2: Juventus CR7 Skin
    {
        int qx = 394;
        bool isDone = questJuventusClaimed || cr7JuventusUnlocked;
        bool canClaim = (totalStars >= 15) && !isDone;
        drawFilledSmoothRect((float)qx, (float)qCardY, (float)qCardW, (float)qCardH, 12, 0.10f, 0.14f, 0.22f, 0.95f);
        drawSmoothRectOutline((float)qx, (float)qCardY, (float)qCardW, (float)qCardH, 12, isDone ? 0.13f : (canClaim ? 0.98f : 0.35f), isDone ? 0.77f : (canClaim ? 0.82f : 0.42f), isDone ? 0.36f : 0.25f, 0.9f, 1.8f);

        if (cr7JuventusTex != -1)
            iShowImageAlpha(qx + 8, qCardY + 14, 58, 64, cr7JuventusTex, 1.0f);

        drawSharpText(qx + 72, qCardY + 68, "JUVENTUS CR7", GLUT_BITMAP_HELVETICA_12, 254, 240, 138);
        int stars = (totalStars > 15) ? 15 : totalStars;
        char progStr[32];
        sprintf(progStr, "Collect 15 Stars (%d/15)", stars);
        drawSharpText(qx + 72, qCardY + 48, progStr, GLUT_BITMAP_HELVETICA_10, 148, 163, 184);

        if (isDone)
        {
            drawFilledSmoothRect((float)(qx + 72), (float)(qCardY + 12), (float)(qCardW - 84), 24, 6, 0.08f, 0.38f, 0.18f, 0.90f);
            drawSharpText(qx + 88, qCardY + 18, "✓ UNLOCKED", GLUT_BITMAP_HELVETICA_10, 220, 252, 231);
        }
        else if (canClaim)
        {
            draw3DButton(qx + 72, qCardY + 10, qCardW - 84, 26, "CLAIM SKIN!", true, 0);
        }
        else
        {
            drawFilledSmoothRect((float)(qx + 72), (float)(qCardY + 12), (float)(qCardW - 84), 24, 6, 0.14f, 0.18f, 0.26f, 0.85f);
            drawSharpText(qx + 84, qCardY + 18, "[LOCKED - 15 STARS]", GLUT_BITMAP_HELVETICA_10, 148, 163, 184);
        }
    }

    // Challenge 3: RenoSir (LLM Researcher Collab & 1-Level Trial)
    {
        int qx = 646;
        bool isDone = characters[HERO_SAHA_RENO].unlocked;
        drawFilledSmoothRect((float)qx, (float)qCardY, (float)qCardW, (float)qCardH, 12, 0.10f, 0.14f, 0.22f, 0.95f);
        drawSmoothRectOutline((float)qx, (float)qCardY, (float)qCardW, (float)qCardH, 12, isDone ? 0.13f : 0.06f, isDone ? 0.77f : 0.70f, isDone ? 0.36f : 0.98f, 0.9f, 1.8f);

        if (characters[HERO_SAHA_RENO].skinTexID != -1)
            iShowImageAlpha(qx + 8, qCardY + 14, 58, 64, characters[HERO_SAHA_RENO].skinTexID, 1.0f);

        drawSharpText(qx + 72, qCardY + 68, "RENOSIR", GLUT_BITMAP_HELVETICA_12, 56, 189, 248);
        drawSharpText(qx + 72, qCardY + 48, "7-Day Login / 1-Level Trial", GLUT_BITMAP_HELVETICA_10, 148, 163, 184);

        if (isDone)
        {
            drawFilledSmoothRect((float)(qx + 72), (float)(qCardY + 12), (float)(qCardW - 84), 24, 6, 0.08f, 0.38f, 0.18f, 0.90f);
            drawSharpText(qx + 86, qCardY + 18, "✓ PERMANENT", GLUT_BITMAP_HELVETICA_10, 220, 252, 231);
        }
        else if (renoSirOneLevelTrial)
        {
            drawFilledSmoothRect((float)(qx + 72), (float)(qCardY + 12), (float)(qCardW - 84), 24, 6, 0.06f, 0.40f, 0.60f, 0.90f);
            drawSharpText(qx + 80, qCardY + 18, "TRIAL ACTIVE", GLUT_BITMAP_HELVETICA_10, 224, 242, 254);
        }
        else
        {
            draw3DButton(qx + 72, qCardY + 10, qCardW - 84, 26, "VIEW COLLAB", true, 0);
        }
    }

    // ---------------- DAILY LOGIN REWARDS (7 CALENDAR CARDS) ----------------
    drawSharpText(380, 218, "DAILY LOGIN TREASURES", GLUT_BITMAP_TIMES_ROMAN_24, 251, 191, 36);

    int calStartX = 72;
    int calSpacing = 126;
    int calCardW = 114;
    int calCardH = 135;
    int calY = 70;

    for (int d = 0; d < 7; d++)
    {
        int dayNum = d + 1;
        int cx = calStartX + d * calSpacing;
        bool isClaimed = (dayNum < dailyLoginDay) || (dayNum == dailyLoginDay && dailyRewardClaimedToday);
        bool isTodayReady = (dayNum == dailyLoginDay && !dailyRewardClaimedToday);
        bool isCardHov = (hoveredDailyCard == d);

        float pulse = (float)(sin(globalAnimTimer * 0.12) * 0.18 + 0.82);
        int cy = calY + (isTodayReady && isCardHov ? 5 : (isTodayReady ? 2 : 0));

        // Card Base
        if (isTodayReady)
            drawMetallicCard(cx, cy, calCardW, calCardH, 14, 0.18f, 0.24f, 0.42f, 0.98f, 0.98f * pulse, 0.82f * pulse, 0.25f, 4, true);
        else if (isClaimed)
            drawMetallicCard(cx, cy, calCardW, calCardH, 14, 0.10f, 0.14f, 0.20f, 0.80f, 0.13f, 0.77f, 0.36f, 2, false);
        else
            drawMetallicCard(cx, cy, calCardW, calCardH, 14, 0.08f, 0.11f, 0.16f, 0.88f, 0.28f, 0.35f, 0.46f, 2, false);

        // Header Tab
        char dayStr[16];
        sprintf(dayStr, "DAY %d", dayNum);
        if (isTodayReady)
        {
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + calCardH - 20), (float)(calCardW - 16), 16, 5, 0.98f, 0.78f, 0.15f, 1.0f);
            drawSharpText(cx + 36, cy + calCardH - 17, dayStr, GLUT_BITMAP_HELVETICA_10, 20, 25, 40);
        }
        else if (isClaimed)
        {
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + calCardH - 20), (float)(calCardW - 16), 16, 5, 0.08f, 0.38f, 0.18f, 0.90f);
            drawSharpText(cx + 36, cy + calCardH - 17, dayStr, GLUT_BITMAP_HELVETICA_10, 220, 252, 231);
        }
        else
        {
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + calCardH - 20), (float)(calCardW - 16), 16, 5, 0.14f, 0.18f, 0.26f, 0.85f);
            drawSharpText(cx + 36, cy + calCardH - 17, dayStr, GLUT_BITMAP_HELVETICA_10, 148, 163, 184);
        }

        // 3D Item Showcase
        int itemCenterY = cy + 70;
        if (d == 0) // Day 1: 50 Gems
        {
            draw3DGem(cx + calCardW / 2, itemCenterY, 15, pulse);
            drawSharpText(cx + 26, cy + 42, "50 GEMS", GLUT_BITMAP_HELVETICA_10, 56, 189, 248);
        }
        else if (d == 1) // Day 2: 100 Coins
        {
            draw3DCoin(cx + calCardW / 2 - 8, itemCenterY - 2, 11, 0);
            draw3DCoin(cx + calCardW / 2 + 8, itemCenterY - 2, 11, 0);
            draw3DCoin(cx + calCardW / 2, itemCenterY + 3, 12, pulse);
            drawSharpText(cx + 22, cy + 42, "100 COINS", GLUT_BITMAP_HELVETICA_10, 251, 191, 36);
        }
        else if (d == 2) // Day 3: Magic Key
        {
            draw3DKey(cx + calCardW / 2, itemCenterY, 0.85);
            drawSharpText(cx + 22, cy + 42, "MAGIC KEY", GLUT_BITMAP_HELVETICA_10, 251, 191, 36);
        }
        else if (d == 3) // Day 4: Hint Pass
        {
            draw3DScroll(cx + calCardW / 2, itemCenterY, 14);
            drawSharpText(cx + 24, cy + 42, "HINT PASS", GLUT_BITMAP_HELVETICA_10, 254, 243, 199);
        }
        else if (d == 4) // Day 5: Royal Shield
        {
            draw3DShield(cx + calCardW / 2, itemCenterY, 16);
            drawSharpText(cx + 17, cy + 42, "ROYAL SHIELD", GLUT_BITMAP_HELVETICA_10, 147, 197, 253);
        }
        else if (d == 5) // Day 6: 250 Gems
        {
            draw3DGemCluster(cx + calCardW / 2, itemCenterY, 12, pulse);
            drawSharpText(cx + 24, cy + 42, "250 GEMS", GLUT_BITMAP_HELVETICA_10, 192, 132, 252);
        }
        else if (d == 6) // Day 7: RenoSir Unlocked!
        {
            drawFilledSmoothRect((float)(cx + 12), (float)(cy + 42), (float)(calCardW - 24), 7, 3, 0.98f, 0.78f, 0.15f, 0.95f);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(0.06f, 0.70f, 0.98f, 0.35f * pulse);
            iFilledCircle(cx + calCardW / 2, itemCenterY, 24);
            glDisable(GL_BLEND);

            int sahaTex = characters[HERO_SAHA_RENO].skinTexID;
            if (sahaTex != -1)
                iShowImageAlpha(cx + 28, cy + 48, 56, 56, sahaTex, 1.0f);

            drawStarShape(cx + calCardW / 2, cy + 106, 6.0, 3.0, 251, 191, 36, true);
            drawSharpText(cx + 20, cy + 38, "RENOSIR!", GLUT_BITMAP_HELVETICA_10, 251, 191, 36);
        }

        // Action plate
        if (isClaimed)
        {
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + 6), (float)(calCardW - 16), 22, 5, 0.08f, 0.35f, 0.16f, 0.90f);
            drawSmoothRectOutline((float)(cx + 8), (float)(cy + 6), (float)(calCardW - 16), 22, 5, 0.13f, 0.77f, 0.36f, 0.85f, 1.2f);
            drawSharpText(cx + 16, cy + 12, "✓ CLAIMED", GLUT_BITMAP_HELVETICA_10, 240, 253, 244);
        }
        else if (isTodayReady)
        {
            draw3DButton(cx + 8, cy + 6, calCardW - 16, 24, "PENALTY!", isCardHov, 0);
        }
        else
        {
            drawFilledSmoothRect((float)(cx + 8), (float)(cy + 6), (float)(calCardW - 16), 22, 5, 0.10f, 0.14f, 0.20f, 0.85f);
            drawSmoothRectOutline((float)(cx + 8), (float)(cy + 6), (float)(calCardW - 16), 22, 5, 0.26f, 0.32f, 0.44f, 0.60f, 1.0f);
            drawSharpText(cx + 28, cy + 12, "[LOCKED]", GLUT_BITMAP_HELVETICA_10, 148, 163, 184);
        }
    }

    // ---------------- 3D HIGH-RELIEF BOTTOM CLAIM ACTION BUTTON ----------------
    int btnW = 390, btnH = 46;
    int btnX = (SCREEN_WIDTH - btnW) / 2, btnY = 16;
    if (!dailyRewardClaimedToday)
    {
        char claimBtnTxt[64];
        sprintf(claimBtnTxt, "★ KICK PENALTY: CLAIM DAY %d REWARD ★", dailyLoginDay);
        draw3DButton(btnX, btnY, btnW, btnH, claimBtnTxt, hoveredEventsClaimBtn, 0);
    }
    else
    {
        draw3DButton(btnX, btnY, btnW, btnH, "★ REMATCH: CR7 VS MESSI (+25 COINS) ★", hoveredEventsClaimBtn, 2);
    }
}

/* -------------------- 3. STATE_CHARACTER_SELECT: 6 HEROES SCREEN -------------------- */
void drawCharacterSelectScreen()
{
    if (menuBgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgTex);
    else if (levelBgTextures[1] != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelBgTextures[1]);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.06f, 0.08f, 0.14f, 0.65f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    drawDiamond(60, 585, 28, 0.18f, 0.22f, 0.32f, 0.98f);
    drawDiamondOutline(60, 585, 28, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(52, 576, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    drawSharpText(370, 585, "CHOOSE YOUR CHAMPION", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    int cardW = 145;
    int cardH = 425;
    int startX = 35;
    int cardSpacing = 160;
    int cardY = 90;

    for (int i = 0; i < HERO_COUNT; i++)
    {
        int cx = startX + i * cardSpacing;
        bool isSel = (i == selectedHero);
        bool hov = (hoveredHeroCardIndex == i);
        int cy = cardY + (hov ? 8 : 0);

        bool isUnlocked = characters[i].unlocked;
        bool isTrial = (i == HERO_SAHA_RENO && sahaRenoTrialActive);

        if (isSel)
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.88f, 0.22f, 0.18f, 0.95f, 0.98f, 0.82f, 0.25f, 4, true);
        else
            drawMetallicCard(cx, cy, cardW, cardH, 20, 0.16f, 0.20f, 0.28f, 0.92f, 0.65f, 0.70f, 0.80f, 2, hov);

        drawFilledSmoothRect((float)(cx + 8), (float)(cy + 155), (float)(cardW - 16), 255, 14, 0.22f, 0.26f, 0.36f, 0.90f);

        int tex = characters[i].skinTexID;
        if (tex != -1)
        {
            if (i == HERO_SAHA_RENO)
                iShowImageAlphaFlipped(cx + 12, cy + 165, cardW - 24, 160, tex, 1.0f);
            else
                iShowImageAlpha(cx + 12, cy + 165, cardW - 24, 160, tex, 1.0f);
        }

        // CR7 Skin Switcher Buttons
        if (i == HERO_CR7)
        {
            int kw = 40, kh = 22;
            int ky = cy + 160;
            // Kit 0: Devil
            drawFilledSmoothRect((float)(cx + 9), (float)ky, (float)kw, (float)kh, 4, (cr7SkinSelected == 0) ? 0.85f : 0.25f, 0.15f, 0.15f, 0.95f);
            drawSmoothRectOutline((float)(cx + 9), (float)ky, (float)kw, (float)kh, 4, (cr7SkinSelected == 0) ? 0.98f : 0.45f, 0.82f, 0.25f, 1.0f, 1.2f);
            drawSharpText(cx + 14, ky + 5, "RED", GLUT_BITMAP_HELVETICA_10, 255, 255, 255);

            // Kit 1: Real Madrid
            drawFilledSmoothRect((float)(cx + 52), (float)ky, (float)kw, (float)kh, 4, (cr7SkinSelected == 1) ? 0.90f : 0.20f, (cr7SkinSelected == 1) ? 0.90f : 0.20f, 0.25f, 0.95f);
            drawSmoothRectOutline((float)(cx + 52), (float)ky, (float)kw, (float)kh, 4, cr7MadridUnlocked ? 0.98f : 0.35f, cr7MadridUnlocked ? 0.82f : 0.35f, 0.25f, 1.0f, 1.2f);
            drawSharpText(cx + 57, ky + 5, cr7MadridUnlocked ? "MAD" : "[LK]", GLUT_BITMAP_HELVETICA_10, cr7MadridUnlocked ? 251 : 148, cr7MadridUnlocked ? 191 : 163, cr7MadridUnlocked ? 36 : 184);

            // Kit 2: Juventus
            drawFilledSmoothRect((float)(cx + 95), (float)ky, (float)kw, (float)kh, 4, (cr7SkinSelected == 2) ? 0.50f : 0.15f, (cr7SkinSelected == 2) ? 0.50f : 0.15f, 0.18f, 0.95f);
            drawSmoothRectOutline((float)(cx + 95), (float)ky, (float)kw, (float)kh, 4, cr7JuventusUnlocked ? 0.98f : 0.35f, cr7JuventusUnlocked ? 0.82f : 0.35f, 0.25f, 1.0f, 1.2f);
            drawSharpText(cx + 100, ky + 5, cr7JuventusUnlocked ? "JUV" : "[LK]", GLUT_BITMAP_HELVETICA_10, cr7JuventusUnlocked ? 251 : 148, cr7JuventusUnlocked ? 191 : 163, cr7JuventusUnlocked ? 36 : 184);
        }

        drawSharpText(cx + 10, cy + 125, characters[i].name, GLUT_BITMAP_HELVETICA_12, 255, 255, 255);
        drawSharpText(cx + 10, cy + 100, characters[i].title, GLUT_BITMAP_HELVETICA_10, 251, 191, 36);
        drawSharpText(cx + 10, cy + 70, characters[i].perkName, GLUT_BITMAP_HELVETICA_10, 148, 163, 184);

        if (isUnlocked)
        {
            if (isSel)
                drawMetallicButton(cx + 12, cy + 15, cardW - 24, 38, "EQUIPPED", false, 0);
            else
                drawMetallicButton(cx + 12, cy + 15, cardW - 24, 38, "EQUIP", hov, 2);
        }
        else if (isTrial || (i == HERO_SAHA_RENO && renoSirOneLevelTrial))
        {
            if (i == HERO_SAHA_RENO && renoSirOneLevelTrial)
            {
                drawSharpText(cx + 14, cy + 56, "1-LEVEL TRIAL ACTIVE", GLUT_BITMAP_HELVETICA_10, 56, 189, 248);
            }
            else
            {
                int sec = sahaRenoTrialFrames / 60;
                char tStr[32];
                sprintf(tStr, "TRIAL: %02d:%02d", sec / 60, sec % 60);
                drawSharpText(cx + 28, cy + 56, tStr, GLUT_BITMAP_HELVETICA_10, 56, 189, 248);
            }

            if (isSel)
                drawMetallicButton(cx + 12, cy + 15, cardW - 24, 38, "EQUIPPED", false, 0);
            else
                drawMetallicButton(cx + 12, cy + 15, cardW - 24, 38, "EQUIP TRIAL", hov, 2);
        }
        else // Locked (RenoSir)
        {
            drawSharpText(cx + 42, cy + 56, "[LOCKED]", GLUT_BITMAP_HELVETICA_12, 239, 68, 68);
            draw3DButton(cx + 8, cy + 12, cardW - 16, 36, "VIEW COLLAB", hov, 0);
        }
    }
}

/* -------------------- 3. STATE_LEVEL_SELECT: CHAPTER 1 MAP (FLOORS 1 - 12) -------------------- */
void drawLevelSelectScreen()
{
    if (levelBgTextures[0] != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelBgTextures[0]);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.06f, 0.08f, 0.14f, 0.55f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    drawDiamond(60, 585, 28, 0.18f, 0.22f, 0.32f, 0.98f);
    drawDiamondOutline(60, 585, 28, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(52, 576, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    drawSharpText(390, 585, "CHAPTER 1: PRINCESS CASTLE", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    int doorW = 75;
    int doorH = 135;
    int colSpacing = 136;
    int startX = 110;

    // Row 1: Floors 1 to 6
    for (int col = 0; col < 6; col++)
    {
        int fNum = col + 1;
        int dx = startX + col * colSpacing;
        bool hov = (hoveredLevelDoor == fNum);
        int dy = 345 + (hov ? 8 : 0);
        bool unlocked = (fNum <= unlockedLevels);

        if (unlocked)
        {
            drawMetallicCard(dx, dy, doorW, doorH, 16, 0.88f, 0.25f, 0.18f, 0.95f, 0.98f, 0.82f, 0.25f, 3, hov);
            char numStr[16];
            sprintf(numStr, "%d", fNum);
            drawSharpText(dx + (doorW - 12) / 2, dy + doorH / 2 - 10, numStr, GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

            for (int s = 0; s < 3; s++)
            {
                bool earned = (s < levelStars[fNum - 1]);
                drawUIStar(dx + 18 + s * 20, dy + 20, earned, 0.85);
            }
        }
        else
        {
            drawMetallicCard(dx, dy, doorW, doorH, 16, 0.18f, 0.22f, 0.30f, 0.88f, 0.40f, 0.45f, 0.55f, 2, false);
            iSetColor(148, 163, 184);
            iFilledRectangle(dx + doorW / 2 - 14, dy + doorH / 2 - 14, 28, 24);
            iCircle(dx + doorW / 2, dy + doorH / 2 + 10, 10);
        }
    }

    // Row 2: Floors 7 to 12
    for (int col = 0; col < 6; col++)
    {
        int fNum = col + 7;
        int dx = startX + col * colSpacing;
        bool hov = (hoveredLevelDoor == fNum);
        int dy = 165 + (hov ? 8 : 0);
        bool unlocked = (fNum <= unlockedLevels);

        if (unlocked)
        {
            drawMetallicCard(dx, dy, doorW, doorH, 16, 0.88f, 0.25f, 0.18f, 0.95f, 0.98f, 0.82f, 0.25f, 3, hov);
            char numStr[16];
            sprintf(numStr, "%d", fNum);
            drawSharpText(dx + (doorW - 12) / 2, dy + doorH / 2 - 10, numStr, GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

            for (int s = 0; s < 3; s++)
            {
                bool earned = (s < levelStars[fNum - 1]);
                drawUIStar(dx + 18 + s * 20, dy + 20, earned, 0.85);
            }
        }
        else
        {
            drawMetallicCard(dx, dy, doorW, doorH, 16, 0.18f, 0.22f, 0.30f, 0.88f, 0.40f, 0.45f, 0.55f, 2, false);
            iSetColor(148, 163, 184);
            iFilledRectangle(dx + doorW / 2 - 14, dy + doorH / 2 - 14, 28, 24);
            iCircle(dx + doorW / 2, dy + doorH / 2 + 10, 10);
        }
    }
}

/* -------------------- 4. STATE_CHAPTER2_SELECT: CHAPTER 2 MAP (FLOORS 13 - 16) -------------------- */
void drawChapter2SelectScreen()
{
    if (chapter2BgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, chapter2BgTex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.06f, 0.08f, 0.14f, 0.55f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    drawDiamond(60, 585, 28, 0.18f, 0.22f, 0.32f, 0.98f);
    drawDiamondOutline(60, 585, 28, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(52, 576, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    drawSharpText(390, 585, "CHAPTER 2: THE CITADEL", GLUT_BITMAP_TIMES_ROMAN_24, 56, 189, 248);

    int doorW = 85;
    int doorH = 150;
    int colSpacing = 180;
    int startX = 200;

    for (int col = 0; col < 4; col++)
    {
        int fNum = col + 13;
        int dx = startX + col * colSpacing;
        bool hov = (hoveredLevelDoor == fNum);
        int dy = 260 + (hov ? 8 : 0);
        bool unlocked = (fNum <= unlockedLevels);

        if (unlocked)
        {
            drawMetallicCard(dx, dy, doorW, doorH, 18, 0.18f, 0.28f, 0.42f, 0.95f, 0.38f, 0.82f, 0.98f, 4, hov);
            char numStr[16];
            sprintf(numStr, "%d", fNum);
            drawSharpText(dx + (doorW - 16) / 2, dy + doorH / 2 - 10, numStr, GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

            for (int s = 0; s < 3; s++)
            {
                bool earned = (s < levelStars[fNum - 1]);
                drawUIStar(dx + 20 + s * 22, dy + 22, earned, 0.9);
            }
        }
        else
        {
            drawMetallicCard(dx, dy, doorW, doorH, 18, 0.18f, 0.22f, 0.30f, 0.88f, 0.40f, 0.45f, 0.55f, 2, false);
            iSetColor(148, 163, 184);
            iFilledRectangle(dx + doorW / 2 - 14, dy + doorH / 2 - 14, 28, 24);
            iCircle(dx + doorW / 2, dy + doorH / 2 + 10, 10);
        }
    }
}

/* -------------------- 4b. STATE_CHAPTER3_SELECT: CHAPTER 3 MAP (FLOORS 17 - 20) -------------------- */
void drawChapter3SelectScreen()
{
    if (chapter3BgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, chapter3BgTex);
    else if (levelBgTextures[6] != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelBgTextures[6]);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08f, 0.04f, 0.16f, 0.65f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    drawDiamond(60, 585, 28, 0.22f, 0.16f, 0.36f, 0.98f);
    drawDiamondOutline(60, 585, 28, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(52, 576, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    drawSharpText(370, 585, "CHAPTER 3: WITCH TOWER", GLUT_BITMAP_TIMES_ROMAN_24, 192, 132, 252);

    int doorW = 85;
    int doorH = 150;
    int colSpacing = 180;
    int startX = 200;

    for (int col = 0; col < 4; col++)
    {
        int fNum = col + 17;
        int dx = startX + col * colSpacing;
        bool hov = (hoveredLevelDoor == fNum);
        int dy = 260 + (hov ? 8 : 0);
        bool unlocked = (fNum <= unlockedLevels);

        if (unlocked)
        {
            drawMetallicCard(dx, dy, doorW, doorH, 18, 0.26f, 0.18f, 0.42f, 0.95f, 0.75f, 0.52f, 0.98f, 4, hov);
            char numStr[16];
            sprintf(numStr, "%d", fNum);
            drawSharpText(dx + (doorW - 16) / 2, dy + doorH / 2 - 10, numStr, GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

            for (int s = 0; s < 3; s++)
            {
                bool earned = (s < levelStars[fNum - 1]);
                drawUIStar(dx + 20 + s * 22, dy + 22, earned, 0.9);
            }
        }
        else
        {
            drawMetallicCard(dx, dy, doorW, doorH, 18, 0.18f, 0.15f, 0.26f, 0.88f, 0.45f, 0.40f, 0.55f, 2, false);
            iSetColor(148, 163, 184);
            iFilledRectangle(dx + doorW / 2 - 14, dy + doorH / 2 - 14, 28, 24);
            iCircle(dx + doorW / 2, dy + doorH / 2 + 10, 10);
        }
    }
}

/* -------------------- 4c. STATE_CHAPTER4_SELECT: CHAPTER 4 MAP (FLOORS 21 - 24) -------------------- */
void drawChapter4SelectScreen()
{
    if (chapter4BgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, chapter4BgTex);
    else if (levelBgTextures[0] != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelBgTextures[0]);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.14f, 0.05f, 0.04f, 0.65f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    drawDiamond(60, 585, 28, 0.32f, 0.16f, 0.16f, 0.98f);
    drawDiamondOutline(60, 585, 28, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(52, 576, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    drawSharpText(360, 585, "CHAPTER 4: DRAGON'S KEEP", GLUT_BITMAP_TIMES_ROMAN_24, 251, 146, 60);

    int doorW = 85;
    int doorH = 150;
    int colSpacing = 180;
    int startX = 200;

    for (int col = 0; col < 4; col++)
    {
        int fNum = col + 21;
        int dx = startX + col * colSpacing;
        bool hov = (hoveredLevelDoor == fNum);
        int dy = 260 + (hov ? 8 : 0);
        bool unlocked = (fNum <= unlockedLevels);

        if (unlocked)
        {
            drawMetallicCard(dx, dy, doorW, doorH, 18, 0.38f, 0.16f, 0.14f, 0.95f, 0.98f, 0.65f, 0.25f, 4, hov);
            char numStr[16];
            sprintf(numStr, "%d", fNum);
            drawSharpText(dx + (doorW - 16) / 2, dy + doorH / 2 - 10, numStr, GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

            for (int s = 0; s < 3; s++)
            {
                bool earned = (s < levelStars[fNum - 1]);
                drawUIStar(dx + 20 + s * 22, dy + 22, earned, 0.9);
            }
        }
        else
        {
            drawMetallicCard(dx, dy, doorW, doorH, 18, 0.22f, 0.15f, 0.15f, 0.88f, 0.55f, 0.40f, 0.40f, 2, false);
            iSetColor(148, 163, 184);
            iFilledRectangle(dx + doorW / 2 - 14, dy + doorH / 2 - 14, 28, 24);
            iCircle(dx + doorW / 2, dy + doorH / 2 + 10, 10);
        }
    }
}

/* -------------------- 5. STATE_SETTINGS: SETTINGS MENU (IMAGE 4 CLONE) -------------------- */
void drawSettingsMenu()
{
    // Solid dark slate background (RGB: 35, 36, 51)
    iSetColor(35, 36, 51);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Top-Left: Diamond return button "<"
    drawDiamond(60, 585, 26, 0.18f, 0.22f, 0.32f, 0.98f);
    drawDiamondOutline(60, 585, 26, 1.0f, 1.0f, 1.0f, 2.5f);
    drawSharpText(53, 577, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    // Top-Right: Version label
    drawSharpText(880, 580, "v1.9.0a", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // Twin Decorative Horizontal Diamond Rails (<>====================<>)
    // Top Rail at y = 490
    drawDiamond(170, 490, 10, 0.55f, 0.60f, 0.70f);
    drawDiamondOutline(170, 490, 10, 0.85f, 0.90f, 0.98f, 1.5f);
    drawDiamond(854, 490, 10, 0.55f, 0.60f, 0.70f);
    drawDiamondOutline(854, 490, 10, 0.85f, 0.90f, 0.98f, 1.5f);
    iSetColor(110, 120, 145);
    iLine(184, 490, 840, 490);

    // Bottom Rail at y = 200
    drawDiamond(170, 200, 10, 0.55f, 0.60f, 0.70f);
    drawDiamondOutline(170, 200, 10, 0.85f, 0.90f, 0.98f, 1.5f);
    drawDiamond(854, 200, 10, 0.55f, 0.60f, 0.70f);
    drawDiamondOutline(854, 200, 10, 0.85f, 0.90f, 0.98f, 1.5f);
    iSetColor(110, 120, 145);
    iLine(184, 200, 840, 200);

    // ---------------- LEFT COLUMN (SOUND, ENGLISH, NEW GAMES) ----------------
    int col1X = 230;

    // 1. Sound Card
    int sndY = 390;
    drawFilledSmoothRect((float)col1X, (float)sndY, 70.0f, 70.0f, 16, 0.16f, 0.18f, 0.25f, 0.95f);
    drawSmoothRectOutline((float)col1X, (float)sndY, 70.0f, 70.0f, 16, 1.0f, 1.0f, 1.0f, 1.0f, 2.5f);
    // Speaker Icon
    iSetColor(255, 255, 255);
    iFilledRectangle(col1X + 20, sndY + 27, 10, 16);
    double sx_pts[3] = { (double)(col1X + 30), (double)(col1X + 44), (double)(col1X + 44) };
    double sy_pts[3] = { (double)(sndY + 35), (double)(sndY + 47), (double)(sndY + 23) };
    iFilledPolygon(sx_pts, sy_pts, 3);
    if (soundEnabled)
    {
        iCircle(col1X + 38, sndY + 35, 12);
        iCircle(col1X + 38, sndY + 35, 17);
    }
    else
    {
        iSetColor(239, 68, 68);
        iLine(col1X + 16, sndY + 18, col1X + 54, sndY + 52);
    }
    drawSharpText(col1X + 90, sndY + 27, "Sound", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // 2. English Language Card
    int langY = 300;
    drawFilledSmoothRect((float)col1X, (float)langY, 70.0f, 70.0f, 16, 0.16f, 0.18f, 0.25f, 0.95f);
    drawSmoothRectOutline((float)col1X, (float)langY, 70.0f, 70.0f, 16, 1.0f, 1.0f, 1.0f, 1.0f, 2.5f);
    // Globe Icon
    iSetColor(255, 255, 255);
    iCircle(col1X + 35, langY + 35, 18);
    iEllipse(col1X + 35, langY + 35, 9, 18);
    iLine(col1X + 17, langY + 35, col1X + 53, langY + 35);
    drawSharpText(col1X + 90, langY + 27, "English", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // 3. New Games Card
    int ngY = 210;
    drawFilledSmoothRect((float)col1X, (float)ngY, 70.0f, 70.0f, 16, 0.16f, 0.18f, 0.25f, 0.95f);
    drawSmoothRectOutline((float)col1X, (float)ngY, 70.0f, 70.0f, 16, 1.0f, 1.0f, 1.0f, 1.0f, 2.5f);
    // Bell Icon
    iSetColor(251, 191, 36);
    iFilledCircle(col1X + 35, ngY + 38, 14);
    iFilledRectangle(col1X + 20, ngY + 24, 30, 8);
    iSetColor(239, 68, 68); // Red notification dot
    iFilledCircle(col1X + 46, ngY + 48, 5);
    drawSharpText(col1X + 90, ngY + 38, "New Games", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);
    drawSharpText(col1X + 90, ngY + 18, "More info", GLUT_BITMAP_HELVETICA_12, 251, 191, 36);

    // ---------------- RIGHT COLUMN (RESET PROGRESS, RESTORE PURCHASES) ----------------
    int col2X = 520;
    int pillW = 270, pillH = 58;

    // 1. Reset progress button
    int rstY = 370;
    drawFilledSmoothRect((float)col2X, (float)rstY, (float)pillW, (float)pillH, 26, 0.16f, 0.18f, 0.25f, 0.95f);
    drawSmoothRectOutline((float)col2X, (float)rstY, (float)pillW, (float)pillH, 26, 1.0f, 1.0f, 1.0f, 1.0f, 2.5f);
    drawSharpText(col2X + 65, rstY + 22, "Reset progress", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // 2. Restore purchases button
    int rstPurY = 270;
    drawFilledSmoothRect((float)col2X, (float)rstPurY, (float)pillW, (float)pillH, 26, 0.16f, 0.18f, 0.25f, 0.95f);
    drawSmoothRectOutline((float)col2X, (float)rstPurY, (float)pillW, (float)pillH, 26, 1.0f, 1.0f, 1.0f, 1.0f, 2.5f);
    drawSharpText(col2X + 50, rstPurY + 22, "Restore purchases", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // ---------------- BOTTOM: FOLLOW US & USER ID ----------------
    drawSharpText(320, 132, "Follow us:", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    // Steam Icon
    int steamX = 530, steamY = 118, socSize = 44;
    drawFilledSmoothRect((float)steamX, (float)steamY, (float)socSize, (float)socSize, 12, 0.10f, 0.20f, 0.35f, 1.0f);
    iSetColor(255, 255, 255);
    iCircle(steamX + 22, steamY + 22, 12);
    iFilledCircle(steamX + 27, steamY + 27, 4);

    // X / Twitter Icon
    int xIconX = 605, xIconY = 118;
    drawFilledSmoothRect((float)xIconX, (float)xIconY, (float)socSize, (float)socSize, 12, 0.12f, 0.58f, 0.95f, 1.0f);
    drawSharpText(xIconX + 16, xIconY + 12, "X", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    // Share Icon
    int shareX = 680, shareY = 118;
    iSetColor(255, 255, 255);
    iFilledCircle(shareX + 32, shareY + 34, 5);
    iFilledCircle(shareX + 32, shareY + 12, 5);
    iFilledCircle(shareX + 14, shareY + 23, 5);
    iLine(shareX + 14, shareY + 23, shareX + 32, shareY + 34);
    iLine(shareX + 14, shareY + 23, shareX + 32, shareY + 12);

    // Footer UserID
    drawSharpText(370, 50, "UserID: 2f565382fffe9af7cc110c12528f5f49", GLUT_BITMAP_HELVETICA_12, 148, 163, 184);
}

/* -------------------- MODERN FROSTED GLASS TOUCH CONTROLS -------------------- */
void drawAuthenticTouchArrow(int x, int y, int size, bool pointingLeft, bool active)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Soft ambient drop shadow beneath glass capsule
    glColor4f(0.0f, 0.0f, 0.0f, active ? 0.40f : 0.25f);
    iFilledCircle(x + size / 2, y + size / 2 - 4, size / 2 - 2);

    // 2. Translucent Frosted Glass Base
    float baseAlpha = active ? 0.38f : 0.22f;
    drawFilledSmoothRect((float)x, (float)y, (float)size, (float)size, 20, 0.88f, 0.94f, 1.0f, baseAlpha);

    // 3. Top-Half Gloss Specular Reflection (Curved Glass Sheen)
    float glossAlpha = active ? 0.50f : 0.32f;
    drawFilledSmoothRect((float)(x + 4), (float)(y + size / 2), (float)(size - 8), (float)(size / 2 - 4), 16, 1.0f, 1.0f, 1.0f, glossAlpha);

    // 4. Luminous Glass Outline Rim (Bright top, subtle cyan-frosted refraction bottom)
    drawSmoothRectOutline((float)x, (float)y, (float)size, (float)size, 20, 1.0f, 1.0f, 1.0f, active ? 0.95f : 0.75f, 2.2f);
    drawSmoothRectOutline((float)(x + 2), (float)(y + 2), (float)(size - 4), (float)(size - 4), 18, 0.56f, 0.85f, 1.0f, active ? 0.70f : 0.35f, 1.0f);

    // 5. Pressed Inner Glass Dispersion Glow
    if (active)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glColor4f(0.22f, 0.74f, 1.0f, 0.35f);
        iFilledCircle(x + size / 2, y + size / 2, size / 2 - 6);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    // 6. Sleek Refractive Glass Arrow Icon (Frosted White & Luminous Ice Cyan)
    double tx[3], ty[3];
    int triPad = 22;
    int pressShift = active ? -1 : 0;
    if (pointingLeft)
    {
        tx[0] = x + size - triPad; ty[0] = y + triPad + pressShift;
        tx[1] = x + size - triPad; ty[1] = y + size - triPad + pressShift;
        tx[2] = x + triPad;        ty[2] = y + size / 2.0 + pressShift;
    }
    else
    {
        tx[0] = x + triPad;        ty[0] = y + triPad + pressShift;
        tx[1] = x + triPad;        ty[1] = y + size - triPad + pressShift;
        tx[2] = x + size - triPad; ty[2] = y + size / 2.0 + pressShift;
    }

    // Arrow shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
    double stx[3] = { tx[0] + 1, tx[1] + 1, tx[2] + 1 };
    double sty[3] = { ty[0] - 2, ty[1] - 2, ty[2] - 2 };
    iFilledPolygon(stx, sty, 3);

    // Arrow body: frosted crystal white / cyan
    if (active)
        glColor4f(0.35f, 0.85f, 1.0f, 0.98f);
    else
        glColor4f(0.95f, 0.98f, 1.0f, 0.90f);
    iFilledPolygon(tx, ty, 3);

    // Arrow crisp highlight line
    iSetColor(255, 255, 255);
    iLine(tx[0], ty[0], tx[2], ty[2]);

    glDisable(GL_BLEND);
}

void drawAuthenticTouchJump(int x, int y, int size, bool active)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Ambient drop shadow beneath glass capsule
    glColor4f(0.0f, 0.0f, 0.0f, active ? 0.40f : 0.25f);
    iFilledCircle(x + size / 2, y + size / 2 - 4, size / 2 - 2);

    // 2. Translucent Frosted Glass Base
    float baseAlpha = active ? 0.38f : 0.22f;
    drawFilledSmoothRect((float)x, (float)y, (float)size, (float)size, 20, 0.88f, 0.94f, 1.0f, baseAlpha);

    // 3. Top-Half Gloss Specular Reflection (Curved Glass Sheen)
    float glossAlpha = active ? 0.50f : 0.32f;
    drawFilledSmoothRect((float)(x + 4), (float)(y + size / 2), (float)(size - 8), (float)(size / 2 - 4), 16, 1.0f, 1.0f, 1.0f, glossAlpha);

    // 4. Luminous Glass Outline Rim
    drawSmoothRectOutline((float)x, (float)y, (float)size, (float)size, 20, 1.0f, 1.0f, 1.0f, active ? 0.95f : 0.75f, 2.2f);
    drawSmoothRectOutline((float)(x + 2), (float)(y + 2), (float)(size - 4), (float)(size - 4), 18, 0.56f, 0.85f, 1.0f, active ? 0.70f : 0.35f, 1.0f);

    // 5. Pressed Inner Glass Dispersion Glow
    if (active)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glColor4f(0.22f, 0.74f, 1.0f, 0.35f);
        iFilledCircle(x + size / 2, y + size / 2, size / 2 - 6);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    // 6. Sleek Refractive Glass Jump Chevron
    int triPad = 22;
    int pressShift = active ? -1 : 0;
    double tx[3] = { (double)(x + triPad), (double)(x + size - triPad), (double)(x + size / 2.0) };
    double ty[3] = { (double)(y + triPad + pressShift), (double)(y + triPad + pressShift), (double)(y + size - triPad + pressShift) };

    // Chevron shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
    double stx[3] = { tx[0] + 1, tx[1] + 1, tx[2] + 1 };
    double sty[3] = { ty[0] - 2, ty[1] - 2, ty[2] - 2 };
    iFilledPolygon(stx, sty, 3);

    // Chevron body: frosted crystal white / cyan
    if (active)
        glColor4f(0.35f, 0.85f, 1.0f, 0.98f);
    else
        glColor4f(0.95f, 0.98f, 1.0f, 0.90f);
    iFilledPolygon(tx, ty, 3);

    // Top edge highlight
    iSetColor(255, 255, 255);
    iLine(tx[0], ty[0], tx[2], ty[2]);

    glDisable(GL_BLEND);
}

void drawOnScreenTouchControls()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Top-Left: Diamond "?" Hint button
    drawDiamond(60, 585, 26, 0.16f, 0.20f, 0.28f, 0.95f);
    drawDiamondOutline(60, 585, 26, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(53, 576, "?", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    // Top-Right: Diamond "||" Pause button
    drawDiamond(960, 585, 26, 0.16f, 0.20f, 0.28f, 0.95f);
    drawDiamondOutline(960, 585, 26, 0.95f, 0.95f, 0.98f, 2.0f);
    drawSharpText(953, 576, "||", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

    // Top-Center: RenoSir 1-Level Trial Active HUD Badge
    if (renoSirOneLevelTrial && !characters[HERO_SAHA_RENO].unlocked)
    {
        drawFilledSmoothRect(410.0f, 575.0f, 204.0f, 32.0f, 10, 0.06f, 0.10f, 0.18f, 0.90f);
        drawSmoothRectOutline(410.0f, 575.0f, 204.0f, 32.0f, 10, 0.06f, 0.70f, 0.98f, 0.95f, 1.8f);
        drawSharpText(422, 584, "⚡ RENOSIR 1-LEVEL TRIAL", GLUT_BITMAP_HELVETICA_12, 56, 189, 248);
    }
    else if (sahaRenoTrialActive && !characters[HERO_SAHA_RENO].unlocked)
    {
        int sec = sahaRenoTrialFrames / 60;
        char trialStr[32];
        sprintf(trialStr, "TRIAL: %02d:%02d", sec / 60, sec % 60);
        drawFilledSmoothRect(430.0f, 575.0f, 164.0f, 32.0f, 8, 0.08f, 0.12f, 0.20f, 0.90f);
        drawSmoothRectOutline(430.0f, 575.0f, 164.0f, 32.0f, 8, 0.06f, 0.70f, 0.98f, 0.95f, 1.8f);
        drawSharpText(458, 584, trialStr, GLUT_BITMAP_HELVETICA_12, 56, 189, 248);
    }

    // Bottom-Left: Authentic Touch Left "<"
    drawAuthenticTouchArrow(40, 25, 76, true, isTouchingLeft);

    // Bottom-Left: Authentic Touch Right ">"
    drawAuthenticTouchArrow(126, 25, 76, false, isTouchingRight);

    // Bottom-Right: Jump Button "^"
    drawAuthenticTouchJump(908, 25, 76, isTouchingJump);

    glDisable(GL_BLEND);
}

/* -------------------- TWO-TIER HINT MODAL WITH INSTANT RETURN -------------------- */
/* -------------------- IN-GAME HINT MODAL (IMAGE 2 CLONE) -------------------- */
void drawHintAdModal()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.04f, 0.06f, 0.12f, 0.78f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    int cardX = 212;
    int cardY = 175;
    int cardW = 600;
    int cardH = 290;

    // Multi-layer Clean White Card with crisp dark border
    drawFilledSmoothRect((float)cardX, (float)cardY, (float)cardW, (float)cardH, 18, 1.0f, 1.0f, 1.0f, 1.0f);
    drawSmoothRectOutline((float)cardX, (float)cardY, (float)cardW, (float)cardH, 18, 0.28f, 0.32f, 0.40f, 1.0f, 3.5f);
    drawSmoothRectOutline((float)(cardX + 4), (float)(cardY + 4), (float)(cardW - 8), (float)(cardH - 8), 14, 0.85f, 0.88f, 0.92f, 1.0f, 1.0f);

    // Top Header / Prompt Question
    if (hintTierRevealed == 0)
    {
        drawSharpText(cardX + 185, cardY + 215, "Do you want to watch", GLUT_BITMAP_TIMES_ROMAN_24, 30, 41, 59);
        drawSharpText(cardX + 115, cardY + 180, "an advertising video and get the hint?", GLUT_BITMAP_TIMES_ROMAN_24, 30, 41, 59);
    }
    else
    {
        drawSharpText(cardX + 225, cardY + 225, "HINT UNLOCKED!", GLUT_BITMAP_TIMES_ROMAN_24, 34, 197, 94);
        drawSharpText(cardX + 45, cardY + 185, levels[currentLevel].gentleHint, GLUT_BITMAP_HELVETICA_12, 30, 41, 59);
    }

    // Ornamental Diamond Divider (<>-------------------------<>)
    int divY = cardY + 140;
    drawDiamond(cardX + 50, divY, 8, 0.35f, 0.40f, 0.50f);
    drawDiamondOutline(cardX + 50, divY, 8, 0.15f, 0.20f, 0.30f, 1.5f);
    drawDiamond(cardX + cardW - 50, divY, 8, 0.35f, 0.40f, 0.50f);
    drawDiamondOutline(cardX + cardW - 50, divY, 8, 0.15f, 0.20f, 0.30f, 1.5f);
    iSetColor(71, 85, 105);
    iLine(cardX + 62, divY, cardX + cardW - 62, divY);

    // Two Buttons: YES (Green) & NO (White/Grey)
    int btnW = 115, btnH = 46;
    int yesX = cardX + 175, noX = cardX + 310, btnY = cardY + 45;

    // YES Button (Vibrant Green with 3D drop highlight)
    drawFilledSmoothRect((float)yesX, (float)btnY, (float)btnW, (float)btnH, 12, 0.29f, 0.87f, 0.35f, 1.0f);
    drawSmoothRectOutline((float)yesX, (float)btnY, (float)btnW, (float)btnH, 12, 0.13f, 0.65f, 0.24f, 1.0f, 2.5f);
    drawFilledSmoothRect((float)(yesX + 4), (float)(btnY + 2), (float)(btnW - 8), 4.0f, 2, 0.13f, 0.50f, 0.18f, 0.40f);
    drawSharpText(yesX + 38, btnY + 15, "YES", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // NO Button (White / Light Grey with grey outline)
    drawFilledSmoothRect((float)noX, (float)btnY, (float)btnW, (float)btnH, 12, 0.98f, 0.98f, 1.0f, 1.0f);
    drawSmoothRectOutline((float)noX, (float)btnY, (float)btnW, (float)btnH, 12, 0.45f, 0.50f, 0.60f, 1.0f, 2.5f);
    drawFilledSmoothRect((float)(noX + 4), (float)(btnY + 2), (float)(btnW - 8), 4.0f, 2, 0.35f, 0.40f, 0.50f, 0.30f);
    drawSharpText(noX + 44, btnY + 15, "NO", GLUT_BITMAP_HELVETICA_18, 71, 85, 105);
}

/* -------------------- CHAPTER 5 COMING SOON MODAL -------------------- */
void drawChapter5ComingSoonModal()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.04f, 0.06f, 0.12f, 0.82f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    int cardX = 232;
    int cardY = 150;
    int cardW = 560;
    int cardH = 340;

    drawMetallicCard(cardX, cardY, cardW, cardH, 24, 0.12f, 0.16f, 0.26f, 0.98f, 0.98f, 0.82f, 0.25f, 4, true);

    drawSharpText(cardX + 105, cardY + 270, "★ CHAPTER 5: ASTRAL SPIRE ★", GLUT_BITMAP_TIMES_ROMAN_24, 251, 191, 36);
    drawSharpText(cardX + 185, cardY + 225, "COMING SOON IN V3.0!", GLUT_BITMAP_HELVETICA_18, 56, 189, 248);

    drawSharpText(cardX + 45, cardY + 175, "Ascend into the celestial heavens! Our architects are actively forging", GLUT_BITMAP_HELVETICA_12, 226, 232, 240);
    drawSharpText(cardX + 45, cardY + 150, "12 anti-gravity orbital chambers, starlight dials, and brand-new", GLUT_BITMAP_HELVETICA_12, 226, 232, 240);
    drawSharpText(cardX + 45, cardY + 125, "legendary champion skins including Cyber RenoSir Ascendant!", GLUT_BITMAP_HELVETICA_12, 226, 232, 240);

    draw3DButton(cardX + 170, cardY + 45, 220, 50, "UNDERSTOOD", false, 0);
}

void drawChapter3ComingSoonModal()
{
    drawChapter5ComingSoonModal();
}

/* -------------------- RENOSIR COLLABORATION BANNER MODAL -------------------- */
void drawRenoSirCollabModal()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.04f, 0.06f, 0.12f, 0.82f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    int cardW = 760;
    int cardH = 510;
    int cardX = (SCREEN_WIDTH - cardW) / 2;
    int cardY = (SCREEN_HEIGHT - cardH) / 2;

    // Metallic frame with glowing cyan edge
    drawMetallicCard(cardX, cardY, cardW, cardH, 20, 0.08f, 0.12f, 0.18f, 0.98f, 0.14f, 0.65f, 0.95f, 4, true);

    // Big vibrant red font "★ COMING SOON ★" above the modal banner
    float modalPulse = (float)(sin(globalAnimTimer * 0.14f) * 0.25f + 0.75f);
    const char* modalSoon = "★ COMING SOON ★";
    int mTextW = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)modalSoon);
    drawBigRedText(cardX + (cardW - mTextW) / 2, cardY + cardH - 34, modalSoon, GLUT_BITMAP_TIMES_ROMAN_24, modalPulse);

    // High-resolution 16:9 Banner inside modal
    int banW = cardW - 36;
    int banH = 310;
    int banX = cardX + 18;
    int banY = cardY + 142;

    if (renoSirCollabBannerTex != -1)
    {
        iShowImage(banX, banY, banW, banH, renoSirCollabBannerTex);
        drawSmoothRectOutline((float)banX, (float)banY, (float)banW, (float)banH, 12, 0.95f, 0.20f, 0.20f, 0.85f, 2.0f);
    }

    // Top-Right Close Button [X]
    int closeX = cardX + cardW - 42;
    int closeY = cardY + cardH - 40;
    drawFilledSmoothRect((float)closeX, (float)closeY, 28, 28, 8, 0.85f, 0.20f, 0.20f, 0.92f);
    drawSmoothRectOutline((float)closeX, (float)closeY, 28, 28, 8, 1.0f, 1.0f, 1.0f, 0.90f, 1.5f);
    drawSharpText(closeX + 8, closeY + 6, "X", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    // Subtitle & Lore
    drawSharpText(cardX + 32, cardY + 115, "RENOSIR: LLM RESEARCHER & AI STRATEGIST", GLUT_BITMAP_TIMES_ROMAN_24, 56, 189, 248);
    drawSharpText(cardX + 32, cardY + 86, "Harnessing LLM algorithmic reasoning to effortlessly predict & bypass tricky castle traps!", GLUT_BITMAP_HELVETICA_12, 226, 232, 240);

    // High-relief 3D Trial Action Button
    int btnW = 380;
    int btnH = 46;
    int btnX = cardX + (cardW - btnW) / 2;
    int btnY = cardY + 22;
    draw3DButton(btnX, btnY, btnW, btnH, "★ CLOSE & ENJOY 1-LEVEL TRIAL ★", true, 0);
}

