#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: GameLogic.h
 * LEAD GAME THEORIST & PHYSICS ARCHITECT: Ovijit Sharma (Student ID: 00725105101134)
 * ROLE & RESPONSIBILITY: Game Theory Execution, 60 FPS Physics Simulation & Collision Rules
 *
 * GAME THEORY & PHYSICS DESIGNED BY OVIJIT SHARMA:
 *   - 60 FPS fixed physics simulation cycle (fixedUpdate)
 *   - Player kinematics: horizontal acceleration, ground friction, and air resistance
 *   - Parabolic jumping physics with variable leap velocity and gravity damping
 *   - Solid tile collision detection: ground detection, ceiling head-bumps, wall bounds
 *   - Moving platform collision and inertia transfer
 *   - Hazard detection: steel floor spikes, phantom traps, and death trigger
 *   - Angel Ghost death animation sequence and room restart
 *   - Puzzle interaction triggers (interactWithBackground): pull chains, buttons, levers
 *   - Key collection logic and locked door exit trigger evaluation
 * DEPENDENCIES: GameDefines.h, RenderUtils.h, CharacterRender.h, AudioSystem.h, SaveSystem.h, Levels.h, PenaltyGame.h
 * =========================================================================== */
#include "GameDefines.h"
#include "RenderUtils.h"
#include "CharacterRender.h"
#include "AudioSystem.h"
#include "SaveSystem.h"
#include "Levels.h"
#include "PenaltyGame.h"

/* -------------------- INTERACTION SYSTEM -------------------- */
void interactWithBackground()
{
    int targetIdx = activeInteractionIndex;
    if (targetIdx < 0 || targetIdx >= bgObjectCount)
    {
        for (int i = 0; i < bgObjectCount; i++)
        {
            BgObject& obj = bgObjects[i];
            if (obj.interactive && obj.type != BG_SPRING_PAD && abs((playerX + PLAYER_WIDTH / 2) - (obj.x + obj.w / 2)) < 125)
            {
                targetIdx = i;
                break;
            }
        }
    }

    if (targetIdx < 0 || targetIdx >= bgObjectCount) return;

    BgObject& obj = bgObjects[targetIdx];
    playSfx("Audios\\interact.wav");

    if (obj.type == BG_PULL_CHAIN) // Floors 1 & 2
    {
        obj.state = !obj.state;
        triggerScreenShake(10, 3.5);
        spawnSparkleBurst(obj.x + 12, obj.y + 14, 251, 191, 36);

        if (currentLevel == 0) // Floor 1
        {
            platforms[platformCount++] = { 360, GROUND_HEIGHT, 260, 26, true };
            spikes[0].lethal = false;
            playSfx("Audios\\door.wav");
            addFloatingText(obj.x - 30, obj.y + 40, "STONE BRIDGE EXTENDED!", 74, 222, 128);
        }
        else if (currentLevel == 1) // Floor 2
        {
            platforms[platformCount++] = { 340, GROUND_HEIGHT, 300, 26, true };
            spikes[0].lethal = false;
            playSfx("Audios\\door.wav");
            addFloatingText(obj.x - 30, obj.y + 40, "STONE BRIDGE EXTENDED!", 74, 222, 128);
        }
        else if (currentLevel == 17) // Floor 18: Douse Witch Cauldron
        {
            keyActive = true;
            keyX = 500; keyY = 300;
            doorOpen = true;
            playSfx("Audios\\door.wav");
            triggerScreenShake(12, 3.5);
            for (int p = 0; p < 30; p++)
                spawnSparkleBurst(500, 270, 56, 189, 248);
            addFloatingText(440, 320, "WITCHFLAME DOUSED & KEY DROPPED!", 56, 189, 248);
        }
    }
    else if (obj.type == BG_CHEST_INTERACTIVE) // Floor 3
    {
        int chestIdx = obj.extraId;
        if (chestIdx >= 0 && chestIdx < chestCount && !chests[chestIdx].opened)
        {
            chests[chestIdx].opened = true;
            if (chests[chestIdx].hasKey)
            {
                keyX = chests[chestIdx].x + 16;
                keyY = chests[chestIdx].y + 55;
                keyActive = true;
                playSfx("Audios\\key.wav");
                spawnSparkleBurst(keyX + 16, keyY + 16, 251, 191, 36);
                addFloatingText(keyX - 15, keyY + 35, "GOLDEN KEY!", 251, 191, 36);
            }
            else if (chests[chestIdx].isTrap)
            {
                ghost.x = chests[chestIdx].x + 12;
                ghost.y = chests[chestIdx].y + 35;
                ghost.active = true;
                playSfx("Audios\\ouch.wav");
                addFloatingText(ghost.x, ghost.y + 45, "CURSED PHANTOM!", 239, 68, 68);
            }
        }
    }
    else if (obj.type == BG_WALL_LEVER) // Floor 4 & Floor 14
    {
        obj.state = true;
        if (currentLevel == 3)
        {
            levels[currentLevel].doorPushable = true;
            doorPushedDistance = 140;
            doorOpen = true;
            playSfx("Audios\\door.wav");
            addFloatingText(obj.x, obj.y + 50, "DOOR UNLATCHED! PUSH IT!", 251, 191, 36);
        }
        else if (currentLevel == 11) // Floor 12: Drawbridge Release Lever
        {
            if (!floor12BridgeLowered)
            {
                buttonPressed = true;
                floor12BridgeLowered = true;
                spikes[0].lethal = false;
                platforms[platformCount++] = { 240, GROUND_HEIGHT, 500, 26, true };
                triggerScreenShake(12, 4.0);
                playSfx("Audios\\door.wav");
                addFloatingText(obj.x, obj.y + 50, "DRAWBRIDGE LOWERED!", 74, 222, 128);
                for (int p = 0; p < 20; p++)
                    spawnSparkleBurst(obj.x + 16, obj.y + 24, 251, 191, 36);
            }
        }
        else if (currentLevel == 12) // Floor 13: Reveal True Key & Lower Bridge
        {
            hasDecoyKey = false;
            keyActive = true;
            spikes[0].lethal = false;
            platforms[platformCount++] = { 280, GROUND_HEIGHT, 420, 26, true };
            playSfx("Audios\\door.wav");
            triggerScreenShake(12, 3.5);
            spawnSparkleBurst(keyX + 16, keyY + 16, 251, 191, 36);
            for (int p = 0; p < 20; p++)
                spawnSparkleBurst(obj.x + 16, obj.y + 24, 74, 222, 128);
            addFloatingText(keyX - 60, keyY + 40, "BRIDGE EXTENDED & KEY REVEALED!", 74, 222, 128);
        }
        else if (currentLevel == 14) // Floor 15: Shift Stone Masonry
        {
            shiftingWallOpen = true;
            playSfx("Audios\\door.wav");
            triggerScreenShake(14, 4.0);
            addFloatingText(obj.x, obj.y + 50, "MASONRY SHIFTED UPWARD!", 74, 222, 128);
        }
    }
    else if (obj.type == BG_COGWHEEL_LEVER) // Chapter 3 Finale (Floor 20)
    {
        cogwheelActive = true;
        cogwheelAngle += 45.0;
        spikes[0].lethal = false;
        platforms[platformCount++] = { 240, GROUND_HEIGHT, 500, 26, true };
        playSfx("Audios\\door.wav");
        triggerScreenShake(14, 4.0);
        addFloatingText(obj.x, obj.y + 70, "CLOCKWORK DRAWBRIDGE EXTENDED!", 251, 191, 36);
    }
    else if (obj.type == BG_TORCH_SCONCE) // Floor 10
    {
        if (obj.hasTorch && !holdingTorch)
        {
            obj.hasTorch = false;
            holdingTorch = true;
            spawnSparkleBurst(playerX + 25, playerY + 35, 245, 158, 11);
            addFloatingText(playerX, playerY + 75, "TORCH TAKEN!", 245, 158, 11);
        }
        else if (!obj.hasTorch && holdingTorch)
        {
            obj.hasTorch = true;
            holdingTorch = false;
            spawnSparkleBurst(obj.x, obj.y + 12, 245, 158, 11);
            addFloatingText(playerX, playerY + 75, "TORCH PLACED!", 245, 158, 11);

            if (currentLevel == 9 && obj.x > 500)
            {
                guardAsleep = true;
                doorOpen = true;
                playSfx("Audios\\door.wav");
                addFloatingText(guardX, guardY + 120, "GUARD IS WARM & ASLEEP!", 56, 189, 248);
            }
        }
    }
    else if (obj.type == BG_WARP_PORTAL) // Arcane Warp
    {
        playerX = (obj.extraId == 0) ? 750 : 200;
        playerY = (obj.extraId == 0) ? 250 : GROUND_HEIGHT;
        playSfx("Audios\\key.wav");
        spawnSparkleBurst(playerX, playerY, 56, 189, 248);
        addFloatingText(playerX, playerY + 50, "WARPED!", 56, 189, 248);
    }
    else if (obj.type == BG_WINCH_DRAWBRIDGE) // Winch (Floor 24)
    {
        if (currentLevel == 23)
            platforms[platformCount++] = { 220, GROUND_HEIGHT, 540, 26, true };
        else
            platforms[platformCount++] = { 340, GROUND_HEIGHT, 420, 26, true };
        spikes[0].lethal = false;
        doorOpen = true;
        triggerScreenShake(16, 4.5);
        playSfx("Audios\\door.wav");
        addFloatingText(obj.x, obj.y + 50, "COLOSSAL DRAWBRIDGE LOWERED!", 74, 222, 128);
    }
}

