#pragma once
/* ===========================================================================
 * PROJECT: Castle Escape: A 2D Puzzle Adventure Game Using iGraphics
 * COURSE: Computer Graphics Lab, Ahsanullah University of Science and Technology (AUST)
 * MODULE: RenderUtils.h
 * LEAD GRAPHICS & AESTHETICS DESIGNER: Ovijit Sharma (Student ID: 00725105101134)
 * UI RENDERING CO-DEVELOPER: Nabeel Saad Borno (Student ID: 00725105101135)
 * ROLE & RESPONSIBILITY: Visual Aesthetics, Stylized 2D Vector Look & Graphics Engine
 *
 * GRAPHICS & LOOK DESIGNED BY OVIJIT SHARMA:
 *   - Overall visual direction, nocturnal castle color palette, and atmosphere
 *   - Procedural vector rendering: rounded rectangles, diamonds, gradient shading
 *   - Atmospheric dark vignette overlays & lighting illumination effects
 *   - Radiant glowing text shaders with pulsing sinusoidal alpha (drawGlowingText)
 *   - Crisp drop-shadow bitmap font typography (drawSharpText)
 *   - Dynamic ambient particle engine: floating torch embers, golden celebration sparks
 *
 * UI RENDERING BY NABEEL SAAD BORNO:
 *   - Toast notification popup overlay with ease-in/out timer fading
 *   - Star rating rendering, coin badges, gem icons, and ornate modal frames
 * DEPENDENCIES: GameDefines.h
 * =========================================================================== */
#include "GameDefines.h"

/* -------------------- HIGH-CONTRAST CRISP TYPOGRAPHY -------------------- */
void drawSharpText(int x, int y, const char* text, void* font, int r, int g, int b)
{
    iSetColor(12, 16, 26);
    iText(x + 1, y - 1, (char*)text, font);

    iSetColor(r, g, b);
    iText(x, y, (char*)text, font);
}

/* -------------------- GLOWING PULSING TEXT -------------------- */
void drawGlowingText(int x, int y, const char* text, void* font, int r, int g, int b, double pulseAlpha)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Multi-pass radiant halo
    glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, (float)(pulseAlpha * 0.45));
    iText(x - 2, y, (char*)text, font);
    iText(x + 2, y, (char*)text, font);
    iText(x, y - 2, (char*)text, font);
    iText(x, y + 2, (char*)text, font);

    glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, (float)(pulseAlpha * 0.7));
    iText(x - 1, y, (char*)text, font);
    iText(x + 1, y, (char*)text, font);
    iText(x, y - 1, (char*)text, font);
    iText(x, y + 1, (char*)text, font);

    // Core crisp text
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    iText(x, y, (char*)text, font);
    glDisable(GL_BLEND);
}

/* -------------------- BIG BOLD PURE RED FONT TEXT -------------------- */
void drawBigRedText(int x, int y, const char* text, void* font, float pulse = 1.0f)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Deep dark maroon drop shadow for 3D depth and readability
    glColor4f(0.10f, 0.0f, 0.0f, 0.85f * pulse);
    iText(x + 2, y - 2, (char*)text, font);
    iText(x + 1, y - 2, (char*)text, font);
    iText(x + 2, y - 1, (char*)text, font);

    // Radiant fiery red outline / halo
    glColor4f(0.80f, 0.05f, 0.05f, 0.70f * pulse);
    iText(x - 2, y, (char*)text, font);
    iText(x + 2, y, (char*)text, font);
    iText(x, y - 2, (char*)text, font);
    iText(x, y + 2, (char*)text, font);

    // Thick vibrant intense RED core (bolded with 1px cross-offsets)
    glColor4f(1.0f, 0.12f, 0.12f, 1.0f);
    iText(x, y, (char*)text, font);
    iText(x + 1, y, (char*)text, font);
    iText(x - 1, y, (char*)text, font);
    iText(x, y + 1, (char*)text, font);
    iText(x, y - 1, (char*)text, font);
    iText(x + 1, y + 1, (char*)text, font);

    glDisable(GL_BLEND);
}

/* -------------------- REALISTIC METALLIC & CARD GEOMETRY -------------------- */
void drawFilledSmoothRect(float x, float y, float w, float h, float rad, float r, float g, float b, float a = 1.0f)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(r, g, b, a);

    glBegin(GL_QUADS);
        glVertex2f(x + rad, y);
        glVertex2f(x + w - rad, y);
        glVertex2f(x + w - rad, y + h);
        glVertex2f(x + rad, y + h);

        glVertex2f(x, y + rad);
        glVertex2f(x + rad, y + rad);
        glVertex2f(x + rad, y + h - rad);
        glVertex2f(x, y + h - rad);

        glVertex2f(x + w - rad, y + rad);
        glVertex2f(x + w, y + rad);
        glVertex2f(x + w, y + h - rad);
        glVertex2f(x + w - rad, y + h - rad);
    glEnd();

    int segments = 8;
    float corners[4][2] = {
        { x + rad, y + rad },
        { x + w - rad, y + rad },
        { x + w - rad, y + h - rad },
        { x + rad, y + h - rad }
    };
    float startAngles[4] = { 3.14159f, 4.71239f, 0.0f, 1.5708f };

    for (int c = 0; c < 4; c++)
    {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(corners[c][0], corners[c][1]);
            for (int i = 0; i <= segments; i++)
            {
                float ang = startAngles[c] + i * (1.570796f / segments);
                glVertex2f(corners[c][0] + cos(ang) * rad, corners[c][1] + sin(ang) * rad);
            }
        glEnd();
    }
    glDisable(GL_BLEND);
}

void drawSmoothRectOutline(float x, float y, float w, float h, float rad, float r, float g, float b, float a = 1.0f, float lineWidth = 2.0f)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(r, g, b, a);
    glLineWidth(lineWidth);

    int segments = 8;
    float corners[4][2] = {
        { x + rad, y + rad },
        { x + w - rad, y + rad },
        { x + w - rad, y + h - rad },
        { x + rad, y + h - rad }
    };
    float startAngles[4] = { 3.14159265f, 4.71238898f, 0.0f, 1.57079632f };

    glBegin(GL_LINE_LOOP);
        // Bottom straight line
        glVertex2f(x + rad, y);
        glVertex2f(x + w - rad, y);

        // Bottom-Right arc
        for (int i = 0; i <= segments; i++)
        {
            float ang = startAngles[1] + i * (1.57079632f / segments);
            glVertex2f(corners[1][0] + cos(ang) * rad, corners[1][1] + sin(ang) * rad);
        }

        // Right straight line
        glVertex2f(x + w, y + rad);
        glVertex2f(x + w, y + h - rad);

        // Top-Right arc
        for (int i = 0; i <= segments; i++)
        {
            float ang = startAngles[2] + i * (1.57079632f / segments);
            glVertex2f(corners[2][0] + cos(ang) * rad, corners[2][1] + sin(ang) * rad);
        }

        // Top straight line
        glVertex2f(x + w - rad, y + h);
        glVertex2f(x + rad, y + h);

        // Top-Left arc
        for (int i = 0; i <= segments; i++)
        {
            float ang = startAngles[3] + i * (1.57079632f / segments);
            glVertex2f(corners[3][0] + cos(ang) * rad, corners[3][1] + sin(ang) * rad);
        }

        // Left straight line
        glVertex2f(x, y + h - rad);
        glVertex2f(x, y + rad);

        // Bottom-Left arc
        for (int i = 0; i <= segments; i++)
        {
            float ang = startAngles[0] + i * (1.57079632f / segments);
            glVertex2f(corners[0][0] + cos(ang) * rad, corners[0][1] + sin(ang) * rad);
        }
    glEnd();

    glLineWidth(1.0f);
    glDisable(GL_BLEND);
}

