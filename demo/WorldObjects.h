#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: WorldObjects.h
 * DEVELOPER: Shahriar Rythm (Student ID: 00725105101132)
 * ROLE & RESPONSIBILITY: Trap Systems, Dungeon Props & Interactive World Entities
 *
 * FEATURES IMPLEMENTED:
 *   - Authentic 3D red floor buttons with depressed/active states (drawRedButton)
 *   - Medieval castle wall torches with procedural flame flickering animation
 *   - Iron ceiling pull-chains, wall levers, and cogwheel switches
 *   - Castle exit doors: wooden oak, iron-barred gates, locked with keyhole slots
 *   - Climbable dungeon ivy vines and pushable wooden crates
 *   - Chapter 2 mechanics: gravity reverse pads, spring jump pads, arcane teleporters
 *   - Heavy winch drawbridges with mechanical lowering animations
 * DEPENDENCIES: GameDefines.h, RenderUtils.h
 * =========================================================================== */
#include "GameDefines.h"
#include "RenderUtils.h"

/* -------------------- AUTHENTIC TRICKY CASTLE 3D RED BUTTON -------------------- */
void drawRedButton(int x, int y, bool pressed)
{
    int baseW = 56;
    int baseH = 10;
    int bx = x - baseW / 2;
    int by = y;

    // Drop shadow beneath button
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08f, 0.10f, 0.15f, 0.60f);
    iFilledRectangle(bx - 3, by - 2, baseW + 6, baseH + 2);

    // Beveled dark steel casing plate
    iSetColor(30, 41, 59);
    iFilledRectangle(bx, by, baseW, baseH);
    iSetColor(148, 163, 184); // Top silver beveled rim
    iLine(bx + 1, by + baseH, bx + baseW - 1, by + baseH);
    iSetColor(15, 23, 42); // Dark base underside
    iLine(bx, by, bx + baseW, by);

    // Red Dome Button Cap
    int capW = 42;
    int capH = pressed ? 5 : 13; // Sinks down smoothly when stepped on!
    int cx = x - capW / 2;
    int cy = by + (pressed ? 2 : 7);

    // Warning Light / Activation Radiant Halo
    if (pressed)
    {
        float pulse = (float)(sin(globalAnimTimer * 0.15) * 0.2 + 0.8);
        glColor4f(0.98f, 0.75f, 0.14f, 0.45f * pulse); // Amber/gold trigger glow
        iFilledCircle(x, cy + capH / 2, 28);
    }
    else
    {
        float pulse = (float)(sin(globalAnimTimer * 0.06) * 0.12 + 0.28);
        glColor4f(0.93f, 0.20f, 0.20f, pulse); // Crimson warning halo
        iFilledCircle(x, cy + capH / 2, 24);
    }
    glDisable(GL_BLEND);

    // 3D Red Cap Body
    iSetColor(153, 27, 27); // Dark Crimson Base
    iFilledRectangle(cx, cy, capW, capH);

    iSetColor(239, 68, 68); // Vibrant Red Core
    iFilledRectangle(cx + 2, cy + 2, capW - 4, capH - 3);

    // 3D Curvature Specular Highlight
    if (!pressed)
    {
        iSetColor(254, 202, 202); // Top bright highlight line
        iLine(cx + 6, cy + capH - 2, cx + capW - 6, cy + capH - 2);
        iSetColor(255, 255, 255); // Crisp glint
        iFilledCircle(cx + 10, cy + capH - 3, 2);
    }
    else
    {
        // Inner active indicator
        iSetColor(251, 191, 36);
        iFilledRectangle(cx + 6, cy + 2, capW - 12, 2);
    }
}

