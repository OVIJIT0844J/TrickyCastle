#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: PenaltyGame.h
 * DEVELOPER: Maheed Abrar (Student ID: 00725105101140)
 * ROLE & RESPONSIBILITY: Mini-Game Engine: Cristiano Ronaldo vs Messi Penalty Derby
 *
 * FEATURES IMPLEMENTED:
 *   - Full standalone mini-game subsystem (~1,593 lines of advanced logic & math)
 *   - Interactive aiming crosshair targeting castle goal corners
 *   - Power charge oscillation meter with precision sweet-spot timing
 *   - Articulated CR7 run-up stride animation and realistic kicking strike pose
 *   - 3D pseudo-perspective ball flight trajectory (parabolic arc with Z-depth scaling)
 *   - Castle Guard Lionel Messi goalkeeper AI: dynamic lateral shuffling & diving leaps
 *   - Collision detection: crossbar rebounds, post deflections, and glove saves
 *   - Goal net ripple vertex physics simulation upon scoring
 *   - Cinematic letterbox movie presentation with widescreen black bars
 *   - World-famous SIUUU celebration sequence with crowd cheer SFX and confetti embers
 *   - Rematch arena loop, reward coin payout, and custom dialogue bubbles
 * DEPENDENCIES: GameDefines.h, RenderUtils.h, CharacterRender.h, AudioSystem.h, SaveSystem.h
 * =========================================================================== */
#include "GameDefines.h"
#include "RenderUtils.h"
#include "CharacterRender.h"
#include "AudioSystem.h"
#include "SaveSystem.h"

/* =========================================================================
   MINI FOOTBALL PENALTY GAME: CRISTIANO RONALDO VS CASTLE GUARD LIONEL MESSI
   Authentic Medieval Penalty Derby for Daily Login Rewards & Rematch Arena
   ========================================================================= */

enum PenaltyPhase
{
    PENALTY_AIMING,       // Player aiming crosshair, Messi shuffling & threatening
    PENALTY_CHARGING,     // Charging kick power meter
    PENALTY_RUNUP,        // CR7 running up to the ball
    PENALTY_IN_FLIGHT,    // Ball flying towards goal in 3D perspective; Messi dives
    PENALTY_GOAL,         // Goal scored! Net ripples, CR7 SIUUU!, Messi defeated
    PENALTY_SAVED,        // Ball blocked by Messi! Messi taunts, retry option
    PENALTY_POST          // Ball hit crossbar or post with iron clang!
};

bool penaltyForDailyReward = true;
int penaltyGoalsTotal = 0;
int penaltySavesTotal = 0;
int penaltyStreak = 0;

// 3D Ball Physics
float pBallX = 512.0f;
float pBallY = 90.0f;
float pBallZ = 0.0f; // 0.0 at penalty spot -> 1.0 at goal net plane
float pBallVx = 0.0f;
float pBallVy = 0.0f;
float pBallVz = 0.0f;
float pBallRot = 0.0f;
float pBallRotSpeed = 0.0f;
float pBallTargetX = 512.0f;
float pBallTargetY = 340.0f;

// Crosshair Aiming
float pAimX = 512.0f;
float pAimY = 340.0f;

// Power Meter
float pPower = 0.0f;
float pPowerSpeed = 0.030f;
int pPowerDir = 1;
bool pIsCharging = false;

// Cristiano Ronaldo (Shooter - Exclusive Penalty Character)
float pCr7X = 396.0f;
float pCr7Y = 55.0f;
int pCr7AnimState = 0; // 0: Idle, 1: Stride 1, 2: Stride 2, 3: Kick strike, 4: SIUUU celebration
int pCr7Timer = 0;
float pCr7JumpY = 0.0f;

// Cinematic Movie Celebration Variables
float pCinemaBarHeight = 0.0f;
float pShockwaveRadius = 0.0f;
float pShockwaveAlpha = 0.0f;

// Castle Guard Captain Lionel Messi (Goalkeeper)
float pMessiX = 512.0f;
float pMessiY = 220.0f;
float pMessiTargetX = 512.0f;
float pMessiTargetY = 220.0f;
float pMessiDiveTilt = 0.0f;
int pMessiState = 0; // 0: Idle shuffle, 1: Diving, 4: Celebrating save, 5: Conceded
int pMessiQuoteTimer = 0;
int pMessiQuoteIndex = 0;
char pMessiCustomQuote[160] = "You shall NOT pass the Castle Gate, Cristiano!";

// Net Physics & Bulge
int pNetRippleTimer = 0;
float pNetBulgeX = 512.0f;
float pNetBulgeY = 340.0f;

// State & UI
PenaltyPhase penaltyPhase = PENALTY_AIMING;
int penaltyResultTimer = 0;
bool penaltyClaimedPopup = false;
bool hoveredPenaltyBackBtn = false;
bool hoveredPenaltyClaimBtn = false;
bool hoveredPenaltyRetryBtn = false;

// Castle Guard Messi Medieval Threat Quotes
const char* messiThreatQuotes[] = {
    "You shall NOT pass the Castle Gate, Cristiano!",
    "I have 8 Ballon d'Or shields! Your penalties cannot pierce my fortress!",
    "Que miras, bobo?! Go back to the bench! This goal is locked!",
    "No 'SIUUU' permitted in my castle today, Ronaldo!",
    "My halberd guards the kingdom, and my gloves guard this net!",
    "Think your knuckleball can beat the World Champion Guard?!",
    "I know all your tricks, CR7! Down the middle or in the corner, it's MINE!",
    "One miss and I'm tossing you straight into the dungeon!",
    "Shoot if you dare! You're facing Captain Lionel Messi!",
    "Your kingdom ends at this penalty spot, Cristiano!"
};
const int MESSI_THREAT_COUNT = 10;

const char* messiSaveQuotes[] = {
    "DENIED! The Castle Vault stays LOCKED! Back to training, Ronny!",
    "HA! Was that a kick or a pass to my gloves? Pathetic!",
    "NOT IN MY HOUSE! You can't beat Castle Guard Messi!",
    "Save number one! You'll never get this daily reward!",
    "Is that your best shot, CR7? My grandma kicks harder!"
};

const char* messiDefeatedQuotes[] = {
    "WHAT A ROCKET! Impossible... The Castle Treasury is yours, King Cristiano!",
    "AGHH! What a strike into the top bin! Claim your royal loot!",
    "Respect, CR7... That strike shattered my defenses! Take the crown!",
    "Unstoppable velocity... I couldn't reach that corner! Well played!",
    "Incredible shot, Ronaldo! Go claim today's treasure!"
};

const char* messiPostQuotes[] = {
    "CLANG! The castle iron stands with me! Denied!",
    "Saved by the woodwork! The fortress protects me!"
};

/* -------------------- 3D PROCEDURAL SOCCER BALL -------------------- */
void drawSoccerBall(float cx, float cy, float radius, float rotAngle)
{
    // Soft ground/air shadow
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.28f);
    iFilledCircle((int)(cx + radius * 0.15f), (int)(cy - radius * 0.25f), (int)radius);

    // Crisp white sphere with realistic specular shading
    glColor4f(0.97f, 0.97f, 0.99f, 1.0f);
    iFilledCircle((int)cx, (int)cy, (int)radius);

    // Subtle spherical shading crescent
    glColor4f(0.12f, 0.18f, 0.28f, 0.16f);
    iFilledCircle((int)(cx + radius * 0.22f), (int)(cy - radius * 0.22f), (int)(radius * 0.85f));
    glColor4f(1.0f, 1.0f, 1.0f, 0.40f);
    iFilledCircle((int)(cx - radius * 0.25f), (int)(cy + radius * 0.25f), (int)(radius * 0.45f));
    glDisable(GL_BLEND);

    // Rotating black pentagonal patches and leather seams
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(rotAngle, 0, 0, 1);

    // Center pentagon
    glColor3f(0.12f, 0.14f, 0.18f);
    float pr = radius * 0.38f;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++)
    {
        float a = i * (6.283185f / 5.0f) - 1.570796f;
        glVertex2f(cos(a) * pr, sin(a) * pr);
    }
    glEnd();

    // 5 outer patches & radial seam lines
    glLineWidth(1.8f);
    glColor3f(0.12f, 0.14f, 0.18f);
    for (int i = 0; i < 5; i++)
    {
        float a1 = i * (6.283185f / 5.0f) - 1.570796f;
        float a2 = (i + 1) * (6.283185f / 5.0f) - 1.570796f;
        float midA = (a1 + a2) * 0.5f;

        glBegin(GL_LINES);
        glVertex2f(cos(a1) * pr, sin(a1) * pr);
        glVertex2f(cos(a1) * (radius * 0.94f), sin(a1) * (radius * 0.94f));
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(cos(a1) * (radius * 0.94f), sin(a1) * (radius * 0.94f));
        glVertex2f(cos(a2) * (radius * 0.94f), sin(a2) * (radius * 0.94f));
        glVertex2f(cos(midA) * (radius * 0.58f), sin(midA) * (radius * 0.58f));
        glEnd();
    }

    // Outer leather rim
    glColor3f(0.15f, 0.18f, 0.22f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 24; i++)
    {
        float a = i * (6.283185f / 24.0f);
        glVertex2f(cos(a) * radius, sin(a) * radius);
    }
    glEnd();

    glPopMatrix();
}