/* -------------------- ALPHA TINTED SPRITE (FOR PRECISE BODY-SHAPED CONTOUR GLOW) -------------------- */
void iShowImageTinted(int x, int y, int width, int height, unsigned int texture, float r, float g, float b, float alpha, bool flipped = false)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4f(r, g, b, alpha);
    glBegin(GL_QUADS);
        if (!flipped)
        {
            glTexCoord2f(0, 0); glVertex2f((float)x, (float)y);
            glTexCoord2f(1, 0); glVertex2f((float)(x + width), (float)y);
            glTexCoord2f(1, -1); glVertex2f((float)(x + width), (float)(y + height));
            glTexCoord2f(0, -1); glVertex2f((float)x, (float)(y + height));
        }
        else
        {
            glTexCoord2f(1, 0); glVertex2f((float)x, (float)y);
            glTexCoord2f(0, 0); glVertex2f((float)(x + width), (float)y);
            glTexCoord2f(0, -1); glVertex2f((float)(x + width), (float)(y + height));
            glTexCoord2f(1, -1); glVertex2f((float)x, (float)(y + height));
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

/* -------------------- ADDITIVE SPRITE LUMINANCE (FOR GENTLE BODY SHEEN) -------------------- */
void iShowImageAdditive(int x, int y, int width, int height, unsigned int texture, float r, float g, float b, float alpha, bool flipped = false)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive gleam
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4f(r, g, b, alpha);
    glBegin(GL_QUADS);
        if (!flipped)
        {
            glTexCoord2f(0, 0); glVertex2f((float)x, (float)y);
            glTexCoord2f(1, 0); glVertex2f((float)(x + width), (float)y);
            glTexCoord2f(1, -1); glVertex2f((float)(x + width), (float)(y + height));
            glTexCoord2f(0, -1); glVertex2f((float)x, (float)(y + height));
        }
        else
        {
            glTexCoord2f(1, 0); glVertex2f((float)x, (float)y);
            glTexCoord2f(0, 0); glVertex2f((float)(x + width), (float)y);
            glTexCoord2f(0, -1); glVertex2f((float)(x + width), (float)(y + height));
            glTexCoord2f(1, -1); glVertex2f((float)x, (float)(y + height));
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void drawMetallicCard(int x, int y, int w, int h, int rad,
                      float fillR, float fillG, float fillB, float fillA,
                      float borderR, float borderG, float borderB, int borderWidth,
                      bool glowing = false)
{
    // Outer magical glow halo if highlighted (using globalAnimTimer)
    if (glowing)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        float pulse = (float)(sin(globalAnimTimer * 0.12) * 0.22 + 0.65);
        glColor4f(borderR, borderG, borderB, pulse * 0.40f);
        drawFilledSmoothRect((float)(x - 8), (float)(y - 8), (float)(w + 16), (float)(h + 16), (float)(rad + 6), borderR, borderG, borderB, pulse * 0.40f);
        glColor4f(1.0f, 0.95f, 0.70f, pulse * 0.30f);
        drawFilledSmoothRect((float)(x - 4), (float)(y - 4), (float)(w + 8), (float)(h + 8), (float)(rad + 3), 1.0f, 0.95f, 0.70f, pulse * 0.30f);
        glDisable(GL_BLEND);
    }

    // Soft realistic depth drop-shadow
    drawFilledSmoothRect((float)x, (float)(y - 6), (float)w, (float)h, (float)rad, 0.03f, 0.04f, 0.08f, 0.50f);

    // Outer solid metallic bevel rim
    drawFilledSmoothRect((float)x, (float)y, (float)w, (float)h, (float)rad, borderR, borderG, borderB, 1.0f);

    // Inner smooth card body
    drawFilledSmoothRect((float)(x + borderWidth), (float)(y + borderWidth),
                         (float)(w - borderWidth * 2), (float)(h - borderWidth * 2),
                         (float)(rad - borderWidth), fillR, fillG, fillB, fillA);

    // 4 Corner Brass Rivets
    float rivetColor[3] = { 0.95f, 0.82f, 0.35f };
    iSetColor((int)(rivetColor[0] * 255), (int)(rivetColor[1] * 255), (int)(rivetColor[2] * 255));
    iFilledCircle(x + rad, y + rad, 3);
    iFilledCircle(x + w - rad, y + rad, 3);
    iFilledCircle(x + w - rad, y + h - rad, 3);
    iFilledCircle(x + rad, y + h - rad, 3);
}

void drawDiamond(int cx, int cy, int size, float r, float g, float b, float a = 1.0f)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(r, g, b, a);
    glBegin(GL_QUADS);
        glVertex2f((float)cx, (float)(cy + size));
        glVertex2f((float)(cx + size), (float)cy);
        glVertex2f((float)cx, (float)(cy - size));
        glVertex2f((float)(cx - size), (float)cy);
    glEnd();
    glDisable(GL_BLEND);
}

void drawDiamondOutline(int cx, int cy, int size, float r, float g, float b, float width = 2.0f)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(r, g, b);
    glLineWidth(width);
    glBegin(GL_LINE_LOOP);
        glVertex2f((float)cx, (float)(cy + size));
        glVertex2f((float)(cx + size), (float)cy);
        glVertex2f((float)cx, (float)(cy - size));
        glVertex2f((float)(cx - size), (float)cy);
    glEnd();
    glDisable(GL_BLEND);
}