/* -------------------- AUTHENTIC CEILING CRUSHER TRAP -------------------- */
void drawCrusher(int x, int y, int w, int h)
{
    // Heavy suspension chains dropping from dungeon ceiling
    iSetColor(100, 116, 139);
    for (int l = y + h; l < 640; l += 14)
    {
        iCircle(x + 25, l + 7, 5);
        iCircle(x + w - 25, l + 7, 5);
    }

    // Heavy Chiseled Stone Block
    iSetColor(51, 65, 85);
    iFilledRectangle(x, y, w, h);

    // Reinforced Iron Strapping & Steel Rivets
    iSetColor(30, 41, 59);
    iFilledRectangle(x, y + 8, w, 10);
    iFilledRectangle(x + 18, y, 12, h);
    iFilledRectangle(x + w - 30, y, 12, h);

    iSetColor(203, 213, 225); // Steel Rivets
    iFilledCircle(x + 24, y + 13, 2);
    iFilledCircle(x + w - 24, y + 13, 2);
    iFilledCircle(x + 24, y + h - 8, 2);
    iFilledCircle(x + w - 24, y + h - 8, 2);

    // Downward Lethal Spikes beneath the block
    int spikeW = 16;
    int numSpikes = w / spikeW;
    iSetColor(226, 232, 240);
    for (int i = 0; i < numSpikes; i++)
    {
        int sx = x + i * spikeW;
        double tx[3] = { (double)sx, (double)(sx + spikeW), (double)(sx + spikeW / 2.0) };
        double ty[3] = { (double)y, (double)y, (double)(y - 12) };
        iFilledPolygon(tx, ty, 3);
    }
    iSetColor(15, 23, 42);
    iRectangle(x, y, w, h);
}

/* -------------------- DRAWING: INTERACTIVE WORLD OBJECTS -------------------- */
void drawPullChain(int x, int y, int w, int h, bool pulled)
{
    // Subtle pendulum sway animation
    double sway = sin(levelTimer * 0.05) * 2.5;

    iSetColor(71, 85, 105);
    iFilledRectangle(x - 10, y + h - 8, w + 20, 10);
    iSetColor(148, 163, 184);
    iRectangle(x - 10, y + h - 8, w + 20, 10);

    int links = h / 14;
    for (int i = 0; i < links; i++)
    {
        double factor = (double)(links - i) / links;
        int lx = x + w / 2 + (int)(sway * factor);
        int ly = y + i * 14;
        iSetColor(217, 119, 6);
        iFilledCircle(lx, ly + 7, 6);
        iSetColor(15, 23, 42);
        iFilledCircle(lx, ly + 7, 3);
    }

    int ry = pulled ? (y - 12) : y;
    int rx = x + w / 2 + (int)sway;
    iSetColor(251, 191, 36);
    iCircle(rx, ry + 14, 16);
    iCircle(rx, ry + 14, 13);
    iCircle(rx, ry + 14, 10);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float pulse = (float)(sin(levelTimer * 0.1) * 0.15 + 0.35);
    glColor4f(0.98f, 0.75f, 0.14f, pulse);
    iFilledCircle(rx, ry + 14, 26);
    glDisable(GL_BLEND);
}

void drawWallTorch(int x, int y, bool lit)
{
    iSetColor(30, 41, 59);
    iFilledRectangle(x - 4, y - 18, 8, 18);
    iFilledRectangle(x - 8, y - 2, 16, 5);

    if (lit)
    {
        iSetColor(245, 158, 11);
        iFilledCircle(x, y + 8, 18);
        iSetColor(254, 240, 138);
        iFilledCircle(x, y + 8, 9);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.96f, 0.62f, 0.05f, 0.28f);
        iFilledCircle(x, y + 8, 48);
        glDisable(GL_BLEND);

        if (rand() % 3 == 0)
        {
            spawnParticle(x + (rand() % 10 - 5), y + 12, ((rand() % 40) - 20) / 30.0, (rand() % 30) / 20.0 + 0.8, 251, 191, 36, 3.0, 24, 2);
        }
    }
    else
    {
        iSetColor(71, 85, 105);
        iFilledCircle(x, y + 6, 6);
    }
}