/* -------------------- RESET & START PENALTY BALL -------------------- */
void resetPenaltyBall()
{
    penaltyPhase = PENALTY_AIMING;
    pBallX = 512.0f;
    pBallY = 90.0f;
    pBallZ = 0.0f;
    pBallVx = 0.0f;
    pBallVy = 0.0f;
    pBallVz = 0.0f;
    pBallRot = 0.0f;
    pBallRotSpeed = 0.0f;
    pPower = 0.0f;
    pPowerDir = 1;
    pIsCharging = false;
    pCr7X = 396.0f;
    pCr7Y = 55.0f;
    pCr7AnimState = 0;
    pCr7Timer = 0;
    pCr7JumpY = 0.0f;
    pMessiDiveTilt = 0.0f;
    pMessiState = 0;
    pNetRippleTimer = 0;
    penaltyResultTimer = 0;
    penaltyClaimedPopup = false;
    pCinemaBarHeight = 0.0f;
    pShockwaveRadius = 0.0f;
    pShockwaveAlpha = 0.0f;
    pMessiQuoteIndex = rand() % MESSI_THREAT_COUNT;
    strcpy(pMessiCustomQuote, messiThreatQuotes[pMessiQuoteIndex]);
}

void startPenaltyGame(bool forDailyReward)
{
    penaltyForDailyReward = forDailyReward;
    gameState = STATE_PENALTY_GAME;
    resetPenaltyBall();
    playSfx("Audios\\whistle.wav");
    spawnSparkleBurst(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 251, 191, 36);
}

void triggerPenaltyKick()
{
    if (penaltyPhase != PENALTY_CHARGING && penaltyPhase != PENALTY_AIMING) return;
    if (pPower < 0.20f) pPower = 0.55f; // minimum kick velocity

    penaltyPhase = PENALTY_RUNUP;
    pCr7AnimState = 1;
    pCr7Timer = 0;
    pIsCharging = false;

    pBallTargetX = pAimX;
    pBallTargetY = pAimY;

    // Overpower penalty (red zone > 0.94) can lift shot slightly
    if (pPower > 0.94f)
    {
        pBallTargetY += (pPower - 0.94f) * 420.0f;
        pBallTargetX += (rand() % 36 - 18);
    }

    playSfx("Audios\\footstep2.wav");
}