void drawMetallicButton(int x, int y, int w, int h, const char* text, bool hovered, int theme)
{
    float fillR = 0.22f, fillG = 0.25f, fillB = 0.32f, fillA = 0.95f;
    float borderR = 0.85f, borderG = 0.88f, borderB = 0.95f;
    int textR = 255, textG = 255, textB = 255;
    int bw = 3;

    if (theme == 0) // Polished Gold / Brass (Primary Action: Play, Continue, Solve)
    {
        fillR = hovered ? 0.92f : 0.82f;
        fillG = hovered ? 0.65f : 0.52f;
        fillB = hovered ? 0.15f : 0.10f;
        borderR = 0.98f; borderG = 0.88f; borderB = 0.35f;
        textR = 25; textG = 20; textB = 10;
        bw = 3;
    }
    else if (theme == 1) // Brushed Steel / Silver (Secondary Action / Resume / Close)
    {
        fillR = hovered ? 0.88f : 0.78f;
        fillG = hovered ? 0.90f : 0.80f;
        fillB = hovered ? 0.95f : 0.86f;
        borderR = 0.45f; borderG = 0.48f; borderB = 0.58f;
        textR = 25; textG = 30; textB = 45;
        bw = 2;
    }
    else if (theme == 2) // Dark Iron / Bronze (Pill Buttons: Rate, Equip, Settings)
    {
        fillR = hovered ? 0.28f : 0.18f;
        fillG = hovered ? 0.32f : 0.22f;
        fillB = hovered ? 0.42f : 0.30f;
        borderR = hovered ? 0.98f : 0.65f;
        borderG = hovered ? 0.82f : 0.70f;
        borderB = hovered ? 0.25f : 0.80f;
        bw = 2;
    }
    else if (theme == 3) // Ruby Crimson (Danger / Close [X])
    {
        fillR = hovered ? 0.90f : 0.78f;
        fillG = hovered ? 0.20f : 0.12f;
        fillB = hovered ? 0.20f : 0.12f;
        borderR = 0.98f; borderG = 0.82f; borderB = 0.25f;
        textR = 255; textG = 255; textB = 255;
        bw = 2;
    }

    drawFilledSmoothRect((float)x, (float)(y - 4), (float)w, (float)h, 12, 0.04f, 0.05f, 0.08f, 0.45f);
    drawFilledSmoothRect((float)x, (float)y, (float)w, (float)h, 12, borderR, borderG, borderB, 1.0f);
    drawFilledSmoothRect((float)(x + bw), (float)(y + bw), (float)(w - bw * 2), (float)(h - bw * 2), 12 - bw, fillR, fillG, fillB, fillA);

    int textLen = (int)strlen(text);
    int tx = x + (w - textLen * 9) / 2;
    int ty = y + (h - 14) / 2 + 2;
    drawSharpText(tx, ty, text, GLUT_BITMAP_HELVETICA_18, textR, textG, textB);
}

/* -------------------- SKETCHED LIGHT-BLUE GEAR SETTINGS BUTTON -------------------- */
void drawMetallicCogGear(int cx, int cy, int r, double spinDeg, bool hovered = false)
{
    // If hovered, draw a soft cyan/sky-blue breathing halo
    if (hovered)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        float pulse = (float)(sin(globalAnimTimer * 0.15) * 0.25 + 0.65);
        glColor4f(0.56f, 0.82f, 1.0f, pulse * 0.50f);
        iFilledCircle(cx, cy, r + 14);
        glColor4f(1.0f, 1.0f, 1.0f, pulse * 0.35f);
        iFilledCircle(cx, cy, r + 8);
        glDisable(GL_BLEND);
    }

    if (gearSketchTex != -1)
    {
        int gSize = 58;
        glPushMatrix();
        glTranslatef((float)cx, (float)cy, 0.0f);
        glRotatef((float)spinDeg, 0.0f, 0.0f, 1.0f);
        iShowImageAlpha(-gSize / 2, -gSize / 2, gSize, gSize, gearSketchTex, 1.0f);
        glPopMatrix();
        return;
    }

    // Outer drop shadow
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.04f, 0.05f, 0.08f, 0.55f);
    iFilledCircle(cx + 2, cy - 3, r + 5);
    glDisable(GL_BLEND);

    glPushMatrix();
    glTranslatef((float)cx, (float)cy, 0.0f);
    glRotatef((float)spinDeg, 0.0f, 0.0f, 1.0f);

    // 8 Hand-drawn style Gear Teeth matching user reference sketch
    int teeth = 8;
    for (int i = 0; i < teeth; i++)
    {
        float ang = i * 2.0f * 3.14159265f / teeth;
        int tx = (int)(cos(ang) * (r + 4));
        int ty = (int)(sin(ang) * (r + 4));
        iSetColor(20, 25, 35); // Bold black outline
        iFilledCircle(tx, ty, 7);
        iSetColor(165, 215, 250); // Light blue sketch fill
        iFilledCircle(tx, ty, 5);
    }

    // Outer Gear Rim
    iSetColor(20, 25, 35);
    iFilledCircle(0, 0, r + 1);
    iSetColor(165, 215, 250);
    iFilledCircle(0, 0, r - 2);

    // Double Concentric Center Rings
    iSetColor(20, 25, 35);
    iCircle(0, 0, (r - 2) * 0.70);
    iCircle(0, 0, (r - 2) * 0.42);
    iFilledCircle(0, 0, (r - 2) * 0.35);

    glPopMatrix();
}

/* -------------------- REALISTIC DYNAMIC GROUND SHADOW -------------------- */
void drawGroundShadow(int cx, int groundY, int currentY, int width)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Height offset attenuation: shadow shrinks and softens as player jumps higher
    int heightAbove = currentY - groundY;
    if (heightAbove < 0) heightAbove = 0;
    double ratio = heightAbove / 250.0;
    if (ratio > 0.65) ratio = 0.65;
    double scale = 1.0 - ratio;
    double shadowAlpha = 0.40 * scale;

    int sw = (int)(width * 0.9 * scale);
    int sh = (int)(11 * scale);

    glColor4f(0.04f, 0.05f, 0.08f, (float)shadowAlpha);
    iFilledEllipse(cx, groundY + 4, sw, sh);
    glColor4f(0.02f, 0.03f, 0.05f, (float)(shadowAlpha * 0.6));
    iFilledEllipse(cx, groundY + 4, (int)(sw * 0.6), (int)(sh * 0.6));

    glDisable(GL_BLEND);
}

