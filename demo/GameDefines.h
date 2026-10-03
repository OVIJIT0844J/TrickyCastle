#pragma once
#define _CRT_SECURE_NO_WARNINGS
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: GameDefines.h
 * LEAD GAME THEORIST: Ovijit Sharma (Student ID: 00725105101134)
 * SYSTEMS CO-DEVELOPER: Maheed Abrar (Student ID: 00725105101140)
 * ROLE & RESPONSIBILITY: Game Theory Concept, Gameplay Rules, Hero Archetypes & State Architecture
 *
 * GAME THEORY & DESIGN BY OVIJIT SHARMA:
 *   - Overall game theory: tricky puzzle-platformer dungeon escape concept
 *   - Central GameState finite state machine design & level flow theory
 *   - CharacterType & 6 Chibi Hero archetypes design (William, CR7, Neymar, Elena, Thorgar, RenoSir)
 *   - Unique hero perks & balance theory (shield defense, speed boosts, bypass abilities)
 *   - Interactive dungeon mechanics theory (BgObjectType, puzzles, gravity inversion)
 *
 * ENGINE IMPLEMENTATION BY MAHEED ABRAR:
 *   - Resolution constants (1024x640), physics parameters, and particle pool buffers
 *   - Automated diagnostic test harness & OpenGL screenshot export (saveGlScreenshot)
 * DEPENDENCIES: iGraphics.h, <mmsystem.h>, winmm.lib
 * =========================================================================== */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "iGraphics.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
 

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 640

#define PLAYER_WIDTH 54
#define PLAYER_HEIGHT 72
#define GROUND_HEIGHT 80
#define LEVEL_COUNT 24
#define MAX_PARTICLES 280
#define MAX_FLOATING_TEXTS 16
#define MAX_BG_OBJECTS 20

enum GameState
{
    STATE_INTRO,
    STATE_MENU,              // World Select Carousel (Matching Image 1)
    STATE_EVENTS,            // Events & Daily Login Reward Screen (NEW!)
    STATE_PENALTY_GAME,      // Mini Football Penalty Game: CR7 vs Messi! (NEW!)
    STATE_CHARACTER_SELECT,  // Costumes Menu (Matching Card 1 in Image 1)
    STATE_LEVEL_SELECT,      // Chapter 1 Map (Floors 1-12)
    STATE_CHAPTER2_SELECT,   // Chapter 2 Map (Floors 13-16)
    STATE_CHAPTER3_SELECT,   // Chapter 3 Map (Floors 17-20: Witch Tower)
    STATE_CHAPTER4_SELECT,   // Chapter 4 Map (Floors 21-24: Dragon's Keep)
    STATE_PLAYING,           // In-game with On-screen Controls (Matching Image 2)
    STATE_PAUSED,            // Pause Dialog
    STATE_SETTINGS,          // Settings Menu (Matching Image 4)
    STATE_LEVEL_CLEAR,       // Win Screen with Stars
    STATE_GAME_OVER          // Tricky Castle Angel Ghost Death Screen
};

GameState gameState = STATE_INTRO;

/* -------------------- 6 CHIBI HEROES (INCLUDING SAHA RENO) -------------------- */
enum CharacterType
{
    HERO_WILLIAM = 0,
    HERO_CR7 = 1,
    HERO_NEYMAR = 2,
    HERO_ELENA = 3,
    HERO_THORGAR = 4,
    HERO_SAHA_RENO = 5,
    HERO_COUNT = 6
};

struct CharacterInfo
{
    const char* name;
    const char* title;
    const char* perkName;
    const char* perkDesc;
    double baseSpeed;
    double jumpSpeed;
    int skinTexID;
    int bootColorR, bootColorG, bootColorB;
    int trimColorR, trimColorG, trimColorB;
    bool unlocked;
};

CharacterInfo characters[HERO_COUNT] =
{
    { "Castle Master", "Royal Castle Guardian", "Shield Guard", "Sturdy knight with impenetrable lion shield.", 3.4, 11.2, -1, 30, 41, 59, 245, 158, 11, true },
    { "Red Devil CR7", "Cristiano Ronaldo #7", "Siuuu Sprint & Flame Blade", "Unstoppable speed, blazing leap, Red Devil plate armor.", 3.9, 11.8, -1, 159, 18, 57, 251, 191, 36, true },
    { "Neymar Jr", "Brazilian King #10", "Samba Dribble & Feather Jump", "Nimble footwork, extra fluid dodging, golden #10 armor.", 3.7, 11.6, -1, 234, 179, 8, 22, 163, 74, true },
    { "Elena", "Chibi Ranger", "Frost Step & +25% Speed", "High agility, swift sprint, frost trail.", 3.8, 11.6, -1, 120, 53, 15, 245, 158, 11, true },
    { "Thorgar", "Chibi Dwarf Guardian", "Titan Brawn", "Mighty dwarf. Shoves crates and heavy doors with 3x strength.", 3.1, 10.8, -1, 64, 64, 64, 217, 119, 6, true },
    { "RenoSir", "LLM Researcher & Tactician", "Algorithmic Tactics & Trap Bypass", "AI strategist easily escapes tricky dungeon traps with logic and foresight.", 4.0, 12.0, -1, 14, 165, 233, 251, 191, 36, false }
};