void drawWallLever(int x, int y, bool pulled)
{
    iSetColor(51, 65, 85);
    iFilledRectangle(x - 6, y, 40, 48);
    iSetColor(15, 23, 42);
    iRectangle(x - 6, y, 40, 48);
    iCircle(x + 14, y + 18, 10);

    if (!pulled)
    {
        iSetColor(180, 83, 9);
        glLineWidth(5.0f);
        iLine(x + 14, y + 18, x + 28, y + 42);
        iSetColor(239, 68, 68);
        iFilledCircle(x + 28, y + 42, 8);
    }
    else
    {
        iSetColor(180, 83, 9);
        glLineWidth(5.0f);
        iLine(x + 14, y + 18, x + 28, y + 6);
        iSetColor(74, 222, 128);
        iFilledCircle(x + 28, y + 6, 8);
    }
}

void drawClimbIvy(int x, int y, int w, int h)
{
    iSetColor(22, 101, 52);
    iFilledRectangle(x + w / 2 - 4, y, 8, h);

    int leafCount = h / 20;
    for (int i = 0; i < leafCount; i++)
    {
        int ly = y + i * 20;
        int lx = (i % 2 == 0) ? (x + 2) : (x + w - 16);
        iSetColor(34, 197, 94);
        iFilledCircle(lx + 7, ly + 7, 8);
        iSetColor(21, 128, 61);
        iCircle(lx + 7, ly + 7, 8);
    }
}

void drawPushCrate(int x, int y, int w, int h)
{
    drawGroundShadow(x + w / 2, GROUND_HEIGHT, y, w);

    iSetColor(146, 64, 14);
    iFilledRectangle(x, y, w, h);
    iSetColor(120, 53, 15);
    iFilledRectangle(x + 4, y + 4, w - 8, h - 8);

    iSetColor(180, 83, 9);
    glLineWidth(4.0f);
    iLine(x + 5, y + 5, x + w - 5, y + h - 5);
    iLine(x + 5, y + h - 5, x + w - 5, y + 5);

    iSetColor(30, 41, 59);
    iRectangle(x, y, w, h);
    iFilledCircle(x + 6, y + 6, 3);
    iFilledCircle(x + w - 6, y + 6, 3);
    iFilledCircle(x + 6, y + h - 6, 3);
    iFilledCircle(x + w - 6, y + h - 6, 3);
}

// Chapter 2: Interactive Spring Pad
void drawSpringPad(int x, int y, int w, int h, bool compressed)
{
    drawGroundShadow(x + w / 2, GROUND_HEIGHT, y, w);

    iSetColor(51, 65, 85);
    iFilledRectangle(x - 4, y, w + 8, 8);
    iSetColor(30, 41, 59);
    iRectangle(x - 4, y, w + 8, 8);

    int springH = compressed ? 8 : 18;
    iSetColor(203, 213, 225);
    glLineWidth(4.0f);
    int coils = 4;
    for (int i = 0; i < coils; i++)
    {
        int sy = y + 8 + i * (springH / coils);
        int sx1 = (i % 2 == 0) ? (x + 10) : (x + w - 10);
        int sx2 = (i % 2 == 0) ? (x + w - 10) : (x + 10);
        iLine(sx1, sy, sx2, sy + (springH / coils));
    }

    int padY = y + 8 + springH;
    iSetColor(180, 83, 9);
    iFilledRectangle(x, padY, w, 12);
    iSetColor(245, 158, 11);
    iFilledRectangle(x + 4, padY + 2, w - 8, 4);
    iSetColor(30, 41, 59);
    iRectangle(x, padY, w, 12);
}

