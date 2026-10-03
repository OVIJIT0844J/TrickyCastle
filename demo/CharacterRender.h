#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: CharacterRender.h
 * LEAD CHARACTER GRAPHICS DESIGNER: Ovijit Sharma (Student ID: 00725105101134)
 * ROLE & RESPONSIBILITY: Character Visuals, Sprite Presentation, Animation & Aesthetic Look
 *
 * GRAPHICS & ANIMATION DESIGNED BY OVIJIT SHARMA:
 *   - Complete visual look and artistic styling of 6 Chibi heroes
 *   - Procedural character animation pipeline (drawCharacterGraphics)
 *   - Natural idle breathing sway and lifelike chest cadence when standing still
 *   - Articulated run cycle: dynamic limb swaying and stride bounce
 *   - Parabolic jump stretching and landing squash deformation effects
 *   - Dynamic facing flip (left/right) with smooth sprite orientation
 *   - Inverted gravity visual transformations (upside-down ceiling walking)
 *   - Hero-specific visual details: lion shield, frost step trails, and custom armor trims
 * DEPENDENCIES: GameDefines.h, RenderUtils.h
 * =========================================================================== */
#include "GameDefines.h"
#include "RenderUtils.h"

/* -------------------- CHARACTER GRAPHICS WITH SPECIAL ANIMATION EFFECTS -------------------- */
void drawCharacterGraphics(int x, int y, int face, bool upsideDown, int hero)
{
    int tex = characters[hero].skinTexID;

    // Idle breathing animation when standing still on ground (smooth, natural cadence)
    double idleBreath = 0.0;
    if (onGround && abs(velocityX) < 0.1)
    {
        idleBreath = sin(levelTimer * 0.045) * 0.028;
    }

    double scaleX = 1.0 - idleBreath * 0.35;
    double scaleY = 1.0 + idleBreath;
    int bobY = 0;

    if (squashTimer > 0)
    {
        scaleX = 1.18;
        scaleY = 0.82;
    }
    else if (!onGround)
    {
        if (velocityY > 1.8) // Jumping upward
        {
            scaleX = 0.90;
            scaleY = 1.12;
        }
        else if (velocityY < -1.8) // Falling downward
        {
            scaleX = 0.94;
            scaleY = 1.06;
        }
    }
    else if (onGround && abs(velocityX) > 0.1)
    {
        // Fluid stride bounce and slight squash & stretch
        bobY = (int)(abs(sin(walkCycle * 0.20)) * 4.0);
        scaleX = 1.0 + sin(walkCycle * 0.20) * 0.03;
        scaleY = 1.0 - sin(walkCycle * 0.20) * 0.03;
    }

    int drawW = (int)(PLAYER_WIDTH * 1.35 * scaleX);
    int drawH = (int)(PLAYER_HEIGHT * 1.35 * scaleY);
    int drawX = x - (drawW - PLAYER_WIDTH) / 2;
    int drawY = y + bobY;

    // Ground Shadow projection beneath player (scales smoothly with air height)
    if (!upsideDown)
    {
        drawGroundShadow(x + PLAYER_WIDTH / 2, GROUND_HEIGHT, y, PLAYER_WIDTH);
    }

    // Running Dynamic Tilt in direction of movement
    double tiltDeg = 0;
    if (onGround && abs(velocityX) > 0.4)
    {
        tiltDeg = (face == 1) ? -5.5 : 5.5;
    }

    // ---------------- AUTHENTIC CHAMPION THEMATIC PARTICLES ----------------
    if (hero == HERO_CR7)
    {
        if (rand() % 3 == 0)
        {
            double fx = x + (face == 1 ? (PLAYER_WIDTH + 8) : -6) + (rand() % 12 - 6);
            double fy = y + 16 + (rand() % 35);
            if (cr7SkinSelected == 1) // Real Madrid: Pristine White & Royal Gold Holy Flames
            {
                spawnParticle(fx, fy, ((rand() % 30) - 15) / 20.0, (rand() % 25) / 15.0 + 0.7, 255, 255, 255, 3.2, 20, 2);
                spawnParticle(fx, fy, ((rand() % 30) - 15) / 20.0, (rand() % 25) / 15.0 + 0.7, 251, 191, 36, 2.5, 16, 1);
            }
            else if (cr7SkinSelected == 2) // Juventus: Electric Gold Lightning & White Sparks
            {
                spawnParticle(fx, fy, ((rand() % 30) - 15) / 20.0, (rand() % 25) / 15.0 + 0.7, 254, 240, 138, 3.2, 18, 4);
                spawnParticle(fx, fy, ((rand() % 30) - 15) / 20.0, (rand() % 25) / 15.0 + 0.7, 241, 245, 249, 2.5, 16, 1);
            }
            else // Red Devil: Crimson & Amber Fire
            {
                spawnParticle(fx, fy, ((rand() % 30) - 15) / 20.0, (rand() % 25) / 15.0 + 0.7, 239, 68, 68, 3.2, 20, 2);
                spawnParticle(fx, fy, ((rand() % 30) - 15) / 20.0, (rand() % 25) / 15.0 + 0.7, 251, 191, 36, 2.5, 16, 1);
            }
        }
    }
    else if (hero == HERO_NEYMAR)
    {
        if (rand() % 3 == 0)
        {
            double nx = x + (rand() % PLAYER_WIDTH);
            double ny = y + 10 + (rand() % (PLAYER_HEIGHT - 20));
            spawnParticle(nx, ny, ((rand() % 20) - 10) / 20.0, (rand() % 20) / 20.0 + 0.5, 250, 204, 21, 3.0, 22, 1);
            spawnParticle(nx, ny, ((rand() % 20) - 10) / 20.0, (rand() % 20) / 20.0 + 0.5, 34, 197, 94, 2.2, 18, 5);
        }
    }
    else if (hero == HERO_WILLIAM)
    {
        if (rand() % 3 == 0)
        {
            spawnParticle(x + (face == 1 ? PLAYER_WIDTH - 8 : 8), y + 36, 0, 0.6, 251, 191, 36, 2.6, 16, 1);
        }
    }
    else if (hero == HERO_ELENA)
    {
        if (abs(velocityX) > 0.4 && onGround && rand() % 3 == 0)
        {
            spawnParticle(x + (face == 1 ? 4 : PLAYER_WIDTH - 4), y + 4, -face * 1.5, 0.4, 125, 211, 252, 2.8, 18, 1);
        }
    }
    else if (hero == HERO_THORGAR)
    {
        if (abs(velocityX) > 0.4 && onGround && rand() % 4 == 0)
        {
            spawnParticle(x + PLAYER_WIDTH / 2, y + 4, ((rand() % 20) - 10) / 10.0, 0.8, 217, 119, 6, 3.2, 16, 1);
        }
    }
    else if (hero == HERO_SAHA_RENO) // The Cyber Architect (Holographic Matrix & Neon Cyan Data Bits)
    {
        if (rand() % 2 == 0)
        {
            double sx = x + (rand() % PLAYER_WIDTH);
            double sy = y + 10 + (rand() % (PLAYER_HEIGHT - 16));
            spawnParticle(sx, sy, ((rand() % 16) - 8) / 20.0, 0.6, 14, 165, 233, 2.8, 22, 1);
            if (rand() % 2 == 0)
                spawnParticle(sx, sy, 0.0, 0.8, 251, 191, 36, 2.2, 18, 1);
        }
    }

    glPushMatrix();

    if (upsideDown)
    {
        glTranslatef((float)(x + PLAYER_WIDTH / 2), (float)(y + PLAYER_HEIGHT / 2), 0.0f);
        glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef((float)(-(x + PLAYER_WIDTH / 2)), (float)(-(y + PLAYER_HEIGHT / 2)), 0.0f);
    }

    if (abs(tiltDeg) > 0.1)
    {
        iRotate(x + PLAYER_WIDTH / 2.0, y + PLAYER_HEIGHT / 2.0, tiltDeg);
    }

    // ---------------- AUTHENTIC BODY-SHAPED CONTOUR SILHOUETTE GLOW ----------------
    // Exact body contour rim glow: slowly appears and breathes around the character's exact body shape!
    if (tex != -1)
    {
        float slowGlowAlpha = (float)(sin(globalAnimTimer * 0.035) * 0.18 + 0.32); // Slow, hypnotic breathing!
        float gr = 0.98f, gg = 0.85f, gb = 0.25f; // Royal Gold

        if (hero == HERO_CR7)
        {
            if (cr7SkinSelected == 1)      { gr = 0.98f; gg = 0.90f; gb = 0.50f; } // Real Madrid Holy Gold
            else if (cr7SkinSelected == 2) { gr = 0.95f; gg = 0.85f; gb = 0.35f; } // Juventus Golden Bull
            else                           { gr = 0.96f; gg = 0.20f; gb = 0.12f; } // Red Devil Crimson
        }
        else if (hero == HERO_NEYMAR) { gr = 0.98f; gg = 0.82f; gb = 0.10f; } // Samba Gold
        else if (hero == HERO_ELENA)  { gr = 0.35f; gg = 0.82f; gb = 0.98f; } // Frost Crystal
        else if (hero == HERO_THORGAR){ gr = 0.92f; gg = 0.50f; gb = 0.15f; } // Titan Amber
        else if (hero == HERO_SAHA_RENO){ gr = 0.08f; gg = 0.75f; gb = 0.98f; } // Neon Cyber Cyan

        // 8-directional contour dilation: precisely matches head, hair, limbs, and cape!
        int dilate = 3;
        bool isFlipped = (hero == HERO_SAHA_RENO) ? (face == 1) : (face == -1);
        iShowImageTinted(drawX - dilate, drawY, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.40f, isFlipped);
        iShowImageTinted(drawX + dilate, drawY, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.40f, isFlipped);
        iShowImageTinted(drawX, drawY - dilate, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.40f, isFlipped);
        iShowImageTinted(drawX, drawY + dilate, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.40f, isFlipped);
        iShowImageTinted(drawX - 2, drawY - 2, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.25f, isFlipped);
        iShowImageTinted(drawX + 2, drawY + 2, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.25f, isFlipped);
        iShowImageTinted(drawX - 2, drawY + 2, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.25f, isFlipped);
        iShowImageTinted(drawX + 2, drawY - 2, drawW, drawH, tex, gr, gg, gb, slowGlowAlpha * 0.25f, isFlipped);
    }

    // RENDER BASE SPRITE (FACING MATCHES KEY DIRECTION: face == 1 -> RIGHT, face == -1 -> LEFT)
    if (tex != -1)
    {
        // RenoSir's source PNG faces left, so flip when moving right (face == 1) to face right!
        bool flipSprite = (hero == HERO_SAHA_RENO) ? (face == 1) : (face == -1);
        if (!flipSprite)
            iShowImageAlpha(drawX, drawY, drawW, drawH, tex, 1.0f);
        else
            iShowImageAlphaFlipped(drawX, drawY, drawW, drawH, tex, 1.0f);
    }

    // ---------------- ORGANIC BODY SHEEN & SURFACE LUMINANCE ----------------
    // Replaces the harsh diagonal sweep with a gentle, breathing additive body sheen
    if (tex != -1)
    {
        double sheenCadence = sin(globalAnimTimer * 0.04);
        if (sheenCadence > 0.25)
        {
            float sheenAlpha = (float)((sheenCadence - 0.25) / 0.75 * 0.26);
            float sr = 1.0f, sg = 0.98f, sb = 0.85f;
            if (hero == HERO_SAHA_RENO) { sr = 0.50f; sg = 0.90f; sb = 1.0f; } // Cyan cyber sheen
            bool isFlipped = (hero == HERO_SAHA_RENO) ? (face == 1) : (face == -1);
            iShowImageAdditive(drawX, drawY, drawW, drawH, tex, sr, sg, sb, sheenAlpha, isFlipped);
        }
    }

    // Held Wall Torch
    if (holdingTorch)
    {
        int tx = (face == 1) ? x + PLAYER_WIDTH + 4 : x - 14;
        int ty = y + 30 + bobY;
        iSetColor(120, 53, 15);
        iFilledRectangle(tx, ty - 14, 5, 20);
        iSetColor(245, 158, 11);
        iFilledCircle(tx + 2, ty + 10, 8);
        iSetColor(254, 240, 138);
        iFilledCircle(tx + 2, ty + 10, 4);

        if (rand() % 3 == 0)
        {
            spawnParticle(tx + 2, ty + 12, ((rand() % 40) - 20) / 20.0, 1.4, 245, 158, 11, 2.5, 15, 2);
        }
    }
    // Held Golden Key
    else if (hasKey)
    {
        int kx = x + PLAYER_WIDTH / 2 - 10;
        int ky = y + PLAYER_HEIGHT + 6 + bobY;
        iSetColor(251, 191, 36);
        iFilledCircle(kx + 7, ky + 12, 8);
        iSetColor(15, 23, 42);
        iFilledCircle(kx + 7, ky + 12, 4);
        iSetColor(251, 191, 36);
        iFilledRectangle(kx + 14, ky + 10, 16, 5);
        iFilledRectangle(kx + 22, ky + 5, 4, 6);
        iFilledRectangle(kx + 26, ky + 5, 4, 8);
    }

    if (abs(tiltDeg) > 0.1)
    {
        iUnRotate();
    }

    glPopMatrix();
}