int selectedHero = HERO_WILLIAM;
int hoveredHeroCardIndex = -1;

/* -------------------- CR7 SKINS & RENOSIR COLLAB / TRIAL SYSTEM -------------------- */
int cr7DevilTex = -1;
int cr7MadridTex = -1;
int cr7JuventusTex = -1;
int cr7SkinSelected = 0; // 0 = Red Devil, 1 = Real Madrid, 2 = Juventus
bool cr7MadridUnlocked = false;
bool cr7JuventusUnlocked = false;

/* -------------------- CUSTOM PENALTY GAME CHARACTERS (MESSI & CR7 EXCLUSIVE) -------------------- */
int penaltyMessiTex = -1;
int penaltyCr7BackTex = -1;
int penaltyCr7SiuTex = -1;

// Segmented Articulated Limbs for Dynamic Leg & Body Animations
int penaltyCr7TorsoTex = -1;
int penaltyCr7LegLTex = -1;
int penaltyCr7LegRTex = -1;
int penaltyMessiTorsoTex = -1;
int penaltyMessiLegLTex = -1;
int penaltyMessiLegRTex = -1;

// Event Challenges
bool questMadridClaimed = false;
bool questJuventusClaimed = false;
bool questRenoClaimed = false;

// RenoSir Collaboration Modal & 1-Level Trial State
bool showRenoSirCollabModal = false;
bool renoSirOneLevelTrial = false;
int renoSirTrialStartLevel = -1;
int renoSirCollabBannerTex = -1;
int gearSketchTex = -1;

// RenoSir 10-Minute Trial (Fallback timer)
bool sahaRenoTrialActive = false;
int sahaRenoTrialFrames = 0;

void updateCR7Skin()
{
    if (cr7SkinSelected == 1 && cr7MadridTex != -1)
    {
        characters[HERO_CR7].skinTexID = cr7MadridTex;
        characters[HERO_CR7].name = "Real Madrid CR7";
        characters[HERO_CR7].title = "Los Blancos Royal Knight #7";
        characters[HERO_CR7].perkName = "Royal Decima & Golden Blade";
    }
    else if (cr7SkinSelected == 2 && cr7JuventusTex != -1)
    {
        characters[HERO_CR7].skinTexID = cr7JuventusTex;
        characters[HERO_CR7].name = "Juventus CR7";
        characters[HERO_CR7].title = "Bianconeri Italian Knight #7";
        characters[HERO_CR7].perkName = "Zebra Thunder & Rampant Bull";
    }
    else
    {
        if (cr7DevilTex != -1)
            characters[HERO_CR7].skinTexID = cr7DevilTex;
        characters[HERO_CR7].name = "Red Devil CR7";
        characters[HERO_CR7].title = "Cristiano Ronaldo #7";
        characters[HERO_CR7].perkName = "Siuuu Sprint & Flame Blade";
    }
}

/* -------------------- TEXTURES -------------------- */
int guardTex = -1;
int levelBgTextures[LEVEL_COUNT];
int introBgTex = -1;
int menuBgTex = -1;
int eventBannerTex = -1;
int eventCollabThumbTex = -1;
int introCr7Tex = -1;
int chapter2BgTex = -1;
int chapter3BgTex = -1;
int chapter4BgTex = -1;

/* -------------------- DAILY LOGIN REWARDS & EVENTS STATE -------------------- */
int dailyLoginDay = 1;
bool dailyRewardClaimedToday = false;
int playerGems = 250;
int playerCoins = 850;
int toastTimer = 0;
char toastMessage[64] = "";
void showToast(const char* msg);

struct LevelInfo
{
    const char* chapterTitle;
    const char* title;
    const char* clue;
    const char* gentleHint;
    const char* instantSolution;
    const char* deathQuote;
    const char* bgFile;
    int spawnX;
    int spawnY;
    int doorX;
    int doorY;
    bool doorRequiresKey;
    bool doorPushable;
};

int currentLevel = 0;
int unlockedLevels = 1;
int levelStars[LEVEL_COUNT] = { 0 };
int levelScores[LEVEL_COUNT] = { 0 };
int totalStars = 0;
bool soundEnabled = true;