// Chapter 2: Rotating Water Cogwheel
void drawRotatingCogwheel(int cx, int cy, int r, double angle)
{
    glPushMatrix();
    glTranslatef((float)cx, (float)cy, 0.0f);
    glRotatef((float)angle, 0.0f, 0.0f, 1.0f);

    iSetColor(120, 53, 15);
    iFilledCircle(0, 0, r);
    iSetColor(180, 83, 9);
    iFilledCircle(0, 0, r - 12);

    int teeth = 8;
    for (int i = 0; i < teeth; i++)
    {
        float a = i * 2.0f * 3.14159f / teeth;
        int tx = (int)(cos(a) * (r + 10));
        int ty = (int)(sin(a) * (r + 10));
        iSetColor(146, 64, 14);
        iFilledCircle(tx, ty, 14);
    }

    iSetColor(251, 191, 36);
    iFilledCircle(0, 0, 20);
    iSetColor(30, 41, 59);
    iFilledCircle(0, 0, 8);

    glPopMatrix();
}

// Chapter 2: Arcane Warp Portals
void drawWarpPortal(int x, int y, int w, int h, bool isOrange)
{
    iSetColor(51, 65, 85);
    iFilledRectangle(x, y, w, h);
    iSetColor(30, 41, 59);
    iRectangle(x, y, w, h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float pulse = (float)(sin(levelTimer * 0.15) * 0.2 + 0.75);
    if (!isOrange)
        glColor4f(0.14f, 0.58f, 0.98f, pulse);
    else
        glColor4f(0.98f, 0.45f, 0.14f, pulse);

    iFilledRectangle(x + 6, y + 6, w - 12, h - 12);
    glDisable(GL_BLEND);

    if (rand() % 4 == 0)
    {
        int pr = isOrange ? 251 : 56;
        int pg = isOrange ? 146 : 189;
        int pb = isOrange ? 60 : 248;
        spawnParticle(x + w / 2, y + 20, ((rand() % 20) - 10) / 15.0, 1.2, pr, pg, pb, 3.0, 20, 4);
    }
}

// Chapter 2: Heavy Drawbridge Winch
void drawFortressWinch(int x, int y, int w, int h)
{
    iSetColor(217, 119, 6);
    iFilledRectangle(x, y, w, h);
    iSetColor(30, 41, 59);
    iRectangle(x, y, w, h);

    iSetColor(120, 53, 15);
    iFilledCircle(x + w / 2, y + h / 2, 18);
    iSetColor(245, 158, 11);
    iFilledCircle(x + w / 2, y + h / 2, 8);

    iSetColor(30, 41, 59);
    glLineWidth(4.0f);
    iLine(x + w / 2, y + h / 2, x + w + 10, y + h / 2 + 12);
    iSetColor(180, 83, 9);
    iFilledCircle(x + w + 10, y + h / 2 + 12, 6);
}

void drawPlatforms()
{
    for (int i = 0; i < platformCount; i++)
    {
        Platform p = platforms[i];
        if (p.y > 0)
        {
            iSetColor(71, 85, 105);
            iFilledRectangle(p.x, p.y, p.w, p.h);
            iSetColor(100, 116, 139);
            iFilledRectangle(p.x, p.y + p.h - 5, p.w, 5);
            iSetColor(30, 41, 59);
            iRectangle(p.x, p.y, p.w, p.h);

            int segs = p.w / 45;
            for (int s = 1; s < segs; s++)
            {
                iLine(p.x + s * 45, p.y, p.x + s * 45, p.y + p.h);
            }
        }
    }
}

void drawChest(int x, int y, bool open)
{
    drawGroundShadow(x + 30, GROUND_HEIGHT, y, 60);

    if (!open)
    {
        iSetColor(180, 83, 9);
        iFilledRectangle(x, y, 60, 44);
        iSetColor(217, 119, 6);
        iFilledRectangle(x, y + 28, 60, 16);
        iSetColor(251, 191, 36);
        iFilledRectangle(x + 25, y + 16, 10, 12);
        iSetColor(15, 23, 42);
        iFilledCircle(x + 30, y + 23, 3);
        iFilledRectangle(x + 29, y + 18, 2, 6);
        iSetColor(30, 41, 59);
        iRectangle(x, y, 60, 44);
    }
    else
    {
        iSetColor(120, 53, 15);
        iFilledRectangle(x, y, 60, 28);
        iSetColor(41, 12, 0);
        iFilledRectangle(x + 5, y + 16, 50, 12);
        iSetColor(146, 64, 14);
        iFilledRectangle(x, y + 28, 60, 16);
        iSetColor(30, 41, 59);
        iRectangle(x, y, 60, 28);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.98f, 0.75f, 0.14f, 0.40f);
        iFilledCircle(x + 30, y + 24, 20);
        glDisable(GL_BLEND);
    }
}