/* -------------------- GLOWING & ANIMATED SECRET STAR & UI STARS -------------------- */
void drawStarShape(int cx, int cy, double rOuter, double rInner, int r, int g, int b, bool glow = false)
{
    if (glow)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        float pulse = (float)(sin(globalAnimTimer * 0.14) * 0.2 + 0.55);
        glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, pulse * 0.45f);
        iFilledCircle(cx, cy, (int)(rOuter * 1.8));
        glColor4f(1.0f, 1.0f, 1.0f, pulse * 0.35f);
        iFilledCircle(cx, cy, (int)(rOuter * 1.15));
        glDisable(GL_BLEND);
    }

    // Specular star shadow
    iSetColor(15, 23, 42);
    double shx[10], shy[10];
    for (int i = 0; i < 10; i++)
    {
        double rad = (i % 2 == 0) ? rOuter : rInner;
        double a = i * 3.14159265 / 5.0 - 3.14159265 / 2.0;
        shx[i] = cx + cos(a) * rad;
        shy[i] = cy - 2 + sin(a) * rad;
    }
    iFilledPolygon(shx, shy, 10);

    // Core star body
    iSetColor(r, g, b);
    double sx[10], sy[10];
    for (int i = 0; i < 10; i++)
    {
        double rad = (i % 2 == 0) ? rOuter : rInner;
        double a = i * 3.14159265 / 5.0 - 3.14159265 / 2.0;
        sx[i] = cx + cos(a) * rad;
        sy[i] = cy + sin(a) * rad;
    }
    iFilledPolygon(sx, sy, 10);

    if (r > 200 && g > 150)
    {
        iSetColor(255, 255, 255);
        iFilledCircle(cx, cy, (int)(rInner * 0.45));
    }
}

void drawStar(int x, int y)
{
    int bobY = (int)(sin(globalAnimTimer * 0.1) * 5.0);
    int sy_pos = y + bobY;

    // Outer radiant pulsing aura
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float pulse = (float)(sin(globalAnimTimer * 0.15) * 0.2 + 0.48);
    glColor4f(0.98f, 0.78f, 0.15f, pulse);
    iFilledCircle(x, sy_pos, (int)(26 + sin(globalAnimTimer * 0.15) * 5));
    glColor4f(1.0f, 0.95f, 0.65f, pulse * 0.7f);
    iFilledCircle(x, sy_pos, 16);
    glDisable(GL_BLEND);

    // 5-Point Core Golden Star
    drawStarShape(x, sy_pos, 16, 7, 251, 191, 36, false);

    // Orbiting sparkle satellite
    if (rand() % 2 == 0)
    {
        double orbitA = globalAnimTimer * 0.18;
        double ox = x + cos(orbitA) * 24;
        double oy = sy_pos + sin(orbitA) * 24;
        spawnParticle(ox, oy, 0, 0.2, 254, 240, 138, 2.8, 14, 1);
    }
}

void drawUIStar(int cx, int cy, bool earned, double scale = 1.0)
{
    if (earned)
    {
        drawStarShape(cx, cy, 10.0 * scale, 4.5 * scale, 251, 191, 36, true);
    }
    else
    {
        drawStarShape(cx, cy, 8.0 * scale, 3.5 * scale, 71, 85, 105, false);
    }
}

/* -------------------- 3D MULTI-FACETED CRYSTAL GEM -------------------- */
void draw3DGem(int cx, int cy, int size, double shinePulse = 1.0)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Soft Ambient Drop-Shadow
    glColor4f(0.02f, 0.04f, 0.08f, 0.45f);
    iFilledCircle(cx + 1, cy - (int)(size * 0.55), (int)(size * 0.75));

    // 2. Radiant Outer Cyan Bloom (Additive)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    float glowAlpha = (float)(0.35f * shinePulse);
    glColor4f(0.06f, 0.70f, 0.98f, glowAlpha);
    iFilledCircle(cx, cy, (int)(size * 1.55));
    glColor4f(0.55f, 0.90f, 1.0f, glowAlpha * 0.55f);
    iFilledCircle(cx, cy, (int)(size * 1.05));
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Geometric facet coordinates
    double s = size;
    double topY = cy + s * 1.15;
    double botY = cy - s * 1.15;
    double midY = cy + s * 0.15;
    double leftX = cx - s * 1.15;
    double rightX = cx + s * 1.15;
    double inLeftX = cx - s * 0.58;
    double inRightX = cx + s * 0.58;
    double inTopY = cy + s * 0.60;

    // 3. Bottom Pavilion (Deep Sapphire & Cyan Shadow facets)
    // Bottom-Left Pavilion
    double blX[3] = { (double)cx, (double)leftX, (double)cx };
    double blY[3] = { (double)midY, (double)midY, (double)botY };
    glColor4f(0.01f, 0.42f, 0.65f, 1.0f);
    iFilledPolygon(blX, blY, 3);

    // Bottom-Right Pavilion (Shadow side)
    double brX[3] = { (double)cx, (double)rightX, (double)cx };
    double brY[3] = { (double)midY, (double)midY, (double)botY };
    glColor4f(0.03f, 0.28f, 0.48f, 1.0f);
    iFilledPolygon(brX, brY, 3);

    // 4. Crown Facets (Upper multi-cut facets)
    // Upper-Left Triangular Facet (Illuminated)
    double ulX[3] = { (double)leftX, (double)inLeftX, (double)inLeftX };
    double ulY[3] = { (double)midY, (double)midY, (double)inTopY };
    glColor4f(0.35f, 0.85f, 1.0f, 1.0f);
    iFilledPolygon(ulX, ulY, 3);

    // Upper-Right Triangular Facet
    double urX[3] = { (double)rightX, (double)inRightX, (double)inRightX };
    double urY[3] = { (double)midY, (double)midY, (double)inTopY };
    glColor4f(0.08f, 0.58f, 0.85f, 1.0f);
    iFilledPolygon(urX, urY, 3);

    // Upper Center Trapezoid
    double tcX[4] = { (double)inLeftX, (double)inRightX, (double)inRightX, (double)inLeftX };
    double tcY[4] = { (double)midY, (double)midY, (double)inTopY, (double)inTopY };
    glColor4f(0.15f, 0.72f, 0.98f, 1.0f);
    iFilledPolygon(tcX, tcY, 4);

    // Top Crest Triangle (Bright Glint Face)
    double tpX[3] = { (double)inLeftX, (double)inRightX, (double)cx };
    double tpY[3] = { (double)inTopY, (double)inTopY, (double)topY };
    glColor4f(0.65f, 0.94f, 1.0f, 1.0f);
    iFilledPolygon(tpX, tpY, 3);

    // 5. Crisp Facet Girdle & Edge Lines
    glColor4f(0.85f, 0.96f, 1.0f, 0.90f);
    iLine((int)leftX, (int)midY, (int)rightX, (int)midY);
    iLine((int)leftX, (int)midY, (int)cx, (int)botY);
    iLine((int)rightX, (int)midY, (int)cx, (int)botY);
    iLine((int)cx, (int)midY, (int)cx, (int)botY);
    iLine((int)inLeftX, (int)inTopY, (int)cx, (int)midY);
    iLine((int)inRightX, (int)inTopY, (int)cx, (int)midY);
    iLine((int)inLeftX, (int)inTopY, (int)cx, (int)topY);
    iLine((int)rightX, (int)midY, (int)inRightX, (int)inTopY);
    iLine((int)leftX, (int)midY, (int)inLeftX, (int)inTopY);
    iLine((int)inRightX, (int)inTopY, (int)cx, (int)topY);

    // 6. Brilliant Specular 4-Point Star Glint
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(1.0f, 1.0f, 1.0f, 0.95f);
    int glintX = cx - (int)(s * 0.35);
    int glintY = cy + (int)(s * 0.40);
    iFilledCircle(glintX, glintY, 2);
    iLine(glintX - 5, glintY, glintX + 5, glintY);
    iLine(glintX, glintY - 5, glintX, glintY + 5);
    glDisable(GL_BLEND);
}