/* -------------------- 120 FPS FIXED LOGIC UPDATE -------------------- */
void fixedUpdate()
{
    if (autoCaptureStep >= 0)
    {
        if (autoCaptureStep == 0)
        {
            // 1. Menu Carousel: RenoSir Collab Thumbnail with Big Red COMING SOON
            gameState = STATE_MENU;
            hoveredCarouselCard = 1; // Highlight Card 1 (RenoSir Collab)
            iDraw();
            saveGlScreenshot("C:\\Users\\USER\\.gemini\\antigravity-ide\\brain\\303356f2-2fa5-4c7e-8461-370538d64b8a\\menu_renosir_thumb.bmp");
            printf("Saved menu_renosir_thumb.bmp\n"); fflush(stdout);
            autoCaptureStep = 1;
        }
        else if (autoCaptureStep == 1)
        {
            // 2. RenoSir Collab Modal with Rebuilt Banner and Red COMING SOON Header
            gameState = STATE_MENU;
            showRenoSirCollabModal = true;
            iDraw();
            saveGlScreenshot("C:\\Users\\USER\\.gemini\\antigravity-ide\\brain\\303356f2-2fa5-4c7e-8461-370538d64b8a\\renosir_collab_modal.bmp");
            printf("Saved renosir_collab_modal.bmp\n"); fflush(stdout);
            showRenoSirCollabModal = false;
            autoCaptureStep = 2;
        }
        else if (autoCaptureStep == 2)
        {
            // 3. Penalty Game Aiming: CR7 Stance & Castle Guard Messi Shuffle
            startPenaltyGame(true);
            pAimX = 670.0f;
            pAimY = 410.0f;
            pPower = 0.85f;
            pCr7X = 396.0f;
            pCr7Y = 55.0f;
            pMessiX = 512.0f;
            pMessiY = 220.0f;
            strcpy(pMessiCustomQuote, "You shall NOT pass the Castle Gate, Cristiano!");
            iDraw();
            saveGlScreenshot("C:\\Users\\USER\\.gemini\\antigravity-ide\\brain\\303356f2-2fa5-4c7e-8461-370538d64b8a\\penalty_aim_cr7_back.bmp");
            printf("Saved penalty_aim_cr7_back.bmp\n"); fflush(stdout);
            autoCaptureStep = 3;
        }
        else if (autoCaptureStep == 3)
        {
            // 3.5 Penalty Run-Up Dynamic Stride
            gameState = STATE_PENALTY_GAME;
            penaltyPhase = PENALTY_RUNUP;
            pCr7Timer = 8;
            pCr7X = 431.0f;
            pCr7Y = 55.0f;
            pMessiX = 525.0f;
            pMessiY = 220.0f;
            iDraw();
            saveGlScreenshot("C:\\Users\\USER\\.gemini\\antigravity-ide\\brain\\303356f2-2fa5-4c7e-8461-370538d64b8a\\penalty_runup_stride.bmp");
            printf("Saved penalty_runup_stride.bmp\n"); fflush(stdout);
            autoCaptureStep = 4;
        }
        else if (autoCaptureStep == 4)
        {
            // 4. Ball In-Flight & Messi Realistic Diving Leap & Strike Follow-Through
            gameState = STATE_PENALTY_GAME;
            penaltyPhase = PENALTY_IN_FLIGHT;
            pBallX = 640.0f;
            pBallY = 380.0f;
            pBallZ = 0.75f;
            pMessiX = 590.0f;
            pMessiY = 280.0f;
            pMessiDiveTilt = 38.0f;
            pCr7X = 466.0f;
            pCr7Y = 55.0f;
            pCr7AnimState = 3; // Strike follow-through
            iDraw();
            saveGlScreenshot("C:\\Users\\USER\\.gemini\\antigravity-ide\\brain\\303356f2-2fa5-4c7e-8461-370538d64b8a\\penalty_messi_dive.bmp");
            printf("Saved penalty_messi_dive.bmp\n"); fflush(stdout);
            autoCaptureStep = 5;
        }
        else if (autoCaptureStep == 5)
        {
            // 5. Cinematic Movie SIUUU Celebration
            gameState = STATE_PENALTY_GAME;
            penaltyPhase = PENALTY_GOAL;
            penaltyResultTimer = 100; // SIUUU landing stance
            pCinemaBarHeight = 52.0f;  // Cinematic Widescreen Letterbox Bars
            pCr7X = 460.0f;
            pCr7Y = 36.0f;
            pCr7JumpY = 0.0f;
            pBallX = 680.0f;
            pBallY = 415.0f;
            pBallZ = 0.96f;
            pNetBulgeX = 680.0f;
            pNetBulgeY = 415.0f;
            pNetRippleTimer = 30;
            pMessiState = 5;
            pMessiDiveTilt = 28.0f;
            pMessiX = 610.0f;
            pMessiY = 220.0f;
            strcpy(pMessiCustomQuote, "WHAT A ROCKET! Impossible... The Castle Treasury is yours, King Cristiano!");
            iDraw();
            saveGlScreenshot("C:\\Users\\USER\\.gemini\\antigravity-ide\\brain\\303356f2-2fa5-4c7e-8461-370538d64b8a\\penalty_movie_siuuu.bmp");
            printf("Saved penalty_movie_siuuu.bmp\n"); fflush(stdout);
            autoCaptureStep = -1;
            exit(0);
        }
        return;
    }

    globalAnimTimer++;
    if (screenShakeTimer > 0) screenShakeTimer--;

    // Saha Reno 10-Minute Trial Timer Countdown
    if (sahaRenoTrialActive && !characters[HERO_SAHA_RENO].unlocked)
    {
        if (sahaRenoTrialFrames > 0)
        {
            sahaRenoTrialFrames--;
        }
        else
        {
            sahaRenoTrialActive = false;
            sahaRenoTrialFrames = 0;
            if (selectedHero == HERO_SAHA_RENO)
            {
                selectedHero = HERO_WILLIAM;
                saveProgress();
            }
            showToast("Saha Reno 10-Min Trial Expired!");
            playSfx("Audios\\ouch.wav");
        }
    }

    // Particles physics
    for (int i = 0; i < particleCount; i++)
    {
        Particle& p = particles[i];
        p.x += p.vx; p.y += p.vy;
        p.life--;
        p.a = (double)p.life / p.maxLife;
        if (p.life <= 0)
        {
            particles[i] = particles[--particleCount];
            i--;
        }
    }

    // Floating text update
    for (int i = 0; i < floatingTextCount; i++)
    {
        FloatingText& ft = floatingTexts[i];
        ft.y += 0.8;
        ft.life--;
        if (ft.life <= 0)
        {
            floatingTexts[i] = floatingTexts[--floatingTextCount];
            i--;
        }
    }

    // Intro Animation with Red Devil CR7 (Sir William Concept)
    if (gameState == STATE_INTRO)
    {
        introTimer++;
        if (introTitleY > 480) introTitleY -= 2.5;
        if (introHeroX < 400)
        {
            introHeroX += 2.0;
            walkCycle++;
            if (introTimer % 10 == 0)
            {
                spawnParticle(introHeroX + 30, introHeroY + 30, ((rand() % 40) - 20) / 20.0, (rand() % 30) / 20.0 + 0.6, 239, 68, 68, 4.0, 24, 2);
                spawnParticle(introHeroX + 30, introHeroY + 30, ((rand() % 40) - 20) / 20.0, (rand() % 30) / 20.0 + 0.6, 251, 191, 36, 3.5, 24, 1);
            }
        }
        else if (!introHeroStopped)
        {
            introHeroStopped = true;
            spawnSparkleBurst(460, GROUND_HEIGHT + 70, 251, 191, 36);
            spawnSparkleBurst(460, GROUND_HEIGHT + 70, 239, 68, 68);
            playSfx("Audios\\win.wav");
        }
        return;
    }

    // Game Over Ghost float
    if (gameState == STATE_GAME_OVER)
    {
        angelGhostTimer++;
        if (angelGhostY < 520)
            angelGhostY += 1.8;
        return;
    }

    if (gameState == STATE_PENALTY_GAME)
    {
        updatePenaltyGame();
        return;
    }

    if (gameState != STATE_PLAYING) return;

    levelTimer++;
    if (levelTimer % 60 == 0 && levelScore > 100)
        levelScore -= 2;

    if (squashTimer > 0) squashTimer--;
    if (coyoteTimer > 0) coyoteTimer--;
    if (jumpBuffer > 0) jumpBuffer--;
    if (pushTimer > 0) pushTimer--;
    if (springCompressTimer > 0) springCompressTimer--;
    isPushing = (pushTimer > 0);

    // Chapter 2: Cogwheel rotation
    if (cogwheelActive)
    {
        cogwheelAngle += 2.0;
        if (cogwheelAngle >= 360.0) cogwheelAngle -= 360.0;
    }

    // CONTINUOUS PROXIMITY DETECTION (EVERY SINGLE FRAME)
    activeInteractionIndex = -1;
    for (int i = 0; i < bgObjectCount; i++)
    {
        BgObject& obj = bgObjects[i];
        if (obj.interactive && obj.type != BG_SPRING_PAD)
        {
            int distX = (int)abs((playerX + PLAYER_WIDTH / 2) - (obj.x + obj.w / 2));
            if (distX < 110)
            {
                if (abs((int)playerY - obj.y) < 220 || (obj.type == BG_PULL_CHAIN && playerY <= obj.y + 120))
                {
                    activeInteractionIndex = i;
                    break;
                }
            }
        }
    }

    // BULLETPROOF KEYBOARD [E] / [SPACE] EDGE-TRIGGER
    static bool prevEKey = false;
    bool curEKey = (isKeyPressed('e') || isKeyPressed('E') || isKeyPressed('f') || isKeyPressed('F') || isKeyPressed(' '));
    if (curEKey && !prevEKey)
    {
        interactWithBackground();
    }
    prevEKey = curEKey;

    double moveSpeed = characters[selectedHero].baseSpeed;
    double jumpSpeed = characters[selectedHero].jumpSpeed;

    bool moving = false;
    double targetVX = 0;

    // Movement: Keyboard (A/D or Arrows) OR On-screen Touch Arrows (CLICK & HOLD CONTINUOUS!)
    bool pressLeft = (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT) || isTouchingLeft);
    bool pressRight = (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT) || isTouchingRight);

    if (selectedHero == HERO_SAHA_RENO)
    {
        // ---------------- DEDICATED RENOSIR QUANTUM MOVEMENT MECHANISM ----------------
        // 1. Instant Directional Snap: Instant turnaround without friction drag or facing delay
        // 2. Cyber Kinetic Vectoring: Immediate acceleration to maximum velocity (5.4 speed)
        // 3. Cybernetic Active Brake: Instant crisp halt when inputs are released on ground
        // 4. Rigid Face Orientation Lock: facing is strictly guaranteed 1 (right) or -1 (left)
        if (pressLeft && !pressRight)
        {
            facing = -1;
            targetVX = -5.4;
            if (velocityX > 0) velocityX = 0; // Cancel forward inertia instantly!
            velocityX = velocityX * 0.35 + targetVX * 0.65;
            moving = true;
        }
        else if (pressRight && !pressLeft)
        {
            facing = 1;
            targetVX = 5.4;
            if (velocityX < 0) velocityX = 0; // Cancel backward inertia instantly!
            velocityX = velocityX * 0.35 + targetVX * 0.65;
            moving = true;
        }
        else
        {
            if (onGround)
                velocityX = 0; // Instant cybernetic active stop!
            else
                velocityX *= 0.70;
        }
        playerX += velocityX;

        // Dedicated RenoSir Cybernetic Data Matrix Trail
        if (moving && onGround)
        {
            if (rand() % 2 == 0)
            {
                double px = (facing == 1) ? playerX - 4 : playerX + PLAYER_WIDTH + 4;
                double py = playerY + 8 + (rand() % (PLAYER_HEIGHT - 20));
                spawnParticle(px, py, -facing * 1.2, 0.5, 56, 189, 248, 2.6, 16, 1);
                if (rand() % 3 == 0)
                    spawnParticle(px, py, 0.0, 0.8, 251, 191, 36, 2.0, 14, 1);
            }
        }

        // Dedicated RenoSir Boot Ion Thruster Plumes
        if (!onGround && !isClimbing)
        {
            if (rand() % 2 == 0)
            {
                double bootY = playerY + 2;
                spawnParticle(playerX + 16, bootY, ((rand() % 10) - 5) / 10.0, -2.0, 56, 189, 248, 3.2, 12, 1);
                spawnParticle(playerX + 38, bootY, ((rand() % 10) - 5) / 10.0, -2.0, 14, 165, 233, 3.2, 12, 1);
            }
        }
    }
    else
    {
        // Standard Hero Movement Physics
        if (pressLeft)
        {
            targetVX = -moveSpeed;
            facing = -1;
            moving = true;
        }
        if (pressRight)
        {
            targetVX = moveSpeed;
            facing = 1;
            moving = true;
        }

        velocityX = velocityX * 0.76 + targetVX * 0.24;
        if (abs(velocityX) < 0.1 && !moving) velocityX = 0;
        playerX += velocityX;
    }

    // Footsteps & Dust Puffs (smooth natural cadence)
    if (moving && onGround)
    {
        walkCycle++;
        footstepTimer++;
        if (footstepTimer % 20 == 0)
        {
            spawnDustPuff(playerX + (facing == 1 ? 10 : 44), playerY);
            if (footstepTimer % 40 == 0)
                playSfx("Audios\\footstep1.wav");
            else
                playSfx("Audios\\footstep2.wav");
        }
    }
    else if (!moving && onGround)
    {
        walkCycle = 0;
        footstepTimer = 0;
    }

    // Climbing Ivy (Floor 6 & Floor 24)
    isClimbing = false;
    for (int i = 0; i < bgObjectCount; i++)
    {
        BgObject& obj = bgObjects[i];
        if (obj.type == BG_CLIMB_IVY)
        {
            if (playerX + PLAYER_WIDTH > obj.x && playerX < obj.x + obj.w &&
                playerY + PLAYER_HEIGHT > obj.y && playerY < obj.y + obj.h)
            {
                if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP))
                {
                    playerY += 4.0;
                    velocityY = 0;
                    isClimbing = true;
                    onGround = false;
                }
                else if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN))
                {
                    playerY -= 4.0;
                    velocityY = 0;
                    isClimbing = true;
                }
            }
        }
    }

    // Interactive Spring Pad Launch (Active across all levels!)
    for (int i = 0; i < bgObjectCount; i++)
    {
        BgObject& obj = bgObjects[i];
        if (obj.type == BG_SPRING_PAD)
        {
            if (playerX + PLAYER_WIDTH > obj.x && playerX < obj.x + obj.w &&
                playerY <= obj.y + obj.h + 8 && playerY >= obj.y)
            {
                springCompressTimer = 12;
                velocityY = 17.5; // High Spring Launch!
                onGround = false;
                playSfx("Audios\\bounce.wav");
                spawnDustPuff(playerX + 25, playerY);
                addFloatingText(playerX, playerY + 50, "BOOING!", 251, 191, 36);
            }
        }
    }

    // Jump Logic (Keyboard or Touch Jump)
    if (((isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) || isTouchingJump) && !isClimbing)
    {
        jumpBuffer = 8;
    }

    if (jumpBuffer > 0 && (onGround || coyoteTimer > 0))
    {
        velocityY = invertedGravity ? -jumpSpeed : jumpSpeed;
        onGround = false;
        coyoteTimer = 0;
        jumpBuffer = 0;
        playSfx("Audios\\jump.wav");
        spawnDustPuff(playerX + 22, playerY);
    }

    // Gravity
    if (!isClimbing)
    {
        double grav = invertedGravity ? 0.55 : -0.55;
        velocityY += grav;
        if (velocityY < -15) velocityY = -15;
        if (velocityY > 15) velocityY = 15;
        playerY += velocityY;
    }

    // Platform & Bridge Collisions
    onGround = false;
    for (int i = 0; i < platformCount; i++)
    {
        Platform p = platforms[i];
        if (!invertedGravity)
        {
            if (playerX + PLAYER_WIDTH > p.x && playerX < p.x + p.w)
            {
                if (playerY <= p.y + p.h && playerY >= p.y + p.h - 18 && velocityY <= 0)
                {
                    if (velocityY < -4) playSfx("Audios\\land.wav");
                    playerY = p.y + p.h;
                    velocityY = 0;
                    onGround = true;
                }
            }
        }
        else // Inverted gravity ceiling collision
        {
            if (playerX + PLAYER_WIDTH > p.x && playerX < p.x + p.w)
            {
                if (playerY + PLAYER_HEIGHT >= p.y && playerY + PLAYER_HEIGHT <= p.y + 24 && velocityY >= 0)
                {
                    if (velocityY > 4) playSfx("Audios\\land.wav");
                    playerY = p.y - PLAYER_HEIGHT;
                    velocityY = 0;
                    onGround = true;
                }
            }
        }
    }

    // Pushable Crates Collision & Physics
    for (int i = 0; i < bgObjectCount; i++)
    {
        BgObject& obj = bgObjects[i];
        if (obj.type == BG_PUSH_CRATE)
        {
            if (playerX + PLAYER_WIDTH > obj.x && playerX < obj.x + obj.w &&
                playerY <= obj.y + obj.h && playerY >= obj.y + obj.h - 16 && velocityY <= 0)
            {
                playerY = obj.y + obj.h;
                velocityY = 0;
                onGround = true;
            }

            if (playerY < obj.y + obj.h && playerY + PLAYER_HEIGHT > obj.y)
            {
                if (facing == 1 && playerX + PLAYER_WIDTH >= obj.x && playerX < obj.x + 10)
                {
                    double pushPower = (selectedHero == HERO_THORGAR) ? 4.0 : 2.2;
                    obj.x += (int)pushPower;
                    pushTimer = 6;
                }
                else if (facing == -1 && playerX <= obj.x + obj.w && playerX > obj.x + obj.w - 10)
                {
                    double pushPower = (selectedHero == HERO_THORGAR) ? 4.0 : 2.2;
                    obj.x -= (int)pushPower;
                    pushTimer = 6;
                }
            }
        }
    }

    if (onGround) coyoteTimer = 6;

    // Screen Bounds
    if (playerX < 0) playerX = 0;
    if (playerX > SCREEN_WIDTH - PLAYER_WIDTH) playerX = SCREEN_WIDTH - PLAYER_WIDTH;

    // Pit Fall
    if (playerY < -60 || playerY > SCREEN_HEIGHT + 60)
    {
        playSfx("Audios\\ouch.wav");
        angelGhostX = playerX;
        angelGhostY = GROUND_HEIGHT;
        angelGhostTimer = 0;
        gameState = STATE_GAME_OVER;
    }

    // Key Collection
    if (keyActive && !hasKey)
    {
        if (playerX + PLAYER_WIDTH > keyX && playerX < keyX + 36 &&
            playerY + PLAYER_HEIGHT > keyY && playerY < keyY + 36)
        {
            hasKey = true;
            keyActive = false;
            doorOpen = true;
            playSfx("Audios\\key.wav");
            spawnSparkleBurst(keyX + 18, keyY + 18, 251, 191, 36);
            addFloatingText(keyX, keyY + 25, "KEY COLLECTED!", 251, 191, 36);
        }
    }

    // Secret Star Collection
    if (starActive)
    {
        if (playerX + PLAYER_WIDTH > starX - 18 && playerX < starX + 18 &&
            playerY + PLAYER_HEIGHT > starY - 18 && playerY < starY + 18)
        {
            starActive = false;
            levelScore += 500;
            playSfx("Audios\\star.wav");
            spawnSparkleBurst(starX, starY, 251, 191, 36);
            addFloatingText(starX, starY + 25, "+500 BONUS STAR!", 251, 191, 36);
        }
    }

    // Ghost Chasing (Floor 3)
    if (ghost.active)
    {
        int dx = (int)playerX - ghost.x;
        int dy = (int)playerY - ghost.y;
        double dist = sqrt((double)(dx * dx + dy * dy));
        if (dist > 5)
        {
            ghost.x += (int)((dx / dist) * 1.8);
            ghost.y += (int)((dy / dist) * 1.8);
        }
        if (abs(playerX - ghost.x) < 24 && abs(playerY - ghost.y) < 24)
        {
            playSfx("Audios\\ouch.wav");
            angelGhostX = playerX;
            angelGhostY = playerY;
            angelGhostTimer = 0;
            gameState = STATE_GAME_OVER;
        }
    }

    // Floor 4: Pushing Heavy Door
    if (levels[currentLevel].doorPushable && !doorOpen)
    {
        if (playerX + PLAYER_WIDTH >= doorX && playerX < doorX + 16 &&
            playerY < doorY + 110 && playerY + PLAYER_HEIGHT > doorY)
        {
            double pushPower = (selectedHero == HERO_THORGAR) ? 5.0 : 2.5;
            doorPushedDistance += (int)pushPower;
            doorX += (int)pushPower;
            if (doorPushedDistance > 130)
            {
                doorOpen = true;
                playSfx("Audios\\door.wav");
            }
        }
    }

    // Floor 5: Falling Key Physics
    if (fallingKeyActive)
    {
        fallingKeyY += (int)fallingKeyVY;

        if (playerX + PLAYER_WIDTH > 520 && playerX < 575 &&
            playerY + PLAYER_HEIGHT > fallingKeyY && playerY < fallingKeyY + 36)
        {
            fallingKeyActive = false;
            hasKey = true;
            doorOpen = true;
            playSfx("Audios\\key.wav");
            addFloatingText(playerX, playerY + 60, "CATCH!", 251, 191, 36);
        }
        else if (fallingKeyY <= GROUND_HEIGHT + 4)
        {
            fallingKeyActive = false;
            buttonPressed = true;
            playSfx("Audios\\ouch.wav");
            angelGhostX = playerX;
            angelGhostY = playerY;
            angelGhostTimer = 0;
            gameState = STATE_GAME_OVER;
        }
    }

    // Floor 7: Gravity Pad Flip (COMPLETELY FIXED & SOLVABLE!)
    if (currentLevel == 6)
    {
        // Step on floor rune -> inverts gravity to ceiling
        if (!invertedGravity && playerX + PLAYER_WIDTH > 195 && playerX < 305 && playerY <= GROUND_HEIGHT + 24)
        {
            invertedGravity = true;
            velocityY = 9.0;
            spawnSparkleBurst(250, GROUND_HEIGHT + 14, 192, 132, 252);
            addFloatingText(250, GROUND_HEIGHT + 40, "GRAVITY INVERTED! WALK ON CEILING", 192, 132, 252);
            playSfx("Audios\\jump.wav");
        }
        // Past the spikes on ceiling (or touching wide return pad or right wall) -> flips gravity safely back to floor!
        if (invertedGravity && (playerX >= 680 || (playerX + PLAYER_WIDTH > 670 && playerY >= 440)))
        {
            invertedGravity = false;
            velocityY = -5.0;
            spawnSparkleBurst((int)playerX + 25, 520, 74, 222, 128);
            addFloatingText((int)playerX, 480, "GRAVITY RESTORED! REACH THE DOOR", 74, 222, 128);
            playSfx("Audios\\door.wav");
        }
        // Also allow manual flip back if player is past spikes and presses Down / Jump / E
        if (invertedGravity && playerX >= 660 && (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN) || isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP) || isTouchingJump || isKeyPressed('e') || isKeyPressed('E')))
        {
            invertedGravity = false;
            velocityY = -5.0;
            spawnSparkleBurst((int)playerX + 25, (int)playerY, 74, 222, 128);
            addFloatingText((int)playerX, (int)playerY - 20, "GRAVITY RESTORED!", 74, 222, 128);
        }
        // Failsafe: if player reached right end on ceiling, drop down immediately
        if (invertedGravity && playerX > 880)
        {
            invertedGravity = false;
            velocityY = -4.0;
        }
    }

    // Floor 8: Meditation / Patience
    if (currentLevel == 7)
    {
        if (!moving)
        {
            meditateTimer++;
            if (meditateTimer > 150)
            {
                meditateState = 2;
                spikes[0].lethal = false;
                doorOpen = true;
                hasKey = true;
                addFloatingText(500, 240, "PATIENCE MASTERY! SPIKES RETRACTED", 74, 222, 128);
            }
        }
        else if (meditateState < 2)
        {
            meditateTimer = 0;
        }
    }

    // Floor 9: Button Trap
    if (currentLevel == 8 && !crusherJammed)
    {
        if (playerX + PLAYER_WIDTH > buttonX - 25 && playerX < buttonX + 25 && playerY <= buttonY + 16)
        {
            buttonPressed = true;
            crusherFalling = true;
        }
        if (crusherFalling)
        {
            crusherY -= 8;
            if (playerX + PLAYER_WIDTH > spikes[0].x && playerX < spikes[0].x + spikes[0].w &&
                playerY + PLAYER_HEIGHT > crusherY - 34 && playerY < crusherY)
            {
                playSfx("Audios\\ouch.wav");
                angelGhostX = playerX;
                angelGhostY = playerY;
                angelGhostTimer = 0;
                gameState = STATE_GAME_OVER;
            }
        }
    }

    // Floor 11: Mirror Dimension Resonance
    if (currentLevel == 10)
    {
        mirrorPlayerX = 512 + (512 - (int)playerX) - PLAYER_WIDTH;
        if (mirrorPlayerX >= 730 && mirrorPlayerX <= 790 && playerY <= GROUND_HEIGHT + 14)
        {
            if (!hasKey)
            {
                hasKey = true;
                doorOpen = true;
                playSfx("Audios\\key.wav");
                spawnSparkleBurst(mirrorPlayerX + 25, GROUND_HEIGHT + 35, 56, 189, 248);
                addFloatingText(512, 280, "MIRROR RESONANCE! DOOR UNLOCKED", 56, 189, 248);
            }
        }
    }

    // Floor 12: End of Chapter 1 - Red Button Drawbridge
    if (currentLevel == 11)
    {
        // Player steps on the upper platform red button
        if (!floor12BridgeLowered && playerX + PLAYER_WIDTH > buttonX - 25 && playerX < buttonX + 25 &&
            playerY >= buttonY - 6 && playerY <= buttonY + 20)
        {
            buttonPressed = true;
            floor12BridgeLowered = true;
            spikes[0].lethal = false;
            platforms[platformCount++] = { 240, GROUND_HEIGHT, 500, 26, true };
            triggerScreenShake(12, 4.0);
            playSfx("Audios\\spring.wav");
            addFloatingText(buttonX, buttonY + 45, "DRAWBRIDGE LOWERED! PIT BRIDGED", 74, 222, 128);
            for (int p = 0; p < 20; p++)
                spawnSparkleBurst(buttonX, buttonY + 12, 251, 191, 36);
        }
    }

    // Floor 13: Decoy Key Trap
    if (currentLevel == 12 && hasDecoyKey)
    {
        if (playerX + PLAYER_WIDTH > decoyKeyX && playerX < decoyKeyX + 32 &&
            playerY + PLAYER_HEIGHT > decoyKeyY && playerY < decoyKeyY + 32)
        {
            hasDecoyKey = false;
            playSfx("Audios\\ouch.wav");
            addFloatingText(decoyKeyX - 30, decoyKeyY + 40, "FOOLED! A DECOY KEY!", 239, 68, 68);
            for (int p = 0; p < 15; p++)
                spawnSparkleBurst(decoyKeyX + 16, decoyKeyY + 16, 239, 68, 68);
        }
    }

    // Floor 14: Swinging Pendulum Blade & Safety Button
    if (currentLevel == 13)
    {
        // Step on floor red button to freeze/lock the blade trap and lower the safety walkway
        if (!pendulumLocked && playerX + PLAYER_WIDTH > buttonX - 25 && playerX < buttonX + 25 &&
            playerY <= buttonY + 16)
        {
            buttonPressed = true;
            pendulumLocked = true;
            spikes[0].lethal = false; // Neutralize the spike chasm!
            platforms[platformCount++] = { 400, GROUND_HEIGHT, 340, 26, true }; // Lower solid safety walkway!
            triggerScreenShake(12, 4.0);
            playSfx("Audios\\interact.wav");
            playSfx("Audios\\door.wav");
            addFloatingText(buttonX - 40, buttonY + 45, "SAFETY BRIDGE LOWERED! BLADE LOCKED", 74, 222, 128);
            for (int p = 0; p < 20; p++)
                spawnSparkleBurst(buttonX, buttonY + 12, 74, 222, 128);
        }

        if (!pendulumLocked)
        {
            pendulumAngle = sin(levelTimer * 0.055) * 48.0;
            int pivX = 520, pivY = 560;
            double rad = pendulumAngle * 3.14159265 / 180.0;
            int blX = pivX + (int)(sin(rad) * 340.0);
            int blY = pivY - (int)(cos(rad) * 340.0);

            // Blade collision with player
            if (playerX + PLAYER_WIDTH > blX - 32 && playerX < blX + 32 &&
                playerY + PLAYER_HEIGHT > blY - 32 && playerY < blY + 32)
            {
                playSfx("Audios\\ouch.wav");
                angelGhostX = playerX;
                angelGhostY = playerY;
                angelGhostTimer = 0;
                gameState = STATE_GAME_OVER;
            }
        }
        else
        {
            // Retract pendulum blade safely up towards the ceiling
            if (pendulumAngle > -80.0)
                pendulumAngle -= 2.5;
        }
    }

    // Floor 15: Shifting Castle Wall
    if (currentLevel == 14)
    {
        if (shiftingWallOpen)
        {
            if (shiftingWallY < 560)
                shiftingWallY += 6;
        }
        else
        {
            // Block player from passing x=500
            if (playerX + PLAYER_WIDTH > 500 && playerX < 590 && playerY < shiftingWallY + 450)
            {
                playerX = 500 - PLAYER_WIDTH;
                velocityX = 0;
            }
        }
    }

    // Floor 19: Arcane Warp Portals
    static int portalCooldown = 0;
    if (portalCooldown > 0) portalCooldown--;
    if (portalCooldown == 0 && currentLevel == 18)
    {
        for (int i = 0; i < bgObjectCount; i++)
        {
            if (bgObjects[i].type == BG_WARP_PORTAL)
            {
                if (playerX + PLAYER_WIDTH > bgObjects[i].x && playerX < bgObjects[i].x + bgObjects[i].w &&
                    playerY + PLAYER_HEIGHT > bgObjects[i].y && playerY < bgObjects[i].y + bgObjects[i].h)
                {
                    int destIdx = (i == 0 && bgObjectCount > 1) ? 1 : 0;
                    playSfx("Audios\\key.wav");
                    for (int p = 0; p < 20; p++) spawnSparkleBurst((int)playerX + 25, (int)playerY + 35, 56, 189, 248);
                    playerX = bgObjects[destIdx].x + 10;
                    playerY = bgObjects[destIdx].y + 10;
                    portalCooldown = 40;
                    for (int p = 0; p < 20; p++) spawnSparkleBurst((int)playerX + 25, (int)playerY + 35, 251, 191, 36);
                    addFloatingText(playerX, playerY + 50, "WARPED!", 56, 189, 248);
                    break;
                }
            }
        }
    }

    // Floor 22: Magma Stepping Stones Button
    if (currentLevel == 21)
    {
        if (!buttonPressed && playerX + PLAYER_WIDTH > buttonX - 25 && playerX < buttonX + 25 &&
            playerY <= buttonY + 16)
        {
            buttonPressed = true;
            spikes[0].lethal = false;
            platforms[platformCount++] = { 260, GROUND_HEIGHT, 480, 26, true };
            playSfx("Audios\\spring.wav");
            triggerScreenShake(12, 3.5);
            addFloatingText(buttonX - 40, buttonY + 45, "MAGMA COOLED! OBSIDIAN BRIDGE EXTENDED", 74, 222, 128);
            for (int p = 0; p < 20; p++)
                spawnSparkleBurst(buttonX, buttonY + 12, 74, 222, 128);
        }
    }

    // Lethal Spike Collision Check
    for (int i = 0; i < spikeCount; i++)
    {
        SpikeTrap s = spikes[i];
        if (s.lethal)
        {
            if (playerX + PLAYER_WIDTH > s.x && playerX < s.x + s.w &&
                playerY < s.y + s.h && playerY + PLAYER_HEIGHT > s.y)
            {
                playSfx("Audios\\ouch.wav");
                angelGhostX = playerX;
                angelGhostY = playerY;
                angelGhostTimer = 0;
                gameState = STATE_GAME_OVER;
            }
        }
    }

    // Exit Door Collision (CLEAR LEVEL)
    if (playerX + PLAYER_WIDTH > doorX && playerX < doorX + 72 &&
        playerY + PLAYER_HEIGHT > doorY && playerY < doorY + 110)
    {
        if (levels[currentLevel].doorRequiresKey)
        {
            if (hasKey)
            {
                doorOpen = true;
                gameState = STATE_LEVEL_CLEAR;

                int starsAwarded = 1;
                if (!usedInstantPassThisLevel)
                {
                    starsAwarded = 2;
                    if (!starActive)
                        starsAwarded = 3;
                }

                if (starsAwarded > levelStars[currentLevel])
                {
                    totalStars += (starsAwarded - levelStars[currentLevel]);
                    levelStars[currentLevel] = starsAwarded;
                }
                if (levelScore > levelScores[currentLevel])
                    levelScores[currentLevel] = levelScore;

                if (currentLevel + 1 >= unlockedLevels)
                {
                    unlockedLevels = currentLevel + 2;
                    if (unlockedLevels > LEVEL_COUNT) unlockedLevels = LEVEL_COUNT;
                }

                saveProgress();
                playSfx("Audios\\win.wav");
            }
        }
        else
        {
            gameState = STATE_LEVEL_CLEAR;
            int starsAwarded = usedInstantPassThisLevel ? 1 : (starActive ? 2 : 3);
            if (starsAwarded > levelStars[currentLevel])
            {
                totalStars += (starsAwarded - levelStars[currentLevel]);
                levelStars[currentLevel] = starsAwarded;
            }
            if (currentLevel + 1 >= unlockedLevels)
            {
                unlockedLevels = currentLevel + 2;
                if (unlockedLevels > LEVEL_COUNT) unlockedLevels = LEVEL_COUNT;
            }
            saveProgress();
            playSfx("Audios\\win.wav");
        }
    }
}