/* -------------------- PLAYER PHYSICS & STATE -------------------- */
double playerX = 80;
double playerY = GROUND_HEIGHT;
double velocityX = 0;
double velocityY = 0;
bool onGround = true;
int facing = 1; // 1 = right, -1 = left
int walkCycle = 0;
int footstepTimer = 0;
int squashTimer = 0;
int coyoteTimer = 0;
int jumpBuffer = 0;
bool isClimbing = false;
bool isPushing = false;
int pushTimer = 0;
bool hasKey = false;
bool doorOpen = false;
int doorPushedDistance = 0;
bool holdingTorch = false;
bool invertedGravity = false;
int meditateTimer = 0;
int meditateState = 0;
int levelTimer = 0;
int levelScore = 1000;
bool usedInstantPassThisLevel = false;

/* -------------------- CONTINUOUS TOUCH CONTROLS STATE -------------------- */
bool isTouchingLeft = false;
bool isTouchingRight = false;
bool isTouchingJump = false;
bool isMouseLeftDown = false;
int globalAnimTimer = 0;

/* -------------------- UI & MODAL STATE -------------------- */
bool showHintAdModal = false;
int hintTierRevealed = 0; // 0 = none/menu, 1 = gentle hint, 2 = full solution
bool showChapter3ComingSoon = false;
bool showChapter5ComingSoon = false;
int hoveredCarouselCard = -1;
int hoveredLevelDoor = -1;
int hoveredDailyCard = -1;
bool hoveredEventsClaimBtn = false;
int activeInteractionIndex = -1;
int screenShakeTimer = 0;
double screenShakeIntensity = 0;

/* -------------------- INTRO & CINEMATIC STATE -------------------- */
int introTimer = 0;
double introHeroX = -180;
double introHeroY = GROUND_HEIGHT;
double introTitleY = 720;
bool introHeroStopped = false;
double angelGhostX = 0;
double angelGhostY = 0;
int angelGhostTimer = 0;

/* -------------------- INTERACTIVE OBJECTS -------------------- */
enum BgObjectType
{
    BG_TORCH_SCONCE,
    BG_PULL_CHAIN,
    BG_WALL_LEVER,
    BG_CLIMB_IVY,
    BG_PUSH_CRATE,
    BG_CHEST_INTERACTIVE,
    BG_GRAVITY_PAD,        // Floor 7
    BG_GRAVITY_RETURN_PAD, // Floor 7 Ceiling Return
    BG_SPRING_PAD,         // Chapter 2: Floor Spring Pad
    BG_COGWHEEL_LEVER,     // Chapter 2: Rotating Cogwheel
    BG_WARP_PORTAL,        // Chapter 2: Arcane Teleporter
    BG_WINCH_DRAWBRIDGE    // Chapter 2: Heavy Drawbridge Winch
};

struct BgObject
{
    BgObjectType type;
    int x;
    int y;
    int w;
    int h;
    bool interactive;
    bool state;
    bool hasTorch;
    const char* prompt;
    int extraId;
};

BgObject bgObjects[MAX_BG_OBJECTS];
int bgObjectCount = 0;

struct Platform { int x, y, w, h; bool isBridge; };
Platform platforms[20];
int platformCount = 0;

struct SpikeTrap { int x, y, w, h; bool lethal; bool ceiling; };
SpikeTrap spikes[8];
int spikeCount = 0;

struct Chest { int x, y, w, h; bool opened; bool hasKey; bool isTrap; };
Chest chests[4];
int chestCount = 0;

struct Ghost { int x, y; bool active; };
Ghost ghost = { 0, 0, false };

int keyX = 500;
int keyY = 200;
bool keyActive = false;
bool keyInUI = false;

int starX = 0;
int starY = 0;
bool starActive = false;

int doorX = 910;
int doorY = GROUND_HEIGHT;

int buttonX = 0;
int buttonY = 0;
bool buttonPressed = false;

int crusherY = 520;
bool crusherFalling = false;
bool crusherJammed = false;

int fallingKeyY = 560;
double fallingKeyVY = 0;
bool fallingKeyActive = false;

int guardX = 680;
int guardY = GROUND_HEIGHT;
bool guardAsleep = false;

// Chapter 2 & Tricky Castle puzzle state variables
double cogwheelAngle = 0.0;
bool cogwheelActive = false;
int springCompressTimer = 0;
double pendulumAngle = 0.0;
bool pendulumLocked = false;
int shiftingWallY = GROUND_HEIGHT;
bool shiftingWallOpen = false;
bool hasDecoyKey = false;
int decoyKeyX = 0, decoyKeyY = 0;
int mirrorPlayerX = 0;
bool floor12BridgeLowered = false;