/* -------------------- 3D STAMPED GOLD COIN -------------------- */
void draw3DCoin(int cx, int cy, int radius, double spinAngle = 0.0)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int r = radius;

    // 1. Soft Realistic Contact Shadow
    glColor4f(0.04f, 0.06f, 0.10f, 0.48f);
    iFilledCircle(cx + 2, cy - 3, r + 1);

    // 2. Warm Golden Halo
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    float glow = (float)(sin(globalAnimTimer * 0.08) * 0.12 + 0.28);
    glColor4f(0.98f, 0.78f, 0.15f, glow * 0.50f);
    iFilledCircle(cx, cy, (int)(r * 1.5));
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 3. Outer Thick Rim (Burnished Deep Bronze & Gold)
    iSetColor(120, 53, 15); // Deep shadow edge
    iFilledCircle(cx, cy, r);
    iSetColor(180, 83, 9); // Bevel transition
    iFilledCircle(cx, cy + 1, r - 1);
    iSetColor(245, 158, 11); // Vibrant gold rim
    iFilledCircle(cx, cy + 1, r - 2);

    // 4. Stamped Inner Coin Cavity
    iSetColor(217, 119, 6); // Cavity drop shadow
    iFilledCircle(cx, cy, r - 4);
    iSetColor(251, 191, 36); // Radiant gold face
    iFilledCircle(cx, cy + 1, r - 5);

    // 5. Coin Face Metallic Lighting / Radial Reflection
    glColor4f(0.99f, 0.90f, 0.45f, 0.35f);
    iFilledCircle(cx - r / 4, cy + r / 4, r / 2);

    // 6. Stamped Royal Star / Crown Relief in Center
    drawStarShape(cx, cy + 1, (double)(r * 0.48), (double)(r * 0.22), 254, 240, 138, false);
    iSetColor(180, 83, 9); // Relief shadow
    iCircle(cx, cy + 1, r - 6);

    // 7. Top Perimeter Curved Specular Glint
    iSetColor(255, 255, 255);
    iLine(cx - (int)(r * 0.5), cy + r - 3, cx + (int)(r * 0.5), cy + r - 3);
    iFilledCircle(cx - (int)(r * 0.35), cy + r - 3, 1);

    glDisable(GL_BLEND);
}

/* -------------------- 3D HIGH-RELIEF METALLIC BUTTON -------------------- */
void draw3DButton(int x, int y, int w, int h, const char* text, bool hovered, int theme)
{
    float baseR = 0.70f, baseG = 0.33f, baseB = 0.04f; // #b45309
    float bodyR = 0.96f, bodyG = 0.62f, bodyB = 0.07f; // #f59e0b
    float topR  = 0.99f, topG  = 0.94f, topB  = 0.54f; // #fef08a
    float haloR = 0.98f, haloG = 0.78f, haloB = 0.15f;
    int txtR = 25, txtG = 20, txtB = 5;

    if (theme == 1) // Emerald Green
    {
        baseR = 0.08f; baseG = 0.40f; baseB = 0.18f;
        bodyR = 0.13f; bodyG = 0.65f; bodyB = 0.30f;
        topR  = 0.50f; topG  = 0.95f; topB  = 0.65f;
        haloR = 0.13f; haloG = 0.77f; haloB = 0.36f;
        txtR = 255; txtG = 255; txtB = 255;
    }
    else if (theme == 2) // Electric Cyan
    {
        baseR = 0.02f; baseG = 0.35f; baseB = 0.55f;
        bodyR = 0.06f; bodyG = 0.65f; bodyB = 0.92f;
        topR  = 0.60f; topG  = 0.92f; topB  = 1.00f;
        haloR = 0.22f; haloG = 0.74f; haloB = 0.97f;
        txtR = 10; txtG = 25; txtB = 40;
    }
    else if (theme == 3) // Dark Titanium
    {
        baseR = 0.08f; baseG = 0.11f; baseB = 0.16f;
        bodyR = 0.18f; bodyG = 0.24f; bodyB = 0.34f;
        topR  = 0.40f; topG  = 0.48f; topB  = 0.60f;
        haloR = 0.30f; haloG = 0.38f; haloB = 0.50f;
        txtR = 148; txtG = 163; txtB = 184;
    }

    int lift = (hovered ? 3 : 0);
    int by = y + lift;

    // Drop Shadow
    drawFilledSmoothRect((float)(x - 2), (float)(y - 5), (float)(w + 4), (float)h, 12, 0.02f, 0.03f, 0.06f, 0.50f);

    // Radiant Glow Halo if Hovered or Theme 0
    if (hovered || theme == 0)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        float pulse = (float)(sin(globalAnimTimer * 0.12) * 0.18 + 0.32);
        glColor4f(haloR, haloG, haloB, pulse * 0.45f);
        drawFilledSmoothRect((float)(x - 6), (float)(by - 6), (float)(w + 12), (float)(h + 12), 16, haloR, haloG, haloB, pulse * 0.45f);
        glDisable(GL_BLEND);
    }

    // 3D Base Shadow Bevel (Bottom lip)
    drawFilledSmoothRect((float)x, (float)by, (float)w, (float)h, 12, baseR, baseG, baseB, 1.0f);

    // 3D Button Body (Slightly raised above base)
    drawFilledSmoothRect((float)x, (float)(by + 4), (float)w, (float)(h - 4), 11, bodyR, bodyG, bodyB, 1.0f);

    // Specular Highlight Crest Line along top
    drawSmoothRectOutline((float)x, (float)(by + 4), (float)w, (float)(h - 4), 11, topR, topG, topB, 0.85f, 1.5f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(topR, topG, topB, 0.50f);
    iLine(x + 12, by + h - 2, x + w - 12, by + h - 2);
    glDisable(GL_BLEND);

    // Centered Typography with Crisp Drop-Shadow
    int textLen = (int)strlen(text);
    int txtX = x + (w - textLen * 9) / 2;
    int txtY = by + (h / 2) - 6;

    // Shadow
    iSetColor(15, 23, 42);
    iText(txtX + 1, txtY - 1, (char*)text, GLUT_BITMAP_HELVETICA_18);
    iSetColor(txtR, txtG, txtB);
    iText(txtX, txtY, (char*)text, GLUT_BITMAP_HELVETICA_18);
}

