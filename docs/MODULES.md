# Castle Escape (Tricky Castle) - Modular Architecture & Team Work Distribution

**Project Title:** Castle Escape: A 2D Puzzle Adventure Game Using iGraphics  
**Course:** Computer Graphics Lab  
**Institution:** Ahsanullah University of Science and Technology (AUST)  
**Lead Game Designer, Game Theory & Graphics Architect:** **Ovijit Sharma** (Student ID: `00725105101134`)  

---

## 1. Team Work Distribution & Coder Attribution

The project implementation is mapped directly to the approved **Computer Graphics Project Proposal**, showcasing **Ovijit Sharma** as the Lead Game Theorist, Game Graphics Designer, Art Director & Physics Architect, alongside significant code contributions from all teammates:

| Member Name | Student ID | Proposal Domain | Assigned Header Files / Modules | Line Count | Key Features & Implementation Scope |
|---|---|---|---|---|---|
| **Ovijit Sharma** | **00725105101134** | **Game Theory, Game Graphics & Look, Physics, Player Controller & Direction** | [`CharacterRender.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/CharacterRender.h)<br/>[`RenderUtils.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/RenderUtils.h)<br/>[`GameLogic.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/GameLogic.h)<br/>[`InputHandler.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/InputHandler.h)<br/>[`GameDefines.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/GameDefines.h) *(Lead Theorist)*<br/>[`iMain.cpp`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/iMain.cpp) *(Game Director)* | **~3,800+ Lines** *(Lead Game Designer & Art Director)* | • **Game Theory & System Design**: Conceptualized the complete tricky dungeon puzzle-platformer theory, game state machine flow, and 6 Chibi Hero archetypes with balanced perks and stats.<br/>• **Game Graphics & Visual Look**: Nocturnal castle color palette, procedural 2D vector primitives, gradient fills, dark vignette lighting, dynamic glowing text (`drawGlowingText`), drop shadows (`drawSharpText`), and ambient torch particle simulation.<br/>• **Character Presentation & Animations**: Complete sprite look of William, CR7, Neymar, Elena, Thorgar, and RenoSir. Procedural idle breathing sway, articulated run stride, jump stretching, facing flips, and upside-down inverted gravity walking.<br/>• **60 FPS Physics Simulation**: Fixed update cycle, acceleration, platform friction, parabolic jump curves, solid tile & moving platform collision detection.<br/>• **Player Controller & Input**: Mouse tracking (`iMouseMove`), click dispatch (`iMouseClick`), keyboard mapping (`iKeyboard`), and on-screen touch button controls. |
| **Maheed Abrar** | **00725105101140** | **Systems Architect, Mini-Game Lead, Persistence & Debugging** | [`PenaltyGame.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/PenaltyGame.h)<br/>[`SaveSystem.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/SaveSystem.h)<br/>[`AudioSystem.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/AudioSystem.h)<br/>[`GameDefines.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/GameDefines.h) *(Diagnostics)*<br/>[`iMain.cpp`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/iMain.cpp) *(Lead Integration)* | **2,434 Lines** | • **Penalty Derby Mini-Game (~1,593 lines)**: Standalone football shootout, crosshair aiming, power gauge charging, 3D parabolic ball trajectory, Messi goalkeeper AI, net ripple physics, cinematic letterbox, and SIUUU celebration sequence.<br/>• **Save/Load Persistence**: Binary file serialization (`tricky_castle_save.dat`), star ratings, unlock records, corruption recovery fallbacks.<br/>• **Audio Engine**: Windows MCI background music streaming, loop handling, SFX playback, audio mute toggle.<br/>• **Engine Core & Testing**: System initialization, automated capture test harness (`--autocapture`), OpenGL screenshot exporter. |
| **Nabeel Saad Borno** | **00725105101135** | **UI, Score System, Menus & Graphic Elements** | [`MenuScreens.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/MenuScreens.h)<br/>[`RenderUtils.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/RenderUtils.h) *(UI Co-Dev)* | **1,362+ Lines** | • **User Interface & Menus (~1,362 lines)**: 3D World Select Carousel, Costumes/Hero Selection Carousel (6 champion cards), 4 Chapter Map selection grids, 7-day login reward modal, RenoSir collab modal, Settings & Pause dialogs.<br/>• **Score & Graphic Elements**: Star rating badges, coin/gem counters, toast popups with ease-in/out timers, and modal dialog frames. |
| **Shahriar Rythm** | **00725105101132** | **Level Design, Traps & Dungeon Props** | [`Levels.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/Levels.h)<br/>[`WorldObjects.h`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/WorldObjects.h) | **1,127 Lines** | • **Level Catalog & Loader (~601 lines)**: 24 puzzle floors across Chapters 1-4, puzzle titles, room hints, instant solutions, room entity spawner (`loadLevel`).<br/>• **Trap System & Dungeon Props (~526 lines)**: 3D red buttons, torches with animated fire, ceiling pull-chains, levers, exit doors (wooden, iron-barred, locked), climbable ivy, pushable crates, gravity pads, drawbridges. |