/* -------------------- UPDATE PENALTY GAME PHYSICS & ANIMATIONS -------------------- */
void updatePenaltyGame()
{
    // 1. Aiming / Idle Stance & Messi Goal-Line Movement
    if (penaltyPhase == PENALTY_AIMING)
    {
        pMessiQuoteTimer++;
        if (pMessiQuoteTimer > 210)
        {
            pMessiQuoteTimer = 0;
            pMessiQuoteIndex = (pMessiQuoteIndex + 1) % MESSI_THREAT_COUNT;
            strcpy(pMessiCustomQuote, messiThreatQuotes[pMessiQuoteIndex]);
        }

        // Castle Guard Messi goal-line dynamic shuffle
        float wave1 = sin(globalAnimTimer * 0.048f) * 115.0f;
        float wave2 = sin(globalAnimTimer * 0.115f) * 32.0f;
        pMessiX = 512.0f + wave1 + wave2;
        pMessiY = 220.0f + abs(sin(globalAnimTimer * 0.22f)) * 7.0f;
        pMessiDiveTilt = sin(globalAnimTimer * 0.08f) * 3.5f;

        // CR7 boot flame aura particles
        if (rand() % 2 == 0)
        {
            spawnParticle(pCr7X + 32 + (rand() % 16 - 8), pCr7Y + 12 + (rand() % 12),
                          ((rand() % 20) - 10) / 18.0, (rand() % 25) / 18.0 + 0.6,
                          239, 68, 68, 3.5, 20, 2);
            spawnParticle(pCr7X + 32 + (rand() % 16 - 8), pCr7Y + 12 + (rand() % 12),
                          ((rand() % 20) - 10) / 18.0, (rand() % 25) / 18.0 + 0.6,
                          251, 191, 36, 3.0, 18, 1);
        }
    }

    // 2. Power Meter charging
    if (penaltyPhase == PENALTY_CHARGING)
    {
        pPower += pPowerSpeed * pPowerDir;
        if (pPower >= 1.0f) { pPower = 1.0f; pPowerDir = -1; }
        else if (pPower <= 0.0f) { pPower = 0.0f; pPowerDir = 1; }

        pMessiDiveTilt = (sin(globalAnimTimer * 0.25f) * 2.0f);
        pMessiY = 220.0f + abs(sin(globalAnimTimer * 0.35f)) * 5.0f;

        spawnParticle(pCr7X + 35, pCr7Y + 10, ((rand() % 24) - 12) / 15.0, (rand() % 30) / 15.0 + 0.8,
                      251, 191, 36, 4.0, 22, 1);
    }

    // 3. CR7 Run-up animation
    if (penaltyPhase == PENALTY_RUNUP)
    {
        pCr7Timer++;
        float runProgress = (float)pCr7Timer / 16.0f;
        if (runProgress > 1.0f) runProgress = 1.0f;
        pCr7X = 396.0f + (466.0f - 396.0f) * runProgress;

        if (pCr7Timer < 6) pCr7AnimState = 1;
        else if (pCr7Timer < 12) pCr7AnimState = 2;
        else if (pCr7Timer < 16) pCr7AnimState = 2;
        else
        {
            // STRIKE THE BALL!
            pCr7AnimState = 3;
            penaltyPhase = PENALTY_IN_FLIGHT;
            playSfx("Audios\\kick.wav");

            // 3D trajectory velocity setup
            float flightFrames = 26.0f - pPower * 11.0f; // 15 to 26 frames
            if (flightFrames < 15.0f) flightFrames = 15.0f;
            pBallVz = 1.0f / flightFrames;
            pBallVx = (pBallTargetX - 512.0f) / flightFrames;
            pBallVy = (pBallTargetY - 90.0f) / flightFrames;
            pBallRotSpeed = (pBallTargetX < 512.0f ? -22.0f : 22.0f) * (0.85f + pPower * 0.5f);

            // Impact flash ring
            spawnSparkleBurst(512, 90, 251, 191, 36);
            spawnSparkleBurst(512, 90, 239, 68, 68);

            // Messi AI anticipates dive direction
            float diveGuessX = pBallTargetX;
            if (pPower > 0.72f && (pBallTargetX < 340.0f || pBallTargetX > 684.0f))
            {
                // Top-corner rocket beats goalkeeper reach!
                diveGuessX = (pBallTargetX < 512.0f ? pBallTargetX + 55.0f : pBallTargetX - 55.0f);
            }
            else if (rand() % 5 == 0)
            {
                // 20% dive wrong way
                diveGuessX = (pBallTargetX < 512.0f ? 640.0f : 380.0f);
            }
            pMessiTargetX = diveGuessX;
            pMessiTargetY = (pBallTargetY > 380.0f ? 220.0f + (pBallTargetY - 220.0f) * 0.65f : 220.0f);
            pMessiState = 1; // diving
        }
    }

    // 4. Ball In-Flight & 3D Goal Plane Collision
    if (penaltyPhase == PENALTY_IN_FLIGHT)
    {
        pBallZ += pBallVz;
        pBallX += pBallVx;
        pBallY += pBallVy;
        pBallRot += pBallRotSpeed;

        // Fiery CR7 comet trail
        spawnParticle(pBallX, pBallY, ((rand() % 16) - 8) / 20.0, ((rand() % 16) - 8) / 20.0,
                      239, 68, 68, 4.5f * (1.0f - pBallZ * 0.5f), 18, 2);
        spawnParticle(pBallX, pBallY, ((rand() % 16) - 8) / 20.0, ((rand() % 16) - 8) / 20.0,
                      251, 191, 36, 4.0f * (1.0f - pBallZ * 0.5f), 18, 1);

        // Castle Guard Messi dives towards ball target
        pMessiX += (pMessiTargetX - pMessiX) * 0.16f;
        pMessiY += (pMessiTargetY - pMessiY) * 0.14f;
        float targetTilt = (pMessiTargetX > 512.0f ? 42.0f : -42.0f);
        if (abs(pMessiTargetX - 512.0f) < 40.0f) targetTilt = 0.0f;
        pMessiDiveTilt += (targetTilt - pMessiDiveTilt) * 0.20f;

        // Arrival at goal line
        if (pBallZ >= 0.96f)
        {
            pBallZ = 0.96f;

            // 1. Check Woodwork (Crossbar Y=480, Posts X=252, 772)
            bool hitCrossbar = (abs(pBallY - 480.0f) < 14.0f && pBallX >= 244.0f && pBallX <= 780.0f);
            bool hitLeftPost = (abs(pBallX - 252.0f) < 14.0f && pBallY >= 210.0f && pBallY <= 486.0f);
            bool hitRightPost = (abs(pBallX - 772.0f) < 14.0f && pBallY >= 210.0f && pBallY <= 486.0f);

            if (hitCrossbar || hitLeftPost || hitRightPost)
            {
                penaltyPhase = PENALTY_POST;
                pBallVx = -pBallVx * 0.35f;
                pBallVy = (hitCrossbar ? -2.8f : pBallVy * 0.3f);
                playSfx("Audios\\door.wav"); // metallic impact clang
                spawnSparkleBurst((int)pBallX, (int)pBallY, 255, 255, 255);
                spawnSparkleBurst((int)pBallX, (int)pBallY, 251, 191, 36);
                pMessiState = 4;
                strcpy(pMessiCustomQuote, messiPostQuotes[rand() % 2]);
                return;
            }

            // 2. Check Messi Save Collision
            float messiBoxX = pMessiX;
            float messiBoxY = pMessiY + 55.0f;
            float distX = abs(pBallX - messiBoxX);
            float distY = abs(pBallY - messiBoxY);

            if (distX < 56.0f && distY < 64.0f)
            {
                // SAVED BY MESSI!
                penaltyPhase = PENALTY_SAVED;
                pBallVx = (pBallX < messiBoxX ? -3.0f : 3.0f);
                pBallVy = 2.4f;
                pBallVz = -0.015f;
                playSfx("Audios\\bounce.wav");
                spawnSparkleBurst((int)pBallX, (int)pBallY, 56, 189, 248);
                spawnSparkleBurst((int)pBallX, (int)pBallY, 255, 255, 255);
                pMessiState = 4;
                pMessiDiveTilt = 0.0f;
                strcpy(pMessiCustomQuote, messiSaveQuotes[rand() % 5]);
                penaltySavesTotal++;
                penaltyStreak = 0;
                return;
            }

            // 3. Inside the Net: GOAL! SIUUUU!
            if (pBallX > 258.0f && pBallX < 766.0f && pBallY > 218.0f && pBallY < 476.0f)
            {
                penaltyPhase = PENALTY_GOAL;
                pNetRippleTimer = 45;
                pNetBulgeX = pBallX;
                pNetBulgeY = pBallY;
                pCr7AnimState = 4; // SIUUU!
                pCr7JumpY = 0.0f;
                pMessiState = 5; // Defeated pose
                pMessiDiveTilt = (pMessiX > 512.0f ? 28.0f : -28.0f);
                pMessiY = 220.0f;
                strcpy(pMessiCustomQuote, messiDefeatedQuotes[rand() % 5]);
                playSfx("Audios\\cheer.wav");

                // Confetti & Star fountains
                for (int i = 0; i < 3; i++)
                {
                    spawnSparkleBurst(320 + i * 190, 360, 251, 191, 36);
                    spawnSparkleBurst(320 + i * 190, 360, 239, 68, 68);
                }

                penaltyGoalsTotal++;
                penaltyStreak++;

                if (penaltyForDailyReward && !dailyRewardClaimedToday)
                {
                    penaltyClaimedPopup = true;
                }
                else
                {
                    playerCoins += 25;
                    showToast("GOAL! +25 BONUS COINS!");
                    saveProgress();
                }
                return;
            }

            // Wide/High shot
            penaltyPhase = PENALTY_SAVED;
            pMessiState = 4;
            strcpy(pMessiCustomQuote, "OUT! Over the crossbar! You can't hit the target, Ronny!");
            penaltyStreak = 0;
        }
    }

    if (pNetRippleTimer > 0) pNetRippleTimer--;

    // Goal SIUUU Celebration for CR7 (Cinematic Movie Sequence)
    if (penaltyPhase == PENALTY_GOAL)
    {
        penaltyResultTimer++;

        // Smooth cinematic letterbox bars gliding in (top & bottom)
        if (pCinemaBarHeight < 52.0f)
            pCinemaBarHeight += 2.0f;

        // Stage 1 (Frames 1-45): CR7 moves back from penalty spot towards camera!
        if (penaltyResultTimer <= 45)
        {
            float t = penaltyResultTimer / 45.0f;
            pCr7X = 500.0f + (460.0f - 500.0f) * t;
            pCr7Y = 55.0f + (36.0f - 55.0f) * t;
            pCr7JumpY = abs(sin(penaltyResultTimer * 0.35f)) * 8.0f; // Jogging back steps
        }
        // Stage 2 (Frames 46-90): Cinematic Slow-Motion Leap & 180 Spin
        else if (penaltyResultTimer <= 90)
        {
            float leapProgress = (penaltyResultTimer - 45) / 45.0f;
            pCr7JumpY = sin(leapProgress * 3.14159f) * 88.0f; // High athletic leap
            pCr7X = 460.0f;
            pCr7Y = 36.0f;

            // Golden leap sparkle trail
            spawnParticle(pCr7X + 45, pCr7Y + pCr7JumpY + 20, ((rand() % 24) - 12) / 10.0, -1.0,
                          251, 191, 36, 4.5, 25, 1);
        }
        // Stage 3 (Frames 91+): Earth-Shattering SIUUU Landing!
        else
        {
            pCr7JumpY = 0.0f;
            if (penaltyResultTimer == 91)
            {
                triggerScreenShake(16, 5.0);
                playSfx("Audios\\siuuu.wav");
                for (int i = 0; i < 4; i++)
                {
                    spawnSparkleBurst((int)pCr7X + 45, (int)pCr7Y + 12, 251, 191, 36);
                    spawnSparkleBurst((int)pCr7X + 45, (int)pCr7Y + 12, 239, 68, 68);
                }
            }

            if (penaltyResultTimer % 6 == 0)
            {
                spawnParticle(pCr7X + 45 + (rand() % 40 - 20), pCr7Y + 12,
                              ((rand() % 30) - 15) / 10.0, (rand() % 28) / 10.0 + 0.5,
                              251, 191, 36, 4.0, 26, 1);
            }
        }
    }
    else
    {
        if (pCinemaBarHeight > 0.0f)
            pCinemaBarHeight -= 3.0f;
    }

    // Ball roll after deflection
    if (penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
    {
        if (pBallY > 90.0f)
        {
            pBallX += pBallVx;
            pBallY += pBallVy;
            pBallVy -= 0.15f;
            pBallRot += pBallVx * 3.0f;
        }
    }
}

/* -------------------- MOUSE & KEYBOARD HANDLERS FOR PENALTY GAME -------------------- */
void updatePenaltyMouseMove(int mx, int my)
{
    hoveredPenaltyBackBtn = (abs(mx - 60) < 28 && abs(my - 585) < 28);
    hoveredPenaltyClaimBtn = false;
    hoveredPenaltyRetryBtn = false;

    if (penaltyPhase == PENALTY_AIMING || penaltyPhase == PENALTY_CHARGING)
    {
        pAimX = (float)mx;
        pAimY = (float)my;
        if (pAimX < 268.0f) pAimX = 268.0f;
        if (pAimX > 756.0f) pAimX = 756.0f;
        if (pAimY < 232.0f) pAimY = 232.0f;
        if (pAimY > 492.0f) pAimY = 492.0f;
    }

    if (penaltyClaimedPopup)
    {
        int btnW = 320, btnH = 46;
        int btnX = (SCREEN_WIDTH - btnW) / 2;
        int btnY = 160;
        if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH)
            hoveredPenaltyClaimBtn = true;
    }
    else if (penaltyPhase == PENALTY_GOAL)
    {
        int btnW = 260, btnH = 42;
        int btnX = SCREEN_WIDTH - btnW - 35;
        int btnY = 32;
        if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH)
            hoveredPenaltyRetryBtn = true;
    }
    else if (penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
    {
        int btnW = 240, btnH = 42;
        int btnX = (SCREEN_WIDTH - btnW) / 2;
        int btnY = 58;
        if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH)
            hoveredPenaltyRetryBtn = true;
    }
}

void handlePenaltyMouseUp()
{
    if (penaltyPhase == PENALTY_CHARGING)
    {
        triggerPenaltyKick();
    }
}

void handlePenaltyMouseDown(int mx, int my)
{
    // Back button '<'
    if (abs(mx - 60) < 28 && abs(my - 585) < 28)
    {
        gameState = STATE_EVENTS;
        return;
    }

    // Daily Claim Modal button
    if (penaltyClaimedPopup)
    {
        int btnW = 320, btnH = 46;
        int btnX = (SCREEN_WIDTH - btnW) / 2;
        int btnY = 160;
        if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH)
        {
            dailyRewardClaimedToday = true;
            if (dailyLoginDay == 1) { playerGems += 50; showToast("Claimed Day 1: +50 Gems!"); }
            else if (dailyLoginDay == 2) { playerCoins += 100; showToast("Claimed Day 2: +100 Coins!"); }
            else if (dailyLoginDay == 3) { showToast("Claimed Day 3: Magic Key Acquired!"); }
            else if (dailyLoginDay == 4) { showToast("Claimed Day 4: Free Hint Pass!"); }
            else if (dailyLoginDay == 5) { showToast("Claimed Day 5: Royal Shield Acquired!"); }
            else if (dailyLoginDay == 6) { playerGems += 250; showToast("Claimed Day 6: +250 Gems!"); }
            else if (dailyLoginDay == 7) { showToast("Claimed Day 7: Saha Reno Unlocked!"); characters[HERO_SAHA_RENO].unlocked = true; selectedHero = HERO_SAHA_RENO; }

            dailyLoginDay++;
            if (dailyLoginDay > 7) dailyLoginDay = 1;
            saveProgress();
            playSfx("Audios\\key.wav");
            gameState = STATE_EVENTS;
            return;
        }
        return;
    }

    // Retry / Shoot Again button
    if (penaltyPhase == PENALTY_GOAL)
    {
        int btnW = 260, btnH = 42;
        int btnX = SCREEN_WIDTH - btnW - 35;
        int btnY = 32;
        if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH)
        {
            resetPenaltyBall();
            return;
        }
    }
    else if (penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
    {
        int btnW = 240, btnH = 42;
        int btnX = (SCREEN_WIDTH - btnW) / 2;
        int btnY = 58;
        if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH)
        {
            resetPenaltyBall();
            return;
        }
    }

    // Start charging power
    if (penaltyPhase == PENALTY_AIMING)
    {
        penaltyPhase = PENALTY_CHARGING;
        pPower = 0.0f;
        pPowerDir = 1;
        pIsCharging = true;
    }
}

