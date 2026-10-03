#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: InputHandler.h
 * DEVELOPER: Ovijit Sharma (Student ID: 00725105101134)
 * ROLE & RESPONSIBILITY: Player Controller, Event Handling & Input Routing
 *
 * FEATURES IMPLEMENTED BY OVIJIT SHARMA:
 *   - Mouse motion tracking & hover detection (iMouseMove) across all menu screens
 *   - Mouse click dispatch (iMouseClick): button presses, carousel selection, level launch
 *   - Standard keyboard handler (iKeyboard): WASD / Space / E interact / Pause / Esc
 *   - Special keyboard handler (iSpecialKeyboard): Arrow keys navigation & mini-game aiming
 *   - On-screen virtual button controls (D-Pad left/right, jump button, interact icon)
 *   - Input routing for Penalty Mini-Game (spacebar charge, arrow key aim, retry)
 * DEPENDENCIES: GameDefines.h, RenderUtils.h, CharacterRender.h, AudioSystem.h, SaveSystem.h, Levels.h, PenaltyGame.h, GameLogic.h
 * =========================================================================== */
#include "GameDefines.h"
#include "RenderUtils.h"
#include "CharacterRender.h"
#include "AudioSystem.h"
#include "SaveSystem.h"
#include "Levels.h"
#include "PenaltyGame.h"
#include "GameLogic.h"

/* -------------------- INPUT: MOUSE MOVE -------------------- */
void iMouseMove(int mx, int my)
{
    if (gameState == STATE_MENU)
    {
        hoveredCarouselCard = -1;
        if (abs(mx - 960) < 32 && abs(my - 585) < 32)
            hoveredCarouselCard = -2; // Settings gear
        else if (my >= 160 && my <= 485)
        {
            for (int c = 0; c < 7; c++)
            {
                int cx = 32 + c * 138;
                if (mx >= cx && mx <= cx + 126)
                {
                    hoveredCarouselCard = c;
                    break;
                }
            }
        }
    }
    else if (gameState == STATE_EVENTS)
    {
        hoveredDailyCard = -1;
        hoveredEventsClaimBtn = false;

        // Bottom main button
        int btnW = 390, btnH = 46;
        int btnX = (SCREEN_WIDTH - btnW) / 2, btnY = 16;
        if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH)
            hoveredEventsClaimBtn = true;

        // 7 Calendar Cards
        int calStartX = 72, calSpacing = 126, calCardW = 114, calCardH = 146, calY = 92;
        for (int d = 0; d < 7; d++)
        {
            int cx = calStartX + d * calSpacing;
            if (mx >= cx && mx <= cx + calCardW && my >= calY && my <= calY + calCardH)
            {
                hoveredDailyCard = d;
                break;
            }
        }
    }
    else if (gameState == STATE_PENALTY_GAME)
    {
        updatePenaltyMouseMove(mx, my);
    }
    else if (gameState == STATE_CHARACTER_SELECT)
    {
        hoveredHeroCardIndex = -1;
        if (my >= 90 && my <= 525)
        {
            for (int i = 0; i < HERO_COUNT; i++)
            {
                int cx = 35 + i * 160;
                if (mx >= cx && mx <= cx + 145)
                {
                    hoveredHeroCardIndex = i;
                    break;
                }
            }
        }
    }
    else if (gameState == STATE_LEVEL_SELECT)
    {
        hoveredLevelDoor = -1;
        int doorW = 75;
        int doorH = 135;
        int colSpacing = 136;
        int startX = 110;

        for (int col = 0; col < 6; col++)
        {
            int dx = startX + col * colSpacing;
            if (mx >= dx && mx <= dx + doorW)
            {
                if (my >= 345 && my <= 345 + doorH) hoveredLevelDoor = col + 1;
                else if (my >= 165 && my <= 165 + doorH) hoveredLevelDoor = col + 7;
            }
        }
    }
    else if (gameState == STATE_CHAPTER2_SELECT)
    {
        hoveredLevelDoor = -1;
        int doorW = 85;
        int doorH = 150;
        int colSpacing = 180;
        int startX = 200;

        for (int col = 0; col < 4; col++)
        {
            int dx = startX + col * colSpacing;
            if (mx >= dx && mx <= dx + doorW && my >= 260 && my <= 260 + doorH)
            {
                hoveredLevelDoor = col + 13;
                break;
            }
        }
    }
    else if (gameState == STATE_CHAPTER3_SELECT)
    {
        hoveredLevelDoor = -1;
        int doorW = 85;
        int doorH = 150;
        int colSpacing = 180;
        int startX = 200;

        for (int col = 0; col < 4; col++)
        {
            int dx = startX + col * colSpacing;
            if (mx >= dx && mx <= dx + doorW && my >= 260 && my <= 260 + doorH)
            {
                hoveredLevelDoor = col + 17;
                break;
            }
        }
    }
    else if (gameState == STATE_CHAPTER4_SELECT)
    {
        hoveredLevelDoor = -1;
        int doorW = 85;
        int doorH = 150;
        int colSpacing = 180;
        int startX = 200;

        for (int col = 0; col < 4; col++)
        {
            int dx = startX + col * colSpacing;
            if (mx >= dx && mx <= dx + doorW && my >= 260 && my <= 260 + doorH)
            {
                hoveredLevelDoor = col + 21;
                break;
            }
        }
    }
    else if (gameState == STATE_PLAYING)
    {
        if (isMouseLeftDown)
        {
            if (mx >= 20 && mx <= 122 && my >= 10 && my <= 115)
            {
                isTouchingLeft = true;
                isTouchingRight = false;
                facing = -1;
            }
            else if (mx >= 124 && mx <= 226 && my >= 10 && my <= 115)
            {
                isTouchingRight = true;
                isTouchingLeft = false;
                facing = 1;
            }
            else if (mx >= 885 && mx <= 1010 && my >= 10 && my <= 115)
            {
                isTouchingJump = true;
                jumpBuffer = 8;
            }
            else
            {
                isTouchingLeft = false;
                isTouchingRight = false;
                isTouchingJump = false;
            }
        }
        else
        {
            isTouchingLeft = false;
            isTouchingRight = false;
            isTouchingJump = false;
        }
    }
}