/* -------------------- 3D ORNATE MASTER SKELETON KEY -------------------- */
void draw3DKey(int cx, int cy, double scale = 1.0)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Soft drop shadow
    glColor4f(0.04f, 0.06f, 0.10f, 0.45f);
    iFilledCircle(cx - 10, cy + 8, (int)(11 * scale));
    iFilledRectangle(cx - 5, cy - 4, (int)(28 * scale), (int)(6 * scale));

    // Outer Burnished Bow Rim
    iSetColor(146, 64, 14); // #92400e
    iFilledCircle(cx - 12, cy + 10, (int)(13 * scale));
    // Gold Bevel
    iSetColor(245, 158, 11); // #f59e0b
    iFilledCircle(cx - 12, cy + 11, (int)(11 * scale));
    // Bright Gold Face
    iSetColor(251, 191, 36); // #fbbf24
    iFilledCircle(cx - 12, cy + 11, (int)(9 * scale));
    // Core Keyhole / Hollow Center
    iSetColor(15, 23, 42); // #0f172a
    iFilledCircle(cx - 12, cy + 11, (int)(4 * scale));
    // Top clover lobed nodes
    iSetColor(254, 240, 138);
    iFilledCircle(cx - 12, cy + 20, (int)(3 * scale));
    iFilledCircle(cx - 22, cy + 10, (int)(3 * scale));

    // Key Shaft
    iSetColor(146, 64, 14);
    iFilledRectangle(cx - 2, cy - 2, (int)(26 * scale), (int)(6 * scale));
    iSetColor(245, 158, 11);
    iFilledRectangle(cx - 1, cy - 1, (int)(24 * scale), (int)(4 * scale));
    // Specular shine line
    iSetColor(255, 255, 255);
    iLine(cx, cy + 2, cx + (int)(20 * scale), cy + 2);

    // Key Wards / Stepped Bit
    iSetColor(146, 64, 14);
    iFilledRectangle(cx + (int)(12 * scale), cy - (int)(10 * scale), (int)(5 * scale), (int)(10 * scale));
    iFilledRectangle(cx + (int)(19 * scale), cy - (int)(14 * scale), (int)(5 * scale), (int)(14 * scale));
    iSetColor(251, 191, 36);
    iFilledRectangle(cx + (int)(13 * scale), cy - (int)(9 * scale), (int)(3 * scale), (int)(9 * scale));
    iFilledRectangle(cx + (int)(20 * scale), cy - (int)(13 * scale), (int)(3 * scale), (int)(13 * scale));

    // Specular glint
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(1.0f, 1.0f, 1.0f, 0.90f);
    iFilledCircle(cx - 16, cy + 14, 2);
    iLine(cx - 19, cy + 14, cx - 13, cy + 14);
    iLine(cx - 16, cy + 11, cx - 16, cy + 17);
    glDisable(GL_BLEND);
}

/* -------------------- 3D ARCANE SCROLL / HINT PASS -------------------- */
void draw3DScroll(int cx, int cy, int size = 26)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int hw = size;
    int hh = (int)(size * 1.15);

    // Drop shadow
    glColor4f(0.04f, 0.06f, 0.10f, 0.45f);
    iFilledRectangle(cx - hw + 2, cy - hh - 4, hw * 2, hh * 2);

    // Parchment Body (Warm Antique Vellum)
    iSetColor(217, 119, 6); // Edge border
    iFilledRectangle(cx - hw + 4, cy - hh + 6, (hw - 4) * 2, (hh - 6) * 2);
    iSetColor(254, 243, 199); // #fef3c7 main vellum
    iFilledRectangle(cx - hw + 6, cy - hh + 8, (hw - 6) * 2, (hh - 8) * 2);

    // Calligraphy Script Lines
    iSetColor(180, 83, 9);
    for (int ly = cy - hh + 14; ly <= cy + hh - 18; ly += 7)
    {
        iLine(cx - hw + 10, ly, cx + hw - 10, ly);
    }

    // Top Roller (3D Shaded Cylinder)
    iSetColor(120, 53, 15); // End caps
    iFilledRectangle(cx - hw - 3, cy + hh - 4, 4, 8);
    iFilledRectangle(cx + hw - 1, cy + hh - 4, 4, 8);
    iSetColor(245, 158, 11); // Gold roller rod
    iFilledRectangle(cx - hw, cy + hh - 3, hw * 2, 6);
    iSetColor(254, 240, 138); // Highlight crest
    iLine(cx - hw + 2, cy + hh + 1, cx + hw - 2, cy + hh + 1);

    // Bottom Roller (3D Shaded Cylinder)
    iSetColor(120, 53, 15);
    iFilledRectangle(cx - hw - 3, cy - hh - 4, 4, 8);
    iFilledRectangle(cx + hw - 1, cy - hh - 4, 4, 8);
    iSetColor(245, 158, 11);
    iFilledRectangle(cx - hw, cy - hh - 3, hw * 2, 6);
    iSetColor(254, 240, 138);
    iLine(cx - hw + 2, cy - hh + 1, cx + hw - 2, cy - hh + 1);

    // Center Royal Crimson Wax Seal with Gold Star
    iSetColor(153, 27, 27); // #991b1b
    iFilledCircle(cx, cy, 10);
    iSetColor(220, 38, 38); // #dc2626
    iFilledCircle(cx, cy + 1, 8);
    drawStarShape(cx, cy + 1, 5.0, 2.5, 251, 191, 36, false);

    // Arcane Cyan Ribbon Glint
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(0.22f, 0.74f, 0.97f, 0.60f);
    iCircle(cx, cy, 12);
    glDisable(GL_BLEND);
}

