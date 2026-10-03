#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: SaveSystem.h
 * DEVELOPER: Maheed Abrar (Student ID: 00725105101140)
 * ROLE & RESPONSIBILITY: Binary Persistence Engine & Save Game Serialization
 *
 * FEATURES IMPLEMENTED:
 *   - Binary serialization engine targeting 'tricky_castle_save.dat'
 *   - Saving & restoring unlocked levels (Floors 1-24) and chapter progression
 *   - Star rating records (3-star evaluation) and room high scores
 *   - Currency tracking: player gold coins and gems persistence
 *   - Hero unlock state persistence (Saha Reno, CR7 Madrid/Juventus kits)
 *   - Daily login reward timestamp and event quest claim tracking
 *   - Corrupted save data bounds-checking, sanitation and recovery fallbacks
 * DEPENDENCIES: GameDefines.h
 * =========================================================================== */
#include "GameDefines.h"

/* -------------------- SAVE SYSTEM -------------------- */
void saveProgress()
{
    FILE* fp = fopen("tricky_castle_save.dat", "wb");
    if (!fp) return;
    fwrite(&unlockedLevels, sizeof(int), 1, fp);
    fwrite(&selectedHero, sizeof(int), 1, fp);
    fwrite(levelStars, sizeof(int), LEVEL_COUNT, fp);
    fwrite(levelScores, sizeof(int), LEVEL_COUNT, fp);
    fwrite(&soundEnabled, sizeof(bool), 1, fp);
    fwrite(&dailyLoginDay, sizeof(int), 1, fp);
    fwrite(&dailyRewardClaimedToday, sizeof(bool), 1, fp);
    fwrite(&playerGems, sizeof(int), 1, fp);
    fwrite(&playerCoins, sizeof(int), 1, fp);
    fwrite(&characters[HERO_SAHA_RENO].unlocked, sizeof(bool), 1, fp);
    fwrite(&cr7MadridUnlocked, sizeof(bool), 1, fp);
    fwrite(&cr7JuventusUnlocked, sizeof(bool), 1, fp);
    fwrite(&cr7SkinSelected, sizeof(int), 1, fp);
    fwrite(&questMadridClaimed, sizeof(bool), 1, fp);
    fwrite(&questJuventusClaimed, sizeof(bool), 1, fp);
    fwrite(&questRenoClaimed, sizeof(bool), 1, fp);
    fclose(fp);
}

void loadProgress()
{
    FILE* fp = fopen("tricky_castle_save.dat", "rb");
    if (!fp) return;
    fread(&unlockedLevels, sizeof(int), 1, fp);
    fread(&selectedHero, sizeof(int), 1, fp);
    fread(levelStars, sizeof(int), LEVEL_COUNT, fp);
    fread(levelScores, sizeof(int), LEVEL_COUNT, fp);
    fread(&soundEnabled, sizeof(bool), 1, fp);
    fread(&dailyLoginDay, sizeof(int), 1, fp);
    fread(&dailyRewardClaimedToday, sizeof(bool), 1, fp);
    fread(&playerGems, sizeof(int), 1, fp);
    fread(&playerCoins, sizeof(int), 1, fp);
    if (!feof(fp)) fread(&characters[HERO_SAHA_RENO].unlocked, sizeof(bool), 1, fp);
    if (!feof(fp)) fread(&cr7MadridUnlocked, sizeof(bool), 1, fp);
    if (!feof(fp)) fread(&cr7JuventusUnlocked, sizeof(bool), 1, fp);
    if (!feof(fp)) fread(&cr7SkinSelected, sizeof(int), 1, fp);
    if (!feof(fp)) fread(&questMadridClaimed, sizeof(bool), 1, fp);
    if (!feof(fp)) fread(&questJuventusClaimed, sizeof(bool), 1, fp);
    if (!feof(fp)) fread(&questRenoClaimed, sizeof(bool), 1, fp);
    fclose(fp);

    if (unlockedLevels < 1) unlockedLevels = 1;
    if (unlockedLevels > LEVEL_COUNT) unlockedLevels = LEVEL_COUNT;
    if (selectedHero < 0 || selectedHero >= HERO_COUNT) selectedHero = HERO_WILLIAM;
    if (dailyLoginDay < 1 || dailyLoginDay > 7) dailyLoginDay = 1;
    if (playerGems < 0) playerGems = 250;
    if (playerCoins < 0) playerCoins = 850;

    // Safety: If RenoSir is selected but not unlocked and no trial active, fallback to William
    if (selectedHero == HERO_SAHA_RENO && !characters[HERO_SAHA_RENO].unlocked && !sahaRenoTrialActive && !renoSirOneLevelTrial)
        selectedHero = HERO_WILLIAM;

    totalStars = 0;
    for (int i = 0; i < LEVEL_COUNT; i++)
    {
        if (levelStars[i] < 0 || levelStars[i] > 3) levelStars[i] = 0;
        if (levelScores[i] < 0 || levelScores[i] > 100000) levelScores[i] = 0;
        totalStars += levelStars[i];
    }

    updateCR7Skin();
}