void iPassiveMouseMove(int mx, int my)
{
    iMouseMove(mx, my);
}

/* -------------------- INPUT: MOUSE CLICK & DRAG -------------------- */
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        // Continuous button release
        if (state == GLUT_UP)
        {
            if (gameState == STATE_PENALTY_GAME)
            {
                handlePenaltyMouseUp();
            }
            isMouseLeftDown = false;
            isTouchingLeft = false;
            isTouchingRight = false;
            isTouchingJump = false;
            return;
        }

        isMouseLeftDown = true;

        if (gameState == STATE_PENALTY_GAME)
        {
            handlePenaltyMouseDown(mx, my);
            return;
        }

        playSfx("Audios\\click.wav");

        // Handle RenoSir Collaboration Modal if open
        if (showRenoSirCollabModal)
        {
            int cardW = 760;
            int cardH = 490;
            int cardX = (SCREEN_WIDTH - cardW) / 2;
            int cardY = (SCREEN_HEIGHT - cardH) / 2;

            int closeX = cardX + cardW - 42;
            int closeY = cardY + cardH - 40;

            int btnW = 380;
            int btnH = 46;
            int btnX = cardX + (cardW - btnW) / 2;
            int btnY = cardY + 22;

            bool clickedCloseX = (mx >= closeX - 5 && mx <= closeX + 35 && my >= closeY - 5 && my <= closeY + 35);
            bool clickedActionBtn = (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH);
            bool clickedOutside = (mx < cardX || mx > cardX + cardW || my < cardY || my > cardY + cardH);

            if (clickedCloseX || clickedActionBtn || clickedOutside)
            {
                showRenoSirCollabModal = false;
                renoSirOneLevelTrial = true;
                selectedHero = HERO_SAHA_RENO;
                renoSirTrialStartLevel = -1;
                saveProgress();
                playSfx("Audios\\win.wav");
                spawnSparkleBurst(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 56, 189, 248);
                showToast("RenoSir 1-Level Trial Activated! Play any level!");
            }
            return;
        }

        // STATE_INTRO
        if (gameState == STATE_INTRO)
        {
            gameState = STATE_MENU;
            return;
        }

        // STATE_MENU
        if (gameState == STATE_MENU)
        {
            if (showChapter3ComingSoon || showChapter5ComingSoon)
            {
                int cardX = 232;
                int cardY = 150;
                if ((mx >= cardX + 170 && mx <= cardX + 390 && my >= cardY + 45 && my <= cardY + 95) ||
                    (mx < cardX || mx > cardX + 560 || my < cardY || my > cardY + 340))
                {
                    showChapter3ComingSoon = false;
                    showChapter5ComingSoon = false;
                }
                return;
            }

            // Top-Right: Settings Cog Gear
            if (abs(mx - 960) < 32 && abs(my - 585) < 32)
            {
                gameState = STATE_SETTINGS;
                return;
            }

            // Top-Left: ADS Button
            if (abs(mx - 60) < 28 && abs(my - 585) < 28)
            {
                playerGems += 10;
                saveProgress();
                showToast("+10 GEMS RECEIVED FROM AD!");
                playSfx("Audios\\key.wav");
                spawnSparkleBurst(60, 585, 251, 191, 36);
                return;
            }

            // Top-Left: Rate Button
            if (mx >= 115 && mx <= 225 && my >= 565 && my <= 605)
            {
                playerCoins += 50;
                saveProgress();
                showToast("+50 COINS RECEIVED FOR RATING!");
                playSfx("Audios\\key.wav");
                spawnSparkleBurst(170, 585, 251, 191, 36);
                return;
            }

            // Carousel Cards (7 Cards: Costumes, Events, Ch1, Ch2, Ch3, Ch4, Ch5 Coming Soon)
            // Card 0: Costumes
            if (mx >= 32 && mx <= 32 + 126 && my >= 160 && my <= 485)
            {
                gameState = STATE_CHARACTER_SELECT;
                return;
            }

            // Card 1: Events (Daily Login & RenoSir Promo)
            if (mx >= 170 && mx <= 170 + 126 && my >= 160 && my <= 485)
            {
                gameState = STATE_EVENTS;
                return;
            }

            // Card 2: Princess Castle (Chapter 1)
            if (mx >= 308 && mx <= 308 + 126 && my >= 160 && my <= 485)
            {
                gameState = STATE_LEVEL_SELECT;
                return;
            }

            // Card 3: The Citadel (Chapter 2)
            if (mx >= 446 && mx <= 446 + 126 && my >= 160 && my <= 485)
            {
                gameState = STATE_CHAPTER2_SELECT;
                return;
            }

            // Card 4: Witch Tower (Chapter 3)
            if (mx >= 584 && mx <= 584 + 126 && my >= 160 && my <= 485)
            {
                gameState = STATE_CHAPTER3_SELECT;
                return;
            }

            // Card 5: Dragon's Keep (Chapter 4)
            if (mx >= 722 && mx <= 722 + 126 && my >= 160 && my <= 485)
            {
                gameState = STATE_CHAPTER4_SELECT;
                return;
            }

            // Card 6: Astral Spire (Chapter 5 - Coming Soon!)
            if (mx >= 860 && mx <= 860 + 126 && my >= 160 && my <= 485)
            {
                showChapter5ComingSoon = true;
                playSfx("Audios\\key.wav");
                return;
            }
            return;
        }

        // STATE_EVENTS
        if (gameState == STATE_EVENTS)
        {
            // Back button "<"
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_MENU;
                return;
            }

            // Currency Capsule Quick Top-Up [+]
            // Gems Capsule (710, 564, 136, 42)
            if (mx >= 710 && mx <= 710 + 136 && my >= 564 && my <= 564 + 42)
            {
                playerGems += 50;
                saveProgress();
                showToast("+50 GEMS ACQUIRED!");
                playSfx("Audios\\key.wav");
                spawnSparkleBurst(710 + 68, 564 + 21, 56, 189, 248);
                return;
            }

            // Coins Capsule (862, 564, 136, 42)
            if (mx >= 862 && mx <= 862 + 136 && my >= 564 && my <= 564 + 42)
            {
                playerCoins += 100;
                saveProgress();
                showToast("+100 GOLD COINS ACQUIRED!");
                playSfx("Audios\\key.wav");
                spawnSparkleBurst(862 + 68, 564 + 21, 251, 191, 36);
                return;
            }

            // Promotional Banner click
            if (mx >= 142 && mx <= 142 + 740 && my >= 375 && my <= 375 + 175)
            {
                showToast("CR7 x Tricky Castle: Champions Odyssey Event!");
                playSfx("Audios\\click.wav");
                return;
            }

            // CR7 Challenge 1: Real Madrid Skin (Clear 5 Floors)
            if (mx >= 142 && mx <= 142 + 236 && my >= 248 && my <= 248 + 92)
            {
                if (cr7MadridUnlocked || questMadridClaimed)
                {
                    showToast("Real Madrid CR7 skin already unlocked!");
                    playSfx("Audios\\click.wav");
                }
                else if (unlockedLevels >= 6)
                {
                    cr7MadridUnlocked = true;
                    questMadridClaimed = true;
                    playerGems += 100;
                    cr7SkinSelected = 1;
                    updateCR7Skin();
                    saveProgress();
                    playSfx("Audios\\win.wav");
                    spawnSparkleBurst(142 + 118, 248 + 46, 255, 255, 255);
                    spawnSparkleBurst(142 + 118, 248 + 46, 251, 191, 36);
                    showToast("Real Madrid CR7 Unlocked! +100 Gems!");
                }
                else
                {
                    showToast("Clear 5 floors to unlock Real Madrid CR7!");
                    playSfx("Audios\\ouch.wav");
                }
                return;
            }

            // CR7 Challenge 2: Juventus Skin (Collect 15 Stars)
            if (mx >= 394 && mx <= 394 + 236 && my >= 248 && my <= 248 + 92)
            {
                if (cr7JuventusUnlocked || questJuventusClaimed)
                {
                    showToast("Juventus CR7 skin already unlocked!");
                    playSfx("Audios\\click.wav");
                }
                else if (totalStars >= 15)
                {
                    cr7JuventusUnlocked = true;
                    questJuventusClaimed = true;
                    playerCoins += 200;
                    cr7SkinSelected = 2;
                    updateCR7Skin();
                    saveProgress();
                    playSfx("Audios\\win.wav");
                    spawnSparkleBurst(394 + 118, 248 + 46, 254, 240, 138);
                    spawnSparkleBurst(394 + 118, 248 + 46, 255, 255, 255);
                    showToast("Juventus CR7 Unlocked! +200 Coins!");
                }
                else
                {
                    showToast("Earn 15 Stars across floors to unlock Juventus CR7!");
                    playSfx("Audios\\ouch.wav");
                }
                return;
            }

            // CR7 Challenge 3: RenoSir Collaboration Modal & 1-Level Trial
            if (mx >= 646 && mx <= 646 + 236 && my >= 248 && my <= 248 + 92)
            {
                if (characters[HERO_SAHA_RENO].unlocked)
                {
                    showToast("RenoSir is permanently unlocked!");
                    playSfx("Audios\\click.wav");
                }
                else
                {
                    showRenoSirCollabModal = true;
                    playSfx("Audios\\click.wav");
                }
                return;
            }

            // 3D Bottom Claim Action button
            int btnW = 390, btnH = 46;
            int btnX = (SCREEN_WIDTH - btnW) / 2, btnY = 16;
            bool clickedClaimBtn = (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH);

            // 7 High-Relief 3D Calendar Cards clicks
            int calStartX = 72, calSpacing = 126, calCardW = 114, calCardH = 146, calY = 92;
            bool clickedTodayCard = false;
            for (int d = 0; d < 7; d++)
            {
                int dayNum = d + 1;
                int cx = calStartX + d * calSpacing;
                if (mx >= cx && mx <= cx + calCardW && my >= calY && my <= calY + calCardH)
                {
                    if (dayNum == dailyLoginDay && !dailyRewardClaimedToday)
                    {
                        clickedTodayCard = true;
                    }
                    else if (dayNum <= dailyLoginDay && dailyRewardClaimedToday)
                    {
                        showToast("Entering Rematch Derby against Castle Guard Messi!");
                        startPenaltyGame(false);
                        return;
                    }
                    else
                    {
                        showToast("Log in consecutive days to unlock!");
                        playSfx("Audios\\click.wav");
                        return;
                    }
                }
            }

            if ((clickedClaimBtn || clickedTodayCard) && !dailyRewardClaimedToday)
            {
                startPenaltyGame(true);
                return;
            }
            else if (clickedClaimBtn && dailyRewardClaimedToday)
            {
                showToast("Entering Rematch Derby against Castle Guard Messi!");
                startPenaltyGame(false);
                return;
            }
            return;
        }

        // STATE_CHARACTER_SELECT
        if (gameState == STATE_CHARACTER_SELECT)
        {
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_MENU;
                return;
            }

            for (int i = 0; i < HERO_COUNT; i++)
            {
                int cx = 35 + i * 160;
                if (mx >= cx && mx <= cx + 145 && my >= 90 && my <= 515)
                {
                    // Special handling for CR7 kit tabs
                    if (i == HERO_CR7 && my >= 245 && my <= 285)
                    {
                        // Kit 0: Devil
                        if (mx >= cx + 9 && mx <= cx + 49)
                        {
                            cr7SkinSelected = 0;
                            updateCR7Skin();
                            saveProgress();
                            playSfx("Audios\\key.wav");
                            showToast("Equipped: Red Devil CR7!");
                            return;
                        }
                        // Kit 1: Real Madrid
                        else if (mx >= cx + 52 && mx <= cx + 92)
                        {
                            if (cr7MadridUnlocked)
                            {
                                cr7SkinSelected = 1;
                                updateCR7Skin();
                                saveProgress();
                                playSfx("Audios\\key.wav");
                                showToast("Equipped: Real Madrid CR7!");
                            }
                            else
                            {
                                showToast("Locked! Clear 5 floors in Events to unlock Real Madrid CR7.");
                                playSfx("Audios\\ouch.wav");
                            }
                            return;
                        }
                        // Kit 2: Juventus
                        else if (mx >= cx + 95 && mx <= cx + 135)
                        {
                            if (cr7JuventusUnlocked)
                            {
                                cr7SkinSelected = 2;
                                updateCR7Skin();
                                saveProgress();
                                playSfx("Audios\\key.wav");
                                showToast("Equipped: Juventus CR7!");
                            }
                            else
                            {
                                showToast("Locked! Collect 15 Stars in Events to unlock Juventus CR7.");
                                playSfx("Audios\\ouch.wav");
                            }
                            return;
                        }
                    }

                    // Special handling for RenoSir trial & unlock
                    if (i == HERO_SAHA_RENO)
                    {
                        if (characters[HERO_SAHA_RENO].unlocked)
                        {
                            selectedHero = HERO_SAHA_RENO;
                            saveProgress();
                            playSfx("Audios\\key.wav");
                            showToast("Equipped: RenoSir!");
                        }
                        else if (renoSirOneLevelTrial)
                        {
                            selectedHero = HERO_SAHA_RENO;
                            saveProgress();
                            playSfx("Audios\\key.wav");
                            showToast("Equipped: RenoSir (1-Level Trial Active)!");
                        }
                        else
                        {
                            // Open Collaboration Banner Modal! Closing activates 1-level trial
                            showRenoSirCollabModal = true;
                            playSfx("Audios\\click.wav");
                        }
                        return;
                    }

                    // Standard Heroes
                    selectedHero = i;
                    saveProgress();
                    playSfx("Audios\\key.wav");
                    return;
                }
            }
            return;
        }

        // STATE_LEVEL_SELECT (CHAPTER 1)
        if (gameState == STATE_LEVEL_SELECT)
        {
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_MENU;
                return;
            }

            int doorW = 75;
            int doorH = 135;
            int colSpacing = 136;
            int startX = 110;

            // Row 1: Floors 1 to 6
            for (int col = 0; col < 6; col++)
            {
                int fNum = col + 1;
                int dx = startX + col * colSpacing;
                int dy = 345;
                if (mx >= dx && mx <= dx + doorW && my >= dy && my <= dy + doorH)
                {
                    if (fNum <= unlockedLevels)
                    {
                        loadLevel(fNum - 1);
                        gameState = STATE_PLAYING;
                        return;
                    }
                }
            }

            // Row 2: Floors 7 to 12
            for (int col = 0; col < 6; col++)
            {
                int fNum = col + 7;
                int dx = startX + col * colSpacing;
                int dy = 165;
                if (mx >= dx && mx <= dx + doorW && my >= dy && my <= dy + doorH)
                {
                    if (fNum <= unlockedLevels)
                    {
                        loadLevel(fNum - 1);
                        gameState = STATE_PLAYING;
                        return;
                    }
                }
            }
            return;
        }

        // STATE_CHAPTER2_SELECT (CHAPTER 2)
        if (gameState == STATE_CHAPTER2_SELECT)
        {
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_MENU;
                return;
            }

            int doorW = 85;
            int doorH = 150;
            int colSpacing = 180;
            int startX = 200;

            for (int col = 0; col < 4; col++)
            {
                int fNum = col + 13;
                int dx = startX + col * colSpacing;
                int dy = 260;
                if (mx >= dx && mx <= dx + doorW && my >= dy && my <= dy + doorH)
                {
                    if (fNum <= unlockedLevels)
                    {
                        loadLevel(fNum - 1);
                        gameState = STATE_PLAYING;
                        return;
                    }
                    else
                    {
                        playSfx("Audios\\ouch.wav");
                        showToast("Complete previous floors to unlock!");
                        return;
                    }
                }
            }
            return;
        }

        // STATE_CHAPTER3_SELECT (CHAPTER 3)
        if (gameState == STATE_CHAPTER3_SELECT)
        {
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_MENU;
                return;
            }

            int doorW = 85;
            int doorH = 150;
            int colSpacing = 180;
            int startX = 200;

            for (int col = 0; col < 4; col++)
            {
                int fNum = col + 17;
                int dx = startX + col * colSpacing;
                int dy = 260;
                if (mx >= dx && mx <= dx + doorW && my >= dy && my <= dy + doorH)
                {
                    if (fNum <= unlockedLevels)
                    {
                        loadLevel(fNum - 1);
                        gameState = STATE_PLAYING;
                        return;
                    }
                    else
                    {
                        playSfx("Audios\\ouch.wav");
                        showToast("Complete previous floors to unlock!");
                        return;
                    }
                }
            }
            return;
        }

        // STATE_CHAPTER4_SELECT (CHAPTER 4)
        if (gameState == STATE_CHAPTER4_SELECT)
        {
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_MENU;
                return;
            }

            int doorW = 85;
            int doorH = 150;
            int colSpacing = 180;
            int startX = 200;

            for (int col = 0; col < 4; col++)
            {
                int fNum = col + 21;
                int dx = startX + col * colSpacing;
                int dy = 260;
                if (mx >= dx && mx <= dx + doorW && my >= dy && my <= dy + doorH)
                {
                    if (fNum <= unlockedLevels)
                    {
                        loadLevel(fNum - 1);
                        gameState = STATE_PLAYING;
                        return;
                    }
                    else
                    {
                        playSfx("Audios\\ouch.wav");
                        showToast("Complete previous floors to unlock!");
                        return;
                    }
                }
            }
            return;
        }

        // STATE_SETTINGS (IMAGE 4 CLONE)
        if (gameState == STATE_SETTINGS)
        {
            // Back button "<"
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_MENU;
                return;
            }

            // Sound Toggle (Left Column)
            int col1X = 230;
            if (mx >= col1X && mx <= col1X + 180 && my >= 390 && my <= 460)
            {
                toggleSound();
                saveProgress();
                showToast(soundEnabled ? "Sound: ON" : "Sound: MUTED");
                return;
            }

            // English Language (Left Column)
            if (mx >= col1X && mx <= col1X + 180 && my >= 300 && my <= 370)
            {
                showToast("Language: English (Default)");
                playSfx("Audios\\click.wav");
                return;
            }

            // New Games (Left Column)
            if (mx >= col1X && mx <= col1X + 180 && my >= 210 && my <= 280)
            {
                showToast("Check back soon for new games!");
                playSfx("Audios\\click.wav");
                return;
            }

            // Reset progress (Right Column)
            int col2X = 520, pillW = 270, pillH = 58;
            if (mx >= col2X && mx <= col2X + pillW && my >= 370 && my <= 370 + pillH)
            {
                unlockedLevels = 1;
                totalStars = 0;
                for (int i = 0; i < LEVEL_COUNT; i++) { levelStars[i] = 0; levelScores[i] = 0; }
                saveProgress();
                showToast("Game progress reset successfully!");
                playSfx("Audios\\ouch.wav");
                return;
            }

            // Restore purchases (Right Column)
            if (mx >= col2X && mx <= col2X + pillW && my >= 270 && my <= 270 + pillH)
            {
                playerGems += 100;
                playerCoins += 200;
                saveProgress();
                showToast("Purchases restored! +100 Gems, +200 Coins");
                playSfx("Audios\\key.wav");
                return;
            }

            // Social Buttons (Steam, X, Share)
            if (mx >= 520 && mx <= 740 && my >= 110 && my <= 170)
            {
                showToast("Thank you for connecting with Tricky Castle!");
                playSfx("Audios\\click.wav");
                return;
            }
            return;
        }

        // STATE_PLAYING
        if (gameState == STATE_PLAYING)
        {
            // HINT MODAL ACTIVE (IMAGE 2 CLONE)
            if (showHintAdModal)
            {
                int cardX = 212;
                int cardY = 175;
                int cardW = 600;
                int cardH = 290;

                int yesX = cardX + 175;
                int noX = cardX + 310;
                int btnY = cardY + 45;
                int btnW = 115;
                int btnH = 46;

                // YES Button (Green: Watch Ad & Get Hint / Instant Solve)
                if (mx >= yesX && mx <= yesX + btnW && my >= btnY && my <= btnY + btnH)
                {
                    if (hintTierRevealed == 0)
                    {
                        hintTierRevealed = 1;
                        playSfx("Audios\\key.wav");
                        showToast("Hint revealed!");
                        spawnSparkleBurst(yesX + btnW / 2, btnY + btnH / 2, 34, 197, 94);
                    }
                    else
                    {
                        usedInstantPassThisLevel = true;
                        if (currentLevel == 0) { platforms[platformCount++] = { 360, GROUND_HEIGHT, 260, 26, true }; spikes[0].lethal = false; }
                        else if (currentLevel == 1) { platforms[platformCount++] = { 340, GROUND_HEIGHT, 300, 26, true }; spikes[0].lethal = false; }
                        else if (currentLevel == 2) { chests[0].opened = true; keyX = chests[0].x + 16; keyY = chests[0].y + 55; keyActive = true; }
                        else if (currentLevel == 3) { doorOpen = true; }
                        else if (currentLevel == 4) { hasKey = true; doorOpen = true; fallingKeyActive = false; }
                        else if (currentLevel == 5) { spikes[0].lethal = false; }
                        else if (currentLevel == 6) { hasKey = true; doorOpen = true; invertedGravity = false; playerX = 750; playerY = GROUND_HEIGHT; }
                        else if (currentLevel == 7) { spikes[0].lethal = false; doorOpen = true; hasKey = true; }
                        else if (currentLevel == 8) { crusherJammed = true; crusherFalling = false; }
                        else if (currentLevel == 9) { guardAsleep = true; doorOpen = true; }
                        else if (currentLevel == 10) { hasKey = true; doorOpen = true; }
                        else if (currentLevel == 11) { buttonPressed = true; floor12BridgeLowered = true; spikes[0].lethal = false; platforms[platformCount++] = { 240, GROUND_HEIGHT, 500, 26, true }; hasKey = true; doorOpen = true; }
                        else if (currentLevel == 12) { hasDecoyKey = false; keyActive = true; spikes[0].lethal = false; platforms[platformCount++] = { 280, GROUND_HEIGHT, 420, 26, true }; hasKey = true; doorOpen = true; }
                        else if (currentLevel == 13) { buttonPressed = true; pendulumLocked = true; spikes[0].lethal = false; platforms[platformCount++] = { 400, GROUND_HEIGHT, 340, 26, true }; hasKey = true; doorOpen = true; }
                        else if (currentLevel == 14) { shiftingWallOpen = true; shiftingWallY = 560; hasKey = true; doorOpen = true; }
                        else if (currentLevel == 15) { hasKey = true; doorOpen = true; playerX = 880; playerY = 280; }
                        else if (currentLevel >= 16 && currentLevel <= 23) { spikes[0].lethal = false; hasKey = true; doorOpen = true; }

                        playSfx("Audios\\door.wav");
                        showToast("Floor puzzle solved!");
                        showHintAdModal = false;
                    }
                    return;
                }

                // NO Button (Dismiss)
                if (mx >= noX && mx <= noX + btnW && my >= btnY && my <= btnY + btnH)
                {
                    showHintAdModal = false;
                    return;
                }

                // Click outside card -> closes modal
                if (mx < cardX || mx > cardX + cardW || my < cardY || my > cardY + cardH)
                {
                    showHintAdModal = false;
                    return;
                }
                return;
            }

            // Top-Left: Diamond "?"
            if (abs(mx - 60) < 30 && abs(my - 585) < 30)
            {
                showHintAdModal = true;
                hintTierRevealed = 0;
                return;
            }

            // Top-Right: Diamond "||"
            if (abs(mx - 960) < 30 && abs(my - 585) < 30)
            {
                gameState = STATE_PAUSED;
                return;
            }

            // Bottom-Left: Authentic Touch Left "<" (Click and Hold!)
            if (mx >= 20 && mx <= 122 && my >= 10 && my <= 115)
            {
                isTouchingLeft = true;
                isTouchingRight = false;
                facing = -1;
                return;
            }

            // Bottom-Left: Authentic Touch Right ">" (Click and Hold!)
            if (mx >= 124 && mx <= 226 && my >= 10 && my <= 115)
            {
                isTouchingRight = true;
                isTouchingLeft = false;
                facing = 1;
                return;
            }

            // Bottom-Right: Touch Jump "^" (Click and Hold!)
            if (mx >= 885 && mx <= 1010 && my >= 10 && my <= 115)
            {
                isTouchingJump = true;
                jumpBuffer = 8;
                if (onGround)
                {
                    velocityY = invertedGravity ? -characters[selectedHero].jumpSpeed : characters[selectedHero].jumpSpeed;
                    onGround = false;
                    playSfx("Audios\\jump.wav");
                }
                return;
            }

            // Direct Click on Active Interactive Object or Prompt
            if (activeInteractionIndex >= 0 && activeInteractionIndex < bgObjectCount)
            {
                interactWithBackground();
                return;
            }

            // Direct Click on Red Button (Floor 12 & Floor 14)
            if (buttonX > 0 && abs(mx - buttonX) <= 35 && my >= buttonY - 4 && my <= buttonY + 35)
            {
                if (currentLevel == 11 && !floor12BridgeLowered)
                {
                    buttonPressed = true;
                    floor12BridgeLowered = true;
                    spikes[0].lethal = false;
                    platforms[platformCount++] = { 240, GROUND_HEIGHT, 500, 26, true };
                    triggerScreenShake(12, 4.0);
                    playSfx("Audios\\spring.wav");
                    addFloatingText(buttonX, buttonY + 45, "DRAWBRIDGE LOWERED!", 74, 222, 128);
                    for (int p = 0; p < 20; p++)
                        spawnSparkleBurst(buttonX, buttonY + 12, 251, 191, 36);
                    return;
                }
                else if (currentLevel == 13 && !pendulumLocked)
                {
                    buttonPressed = true;
                    pendulumLocked = true;
                    spikes[0].lethal = false;
                    platforms[platformCount++] = { 400, GROUND_HEIGHT, 340, 26, true };
                    triggerScreenShake(12, 4.0);
                    playSfx("Audios\\interact.wav");
                    playSfx("Audios\\door.wav");
                    addFloatingText(buttonX, buttonY + 45, "SAFETY BRIDGE LOWERED!", 74, 222, 128);
                    for (int p = 0; p < 20; p++)
                        spawnSparkleBurst(buttonX, buttonY + 12, 74, 222, 128);
                    return;
                }
            }

            // Direct Click on Shifting Wall (Floor 15)
            if (currentLevel == 14 && mx >= 500 && mx <= 590 && my >= shiftingWallY && my <= shiftingWallY + 480)
            {
                shiftingWallOpen = true;
                playSfx("Audios\\door.wav");
                triggerScreenShake(12, 3.5);
                addFloatingText(545, my + 30, "MASONRY SHIFTED!", 74, 222, 128);
                return;
            }

            // Direct Click on Decoy Key (Floor 13)
            if (currentLevel == 12 && hasDecoyKey && abs(mx - (decoyKeyX + 16)) < 32 && abs(my - (decoyKeyY + 16)) < 32)
            {
                hasDecoyKey = false;
                playSfx("Audios\\ouch.wav");
                addFloatingText(decoyKeyX - 30, decoyKeyY + 40, "FOOLED! A DECOY KEY!", 239, 68, 68);
                return;
            }

            // Direct Click on Golden Key
            if (keyActive && !hasKey && abs(mx - (keyX + 16)) < 35 && abs(my - (keyY + 16)) < 35)
            {
                hasKey = true;
                keyActive = false;
                doorOpen = true;
                playSfx("Audios\\key.wav");
                spawnSparkleBurst(keyX + 18, keyY + 18, 251, 191, 36);
                addFloatingText(keyX, keyY + 40, "KEY COLLECTED!", 251, 191, 36);
                return;
            }

            // Floor 3 Direct Chest Clicks
            if (currentLevel == 2)
            {
                for (int i = 0; i < chestCount; i++)
                {
                    Chest& c = chests[i];
                    if (mx >= c.x - 10 && mx <= c.x + c.w + 10 && my >= c.y && my <= c.y + c.h + 25 && !c.opened)
                    {
                        c.opened = true;
                        if (c.hasKey)
                        {
                            keyX = c.x + 16; keyY = c.y + 55; keyActive = true;
                            playSfx("Audios\\key.wav");
                            spawnSparkleBurst(keyX + 16, keyY + 16, 251, 191, 36);
                        }
                        else if (c.isTrap)
                        {
                            ghost.x = c.x + 12; ghost.y = c.y + 35; ghost.active = true;
                            playSfx("Audios\\ouch.wav");
                        }
                        return;
                    }
                }
            }

            // Floor 1 & 2 Direct Chain Clicks
            if (currentLevel == 0 || currentLevel == 1)
            {
                for (int i = 0; i < bgObjectCount; i++)
                {
                    BgObject& obj = bgObjects[i];
                    if (obj.type == BG_PULL_CHAIN)
                    {
                        if (abs(mx - (obj.x + obj.w / 2)) < 40 && my >= obj.y - 20 && my <= obj.y + 70)
                        {
                            activeInteractionIndex = i;
                            interactWithBackground();
                            return;
                        }
                    }
                }
            }
            return;
        }

        // STATE_PAUSED
        if (gameState == STATE_PAUSED)
        {
            int cardX = 312;
            int cardY = 120;
            if (mx >= cardX + 50 && mx <= cardX + 350)
            {
                if (my >= cardY + 280 && my <= cardY + 330) gameState = STATE_PLAYING;
                else if (my >= cardY + 210 && my <= cardY + 260) { loadLevel(currentLevel); gameState = STATE_PLAYING; }
                else if (my >= cardY + 140 && my <= cardY + 190) gameState = STATE_CHARACTER_SELECT;
                else if (my >= cardY + 70 && my <= cardY + 120) gameState = (currentLevel >= 20 ? STATE_CHAPTER4_SELECT : (currentLevel >= 16 ? STATE_CHAPTER3_SELECT : (currentLevel >= 12 ? STATE_CHAPTER2_SELECT : STATE_LEVEL_SELECT)));
            }
            return;
        }

        // STATE_GAME_OVER
        if (gameState == STATE_GAME_OVER)
        {
            int cardX = 262;
            int cardY = 140;
            if (mx >= cardX + 100 && mx <= cardX + 400)
            {
                if (my >= cardY + 100 && my <= cardY + 148) { loadLevel(currentLevel); gameState = STATE_PLAYING; }
                else if (my >= cardY + 40 && my <= cardY + 88) { showHintAdModal = true; hintTierRevealed = 0; gameState = STATE_PLAYING; }
            }
            return;
        }

        // STATE_LEVEL_CLEAR
        if (gameState == STATE_LEVEL_CLEAR)
        {
            int cardX = 282;
            int cardY = 160;
            if (mx >= cardX + 80 && mx <= cardX + 380 && my >= cardY + 50 && my <= cardY + 100)
            {
                currentLevel++;
                if (currentLevel >= LEVEL_COUNT) currentLevel = 0;
                loadLevel(currentLevel);
                gameState = STATE_PLAYING;
            }
            return;
        }
    }
}