void handlePenaltySpaceAction()
{
    if (penaltyClaimedPopup)
    {
        dailyRewardClaimedToday = true;
        if (dailyLoginDay == 1) { playerGems += 50; showToast("Claimed Day 1: +50 Gems!"); }
        else if (dailyLoginDay == 2) { playerCoins += 100; showToast("Claimed Day 2: +100 Coins!"); }
        else if (dailyLoginDay == 3) { showToast("Claimed Day 3: Magic Key Acquired!"); }
        else if (dailyLoginDay == 4) { showToast("Claimed Day 4: Free Hint Pass!"); }
        else if (dailyLoginDay == 5) { showToast("Claimed Day 5: Royal Shield Acquired!"); }
        else if (dailyLoginDay == 6) { playerGems += 250; showToast("Claimed Day 6: +250 Gems!"); }
        else if (dailyLoginDay == 7) { showToast("Claimed Day 7: Saha Reno Unlocked!"); characters[HERO_SAHA_RENO].unlocked = true; selectedHero = HERO_SAHA_RENO; }

        dailyLoginDay++;
        if (dailyLoginDay > 7) dailyLoginDay = 1;
        saveProgress();
        playSfx("Audios\\key.wav");
        gameState = STATE_EVENTS;
        return;
    }

    if (penaltyPhase == PENALTY_GOAL || penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
    {
        resetPenaltyBall();
        return;
    }

    if (penaltyPhase == PENALTY_AIMING)
    {
        penaltyPhase = PENALTY_CHARGING;
        pPower = 0.0f;
        pPowerDir = 1;
        pIsCharging = true;
    }
    else if (penaltyPhase == PENALTY_CHARGING)
    {
        triggerPenaltyKick();
    }
}

void handlePenaltySpecialKey(unsigned char key)
{
    if (penaltyPhase == PENALTY_AIMING || penaltyPhase == PENALTY_CHARGING)
    {
        if (key == GLUT_KEY_LEFT) pAimX -= 15.0f;
        if (key == GLUT_KEY_RIGHT) pAimX += 15.0f;
        if (key == GLUT_KEY_UP) pAimY += 15.0f;
        if (key == GLUT_KEY_DOWN) pAimY -= 15.0f;

        if (pAimX < 268.0f) pAimX = 268.0f;
        if (pAimX > 756.0f) pAimX = 756.0f;
        if (pAimY < 232.0f) pAimY = 232.0f;
        if (pAimY > 492.0f) pAimY = 492.0f;
    }
}

/* -------------------- DRAW PENALTY DERBY SCREEN -------------------- */
void drawPenaltyGame()
{
    // 1. Castle Stadium Background & Atmospheric Vignette
    if (menuBgTex != -1)
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgTex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.04f, 0.06f, 0.12f, 0.70f);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glDisable(GL_BLEND);

    // Castle Stone Arch & Wall Behind Goal
    drawFilledSmoothRect(110, 200, 804, 390, 16, 0.09f, 0.11f, 0.17f, 0.88f);
    drawSmoothRectOutline(110, 200, 804, 390, 16, 0.28f, 0.35f, 0.46f, 0.75f, 2.0f);

    // Flickering Castle Torch Sconces Flanking the Arena
    {
        // Left Torch
        drawFilledSmoothRect(132, 410, 18, 50, 4, 0.22f, 0.18f, 0.12f, 0.95f);
        drawFilledSmoothRect(126, 452, 30, 14, 4, 0.35f, 0.28f, 0.18f, 1.0f);
        float flm1 = (float)(sin(globalAnimTimer * 0.25) * 2.0 + 9.0);
        glColor4f(0.98f, 0.58f, 0.15f, 0.95f);
        iFilledCircle(141, 472, (int)flm1);
        glColor4f(1.0f, 0.88f, 0.35f, 0.95f);
        iFilledCircle(141, 474, (int)(flm1 * 0.6f));

        // Right Torch
        drawFilledSmoothRect(874, 410, 18, 50, 4, 0.22f, 0.18f, 0.12f, 0.95f);
        drawFilledSmoothRect(868, 452, 30, 14, 4, 0.35f, 0.28f, 0.18f, 1.0f);
        float flm2 = (float)(cos(globalAnimTimer * 0.28) * 2.0 + 9.0);
        glColor4f(0.98f, 0.58f, 0.15f, 0.95f);
        iFilledCircle(883, 472, (int)flm2);
        glColor4f(1.0f, 0.88f, 0.35f, 0.95f);
        iFilledCircle(883, 474, (int)(flm2 * 0.6f));
    }

    // Overhead Tournament Team Banners
    {
        // Left Banner: CR7 EL BICHO
        drawFilledSmoothRect(155, 522, 192, 38, 8, 0.65f, 0.12f, 0.14f, 0.92f);
        drawSmoothRectOutline(155, 522, 192, 38, 8, 0.98f, 0.82f, 0.25f, 1.0f, 1.5f);
        drawSharpText(165, 534, "★ CR7 - EL BICHO #7 ★", GLUT_BITMAP_HELVETICA_10, 254, 240, 138);

        // Right Banner: MESSI CASTLE CAPTAIN
        drawFilledSmoothRect(677, 522, 192, 38, 8, 0.10f, 0.22f, 0.52f, 0.92f);
        drawSmoothRectOutline(677, 522, 192, 38, 8, 0.98f, 0.82f, 0.25f, 1.0f, 1.5f);
        drawSharpText(685, 534, "★ MESSI - CAPTAIN #10 ★", GLUT_BITMAP_HELVETICA_10, 254, 240, 138);
    }

    // 2. Emerald Grass Pitch with Perspective Striping
    {
        float turfY1 = 0, turfY2 = 220;
        float bands[4][2] = { {0, 55}, {55, 110}, {110, 165}, {165, 220} };
        for (int b = 0; b < 4; b++)
        {
            float yb = bands[b][0];
            float yt = bands[b][1];
            float xl1 = (yb / turfY2) * 160.0f;
            float xr1 = SCREEN_WIDTH - (yb / turfY2) * 160.0f;
            float xl2 = (yt / turfY2) * 160.0f;
            float xr2 = SCREEN_WIDTH - (yt / turfY2) * 160.0f;

            if (b % 2 == 0)
                glColor4f(0.11f, 0.44f, 0.20f, 1.0f);
            else
                glColor4f(0.14f, 0.52f, 0.24f, 1.0f);

            glBegin(GL_QUADS);
            glVertex2f(xl1, yb);
            glVertex2f(xr1, yb);
            glVertex2f(xr2, yt);
            glVertex2f(xl2, yt);
            glEnd();
        }

        // White Pitch Lines
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 1.0f, 0.75f);
        glLineWidth(2.5f);

        // Goal line
        glBegin(GL_LINES);
        glVertex2f(160.0f, 220.0f);
        glVertex2f(864.0f, 220.0f);
        glEnd();

        // Penalty Box & 6-Yard Box perspective
        glLineWidth(1.8f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(210.0f, 0.0f);
        glVertex2f(290.0f, 160.0f);
        glVertex2f(734.0f, 160.0f);
        glVertex2f(814.0f, 0.0f);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex2f(340.0f, 220.0f);
        glVertex2f(355.0f, 185.0f);
        glVertex2f(669.0f, 185.0f);
        glVertex2f(684.0f, 220.0f);
        glEnd();

        // Penalty Spot at (512, 90)
        glColor4f(1.0f, 1.0f, 1.0f, 0.95f);
        iFilledCircle(512, 90, 6);
        float pHalo = (float)(sin(globalAnimTimer * 0.12) * 3.0 + 12.0);
        glColor4f(0.98f, 0.82f, 0.25f, 0.40f);
        iCircle(512, 90, (int)pHalo);
        glDisable(GL_BLEND);
    }

    // 3. 3D Medieval Iron Goalposts & Woven Net
    {
        float gx1 = 252.0f, gy1 = 220.0f;
        float gx2 = 772.0f, gy2 = 480.0f;
        float bx1 = 287.0f, by1 = 250.0f;
        float bx2 = 737.0f, by2 = 506.0f;

        // Dynamic Net Ripple Displacement
        float bulgeFactor = 0.0f;
        if (pNetRippleTimer > 0)
        {
            bulgeFactor = sin(pNetRippleTimer * 0.45f) * (pNetRippleTimer * 0.35f);
        }

        // Net Mesh (Translucent Diamond Grid)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.85f, 0.92f, 1.0f, 0.28f);
        glLineWidth(1.2f);

        // Vertical Net Strands
        int vLines = 22;
        for (int i = 0; i <= vLines; i++)
        {
            float t = (float)i / vLines;
            float fx = gx1 + t * (gx2 - gx1);
            float bx = bx1 + t * (bx2 - bx1);

            // Bulge perturbation
            float d = abs(fx - pNetBulgeX);
            float offset = (d < 100.0f ? bulgeFactor * ((100.0f - d) / 100.0f) : 0.0f);

            glBegin(GL_LINE_STRIP);
            glVertex2f(fx, gy1);
            glVertex2f(bx + offset * 0.3f, by1);
            glVertex2f(bx + offset * 0.8f, by2);
            glVertex2f(fx, gy2);
            glEnd();
        }

        // Horizontal Net Strands
        int hLines = 14;
        for (int j = 0; j <= hLines; j++)
        {
            float t = (float)j / hLines;
            float fy = gy1 + t * (gy2 - gy1);
            float by = by1 + t * (by2 - by1);

            float d = abs(fy - pNetBulgeY);
            float offset = (d < 80.0f ? bulgeFactor * ((80.0f - d) / 80.0f) : 0.0f);

            // Back net line
            glBegin(GL_LINES);
            glVertex2f(bx1, by + offset * 0.5f);
            glVertex2f(bx2, by + offset * 0.5f);
            glEnd();

            // Left net flank
            glBegin(GL_LINES);
            glVertex2f(gx1, fy);
            glVertex2f(bx1, by);
            glEnd();

            // Right net flank
            glBegin(GL_LINES);
            glVertex2f(gx2, fy);
            glVertex2f(bx2, by);
            glEnd();
        }

        // Goal Posts (Cylindrical 3D Metallic Posts)
        // Left Post
        drawFilledSmoothRect(gx1 - 6, gy1, 12, gy2 - gy1, 4, 0.45f, 0.48f, 0.54f, 1.0f);
        drawFilledSmoothRect(gx1 - 2, gy1, 4, gy2 - gy1, 2, 0.95f, 0.97f, 1.0f, 0.90f); // specular spine

        // Right Post
        drawFilledSmoothRect(gx2 - 6, gy1, 12, gy2 - gy1, 4, 0.45f, 0.48f, 0.54f, 1.0f);
        drawFilledSmoothRect(gx2 - 2, gy1, 4, gy2 - gy1, 2, 0.95f, 0.97f, 1.0f, 0.90f);

        // Crossbar
        drawFilledSmoothRect(gx1 - 6, gy2 - 6, (gx2 - gx1) + 12, 12, 4, 0.45f, 0.48f, 0.54f, 1.0f);
        drawFilledSmoothRect(gx1 - 6, gy2 - 2, (gx2 - gx1) + 12, 4, 2, 0.95f, 0.97f, 1.0f, 0.90f);

        // Corner Joint Brackets with Golden Rivets
        drawFilledSmoothRect(gx1 - 8, gy2 - 8, 16, 16, 3, 0.78f, 0.65f, 0.22f, 1.0f);
        drawFilledSmoothRect(gx2 - 8, gy2 - 8, 16, 16, 3, 0.78f, 0.65f, 0.22f, 1.0f);
        glDisable(GL_BLEND);
    }

    // 4. Castle Guard Captain Lionel Messi (Goalkeeper - Exclusive Character)
    {
        int messiW = 94, messiH = 94;
        float baseMX = pMessiX - messiW / 2.0f;
        float baseMY = pMessiY;

        float mHipLX = baseMX + messiW * 0.352f;
        float mHipLY = baseMY + messiH * 0.277f;
        float mHipRX = baseMX + messiW * 0.645f;
        float mHipRY = baseMY + messiH * 0.277f;
        float mPelvisX = baseMX + messiW * 0.500f;
        float mPelvisY = baseMY + messiH * 0.277f;

        float mTorsoTilt = 0.0f;
        float mTorsoScaleX = 1.0f;
        float mTorsoScaleY = 1.0f;
        float mLegLAngle = 0.0f;
        float mLegRAngle = 0.0f;
        float mBobY = 0.0f;

        if (penaltyPhase == PENALTY_AIMING)
        {
            // Active foot-shuffle & knee spring on the goal line
            float shufflePhase = globalAnimTimer * 0.28f;
            mLegLAngle = (float)sin(shufflePhase) * 18.0f;
            mLegRAngle = (float)sin(shufflePhase + 2.4f) * 18.0f;
            mBobY = (float)fabs(sin(shufflePhase * 2.0f)) * 4.0f;

            // Lateral lean in direction of movement
            float waveVel = (float)cos(globalAnimTimer * 0.048f) * 5.5f;
            mTorsoTilt = waveVel;
            mTorsoScaleY = 1.0f + (float)sin(shufflePhase * 2.0f) * 0.03f;
            mTorsoScaleX = 1.0f - (float)sin(shufflePhase * 2.0f) * 0.02f;
        }
        else if (penaltyPhase == PENALTY_CHARGING)
        {
            // Low goalkeeper ready crouch with nervous jitter steps
            float tapPhase = globalAnimTimer * 0.75f;
            mLegLAngle = 11.0f + (float)sin(tapPhase) * 5.0f;
            mLegRAngle = -11.0f - (float)cos(tapPhase) * 5.0f;
            mTorsoScaleY = 0.86f;
            mTorsoScaleX = 1.12f;
            mBobY = -5.0f;
            mTorsoTilt = (float)sin(globalAnimTimer * 0.3f) * 3.0f;
        }
        else if (penaltyPhase == PENALTY_RUNUP)
        {
            // Tense anticipation stance
            mLegLAngle = 9.0f;
            mLegRAngle = -9.0f;
            mTorsoScaleY = 0.88f;
            mTorsoScaleX = 1.10f;
            mBobY = -4.0f;
        }
        else if (penaltyPhase == PENALTY_IN_FLIGHT)
        {
            // Full diving extension!
            bool diveRight = (pMessiTargetX > 512.0f);
            if (diveRight)
            {
                mLegLAngle = -30.0f; // Trailing leg extended back
                mLegRAngle = 12.0f;  // Leading leg tucked
            }
            else
            {
                mLegRAngle = -30.0f;
                mLegLAngle = 12.0f;
            }
            mTorsoScaleX = 1.18f; // Elongated reach
            mTorsoScaleY = 0.88f;
            mTorsoTilt = 0.0f;
        }
        else if (penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
        {
            // Save celebration! Jumping for joy with knee tucks!
            float hopPhase = penaltyResultTimer * 0.28f;
            float hopY = (float)fabs(sin(hopPhase)) * 16.0f;
            mBobY = hopY;
            if (hopY > 4.0f)
            {
                mLegLAngle = 20.0f;
                mLegRAngle = -20.0f;
                mTorsoScaleY = 1.06f;
                mTorsoScaleX = 0.94f;
            }
            else
            {
                mLegLAngle = 8.0f;
                mLegRAngle = -8.0f;
                mTorsoScaleY = 0.88f;
                mTorsoScaleX = 1.10f;
            }
            mTorsoTilt = (float)sin(hopPhase * 0.5f) * 4.0f;
        }
        else if (penaltyPhase == PENALTY_GOAL)
        {
            // Conceded goal despair: collapsed on knees on the turf
            mBobY = -10.0f;
            mTorsoScaleY = 0.82f;
            mTorsoScaleX = 1.12f;
            mLegLAngle = 28.0f; // Folded knees
            mLegRAngle = -28.0f;
            mTorsoTilt = (pMessiX > 512.0f ? 22.0f : -22.0f) + (float)sin(penaltyResultTimer * 0.12f) * 4.0f;
        }

        // Shadow beneath Messi (scales with jump/bob height)
        drawGroundShadow((int)pMessiX, 220, (int)(baseMY + mBobY), 74);

        // Render Messi with articulated limbs
        if (penaltyMessiTorsoTex != -1 && penaltyMessiLegLTex != -1 && penaltyMessiLegRTex != -1)
        {
            glPushMatrix();
            // Master Dive rotation around center of mass
            glTranslatef(pMessiX, baseMY + mBobY + 46.0f, 0.0f);
            glRotatef(pMessiDiveTilt, 0.0f, 0.0f, 1.0f);
            glTranslatef(-pMessiX, -(baseMY + mBobY + 46.0f), 0.0f);

            // 1. Left Leg
            glPushMatrix();
            glTranslatef(mHipLX, mHipLY + mBobY, 0.0f);
            glRotatef(mLegLAngle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-mHipLX, -(mHipLY + mBobY), 0.0f);
            iShowImageAlpha((int)baseMX, (int)(baseMY + mBobY), messiW, messiH, penaltyMessiLegLTex, 1.0f);
            glPopMatrix();

            // 2. Right Leg
            glPushMatrix();
            glTranslatef(mHipRX, mHipRY + mBobY, 0.0f);
            glRotatef(mLegRAngle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-mHipRX, -(mHipRY + mBobY), 0.0f);
            iShowImageAlpha((int)baseMX, (int)(baseMY + mBobY), messiW, messiH, penaltyMessiLegRTex, 1.0f);
            glPopMatrix();

            // 3. Torso & Arms
            glPushMatrix();
            glTranslatef(mPelvisX, mPelvisY + mBobY, 0.0f);
            glRotatef(mTorsoTilt, 0.0f, 0.0f, 1.0f);
            glScalef(mTorsoScaleX, mTorsoScaleY, 1.0f);
            glTranslatef(-mPelvisX, -(mPelvisY + mBobY), 0.0f);
            iShowImageAlpha((int)baseMX, (int)(baseMY + mBobY), messiW, messiH, penaltyMessiTorsoTex, 1.0f);
            glPopMatrix();

            glPopMatrix(); // End master dive
        }
        else
        {
            // Fallback to static texture
            glPushMatrix();
            glTranslatef(pMessiX, pMessiY + 46 + mBobY, 0);
            glRotatef(pMessiDiveTilt + mTorsoTilt, 0, 0, 1);
            glScalef(mTorsoScaleX, mTorsoScaleY, 1.0f);
            if (penaltyMessiTex != -1)
                iShowImageAlpha(-messiW / 2, -messiH / 2, messiW, messiH, penaltyMessiTex, 1.0f);
            else if (guardTex != -1)
                iShowImageAlpha(-48, -48, 96, 96, guardTex, 1.0f);
            glPopMatrix();
        }

        // Dynamic Hand & Gauntlet Energy Auras
        float pulseM = (float)(sin(globalAnimTimer * 0.18) * 0.25 + 0.75);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        if (penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
            glColor4f(0.98f, 0.82f, 0.25f, 0.65f * pulseM); // Golden victory glow
        else
            glColor4f(0.22f, 0.74f, 1.0f, 0.45f * pulseM); // Sapphire guard glow

        glPushMatrix();
        glTranslatef(pMessiX, baseMY + mBobY + 46.0f, 0.0f);
        glRotatef(pMessiDiveTilt + mTorsoTilt, 0, 0, 1);
        iFilledCircle(-32, 10, 12);
        iFilledCircle(32, 10, 12);
        glPopMatrix();
        glDisable(GL_BLEND);

        // ---------------- MESSI ANIMATED MEDIEVAL SPEECH BUBBLE ----------------
        int bubW = 390;
        int bubH = 50;
        int bubX = (int)pMessiX - bubW / 2;
        if (bubX < 30) bubX = 30;
        if (bubX + bubW > SCREEN_WIDTH - 30) bubX = SCREEN_WIDTH - 30 - bubW;
        int bubY = (int)pMessiY + 116;

        drawFilledSmoothRect((float)bubX, (float)bubY, (float)bubW, (float)bubH, 10, 0.08f, 0.12f, 0.20f, 0.94f);
        drawSmoothRectOutline((float)bubX, (float)bubY, (float)bubW, (float)bubH, 10, 0.98f, 0.82f, 0.25f, 1.0f, 1.8f);

        // Speech Bubble Pointer Triangle
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.08f, 0.12f, 0.20f, 0.94f);
        glBegin(GL_TRIANGLES);
        glVertex2f(pMessiX - 10, (float)bubY);
        glVertex2f(pMessiX + 10, (float)bubY);
        glVertex2f(pMessiX, (float)(bubY - 12));
        glEnd();
        glDisable(GL_BLEND);

        drawSharpText(bubX + 14, bubY + 31, "⚔️ CASTLE GUARD MESSI #10:", GLUT_BITMAP_HELVETICA_10, 251, 191, 36);
        drawSharpText(bubX + 14, bubY + 13, pMessiCustomQuote, GLUT_BITMAP_HELVETICA_12, 240, 246, 255);
    }

    // 5. 3D Soccer Ball
    {
        float ballRadius = 24.0f * (1.0f - pBallZ * 0.52f);
        drawSoccerBall(pBallX, pBallY, ballRadius, pBallRot);
    }

    // 6. Cristiano Ronaldo CR7 (Striker - Exclusive Back View & Movie SIUUU)
    {
        int cr7W = 96, cr7H = 125; // TALLER than Messi (125px vs 94px, matching 685x890 sprite)

        // Calculate dynamic leg & body parameters
        float cr7TorsoTilt = 0.0f;
        float cr7TorsoScaleX = 1.0f;
        float cr7TorsoScaleY = 1.0f;
        float cr7LegLAngle = 0.0f;
        float cr7LegRAngle = 0.0f;
        float cr7AnimJumpY = pCr7JumpY;

        if (penaltyPhase == PENALTY_AIMING)
        {
            // Idle stance: deep athletic breathing & rhythmic weight shift
            float breath = (float)sin(globalAnimTimer * 0.08f);
            cr7TorsoScaleY = 1.0f + breath * 0.032f;
            cr7TorsoScaleX = 1.0f - breath * 0.016f;
            cr7LegLAngle = breath * 2.8f;
            cr7LegRAngle = -breath * 2.8f;
            cr7TorsoTilt = -breath * 1.5f;

            // Cleat sparks on planted boots
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(1.0f, 0.75f, 0.20f, 0.35f + (float)fabs(breath) * 0.35f);
            iFilledCircle((int)pCr7X + 28, (int)pCr7Y + 8, 8);
            iFilledCircle((int)pCr7X + 66, (int)pCr7Y + 8, 8);
            glDisable(GL_BLEND);
        }
        else if (penaltyPhase == PENALTY_CHARGING)
        {
            // Coiled striker crouch: center of gravity drops, knees bend, body squashes
            float crouch = pPower;
            cr7AnimJumpY = -crouch * 6.0f;
            cr7TorsoScaleY = 1.0f - crouch * 0.12f;
            cr7TorsoScaleX = 1.0f + crouch * 0.09f;
            cr7TorsoTilt = -crouch * 9.0f; // Tense forward lean
            cr7LegLAngle = crouch * 9.0f;  // Knees bend outward
            cr7LegRAngle = -crouch * 9.0f;

            // Tremor jitter at high power
            if (pPower > 0.60f)
            {
                float jit = ((rand() % 5) - 2) * 0.6f;
                cr7TorsoTilt += jit;
            }

            // Power flame boots
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(1.0f, 0.40f, 0.10f, 0.75f);
            iFilledCircle((int)pCr7X + 28, (int)(pCr7Y + cr7AnimJumpY) + 8, 11);
            iFilledCircle((int)pCr7X + 66, (int)(pCr7Y + cr7AnimJumpY) + 8, 11);
            glDisable(GL_BLEND);
        }
        else if (penaltyPhase == PENALTY_RUNUP)
        {
            // Dynamic multi-stride sprinting approach!
            float runProgress = (float)pCr7Timer / 16.0f;
            float strideCycle = runProgress * 3.14159f * 2.6f;

            // Alternating leg strides
            cr7LegLAngle = (float)sin(strideCycle) * 28.0f;
            cr7LegRAngle = -(float)sin(strideCycle) * 28.0f;

            // Vertical stride bounce
            cr7AnimJumpY = (float)fabs(sin(strideCycle)) * 7.0f;

            // Forward sprint lean
            cr7TorsoTilt = -14.0f + (float)sin(strideCycle * 2.0f) * 2.5f;
            cr7TorsoScaleX = 0.95f;
            cr7TorsoScaleY = 1.05f;

            // Turf dust puffs beneath active boot
            if (pCr7Timer % 3 == 0)
            {
                float bootX = (cr7LegLAngle > 0.0f ? pCr7X + 28 : pCr7X + 66);
                spawnParticle(bootX, pCr7Y + 8, ((rand() % 16) - 8) / 10.0, 0.8,
                              251, 191, 36, 3.2, 14, 1);
            }
        }
        else if (penaltyPhase == PENALTY_IN_FLIGHT)
        {
            // The Strike Follow-Through!
            // Left leg planted hard at the penalty spot
            cr7LegLAngle = -6.0f;
            // Right kicking leg extended high in follow-through
            cr7LegRAngle = 46.0f;
            // Torso snaps back in violent athletic strike recoil
            cr7TorsoTilt = 16.0f;
            cr7TorsoScaleX = 1.05f;
            cr7TorsoScaleY = 0.96f;
            cr7AnimJumpY = 0.0f;

            // Rocket kick shockwave trail from right boot
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(1.0f, 0.85f, 0.30f, 0.65f);
            iFilledCircle((int)pCr7X + 68, (int)pCr7Y + 28, 14);
            glDisable(GL_BLEND);
        }
        else if (penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
        {
            // Disappointment & frustration pose
            cr7AnimJumpY = -4.0f;
            cr7TorsoScaleY = 0.92f;
            cr7TorsoScaleX = 1.04f;
            cr7TorsoTilt = -16.0f + (float)sin(penaltyResultTimer * 0.15f) * 3.0f; // Head hang & sorrow shake
            cr7LegLAngle = 6.0f;
            cr7LegRAngle = 8.0f;
        }

        // Ground shadow beneath Ronaldo
        drawGroundShadow((int)pCr7X + cr7W / 2, 50, (int)(pCr7Y + cr7AnimJumpY), 70);

        // A. Aiming, Charging, Run-up, Ball in Flight: STRICTLY BACK SIDE VIEW WITH ARTICULATED LIMBS!
        if (penaltyPhase == PENALTY_AIMING || penaltyPhase == PENALTY_CHARGING || penaltyPhase == PENALTY_RUNUP || penaltyPhase == PENALTY_IN_FLIGHT || penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
        {
            if (penaltyCr7TorsoTex != -1 && penaltyCr7LegLTex != -1 && penaltyCr7LegRTex != -1)
            {
                float drawY = pCr7Y + cr7AnimJumpY;
                float hipLY = drawY + cr7H * 0.348f;
                float hipLX = pCr7X + cr7W * 0.292f;
                float hipRY = drawY + cr7H * 0.348f;
                float hipRX = pCr7X + cr7W * 0.701f;
                float pelvisX = pCr7X + cr7W * 0.499f;
                float pelvisY = drawY + cr7H * 0.348f;

                // 1. Left Leg
                glPushMatrix();
                glTranslatef(hipLX, hipLY, 0.0f);
                glRotatef(cr7LegLAngle, 0.0f, 0.0f, 1.0f);
                glTranslatef(-hipLX, -hipLY, 0.0f);
                iShowImageAlpha((int)pCr7X, (int)drawY, cr7W, cr7H, penaltyCr7LegLTex, 1.0f);
                glPopMatrix();

                // 2. Right Leg
                glPushMatrix();
                glTranslatef(hipRX, hipRY, 0.0f);
                glRotatef(cr7LegRAngle, 0.0f, 0.0f, 1.0f);
                glTranslatef(-hipRX, -hipRY, 0.0f);
                iShowImageAlpha((int)pCr7X, (int)drawY, cr7W, cr7H, penaltyCr7LegRTex, 1.0f);
                glPopMatrix();

                // 3. Torso (Head, Arms, Jersey #7, Shorts)
                glPushMatrix();
                glTranslatef(pelvisX, pelvisY, 0.0f);
                glRotatef(cr7TorsoTilt, 0.0f, 0.0f, 1.0f);
                glScalef(cr7TorsoScaleX, cr7TorsoScaleY, 1.0f);
                glTranslatef(-pelvisX, -pelvisY, 0.0f);
                iShowImageAlpha((int)pCr7X, (int)drawY, cr7W, cr7H, penaltyCr7TorsoTex, 1.0f);
                glPopMatrix();
            }
            else
            {
                // Fallback to static back texture with squash & tilt
                glPushMatrix();
                glTranslatef(pCr7X + cr7W / 2, pCr7Y + cr7AnimJumpY + cr7H / 2, 0);
                glRotatef(cr7TorsoTilt, 0, 0, 1);
                glScalef(cr7TorsoScaleX, cr7TorsoScaleY, 1.0f);
                if (penaltyCr7BackTex != -1)
                    iShowImageAlpha(-cr7W / 2, -cr7H / 2, cr7W, cr7H, penaltyCr7BackTex, 1.0f);
                glPopMatrix();
            }
        }
        // B. GOAL: Cinematic Multi-Stage Movie SIUUU!
        else if (penaltyPhase == PENALTY_GOAL)
        {
            // Stage 1 (Frames 1-45): Run back towards camera
            if (penaltyResultTimer <= 45)
            {
                // Jogging back towards camera with energetic body bounce and leg lift
                float jogPhase = penaltyResultTimer * 0.38f;
                float jogTilt = (float)sin(jogPhase) * 3.5f;
                glPushMatrix();
                glTranslatef(pCr7X + cr7W / 2, pCr7Y + pCr7JumpY + cr7H / 2, 0);
                glRotatef(jogTilt, 0, 0, 1);
                if (penaltyCr7SiuTex != -1)
                    iShowImageAlpha(-cr7W / 2, -cr7H / 2, cr7W, cr7H, penaltyCr7SiuTex, 1.0f);
                else if (penaltyCr7BackTex != -1)
                    iShowImageAlpha(-cr7W / 2, -cr7H / 2, cr7W, cr7H, penaltyCr7BackTex, 1.0f);
                glPopMatrix();
            }
            // Stage 2 (Frames 46-90): Slow-Motion Mid-Air Leap & 180 Spin with Spotlight!
            else if (penaltyResultTimer <= 90)
            {
                // Mid-air leap
                glPushMatrix();
                glTranslatef(pCr7X + cr7W / 2, pCr7Y + pCr7JumpY + cr7H / 2, 0);
                float spinT = (penaltyResultTimer - 45) / 45.0f;
                // Scale width to simulate 3D rotation from back to front!
                float rotScaleX = (float)cos(spinT * 3.14159f);
                glScalef(rotScaleX, 1.0f, 1.0f);

                unsigned int midAirTex = (spinT < 0.5f && penaltyCr7BackTex != -1) ? penaltyCr7BackTex : penaltyCr7SiuTex;
                if (midAirTex != -1)
                    iShowImageAlpha(-cr7W / 2, -cr7H / 2, cr7W, cr7H, midAirTex, 1.0f);

                glPopMatrix();
            }
            // Stage 3 (Frames 91+): Earth-Shattering SIUUU Landing!
            else
            {
                int siuW = 104, siuH = 126; // Full glorious SIUUU stance
                float landProgress = (penaltyResultTimer - 91) / 14.0f;
                if (landProgress > 1.0f) landProgress = 1.0f;
                float crouchScaleY = 0.80f + 0.20f * landProgress;
                float crouchScaleX = 1.18f - 0.18f * landProgress;
                float landCrouchY = -10.0f * (1.0f - landProgress);

                glPushMatrix();
                glTranslatef(pCr7X + siuW / 2 - 7, pCr7Y + landCrouchY + siuH / 2, 0);
                glScalef(crouchScaleX, crouchScaleY, 1.0f);
                if (penaltyCr7SiuTex != -1)
                    iShowImageAlpha(-siuW / 2, -siuH / 2, siuW, siuH, penaltyCr7SiuTex, 1.0f);
                else
                    iShowImageAlpha(-cr7W / 2, -cr7H / 2, cr7W, cr7H, characters[HERO_CR7].skinTexID, 1.0f);
                glPopMatrix();

                // Golden celebration aura around CR7
                float siuPulse = (float)(sin(globalAnimTimer * 0.20) * 0.25 + 0.75);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                glColor4f(0.98f, 0.82f, 0.25f, 0.35f * siuPulse);
                iFilledCircle((int)pCr7X + 45, (int)(pCr7Y + landCrouchY) + 68, 55);
                glDisable(GL_BLEND);
            }

            // Expanding SIUUU Shockwave Ripple across the grass
            if (penaltyResultTimer >= 91)
            {
                float swRad = (penaltyResultTimer - 91) * 7.5f;
                if (swRad < 280.0f)
                {
                    float swAlpha = 1.0f - (swRad / 280.0f);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glColor4f(0.98f, 0.82f, 0.25f, swAlpha * 0.90f);
                    glLineWidth(4.0f);
                    iCircle((int)pCr7X + 45, (int)pCr7Y + 12, (int)swRad);
                    glColor4f(1.0f, 0.95f, 0.75f, swAlpha * 0.50f);
                    glLineWidth(2.0f);
                    iCircle((int)pCr7X + 45, (int)pCr7Y + 12, (int)(swRad * 0.82f));
                    glDisable(GL_BLEND);
                }
            }

            // Dramatic Castle Spotlight shining from Keep roof onto CR7
            if (penaltyResultTimer > 35)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                glColor4f(1.0f, 0.92f, 0.50f, 0.18f);
                glBegin(GL_TRIANGLES);
                glVertex2f(512, 600); // Light source at roof
                glVertex2f(pCr7X - 65, pCr7Y);
                glVertex2f(pCr7X + 155, pCr7Y);
                glEnd();
                glDisable(GL_BLEND);
            }

            // Cinematic Movie Banner: S I U U U U U !
            if (penaltyResultTimer >= 40 && !penaltyClaimedPopup)
            {
                int banW = 460, banH = 46;
                int banX = (SCREEN_WIDTH - banW) / 2;
                int banY = 495;
                drawFilledSmoothRect(banX, banY, banW, banH, 10, 0.08f, 0.12f, 0.20f, 0.96f);
                drawSmoothRectOutline(banX, banY, banW, banH, 10, 0.98f, 0.82f, 0.25f, 1.0f, 2.0f);
                drawSharpText(banX + 85, banY + 14, "★ S  I  U  U  U  U  U ! ★", GLUT_BITMAP_TIMES_ROMAN_24, 251, 191, 36);
                drawSharpText(banX + 115, banY - 18, "CR7 CONQUERS CASTLE GUARD MESSI!", GLUT_BITMAP_HELVETICA_10, 254, 240, 138);
            }
        }
    }

    // 7. Aiming Crosshair & Dashed Trajectory Arc
    if (penaltyPhase == PENALTY_AIMING || penaltyPhase == PENALTY_CHARGING)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Dashed Trajectory Arc from Ball to Aim Target
        int arcSteps = 12;
        for (int i = 0; i < arcSteps; i += 2)
        {
            float t1 = (float)i / arcSteps;
            float t2 = (float)(i + 1) / arcSteps;
            float x1 = 512.0f + t1 * (pAimX - 512.0f);
            float y1 = 90.0f + t1 * (pAimY - 90.0f) + sin(t1 * 3.14159f) * 35.0f;
            float x2 = 512.0f + t2 * (pAimX - 512.0f);
            float y2 = 90.0f + t2 * (pAimY - 90.0f) + sin(t2 * 3.14159f) * 35.0f;

            glColor4f(0.98f, 0.82f, 0.25f, 0.55f);
            glLineWidth(2.0f);
            glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glEnd();
        }

        // Aiming Crosshair Reticle
        float retRad = 16.0f;
        glColor4f(0.98f, 0.82f, 0.25f, 0.90f);
        iCircle((int)pAimX, (int)pAimY, (int)retRad);
        iFilledCircle((int)pAimX, (int)pAimY, 3);

        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(pAimX - 22, pAimY); glVertex2f(pAimX - 8, pAimY);
        glVertex2f(pAimX + 8, pAimY);  glVertex2f(pAimX + 22, pAimY);
        glVertex2f(pAimX, pAimY - 22); glVertex2f(pAimX, pAimY - 8);
        glVertex2f(pAimX, pAimY + 8);  glVertex2f(pAimX, pAimY + 22);
        glEnd();
        glDisable(GL_BLEND);
    }

    // 8. Bottom Kick Power Meter
    {
        int barW = 340, barH = 22;
        int barX = (SCREEN_WIDTH - barW) / 2;
        int barY = 22;

        drawFilledSmoothRect((float)barX, (float)barY, (float)barW, (float)barH, 6, 0.08f, 0.10f, 0.16f, 0.92f);
        drawSmoothRectOutline((float)barX, (float)barY, (float)barW, (float)barH, 6, 0.40f, 0.48f, 0.60f, 0.85f, 1.2f);

        // Gradient Power Fill
        if (pPower > 0.01f)
        {
            float fillW = barW * pPower;
            float r = (pPower < 0.70f ? 0.20f : (pPower < 0.92f ? 0.98f : 0.90f));
            float g = (pPower < 0.70f ? 0.70f : (pPower < 0.92f ? 0.82f : 0.22f));
            float b = (pPower < 0.70f ? 0.95f : 0.20f);
            drawFilledSmoothRect((float)(barX + 2), (float)(barY + 2), fillW - 4, (float)(barH - 4), 4, r, g, b, 0.95f);
        }

        // Sweet-Spot Marker (70% to 92%: Golden Rocket Strike)
        int sw1 = barX + (int)(barW * 0.70f);
        int sw2 = barX + (int)(barW * 0.92f);
        drawSmoothRectOutline((float)sw1, (float)barY, (float)(sw2 - sw1), (float)barH, 2, 0.98f, 0.82f, 0.25f, 0.90f, 1.5f);
        drawSharpText(sw1 + 10, barY + 6, "SWEET SPOT", GLUT_BITMAP_HELVETICA_10, 254, 240, 138);

        // Helper instruction text
        if (penaltyPhase == PENALTY_AIMING || penaltyPhase == PENALTY_CHARGING)
        {
            drawSharpText(barX + 16, barY + 28, "HOLD LEFT CLICK OR SPACE TO CHARGE -- RELEASE TO STRIKE!", GLUT_BITMAP_HELVETICA_10, 224, 231, 255);
        }
    }

    // 9. Top Match Header & Scoreboard
    {
        // Top-Left: 3D Diamond Return Button "<"
        drawDiamond(60, 585, 28, 0.14f, 0.18f, 0.26f, 0.98f);
        drawDiamondOutline(60, 585, 28, hoveredPenaltyBackBtn ? 0.98f : 0.70f, hoveredPenaltyBackBtn ? 0.82f : 0.75f, 0.35f, 2.0f);
        drawSharpText(52, 576, "<", GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);

        // Top-Center: Royal Derby Match Board
        int scW = 440, scH = 44;
        int scX = (SCREEN_WIDTH - scW) / 2, scY = 565;
        drawFilledSmoothRect((float)scX, (float)scY, (float)scW, (float)scH, 10, 0.08f, 0.12f, 0.20f, 0.95f);
        drawSmoothRectOutline((float)scX, (float)scY, (float)scW, (float)scH, 10, 0.98f, 0.82f, 0.25f, 1.0f, 1.6f);

        char scTxt[64];
        sprintf(scTxt, "CR7 %d  -  %d  MESSI", penaltyGoalsTotal, penaltySavesTotal);
        drawSharpText(scX + 112, scY + 14, scTxt, GLUT_BITMAP_TIMES_ROMAN_24, 251, 191, 36);

        char streakTxt[32];
        sprintf(streakTxt, "STREAK: %d", penaltyStreak);
        drawSharpText(scX + 14, scY + 16, streakTxt, GLUT_BITMAP_HELVETICA_10, 56, 189, 248);

        if (penaltyForDailyReward && !dailyRewardClaimedToday)
            drawSharpText(scX + 328, scY + 16, "DAILY REWARD", GLUT_BITMAP_HELVETICA_10, 34, 197, 94);
        else
            drawSharpText(scX + 338, scY + 16, "EXHIBITION", GLUT_BITMAP_HELVETICA_10, 244, 114, 182);

        // Top-Right: Player Gem & Coin displays
        draw3DCurrencyCapsule(710, 564, 136, 42, 0, playerGems);
        draw3DCurrencyCapsule(862, 564, 136, 42, 1, playerCoins);
    }

    // 10. Post-Shot Result Modals & Action Buttons
    if (penaltyClaimedPopup)
    {
        // Blackout overlay
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.04f, 0.06f, 0.10f, 0.82f);
        iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glDisable(GL_BLEND);

        int modW = 460, modH = 320;
        int modX = (SCREEN_WIDTH - modW) / 2;
        int modY = (SCREEN_HEIGHT - modH) / 2;

        drawMetallicCard(modX, modY, modW, modH, 16, 0.10f, 0.14f, 0.22f, 0.98f, 0.98f, 0.82f, 0.25f, 4, true);

        drawSharpText(modX + 54, modY + 275, "★ ROYAL PENALTY VICTORY! ★", GLUT_BITMAP_TIMES_ROMAN_24, 251, 191, 36);
        drawSharpText(modX + 68, modY + 248, "Castle Guard Messi Conceded! Daily Vault Unlocked!", GLUT_BITMAP_HELVETICA_10, 224, 231, 255);

        // Reward Showcase
        drawFilledSmoothRect((float)(modX + 60), (float)(modY + 95), (float)(modW - 120), 130, 12, 0.14f, 0.18f, 0.28f, 0.90f);
        drawSmoothRectOutline((float)(modX + 60), (float)(modY + 95), (float)(modW - 120), 130, 12, 0.98f, 0.82f, 0.25f, 0.90f, 1.5f);

        float rPulse = (float)(sin(globalAnimTimer * 0.14) * 0.15 + 0.85);
        int itemY = modY + 165;
        if (dailyLoginDay == 1) { draw3DGem(modX + modW / 2, itemY, 18, rPulse); drawSharpText(modX + modW / 2 - 50, modY + 115, "+50 SHINY GEMS", GLUT_BITMAP_HELVETICA_12, 56, 189, 248); }
        else if (dailyLoginDay == 2) { draw3DCoin(modX + modW / 2, itemY, 16, rPulse); drawSharpText(modX + modW / 2 - 55, modY + 115, "+100 GOLD COINS", GLUT_BITMAP_HELVETICA_12, 251, 191, 36); }
        else if (dailyLoginDay == 3) { draw3DKey(modX + modW / 2, itemY, 1.1); drawSharpText(modX + modW / 2 - 45, modY + 115, "MAGIC KEEP KEY", GLUT_BITMAP_HELVETICA_12, 251, 191, 36); }
        else if (dailyLoginDay == 4) { draw3DScroll(modX + modW / 2, itemY, 16); drawSharpText(modX + modW / 2 - 40, modY + 115, "FREE HINT PASS", GLUT_BITMAP_HELVETICA_12, 254, 243, 199); }
        else if (dailyLoginDay == 5) { draw3DShield(modX + modW / 2, itemY, 18); drawSharpText(modX + modW / 2 - 50, modY + 115, "ROYAL LION SHIELD", GLUT_BITMAP_HELVETICA_12, 147, 197, 253); }
        else if (dailyLoginDay == 6) { draw3DGemCluster(modX + modW / 2, itemY, 15, rPulse); drawSharpText(modX + modW / 2 - 55, modY + 115, "+250 ROYAL GEMS", GLUT_BITMAP_HELVETICA_12, 192, 132, 252); }
        else if (dailyLoginDay == 7) { int sahaTex = characters[HERO_SAHA_RENO].skinTexID; if (sahaTex != -1) iShowImageAlpha(modX + modW / 2 - 32, itemY - 32, 64, 64, sahaTex, 1.0f); drawSharpText(modX + modW / 2 - 65, modY + 115, "SAHA RENO UNLOCKED!", GLUT_BITMAP_HELVETICA_12, 251, 191, 36); }

        // Claim Button
        draw3DButton(modX + 70, modY + 30, modW - 140, 46, "★ COLLECT REWARD & RETURN ★", hoveredPenaltyClaimBtn, 0);
    }
    else if (penaltyPhase == PENALTY_GOAL)
    {
        // Rematch victory button - placed neatly at bottom right
        int btnW = 260, btnH = 42;
        int btnX = SCREEN_WIDTH - btnW - 35;
        int btnY = 32;
        draw3DButton(btnX, btnY, btnW, btnH, "★ SHOOT AGAIN (REMATCH) ★", hoveredPenaltyRetryBtn, 0);
    }
    else if (penaltyPhase == PENALTY_SAVED || penaltyPhase == PENALTY_POST)
    {
        // Try Again Button
        int btnW = 240, btnH = 42;
        int btnX = (SCREEN_WIDTH - btnW) / 2;
        int btnY = 58;
        draw3DButton(btnX, btnY, btnW, btnH, "★ TRY AGAIN (KICK) ★", hoveredPenaltyRetryBtn, 1);
    }

    // 11. Cinematic Widescreen Letterbox Bars (Top & Bottom Cinema Framing)
    if (pCinemaBarHeight > 0.5f)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.01f, 0.02f, 0.04f, 0.98f);
        // Top Cinema Bar
        iFilledRectangle(0, SCREEN_HEIGHT - (int)pCinemaBarHeight, SCREEN_WIDTH, (int)pCinemaBarHeight);
        // Bottom Cinema Bar
        iFilledRectangle(0, 0, SCREEN_WIDTH, (int)pCinemaBarHeight);
        glDisable(GL_BLEND);
    }
}

