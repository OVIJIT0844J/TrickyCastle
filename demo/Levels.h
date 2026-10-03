#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: Levels.h
 * DEVELOPER: Shahriar Rythm (Student ID: 00725105101132)
 * ROLE & RESPONSIBILITY: Level Design, Room Puzzle Layouts & Level Manager
 *
 * FEATURES IMPLEMENTED:
 *   - Level catalog containing 24 distinct castle puzzle floors (levels[])
 *   - Chapter 1: Princess Castle (Floors 1-12) - chain puzzles, chest traps, levers
 *   - Chapter 2: Royal Citadel (Floors 13-16) - gravity inversions, cogwheels, springs
 *   - Chapter 3: Witch Tower (Floors 17-20) & Chapter 4: Dragon's Keep (Floors 21-24)
 *   - Contextual hints and instant solutions for stuck players
 *   - Room entity loader (loadLevel): spawns spikes, buttons, keys, doors and props
 * DEPENDENCIES: GameDefines.h, RenderUtils.h, WorldObjects.h, AudioSystem.h, SaveSystem.h
 * =========================================================================== */
#include "GameDefines.h"
#include "RenderUtils.h"
#include "WorldObjects.h"
#include "AudioSystem.h"
#include "SaveSystem.h"

LevelInfo levels[LEVEL_COUNT] =
{
    // ---------- CHAPTER 1: PRINCESS CASTLE (FLOORS 1 - 12) ----------
    { "Chapter 1", "Floor 1", "Jump across, or find another way",
      "Steel spikes block the pit. Pull the glowing golden ceiling chain with [E] to extend the stone bridge!",
      "INSTANT SOLUTION: Walk to the glowing chain at the center and press [E] or Click it to extend the bridge safely across.",
      "Mind the spike pit! Watch your step next time.",
      "Images//bg_castle_dungeon.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 2", "The chain knows the way",
      "Look up! The iron ceiling pull-chain extends the stone floor.",
      "INSTANT SOLUTION: Pull the ceiling chain with [E] to extend the stone bridge, or push the wooden crate into the spikes.",
      "Steel spikes are sharp! Try pulling the ceiling chain next time.",
      "Images//bg_castle_hall.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 3", "Don't get carried away too much",
      "Inspect the chests carefully! Only the first chest holds the golden key; others awaken phantoms.",
      "INSTANT SOLUTION: Open ONLY the first chest on the left with [E] or Click to get the key. Avoid the trap chests!",
      "Curiosity awakened a dungeon phantom!",
      "Images//bg_castle_dungeon.jpg",
      90, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 4", "Use force - not key",
      "There is no key in this room! Walk right up to the heavy door and push it. Pulling the wall lever loosens it!",
      "INSTANT SOLUTION: Pull the background lever on the wall with [E], then push firmly against the heavy stone door.",
      "No keyhole exists! Brute force is required.",
      "Images//bg_castle_hall.jpg",
      90, GROUND_HEIGHT, 760, GROUND_HEIGHT, false, true },

    { "Chapter 1", "Floor 5", "Don't let it press the button",
      "The key is falling from the ceiling toward a deadly pressure plate! Sprint and catch it mid-air.",
      "INSTANT SOLUTION: Sprint forward and jump immediately to catch the falling key before it touches the ground switch.",
      "The ceiling crusher triggered! Catch the key mid-air!",
      "Images//bg_castle_dungeon.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 6", "Sometimes you need to find short way",
      "The spikes across the floor are impossible to jump. Climb the background ivy to reach the ceiling passage!",
      "INSTANT SOLUTION: Grab the green ivy vines on the wall (press Up/W) to climb up into the secret ceiling tunnel.",
      "Floor spikes 1, Knight 0. Look for the climbing vines!",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 7", "Defy gravity",
      "Step on the glowing purple floor rune to flip gravity! Walk along the ceiling walkway, grab the key, and touch the ceiling rune to return!",
      "INSTANT SOLUTION: Step onto the purple floor rune to reverse gravity, walk across the ceiling arches to get the key, then touch the purple ceiling rune to drop down safely at the exit.",
      "Gravity is a harsh mistress in the arcane hall.",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 8", "Patience opens all doors",
      "Running triggers the spikes! Stand completely still and meditate for 2.5 seconds.",
      "INSTANT SOLUTION: Stop moving completely for 2.5 seconds. The spike pit will slowly retract into the floor.",
      "Rushing caused your downfall. Patience is a knight's virtue!",
      "Images//bg_castle_hall.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 9", "The button is a lie",
      "Do NOT step on the red button without cover! Push the oak crate under the crusher first.",
      "INSTANT SOLUTION: Shove the wooden crate under the crusher block, then step safely across.",
      "Crushed by a stone trap! Jam it with a crate.",
      "Images//bg_castle_hall.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 10", "The cold guard: Captain Messi",
      "Castle Guard Captain Lionel Messi is shivering in the dungeon. Bring him a warm burning torch to put him to sleep!",
      "INSTANT SOLUTION: Take a lit torch from the left wall sconce with [E], carry it to the brazier near Captain Messi to put him to sleep.",
      "Guard Captain Messi spotted you! Warm the brazier before walking past.",
      "Images//bg_castle_dungeon.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, false, false },

    { "Chapter 1", "Floor 11", "Mirror dimension",
      "Look at your reflection in the enchanted glass. It moves with you and holds the clue.",
      "INSTANT SOLUTION: Walk your reflection over the mirror pedestal to open the secret door.",
      "The mirror trap shattered!",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 1", "Floor 12", "Build the bridge yourself",
      "The chasm is impassable! Step on the red button or pull the high platform down to span the spikes.",
      "INSTANT SOLUTION: Step on the red button on the upper platform (or click it) to lower the stone drawbridge and collect the key.",
      "The bridge remained raised! Press the red button.",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    // ---------- CHAPTER 2: THE CITADEL (FLOORS 13 - 16) ----------
    { "Chapter 2", "Floor 13", "The deceptive key",
      "Don't trust the flashing decoy key over the spike pit! Pull the secret wall lever to extend the stone bridge and reveal the true key, or bounce on the spring pad across the high archway.",
      "INSTANT SOLUTION: Pull the secret wall lever with [E] to lower the stone drawbridge across the spikes and reveal the real key!",
      "Tricked by the false decoy key! Pull the secret wall lever next time.",
      "Images//bg_chapter2_citadel.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 2", "Floor 14", "The blade & safety switch",
      "A swinging pendulum blade blocks the passage! Step on the red button to lock the blade safely in place.",
      "INSTANT SOLUTION: Step onto the red floor button to halt the swinging blade trap, then safely grab the key.",
      "Sliced by the swinging blade! Press the red button to stop it.",
      "Images//bg_chapter2_citadel.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 2", "Floor 15", "Shift the castle walls",
      "Solid masonry seals the path! Click or press [E] on the central stone pillar to slide it into the ceiling.",
      "INSTANT SOLUTION: Approach or click the central stone wall pillar to shift it upward, revealing the corridor.",
      "Blocked by impenetrable fortress stones!",
      "Images//bg_chapter2_citadel.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 2", "Floor 16", "Walk on the words",
      "No ground crosses the bottomless pit! Look at the riddle in the air—the words themselves are solid!",
      "INSTANT SOLUTION: Jump onto the floating letters 'WORDS ARE SOLID BRIDGES' and walk across them to the door.",
      "Fell into the abyss! Step onto the floating words.",
      "Images//bg_chapter2_citadel.jpg",
      80, GROUND_HEIGHT, 910, 250, true, false },

    // ---------- CHAPTER 3: WITCH TOWER (FLOORS 17 - 20) ----------
    { "Chapter 3", "Floor 17", "Walk upon the mystic glyphs",
      "Arcane gravity runes levitate stepping stones. Step onto the purple floor rune to summon the rising path!",
      "INSTANT SOLUTION: Step on the glowing purple rune on the floor to raise the mystic stepping stones up to the door.",
      "Lost in the arcane abyss! Follow the glowing runes.",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, 320, true, false },

    { "Chapter 3", "Floor 18", "Extinguish the blue witchflame",
      "A blue witchflame cauldron guards the exit door. Pull the high water valve chain to douse the fire!",
      "INSTANT SOLUTION: Pull the high ceiling water chain to douse the cauldron fire and claim the key.",
      "Burned by arcane witchflame! Douse it with water first.",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 3", "Floor 19", "Enter the blue to exit the gold",
      "Twin arcane warp portals shimmer in the hall. Step into the blue portal to teleport past the spike wall!",
      "INSTANT SOLUTION: Step into the blue portal at the left to instantly teleport to the golden exit portal on the high ledge.",
      "Impaled by arcane barrier spikes! Use the warp portals.",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, 240, true, false },

    { "Chapter 3", "Floor 20", "Turn the Great Clockwork",
      "Chapter 3 Grand Finale! Turn the massive golden clockwork cogwheel to raise the drawbridge across the chasm!",
      "INSTANT SOLUTION: Approach the Great Cogwheel and press [E] to rotate it, bridging the deep arcane void.",
      "The tower clockwork froze! Keep turning the gear.",
      "Images//bg_castle_runes.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    // ---------- CHAPTER 4: DRAGON'S KEEP (FLOORS 21 - 24) ----------
    { "Chapter 4", "Floor 21", "Time your dash between fire blasts",
      "A stone dragon gargoyle breathes periodic fire! Push the heavy iron shield crate to block the flames.",
      "INSTANT SOLUTION: Push the iron shield crate directly ahead of you to deflect the dragon's fire breath, then grab the key.",
      "Scorched by dragon breath! Hide behind the iron shield crate.",
      "Images//bg_castle_dungeon.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 4", "Floor 22", "Not all stones sink into lava",
      "Boiling magma blocks the floor! Step on the cool obsidian switch to solidify safe stepping stones.",
      "INSTANT SOLUTION: Step onto the red floor button to cool the bubbling magma into solid obsidian platforms.",
      "Fell into the boiling magma lake! Step on the cooling switch first.",
      "Images//bg_castle_dungeon.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 4", "Floor 23", "Only the unpolished relic holds truth",
      "Three relic chests rest in the dragon's hoard. Open the ancient stone chest to claim the dragon key!",
      "INSTANT SOLUTION: Open the ancient stone chest with [E] to obtain the dragon seal key. Avoid the decoy chests!",
      "The dragon's phantom guardian was awakened!",
      "Images//bg_castle_dungeon.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false },

    { "Chapter 4", "Floor 24", "Winch the colossal chains",
      "Chapter 4 Grand Finale! Turn the heavy fortress winch to lower the giant dragon keep drawbridge!",
      "INSTANT SOLUTION: Stand by the fortress winch and press [E] to turn the colossal chains and lower the great drawbridge.",
      "The dragon keep gates remained shut! Turn the winch.",
      "Images//bg_castle_dungeon.jpg",
      80, GROUND_HEIGHT, 910, GROUND_HEIGHT, true, false }
};

/* -------------------- LEVEL LOADING -------------------- */
void loadLevel(int lvl)
{
    if (lvl < 0) lvl = 0;
    if (lvl >= LEVEL_COUNT) lvl = LEVEL_COUNT - 1;

    // RenoSir 1-Level Trial Tracker
    if (renoSirOneLevelTrial && !characters[HERO_SAHA_RENO].unlocked)
    {
        if (renoSirTrialStartLevel == -1)
        {
            renoSirTrialStartLevel = lvl;
        }
        else if (lvl != renoSirTrialStartLevel)
        {
            renoSirOneLevelTrial = false;
            renoSirTrialStartLevel = -1;
            if (selectedHero == HERO_SAHA_RENO)
            {
                selectedHero = HERO_WILLIAM;
                saveProgress();
            }
            showToast("RenoSir 1-Level Trial Complete!");
        }
    }

    currentLevel = lvl;

    playerX = levels[lvl].spawnX;
    playerY = levels[lvl].spawnY;
    velocityX = 0;
    velocityY = 0;
    onGround = true;
    facing = 1; // Default facing RIGHT
    hasKey = false;
    doorOpen = false;
    doorPushedDistance = 0;
    holdingTorch = false;
    invertedGravity = false;
    meditateTimer = 0;
    meditateState = 0;
    squashTimer = 0;
    levelTimer = 0;
    levelScore = 1000;
    usedInstantPassThisLevel = false;
    showHintAdModal = false;
    hintTierRevealed = 0;
    activeInteractionIndex = -1;
    cogwheelAngle = 0.0;
    cogwheelActive = false;
    springCompressTimer = 0;
    isTouchingLeft = false;
    isTouchingRight = false;
    isTouchingJump = false;

    doorX = levels[lvl].doorX;
    doorY = levels[lvl].doorY;

    bgObjectCount = 0;
    platformCount = 0;
    spikeCount = 0;
    chestCount = 0;
    ghost.active = false;
    keyActive = true;
    keyInUI = false;
    starActive = true;
    buttonX = 0;
    buttonY = 0;
    buttonPressed = false;
    crusherFalling = false;
    crusherJammed = false;
    fallingKeyActive = false;
    guardAsleep = false;
    pendulumAngle = 0.0;
    pendulumLocked = false;
    shiftingWallY = GROUND_HEIGHT;
    shiftingWallOpen = false;
    hasDecoyKey = false;
    decoyKeyX = 0;
    decoyKeyY = 0;
    mirrorPlayerX = 0;
    floor12BridgeLowered = false;

    // Ground platform spanning entire screen width
    platforms[platformCount++] = { 0, 0, SCREEN_WIDTH, GROUND_HEIGHT, false };

    // ---------------- CHAPTER 1 (FLOORS 1 - 12) ----------------
    if (currentLevel == 0) // Floor 1: Spikes & Pull Chain Bridge
    {
        spikes[spikeCount++] = { 380, GROUND_HEIGHT, 220, 26, true, false };
        keyX = 700; keyY = 180;
        starX = 490; starY = 270;
        bgObjects[bgObjectCount++] = { BG_PULL_CHAIN, 310, 180, 24, 460, true, false, false, "[E] Pull Chain to Drop Bridge", 0 };
    }
    else if (currentLevel == 1) // Floor 2: Chain Bridge or Crate
    {
        spikes[spikeCount++] = { 350, GROUND_HEIGHT, 280, 26, true, false };
        keyX = 720; keyY = 180;
        starX = 512; starY = 280;
        bgObjects[bgObjectCount++] = { BG_PULL_CHAIN, 320, 180, 24, 460, true, false, false, "[E] Pull Chain to Drop Bridge", 0 };
        bgObjects[bgObjectCount++] = { BG_PUSH_CRATE, 200, GROUND_HEIGHT, 50, 50, true, false, false, "[E] Push Heavy Crate", 0 };
    }
    else if (currentLevel == 2) // Floor 3: FIXED MULTI-INPUT CHEST LOGIC
    {
        starX = 700; starY = 220;
        chests[chestCount++] = { 200, GROUND_HEIGHT, 60, 44, false, true, false };
        bgObjects[bgObjectCount++] = { BG_CHEST_INTERACTIVE, 200, GROUND_HEIGHT, 60, 44, true, false, false, "[E / Click] Open Treasure Chest", 0 };

        chests[chestCount++] = { 420, GROUND_HEIGHT, 60, 44, false, false, true };
        bgObjects[bgObjectCount++] = { BG_CHEST_INTERACTIVE, 420, GROUND_HEIGHT, 60, 44, true, false, false, "[E / Click] Open Treasure Chest", 1 };

        chests[chestCount++] = { 640, GROUND_HEIGHT, 60, 44, false, false, true };
        bgObjects[bgObjectCount++] = { BG_CHEST_INTERACTIVE, 640, GROUND_HEIGHT, 60, 44, true, false, false, "[E / Click] Open Treasure Chest", 2 };

        keyActive = false;
        bgObjects[bgObjectCount++] = { BG_TORCH_SCONCE, 260, 280, 28, 40, true, true, false, "[E] Inspect Sconce Clue", 0 };
    }
    else if (currentLevel == 3) // Floor 4: Push Door & Wall Lever
    {
        keyActive = false;
        starX = 400; starY = 220;
        bgObjects[bgObjectCount++] = { BG_WALL_LEVER, 300, 160, 32, 48, true, false, false, "[E] Pull Wall Lever", 0 };
    }
    else if (currentLevel == 4) // Floor 5: Catch Falling Key
    {
        fallingKeyY = 560;
        fallingKeyVY = -2.2;
        fallingKeyActive = true;
        keyActive = false;
        buttonX = 520; buttonY = GROUND_HEIGHT;
        spikes[spikeCount++] = { 460, 560, 160, 32, false, true };
        starX = 640; starY = 280;
        bgObjects[bgObjectCount++] = { BG_PUSH_CRATE, 200, GROUND_HEIGHT, 50, 50, true, false, false, "[E] Push Crate", 0 };
    }
    else if (currentLevel == 5) // Floor 6: Climb Wall Ivy
    {
        spikes[spikeCount++] = { 220, GROUND_HEIGHT, 540, 28, true, false };
        keyX = 820; keyY = 200;
        starX = 512; starY = 510;
        bgObjects[bgObjectCount++] = { BG_CLIMB_IVY, 130, GROUND_HEIGHT, 48, 460, true, false, false, "[W / Up] Climb Green Ivy", 0 };
        platforms[platformCount++] = { 120, 500, 700, 24, false };
    }
    else if (currentLevel == 6) // Floor 7: Defy Gravity (COMPLETELY FIXED & SOLVABLE!)
    {
        keyX = 512; keyY = 475;
        starX = 512; starY = 320;
        spikes[spikeCount++] = { 320, GROUND_HEIGHT, 340, 26, true, false };

        // Ceiling stone walkway for inverted gravity walking!
        platforms[platformCount++] = { 0, 560, SCREEN_WIDTH, 80, false };

        // Floor rune to invert gravity
        bgObjects[bgObjectCount++] = { BG_GRAVITY_PAD, 200, GROUND_HEIGHT, 95, 18, true, false, false, "Step on Rune: Invert Gravity", 0 };

        // Wide ceiling rune to flip gravity back down safely past the spikes!
        bgObjects[bgObjectCount++] = { BG_GRAVITY_RETURN_PAD, 680, 542, 200, 18, true, false, false, "Ceiling Rune: Restore Gravity", 0 };
    }
    else if (currentLevel == 7) // Floor 8: Meditation / Patience
    {
        spikes[spikeCount++] = { 320, GROUND_HEIGHT, 360, 26, true, false };
        keyX = 760; keyY = 180;
        starX = 500; starY = 280;
    }
    else if (currentLevel == 8) // Floor 9: Jam Crusher
    {
        buttonX = 460; buttonY = GROUND_HEIGHT;
        spikes[spikeCount++] = { 420, 480, 140, 30, true, true };
        crusherY = 480;
        keyX = 800; keyY = 180;
        starX = 500; starY = 340;
        bgObjects[bgObjectCount++] = { BG_PUSH_CRATE, 220, GROUND_HEIGHT, 50, 50, true, false, false, "[E] Push Crate Under Crusher", 0 };
    }
    else if (currentLevel == 9) // Floor 10: Cold Guard
    {
        guardX = 680; guardY = GROUND_HEIGHT;
        doorX = 910; doorY = GROUND_HEIGHT;
        keyActive = false;
        starX = 420; starY = 280;
        bgObjects[bgObjectCount++] = { BG_TORCH_SCONCE, 180, 240, 28, 40, true, true, true, "[E] Take Burning Torch", 0 };
        bgObjects[bgObjectCount++] = { BG_TORCH_SCONCE, 590, 220, 28, 40, true, false, false, "[E] Place Torch at Cold Brazier", 1 };
    }
    else if (currentLevel == 10) // Floor 11: Mirror Dimension
    {
        keyX = 512; keyY = 240;
        starX = 780; starY = 320;
        spikes[spikeCount++] = { 360, GROUND_HEIGHT, 240, 26, true, false };
        platforms[platformCount++] = { 350, 200, 260, 22, false };
    }
    else if (currentLevel == 11) // Floor 12: Build the bridge yourself (End of Chapter 1)
    {
        keyX = 860; keyY = 200;
        keyActive = true;
        keyInUI = false;
        starX = 512; starY = 380;
        floor12BridgeLowered = false;
        buttonPressed = false;

        // Lethal spike chasm across center
        spikes[spikeCount++] = { 240, GROUND_HEIGHT, 500, 26, true, false };

        // Upper mechanism balcony with the prominent 3D RED BUTTON
        platforms[platformCount++] = { 180, 280, 260, 22, false };
        buttonX = 310;
        buttonY = 302; // Positioned right on the upper balcony platform!

        // Wall ivy to climb up to the mechanism
        bgObjects[bgObjectCount++] = { BG_CLIMB_IVY, 130, GROUND_HEIGHT, 48, 280, true, false, false, "[W / Up] Climb to Mechanism", 0 };

        // Lower left wall release lever as alternate interactable
        bgObjects[bgObjectCount++] = { BG_WALL_LEVER, 90, 160, 32, 48, true, false, false, "[E] Pull Bridge Release Lever", 0 };
    }
    // ---------------- CHAPTER 2: THE CITADEL (FLOORS 13 - 16) ----------------
    else if (currentLevel == 12) // Floor 13: The Deceptive Key (FIXED & FULLY SOLVABLE!)
    {
        spikes[spikeCount++] = { 280, GROUND_HEIGHT, 420, 26, true, false };
        platforms[platformCount++] = { 260, 320, 460, 22, false }; // Upper stone archway

        // Interactive Spring Pad at foot of the pit to bounce onto upper archway!
        bgObjects[bgObjectCount++] = { BG_SPRING_PAD, 210, GROUND_HEIGHT, 50, 18, false, false, false, "Spring Pad", 0 };

        // Flashing decoy key hovering over the pit
        hasDecoyKey = true;
        decoyKeyX = 490;
        decoyKeyY = 220;

        // Real key concealed until secret mechanism engaged
        keyX = 840; keyY = 200;
        keyActive = false;
        starX = 512; starY = 380;

        // Secret wall lever
        bgObjects[bgObjectCount++] = { BG_WALL_LEVER, 140, 160, 32, 48, true, false, false, "[E] Pull Secret Mechanism", 0 };
    }
    else if (currentLevel == 13) // Floor 14: The Blade & Safety Switch
    {
        // Lethal spike chasm across the corridor
        spikes[spikeCount++] = { 420, GROUND_HEIGHT, 300, 26, true, false };

        // Reachable stepping platforms for upper exploration
        platforms[platformCount++] = { 440, 150, 110, 20, false };
        platforms[platformCount++] = { 590, 210, 120, 20, false };

        keyX = 820; keyY = GROUND_HEIGHT + 15;
        keyActive = true;
        starX = 512; starY = 320;

        // Safety red switch button on the floor to halt the swinging blade and lower the walkway!
        buttonX = 260;
        buttonY = GROUND_HEIGHT;
        buttonPressed = false;
        pendulumLocked = false;
    }
    else if (currentLevel == 14) // Floor 15: Shift the Castle Walls
    {
        keyX = 840; keyY = 200;
        keyActive = true;
        starX = 512; starY = 360;

        shiftingWallY = GROUND_HEIGHT;
        shiftingWallOpen = false;

        // Wall shift lever
        bgObjects[bgObjectCount++] = { BG_WALL_LEVER, 380, 180, 32, 48, true, false, false, "[E] Shift Castle Masonry", 0 };
    }
    else if (currentLevel == 15) // Floor 16: Walk on the Words
    {
        // Lethal bottomless spike chasm across the floor
        spikes[spikeCount++] = { 140, GROUND_HEIGHT, 710, 26, true, false };

        // Stepped word platforms:
        // Word 1: "W A L K" (Y = 135) - jumpable from starting ground at Y=64 (delta 71px)
        platforms[platformCount++] = { 120, 135, 115, 20, false };

        // Word 2: "O N" (Y = 195) - jumpable from Word 1 (delta 60px)
        platforms[platformCount++] = { 260, 195, 80, 20, false };

        // Word 3: "T H E   S O L I D   W O R D S" (Y = 250) - jumpable from Word 2 (delta 55px)
        platforms[platformCount++] = { 365, 250, 465, 20, false };

        // Exit landing platform at the elevated door
        platforms[platformCount++] = { 840, 250, 170, 24, false };

        doorX = 910; doorY = 250;
        keyX = 860; keyY = 310;
        keyActive = true;
        starX = 520; starY = 350;
    }
    // ---------------- CHAPTER 3: WITCH TOWER (FLOORS 17 - 20) ----------------
    else if (currentLevel == 16) // Floor 17: Mystic Floating Runes
    {
        // Lethal pit spikes
        spikes[spikeCount++] = { 220, GROUND_HEIGHT, 520, 26, true, false };

        // Ascending mystic rune stepping stones
        platforms[platformCount++] = { 220, 120, 95, 20, false };
        platforms[platformCount++] = { 350, 175, 95, 20, false };
        platforms[platformCount++] = { 480, 230, 95, 20, false };
        platforms[platformCount++] = { 610, 285, 95, 20, false };
        platforms[platformCount++] = { 730, 320, 280, 24, false }; // High door platform

        doorX = 910; doorY = 320;
        keyX = 630; keyY = 335;
        keyActive = true;
        starX = 480; starY = 280;

        bgObjects[bgObjectCount++] = { BG_GRAVITY_PAD, 140, GROUND_HEIGHT, 70, 18, true, false, false, "Mystic Rune Stone", 0 };
    }
    else if (currentLevel == 17) // Floor 18: The Witch's Cauldron
    {
        spikes[spikeCount++] = { 220, GROUND_HEIGHT, 520, 26, true, false };
        platforms[platformCount++] = { 270, 240, 470, 22, false };
        platforms[platformCount++] = { 750, 240, 260, 22, false };

        doorX = 910; doorY = 240;
        keyX = 500; keyY = 300;
        keyActive = false;
        starX = 500; starY = 370;

        bgObjects[bgObjectCount++] = { BG_PULL_CHAIN, 180, 180, 24, 460, true, false, false, "[E] Douse Witch Cauldron", 0 };
        bgObjects[bgObjectCount++] = { BG_SPRING_PAD, 140, GROUND_HEIGHT, 50, 18, false, false, false, "Spring Pad", 0 };
    }
    else if (currentLevel == 18) // Floor 19: The Warp Portals
    {
        spikes[spikeCount++] = { 320, GROUND_HEIGHT, 380, 26, true, false };
        platforms[platformCount++] = { 720, 240, 280, 22, false };

        doorX = 910; doorY = 240;
        keyX = 840; keyY = 300;
        keyActive = true;
        starX = 512; starY = 380;

        bgObjects[bgObjectCount++] = { BG_WARP_PORTAL, 180, GROUND_HEIGHT, 54, 85, true, false, false, "Blue Warp Portal", 0 };
        bgObjects[bgObjectCount++] = { BG_WARP_PORTAL, 740, 240, 54, 85, true, false, false, "Golden Warp Portal", 1 };
    }
    else if (currentLevel == 19) // Floor 20: Arcane Clockwork (Chapter 3 Finale)
    {
        spikes[spikeCount++] = { 220, GROUND_HEIGHT, 580, 26, true, false };

        platforms[platformCount++] = { 90, 140, 100, 20, false }; // Ledge to reach cogwheel
        platforms[platformCount++] = { 820, GROUND_HEIGHT, 190, 24, false }; // Exit ledge

        doorX = 910; doorY = GROUND_HEIGHT;
        keyX = 860; keyY = 120;
        keyActive = true;
        starX = 512; starY = 360;

        bgObjects[bgObjectCount++] = { BG_COGWHEEL_LEVER, 130, 170, 60, 60, true, false, false, "[E] Turn Great Clockwork", 0 };
        bgObjects[bgObjectCount++] = { BG_SPRING_PAD, 170, GROUND_HEIGHT, 50, 18, false, false, false, "Spring Pad", 0 };
    }
    // ---------------- CHAPTER 4: DRAGON'S KEEP (FLOORS 21 - 24) ----------------
    else if (currentLevel == 20) // Floor 21: Dragon's Breath & Shield Crate
    {
        spikes[spikeCount++] = { 420, GROUND_HEIGHT, 300, 26, true, false };
        platforms[platformCount++] = { 400, 260, 340, 22, false };

        keyX = 560; keyY = 320;
        keyActive = true;
        starX = 560; starY = 420;

        bgObjects[bgObjectCount++] = { BG_PUSH_CRATE, 200, GROUND_HEIGHT, 52, 52, true, false, false, "[E] Push Shield Crate", 0 };
        bgObjects[bgObjectCount++] = { BG_SPRING_PAD, 320, GROUND_HEIGHT, 50, 18, false, false, false, "Spring Pad", 0 };
    }
    else if (currentLevel == 21) // Floor 22: Magma Stepping Stones
    {
        spikes[spikeCount++] = { 260, GROUND_HEIGHT, 480, 26, true, false };

        keyX = 840; keyY = 200;
        keyActive = true;
        starX = 512; starY = 360;

        buttonX = 180;
        buttonY = GROUND_HEIGHT;
        buttonPressed = false;
    }
    else if (currentLevel == 22) // Floor 23: The Dragon's Relic Hoard
    {
        starX = 720; starY = 240;

        chests[chestCount++] = { 220, GROUND_HEIGHT, 60, 44, false, true, false };
        bgObjects[bgObjectCount++] = { BG_CHEST_INTERACTIVE, 220, GROUND_HEIGHT, 60, 44, true, false, false, "[E] Open Ancient Relic Chest", 0 };

        chests[chestCount++] = { 460, GROUND_HEIGHT, 60, 44, false, false, true };
        bgObjects[bgObjectCount++] = { BG_CHEST_INTERACTIVE, 460, GROUND_HEIGHT, 60, 44, true, false, false, "[E] Open Decoy Chest", 1 };

        chests[chestCount++] = { 680, GROUND_HEIGHT, 60, 44, false, false, true };
        bgObjects[bgObjectCount++] = { BG_CHEST_INTERACTIVE, 680, GROUND_HEIGHT, 60, 44, true, false, false, "[E] Open Decoy Chest", 2 };

        keyActive = false;
    }
    else if (currentLevel == 23) // Floor 24: Winch the Colossal Chains (Chapter 4 Grand Finale)
    {
        spikes[spikeCount++] = { 220, GROUND_HEIGHT, 540, 26, true, false };

        platforms[platformCount++] = { 100, 280, 220, 22, false };
        bgObjects[bgObjectCount++] = { BG_CLIMB_IVY, 60, GROUND_HEIGHT, 44, 280, true, false, false, "[W / Up] Climb to Winch", 0 };
        bgObjects[bgObjectCount++] = { BG_WINCH_DRAWBRIDGE, 140, 280, 64, 64, true, false, false, "[E] Turn Fortress Winch", 0 };

        keyX = 840; keyY = 200;
        keyActive = true;
        starX = 512; starY = 400;
    }
}