void drawGhost(int x, int y)
{
    iSetColor(192, 132, 252);
    iFilledCircle(x + 18, y + 22, 18);
    iFilledRectangle(x, y + 6, 36, 18);

    double px[] = { (double)x, (double)(x + 12), (double)(x + 24), (double)(x + 36) };
    double py[] = { (double)y, (double)(y + 8), (double)y, (double)(y + 8) };
    iFilledPolygon(px, py, 4);

    iSetColor(15, 23, 42);
    iFilledCircle(x + 12, y + 24, 3.5);
    iFilledCircle(x + 24, y + 24, 3.5);
}

void drawDoor(int x, int y, bool open)
{
    iSetColor(51, 65, 85);
    iFilledRectangle(x - 6, y, 84, 115);
    iSetColor(30, 41, 59);
    iRectangle(x - 6, y, 84, 115);

    if (open)
    {
        iSetColor(251, 191, 36);
        iFilledRectangle(x, y, 72, 110);
        iSetColor(254, 240, 138);
        iFilledRectangle(x + 8, y + 8, 56, 94);
        iSetColor(255, 255, 255);
        iFilledRectangle(x + 18, y + 18, 36, 74);
    }
    else
    {
        iSetColor(120, 53, 15);
        iFilledRectangle(x, y, 72, 110);
        iSetColor(69, 26, 3);
        iLine(x + 24, y, x + 24, y + 110);
        iLine(x + 48, y, x + 48, y + 110);

        iSetColor(30, 41, 59);
        iFilledRectangle(x, y + 24, 72, 12);
        iFilledRectangle(x, y + 78, 72, 12);

        iSetColor(15, 23, 42);
        iFilledCircle(x + 36, y + 52, 6);
        iFilledRectangle(x + 34, y + 44, 4, 10);
    }
}

void drawSpikes(int x, int y, int w, int h, bool ceiling)
{
    int count = w / 22;
    iSetColor(148, 163, 184);
    for (int i = 0; i < count; i++)
    {
        int sx = x + i * 22;
        double px[] = { (double)sx, (double)(sx + 22), (double)(sx + 11) };
        double py[3];
        if (ceiling)
        {
            py[0] = (double)y; py[1] = (double)y; py[2] = (double)(y - h);
        }
        else
        {
            py[0] = (double)y; py[1] = (double)y; py[2] = (double)(y + h);
        }
        iFilledPolygon(px, py, 3);
        iSetColor(203, 213, 225);
        iLine(sx + 11, y, sx + 11, ceiling ? (y - h) : (y + h));
        iSetColor(148, 163, 184);
    }
}

void drawKey(int x, int y)
{
    // Floating bob
    int bob = (int)(sin(levelTimer * 0.12) * 4.0);
    int ky = y + bob;

    iSetColor(251, 191, 36);
    iFilledCircle(x + 9, ky + 18, 10);
    iSetColor(15, 23, 42);
    iFilledCircle(x + 9, ky + 18, 5);
    iSetColor(251, 191, 36);
    iFilledRectangle(x + 16, ky + 15, 18, 7);
    iFilledRectangle(x + 26, ky + 8, 5, 8);
    iFilledRectangle(x + 20, ky + 8, 4, 6);

    if (rand() % 3 == 0)
    {
        spawnParticle(x + 12, ky + 18, ((rand() % 20) - 10) / 10.0, 0.9, 251, 191, 36, 3.0, 18, 1);
    }
}