---

## 2. High-Level Architecture & Dependency Hierarchy

```mermaid
graph TD
    subgraph Game Theory, Graphics & Physics [Ovijit Sharma]
        GD[GameDefines.h<br/>Game Theory & State Machine]
        RU[RenderUtils.h<br/>Aesthetics, Glow & Particles]
        CR[CharacterRender.h<br/>Chibi Hero Graphics & Strides]
        GL[GameLogic.h<br/>60 FPS Physics & Collision]
        IH[InputHandler.h<br/>Player Controller & Input]
    end

    subgraph Systems and Mini-Game [Maheed Abrar]
        AS[AudioSystem.h<br/>MCI BGM & SFX Engine]
        SS[SaveSystem.h<br/>Binary Save/Load System]
        PG[PenaltyGame.h<br/>CR7 vs Messi Mini-Game]
    end

    subgraph Level Design and Traps [Shahriar Rythm]
        WO[WorldObjects.h<br/>Dungeon Props & Traps]
        LV[Levels.h<br/>24 Floor Puzzle Catalog]
    end

    subgraph UI and Menus [Nabeel Saad Borno]
        MS[MenuScreens.h<br/>World Carousel & Modals]
    end

    subgraph Application Bootstrap [Ovijit Sharma & Maheed Abrar]
        MAIN[iMain.cpp<br/>Display Loop & System Setup]
    end

    GD --> AS
    GD --> SS
    GD --> RU

    RU --> WO
    RU --> CR

    WO --> LV
    SS --> LV
    AS --> LV

    CR --> PG
    RU --> PG
    AS --> PG
    SS --> PG

    CR --> MS
    RU --> MS
    AS --> MS
    SS --> MS

    LV --> GL
    PG --> GL
    AS --> GL
    SS --> GL

    GL --> IH
    MS --> IH
    LV --> IH
    PG --> IH

    IH --> MAIN
    MS --> MAIN
    PG --> MAIN
    CR --> MAIN
    WO --> MAIN
    RU --> MAIN
```

---

## 3. Visual Studio Solution Explorer Categorization

In both [`demo.vcxproj`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/demo.vcxproj) and [`TorchboundKeep.vcxproj`](file:///c:/Users/USER/.gemini/antigravity-ide/scratch/castle_extracted/CastleTrapVS2013/demo/TorchboundKeep.vcxproj), the Solution Explorer filters display:

```
Solution Explorer
└── Header Files
    ├── 1. Game Theory, Graphics & Physics [Ovijit Sharma]
    │   ├── CharacterRender.h
    │   ├── RenderUtils.h
    │   ├── GameLogic.h
    │   └── InputHandler.h
    ├── 2. Core Systems, Audio, Save & Mini-Game [Maheed Abrar]
    │   ├── GameDefines.h
    │   ├── AudioSystem.h
    │   ├── SaveSystem.h
    │   └── PenaltyGame.h
    ├── 3. Level Design, Traps & Dungeon World [Shahriar Rythm]
    │   ├── WorldObjects.h
    │   └── Levels.h
    ├── 4. UI, Menus & Score System [Nabeel Saad Borno]
    │   └── MenuScreens.h
    └── 5. Third-Party & Framework
        ├── iGraphics.h
        ├── glut.h
        ├── glaux.h
        ├── stb_image.h
        └── bitmap_loader.h
```

---

## 4. Git Sharing Best Practices

To share this repository cleanly on GitHub / GitLab without bloated binaries:

### Files Tracked by Git:
- Source code: all `.h` and `.cpp` files.
- Visual Studio files: `.sln`, `.vcxproj`, `.vcxproj.filters`.
- Assets: `Images/`, `Audios/`, `GLUT32.DLL`, OpenGL `.lib` files.
- Scripts & Documentation: `extract_headers3.ps1`, `MODULES.md`, `.gitignore`.

### Files Ignored via `.gitignore`:
- Oversized binaries: `ffmpeg.exe` (164MB), `ffprobe.exe` (164MB), `yt-dlp.exe` (17MB).
- Visual Studio database caches: `*.sdf`, `*.opensdf`, `*.suo`, `.vs/`, `ipch/`, `*.user`.
- Compiled build folders: `Debug/`, `Release/`, `*.obj`, `*.pdb`, `*.ilk`.
- Raw audio/video captures: `tricky_castle_audio.m4a`, `frame*.png`, `screenshot_*.png`.
- Local player save: `tricky_castle_save.dat`.

---

## 5. How to Build & Run

1. **Visual Studio**: Open `TorchboundKeep.sln`, select `Debug | Win32`, press **F5** to run with debugging (or **Ctrl+F5** without debugging).
2. **Command Line**:
   ```cmd
   "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" TorchboundKeep.sln /p:Configuration=Debug /p:Platform=Win32
   ```
3. **Automated Diagnostic Run**:
   ```powershell
   .\demo.exe --autocapture
   ```