/* -------------------- INPUT: KEYBOARD -------------------- */
void iKeyboard(unsigned char key)
{
    if (gameState == STATE_INTRO)
    {
        gameState = STATE_MENU;
        return;
    }

    if (gameState == STATE_PENALTY_GAME)
    {
        if (key == 27) // ESC: return to events
        {
            gameState = STATE_EVENTS;
            return;
        }
        if (key == ' ' || key == 13) // Space or Enter
        {
            handlePenaltySpaceAction();
            return;
        }
    }

    // Modal dismiss with ESC or H
    if (showHintAdModal)
    {
        if (key == 27 || key == 'h' || key == 'H' || key == 13 || key == ' ')
        {
            showHintAdModal = false;
            return;
        }
    }

    if (showChapter3ComingSoon || showChapter5ComingSoon)
    {
        if (key == 27 || key == 13 || key == ' ')
        {
            showChapter3ComingSoon = false;
            showChapter5ComingSoon = false;
            return;
        }
    }

    if (key == 13) // Enter
    {
        if (gameState == STATE_MENU)
        {
            loadLevel(0);
            gameState = STATE_PLAYING;
        }
        else if (gameState == STATE_LEVEL_CLEAR)
        {
            currentLevel++;
            if (currentLevel >= LEVEL_COUNT) currentLevel = 0;
            loadLevel(currentLevel);
            gameState = STATE_PLAYING;
        }
        else if (gameState == STATE_PAUSED)
        {
            gameState = STATE_PLAYING;
        }
    }
    else if (key == 'e' || key == 'E' || key == 'f' || key == 'F' || key == ' ')
    {
        if (gameState == STATE_PLAYING)
            interactWithBackground();
    }
    else if (key == 'p' || key == 'P' || key == 27) // ESC or P = Pause
    {
        if (gameState == STATE_PLAYING) gameState = STATE_PAUSED;
        else if (gameState == STATE_PAUSED) gameState = STATE_PLAYING;
    }
    else if (key == 'h' || key == 'H') // Hint Modal
    {
        if (gameState == STATE_PLAYING)
        {
            showHintAdModal = !showHintAdModal;
            hintTierRevealed = 0;
        }
    }
    else if (key == 'r' || key == 'R') // Restart
    {
        loadLevel(currentLevel);
        gameState = STATE_PLAYING;
    }
    else if (key == 'c' || key == 'C') // Costumes / Characters
    {
        gameState = STATE_CHARACTER_SELECT;
    }
    else if (key == 'l' || key == 'L') // Level Map
    {
        gameState = (currentLevel >= 20 ? STATE_CHAPTER4_SELECT : (currentLevel >= 16 ? STATE_CHAPTER3_SELECT : (currentLevel >= 12 ? STATE_CHAPTER2_SELECT : STATE_LEVEL_SELECT)));
    }
    else if (key == 'm' || key == 'M') // Mute / Unmute
    {
        toggleSound();
    }
    else if (key >= '1' && key <= '6' && gameState == STATE_CHARACTER_SELECT)
    {
        int heroIdx = key - '1';
        if (heroIdx == HERO_SAHA_RENO && !characters[HERO_SAHA_RENO].unlocked && !renoSirOneLevelTrial)
        {
            showRenoSirCollabModal = true;
            playSfx("Audios\\click.wav");
        }
        else
        {
            selectedHero = heroIdx;
            playSfx("Audios\\key.wav");
            saveProgress();
        }
    }
    else if (key >= '1' && key <= '9' && gameState == STATE_PLAYING)
    {
        loadLevel(key - '1');
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if (gameState == STATE_PENALTY_GAME)
    {
        handlePenaltySpecialKey(key);
    }
}