/* -------------------- PARTICLES -------------------- */
struct Particle
{
    double x, y, vx, vy;
    int r, g, b;
    double size;
    int life, maxLife;
    int type; // 0=dust, 1=sparkle, 2=flame, 3=smoke, 4=portal, 5=samba
    double a;
};
Particle particles[MAX_PARTICLES];
int particleCount = 0;

void spawnParticle(double x, double y, double vx, double vy, int r, int g, int b, double size, int life, int type)
{
    if (particleCount >= MAX_PARTICLES) return;
    particles[particleCount++] = { x, y, vx, vy, r, g, b, size, life, life, type, 1.0 };
}

void spawnDustPuff(double x, double y)
{
    for (int i = 0; i < 5; i++)
    {
        double vx = ((rand() % 30) - 15) / 10.0;
        double vy = (rand() % 20) / 10.0 + 0.4;
        spawnParticle(x, y, vx, vy, 180, 180, 190, 4.0, 22, 0);
    }
}

void spawnSparkleBurst(double x, double y, int r, int g, int b)
{
    for (int i = 0; i < 20; i++)
    {
        double ang = (rand() % 360) * 3.14159 / 180.0;
        double spd = (rand() % 45 + 10) / 10.0;
        spawnParticle(x, y, cos(ang) * spd, sin(ang) * spd, r, g, b, 3.5, 32, 1);
    }
}

struct FloatingText
{
    double x, y;
    char text[64];
    int r, g, b;
    int life, maxLife;
};
FloatingText floatingTexts[MAX_FLOATING_TEXTS];
int floatingTextCount = 0;

void addFloatingText(double x, double y, const char* txt, int r, int g, int b)
{
    if (floatingTextCount >= MAX_FLOATING_TEXTS) return;
    FloatingText& ft = floatingTexts[floatingTextCount++];
    ft.x = x; ft.y = y;
    strncpy(ft.text, txt, 63);
    ft.text[63] = '\0';
    ft.r = r; ft.g = g; ft.b = b;
    ft.life = 50; ft.maxLife = 50;
}

void triggerScreenShake(int frames, double intensity)
{
    screenShakeTimer = frames;
    screenShakeIntensity = intensity;
}

void showToast(const char* msg)
{
    strncpy(toastMessage, msg, 63);
    toastMessage[63] = '\0';
    toastTimer = 120;
}
int autoCaptureStep = -1;

void saveGlScreenshot(const char* filename)
{
    int w = SCREEN_WIDTH;
    int h = SCREEN_HEIGHT;
    unsigned char* pixels = (unsigned char*)malloc(w * h * 3);
    if (!pixels) return;
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    FILE* f = fopen(filename, "wb");
    if (!f) { free(pixels); return; }

    unsigned char bmpFileHeader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpInfoHeader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

    int rowSize = (w * 3 + 3) & (~3);
    int imageSize = rowSize * h;
    int fileSize = 54 + imageSize;

    bmpFileHeader[2] = (unsigned char)(fileSize);
    bmpFileHeader[3] = (unsigned char)(fileSize >> 8);
    bmpFileHeader[4] = (unsigned char)(fileSize >> 16);
    bmpFileHeader[5] = (unsigned char)(fileSize >> 24);

    bmpInfoHeader[4] = (unsigned char)(w);
    bmpInfoHeader[5] = (unsigned char)(w >> 8);
    bmpInfoHeader[6] = (unsigned char)(w >> 16);
    bmpInfoHeader[7] = (unsigned char)(w >> 24);

    bmpInfoHeader[8] = (unsigned char)(h);
    bmpInfoHeader[9] = (unsigned char)(h >> 8);
    bmpInfoHeader[10] = (unsigned char)(h >> 16);
    bmpInfoHeader[11] = (unsigned char)(h >> 24);

    bmpInfoHeader[20] = (unsigned char)(imageSize);
    bmpInfoHeader[21] = (unsigned char)(imageSize >> 8);
    bmpInfoHeader[22] = (unsigned char)(imageSize >> 16);
    bmpInfoHeader[23] = (unsigned char)(imageSize >> 24);

    fwrite(bmpFileHeader, 1, 14, f);
    fwrite(bmpInfoHeader, 1, 40, f);

    unsigned char* row = (unsigned char*)malloc(rowSize);
    if (row)
    {
        memset(row, 0, rowSize);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int glIdx = (y * w + x) * 3;
                row[x * 3 + 0] = pixels[glIdx + 2]; // B
                row[x * 3 + 1] = pixels[glIdx + 1]; // G
                row[x * 3 + 2] = pixels[glIdx + 0]; // R
            }
            fwrite(row, 1, rowSize, f);
        }
        free(row);
    }

    free(pixels);
    fclose(f);
}