/* -------------------- 3D KNIGHT / AEGIS SHIELD -------------------- */
void draw3DShield(int cx, int cy, int size = 22)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int s = size;

    // Shield Polygon Points (Heater Shield Shape)
    double shX[7] = { (double)(cx - s), (double)(cx + s), (double)(cx + s), (double)(cx + s * 0.6), (double)cx, (double)(cx - s * 0.6), (double)(cx - s) };
    double shY[7] = { (double)(cy + s), (double)(cy + s), (double)(cy), (double)(cy - s * 0.7), (double)(cy - s * 1.2), (double)(cy - s * 0.7), (double)(cy) };

    // Drop Shadow
    double sdX[7], sdY[7];
    for (int i = 0; i < 7; i++) { sdX[i] = shX[i] + 3; sdY[i] = shY[i] - 4; }
    glColor4f(0.04f, 0.06f, 0.10f, 0.45f);
    iFilledPolygon(sdX, sdY, 7);

    // Outer Burnished Gold Rim
    glColor4f(0.70f, 0.33f, 0.04f, 1.0f);
    iFilledPolygon(shX, shY, 7);

    // Inner Bevel
    double inX[7], inY[7];
    for (int i = 0; i < 7; i++) { inX[i] = cx + (shX[i] - cx) * 0.88; inY[i] = cy + (shY[i] - cy) * 0.88; }
    glColor4f(0.96f, 0.62f, 0.07f, 1.0f);
    iFilledPolygon(inX, inY, 7);

    // Deep Royal Sapphire Field
    double fX[7], fY[7];
    for (int i = 0; i < 7; i++) { fX[i] = cx + (shX[i] - cx) * 0.76; fY[i] = cy + (shY[i] - cy) * 0.76; }
    glColor4f(0.12f, 0.23f, 0.54f, 1.0f); // #1e3a8a
    iFilledPolygon(fX, fY, 7);

    // Emblazoned Golden Heraldic Cross
    iSetColor(251, 191, 36);
    iFilledRectangle(cx - (int)(s * 0.14), cy - (int)(s * 0.65), (int)(s * 0.28), (int)(s * 1.3));
    iFilledRectangle(cx - (int)(s * 0.55), cy + (int)(s * 0.10), (int)(s * 1.1), (int)(s * 0.28));

    // Golden Rim Studs (Rivets)
    iSetColor(254, 240, 138);
    iFilledCircle(cx - s + 4, cy + s - 4, 2);
    iFilledCircle(cx + s - 4, cy + s - 4, 2);
    iFilledCircle(cx, cy + s - 3, 2);
    iFilledCircle(cx, cy - (int)(s * 0.95), 2);

    // Top-Left Specular Glint
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(1.0f, 1.0f, 1.0f, 0.75f);
    iLine(cx - s + 4, cy + s - 2, cx - 2, cy + s - 2);
    glDisable(GL_BLEND);
}

/* -------------------- 3D TRIPLE GEM CLUSTER -------------------- */
void draw3DGemCluster(int cx, int cy, int size = 14, double shinePulse = 1.0)
{
    glEnable(GL_BLEND);

    // Left Ruby Gem
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(0.89f, 0.15f, 0.45f, 0.35f);
    iFilledCircle(cx - (int)(size * 0.85), cy - 4, (int)(size * 1.2));
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int rx = cx - (int)(size * 0.85);
    int ry = cy - 4;
    int rs = (int)(size * 0.85);
    glColor4f(0.60f, 0.05f, 0.25f, 1.0f);
    iFilledCircle(rx, ry, rs);
    glColor4f(0.95f, 0.20f, 0.55f, 1.0f);
    iFilledCircle(rx - 1, ry + 1, rs - 2);
    glColor4f(1.0f, 0.70f, 0.85f, 1.0f);
    iLine(rx - rs / 2, ry + rs - 2, rx + rs / 2, ry + rs - 2);

    // Right Emerald Gem
    int ex = cx + (int)(size * 0.85);
    int ey = cy - 4;
    int es = (int)(size * 0.85);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(0.13f, 0.77f, 0.36f, 0.35f);
    iFilledCircle(ex, ey, (int)(size * 1.2));
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.04f, 0.40f, 0.18f, 1.0f);
    iFilledCircle(ex, ey, es);
    glColor4f(0.18f, 0.80f, 0.44f, 1.0f);
    iFilledCircle(ex - 1, ey + 1, es - 2);
    glColor4f(0.70f, 1.0f, 0.80f, 1.0f);
    iLine(ex - es / 2, ey + es - 2, ex + es / 2, ey + es - 2);

    // Center Large Diamond / Sapphire Gem
    draw3DGem(cx, cy + 4, size, shinePulse);
    glDisable(GL_BLEND);
}

/* -------------------- 3D LUXURY CURRENCY CAPSULE HUD -------------------- */
void draw3DCurrencyCapsule(int x, int y, int w, int h, int type, int amount)
{
    // type 0 = Gems (Cyan/Sapphire), type 1 = Coins (Gold)
    float rimR = (type == 0) ? 0.06f : 0.98f;
    float rimG = (type == 0) ? 0.70f : 0.78f;
    float rimB = (type == 0) ? 0.98f : 0.15f;

    // Drop Shadow
    drawFilledSmoothRect((float)(x + 2), (float)(y - 4), (float)w, (float)h, 14, 0.02f, 0.04f, 0.08f, 0.55f);

    // Outer Dark Titanium Capsule Body
    drawFilledSmoothRect((float)x, (float)y, (float)w, (float)h, 14, 0.10f, 0.14f, 0.22f, 0.95f);

    // Beveled Metallic Rim Outline
    drawSmoothRectOutline((float)x, (float)y, (float)w, (float)h, 14, rimR, rimG, rimB, 0.85f, 1.8f);

    // Inner Recessed Display Window
    drawFilledSmoothRect((float)(x + 36), (float)(y + 5), (float)(w - 68), (float)(h - 10), 8, 0.06f, 0.08f, 0.14f, 0.90f);

    // Render 3D Icon on Left
    if (type == 0)
        draw3DGem(x + 19, y + h / 2, 12, sin(globalAnimTimer * 0.1) * 0.2 + 0.8);
    else
        draw3DCoin(x + 19, y + h / 2, 12, globalAnimTimer * 0.2);

    // Amount Typography
    char amtStr[32];
    sprintf(amtStr, "%d", amount);
    int txtLen = (int)strlen(amtStr);
    int tx = x + 38 + (w - 74 - txtLen * 9) / 2;
    int ty = y + h / 2 - 6;

    // Drop Shadow
    iSetColor(15, 23, 42);
    iText(tx + 1, ty - 1, amtStr, GLUT_BITMAP_HELVETICA_18);
    // Core Color
    if (type == 0) iSetColor(224, 242, 254); // Ice Cyan
    else iSetColor(254, 240, 138);           // Bright Gold
    iText(tx, ty, amtStr, GLUT_BITMAP_HELVETICA_18);

    // 3D Small Plus [+] Button on Right
    int pX = x + w - 26, pY = y + 7, pW = 20, pH = h - 14;
    float btnR = (type == 0) ? 0.13f : 0.96f;
    float btnG = (type == 0) ? 0.65f : 0.62f;
    float btnB = (type == 0) ? 0.30f : 0.07f;
    drawFilledSmoothRect((float)pX, (float)pY, (float)pW, (float)pH, 6, btnR, btnG, btnB, 1.0f);
    drawSmoothRectOutline((float)pX, (float)pY, (float)pW, (float)pH, 6, 1.0f, 1.0f, 1.0f, 0.70f, 1.0f);
    iSetColor(255, 255, 255);
    iText(pX + 5, pY + 4, (char*)"+", GLUT_BITMAP_HELVETICA_18);
}

/* -------------------- 3D LUXURY EVENT BANNER CHASSIS -------------------- */
void draw3DBannerChassis(int x, int y, int w, int h, int texID)
{
    // 1. Soft Ambient Drop-Shadow
    drawFilledSmoothRect((float)(x + 4), (float)(y - 8), (float)w, (float)h, 18, 0.02f, 0.03f, 0.06f, 0.65f);

    // 2. Heavy Titanium Plaque Chassis Frame
    drawFilledSmoothRect((float)(x - 4), (float)(y - 4), (float)(w + 8), (float)(h + 8), 16, 0.08f, 0.11f, 0.18f, 0.98f);
    drawSmoothRectOutline((float)(x - 4), (float)(y - 4), (float)(w + 8), (float)(h + 8), 16, 0.22f, 0.30f, 0.44f, 0.80f, 2.0f);

    // 3. Banner Artwork with Subtle Inner Inset
    if (texID != -1)
    {
        iShowImageAlpha(x, y, w, h, texID, 1.0f);
    }
    else
    {
        drawFilledSmoothRect((float)x, (float)y, (float)w, (float)h, 12, 0.15f, 0.20f, 0.35f, 1.0f);
    }

    // 4. Shimmering Gold & Cyan Dual Bevel Outline
    float pulse = (float)(sin(globalAnimTimer * 0.08) * 0.15 + 0.85);
    drawSmoothRectOutline((float)x, (float)y, (float)w, (float)h, 12, 0.98f * pulse, 0.82f * pulse, 0.25f, 1.0f, 2.5f);

    // 5. Four 3D Cyber-Gold Corner Brackets
    int bSize = 22;
    int bThick = 4;
    // Top-Left
    iSetColor(251, 191, 36);
    iFilledRectangle(x - 2, y + h - bSize, bThick, bSize + 2);
    iFilledRectangle(x - 2, y + h - bThick, bSize + 2, bThick);
    iSetColor(56, 189, 248); // Cyan rivet
    iFilledCircle(x + 5, y + h - 5, 2);

    // Top-Right
    iSetColor(251, 191, 36);
    iFilledRectangle(x + w - bThick + 2, y + h - bSize, bThick, bSize + 2);
    iFilledRectangle(x + w - bSize, y + h - bThick, bSize + 2, bThick);
    iSetColor(56, 189, 248);
    iFilledCircle(x + w - 5, y + h - 5, 2);

    // Bottom-Left
    iSetColor(251, 191, 36);
    iFilledRectangle(x - 2, y - 2, bThick, bSize + 2);
    iFilledRectangle(x - 2, y - 2, bSize + 2, bThick);
    iSetColor(56, 189, 248);
    iFilledCircle(x + 5, y + 5, 2);

    // Bottom-Right
    iSetColor(251, 191, 36);
    iFilledRectangle(x + w - bThick + 2, y - 2, bThick, bSize + 2);
    iFilledRectangle(x + w - bSize, y - 2, bSize + 2, bThick);
    iSetColor(56, 189, 248);
    iFilledCircle(x + w - 5, y + 5, 2);

    // 6. Top Metallic Ribbon Plaque
    int ribW = 420;
    int ribH = 30;
    int ribX = x + (w - ribW) / 2;
    int ribY = y + h - 14;

    // Ribbon drop shadow
    drawFilledSmoothRect((float)(ribX + 2), (float)(ribY - 3), (float)ribW, (float)ribH, 10, 0.02f, 0.03f, 0.06f, 0.60f);
    // Ribbon body (Deep Crimson & Burnished Gold)
    drawFilledSmoothRect((float)ribX, (float)ribY, (float)ribW, (float)ribH, 10, 0.88f, 0.22f, 0.18f, 0.98f);
    drawSmoothRectOutline((float)ribX, (float)ribY, (float)ribW, (float)ribH, 10, 0.98f, 0.82f, 0.25f, 1.0f, 2.0f);

    // Ribbon Jewels on sides
    draw3DGem(ribX + 16, ribY + ribH / 2, 7, 1.0);
    draw3DGem(ribX + ribW - 16, ribY + ribH / 2, 7, 1.0);

    // Ribbon text
    const char* ribTxt = "★ SPECIAL COLLABORATION EVENT ★";
    int rLen = (int)strlen(ribTxt);
    int rx = ribX + (ribW - rLen * 9) / 2;
    drawSharpText(rx, ribY + 8, ribTxt, GLUT_BITMAP_HELVETICA_12, 254, 240, 138);

    // 7. Bottom-Left Status Badge: "● LIVE COLLABORATION"
    int stW = 160, stH = 24;
    int stX = x + 16, stY = y + 12;
    drawFilledSmoothRect((float)stX, (float)stY, (float)stW, (float)stH, 6, 0.08f, 0.11f, 0.18f, 0.85f);
    drawSmoothRectOutline((float)stX, (float)stY, (float)stW, (float)stH, 6, 0.13f, 0.77f, 0.36f, 0.80f, 1.2f);
    // Pulsing Green LED
    float ledPulse = (float)(sin(globalAnimTimer * 0.18) * 0.3 + 0.7);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(0.13f, 0.77f, 0.36f, ledPulse);
    iFilledCircle(stX + 14, stY + stH / 2, 4);
    glDisable(GL_BLEND);
    drawSharpText(stX + 26, stY + 6, "LIVE COLLABORATION", GLUT_BITMAP_HELVETICA_10, 240, 253, 244);

    // 8. Sparkle Particles across banner
    if (rand() % 4 == 0)
    {
        double spx = x + 10 + (rand() % (w - 20));
        double spy = y + 10 + (rand() % (h - 20));
        spawnParticle(spx, spy, ((rand() % 20) - 10) / 20.0, 0.5, 251, 191, 36, 2.5, 16, 1);
    }
}

void drawToastNotification()
{
    if (toastTimer <= 0) return;
    toastTimer--;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float alpha = (toastTimer < 20) ? (toastTimer / 20.0f) : 0.92f;
    int tw = (int)strlen(toastMessage) * 10 + 40;
    int tx = (SCREEN_WIDTH - tw) / 2;
    int ty = 80;
    drawFilledSmoothRect((float)tx, (float)ty, (float)tw, 36.0f, 12, 0.10f, 0.12f, 0.18f, alpha);
    drawSmoothRectOutline((float)tx, (float)ty, (float)tw, 36.0f, 12, 0.98f, 0.82f, 0.25f, alpha, 1.5f);
    drawSharpText(tx + 20, ty + 12, toastMessage, GLUT_BITMAP_HELVETICA_12, 255, 255, 255);
    glDisable(GL_BLEND);
}
