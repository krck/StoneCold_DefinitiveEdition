StoneCold (2D Game and Engine)
==============================

# Table of Contents  
1. [About](#about)
2. [Game Design Document](#gdd)
3. [Technical Description](#technical)
4. [Copyright and Attribution Notices](#copyr)
5. [Work Items](#work)
6. [Development Setup](#devsetup)

<a name="about"/>

# 1. About

Another one. Lost count of all the 2D/3D SDL2, SFML or "pure" OpenGL based Game and Engine Projects i started. But maybe this one is different ... may this one gets finished. lol.

<a name="gdd"/>

# 2. Game Design Document

### 2.1 Project Description
 
StoneCold will be a Buzzword hell. Its a 2D, top-down, rouge-like, tile-based, bullet-hell RPG and comes with its own SFML based Engine. The concept is heavily inspired by games like Vampire Survivors (Gameplay), Diablo 2 (RPG Elements), Nuclear Throne (Map generation) and many more.

### 2.2 Story, Characters and Theme

The main character is a dwarf called Henry and lives in the small village Boulder, by the Mountain. Many years ago, a strange comet impacted nearby and shattered its core all over the Dwarven kingdom. A special metal was found in those fragments, mined and forged by the dwarves. This special metal has great empowering abilities once forged, but many of the shattered fragments are still out there. Slowly corrupting the land around them and spawning strange creatures that now threaten the dwarven kingdom.

### 2.3 Progression

The player starts out in a town-hub, to which he will return to after every level. Here the player can change class and respec freely. The player progresses through a series of zones (grasslands, highlands, desert, arctic, castles, ...). Each zone has 5 randomly generated levels and ends with a boss fight. Each level spawns a constant number of different enemies, increasing in difficulty and amount. The goal is to survive these waves and destroy all corrupted comet fragments on the map. Once all zones are traversed Henry reaches the biggest of the raw comet-fragments and fights the final boss, to cleanse the lands for good.

After that an "endless-mode" will be unlocked in town, to level and grind further.

### 2.4 Gameplay and User Skills

- Keyboard and Mouse input
- Navigating different map types and finding fragments
- Long and short-term resource management and the fight against RNG
- Depth based on actuals "builds" and "combos"

### 2.5 Game Mechanics

- 4 Different classes (Berserker, Crusader, Battle Mage and Gunslinger)
- RNG Powerups/Pickups in form of Ore-Fragments to flat increase Player Power (Lost on Death or finished Level)
- Stat and skill management on Levelup - Skill Tree for each class (Kept after Death or finished Level)
- Special Skills (on cooldown)
- Healing potion (on cooldown)

### 2.6 Progression, Challenge and Losing

- Defeat the waves of enemies, get XP, Level up
- Each level allows to advance a specific skill
- Enemy difficulty increases slow during "story" and fast during "endless" mode
If all health is lost, the level will be reset and has to be started from the beginning (Zone progression stays).

### 2.7 Art Style and Music

2D Pixel-Art using the dawnbringer color palette. Most sprites are aimed to be 32x32 (pixels in image) and then displayed with a three-times scaling 96x96 (pixels on screen). Some are hand drawn but most of the characters, enemies, etc. will be open source artworks by various artists (see below).

<a name="technical"/>

# 3. Technical Description

### 3.1 Language and libraries

- C++ 17 (CMake, VS Code)
- [SFML 2.5.1](https://www.sfml-dev.org/) : Cross-platform Graphics and IO library
- [ini parser](https://github.com/SSARCandy/ini-cpp) : Simple .ini file parser by Andy Hsu (SSARCandy)
- More dependencies should be avoided at all cost

### 3.2 Architecture and Code Structure

The code is written in Modern C++ (11,14,17 and beyond) and in a object oriented manner. Simplicity (or rather: avoiding complexity) is a main goal. Well. Fingers crossed.

Engine reusability, common Render-API, etc. are no factor when it comes to the core design and left to SFML as much as possible. The result is a thigh coupled structure composed of four projects, that revolve around games resource management, game object creation, game state management, the Entity-Component-Sytem and feeding it all to SFML:
- <b>StoneCold.Base:</b> Basic Settings, common Types and Enums, Math and Exception classes
- <b>StoneCold.Engine:</b> Entity-Component-System, Game-State-Management and Event handling
- <b>StoneCold.Game:</b> Window creation, Levels/NPCs/Menu Setup, Manager init and main loop
- <b>StoneCold.Resources:</b> Resource management with Lifetime checks (loading and unloading)
- <b>StoneCold.Tests:</b> Unit Tests

The Engines core building blocks are the Entity–component–system (ECS) and the Game-State management. 

<a name="copyr"/>

# 4. Copyright and Attribution Notices

Some of the Textures are hand drawn (thanks MS Paint and Gimp) but all the nice looking ones are created by actual Artists:

- DawnBringer Color-Palette by Richard Fhager [link to his pixeljoint](http://pixeljoint.com/p/23821.htm)
- Dwarf Sprites by Elthen (Ahmet Avci) [link to his patreon](https://www.patreon.com/elthen)
- Skeleton Sprites by Jesse Munguia [link to his homepage](https://jessemunguia.com/)
- Mountain Background by NotTandy [link to his pixelart](https://www.pixilart.com/nottandy)
- UI Textures (RPG Pack) by Kenney Vleugels [link to his art](https://www.kenney.nl)
- Font Crom by russh (Russell Herschler) [link to his homepage](http://www.dragonfang.com/)
- Font OldeDethek by Pixel Sagas [link to the homepage](http://www.pixelsagas.com/)

<a name="work"/>

# 5. Work Items

### 5.1 Current tasks

- [ ] ...

### 5.2 Backlog, cleanup and housekeeping

- [ ] ...

### 5.3 Known Bugs

- [ ] ...

### 5.4 Future features

- Add different Map-Generation algorithms (Rooms/Indoor, Caves)
- Add Portals and automatic Level-Loading (maybe Loading-Screen or transition effect)
- Add Player GUI (Lifebar, Action-Bar, Skill/Stat Window)
- Add Pickups and Buffs (Gold, Items, Chests)
- Add Controller Support (with automatic check if Controller is available)
- Add a basic Options Menu and Save/Load functionality 
- Add Sound and Music

<a name="devsetup"/>

# 6. Development Setup

### 6.1 BASIC SETUP with VS Code (on Windows)

Install VS Code
- Add the "C++ Extension Package" (for IntelliSense, CMake tools, Better Syntax, Themes, etc.)

Install [git](https://git-scm.com/download/win)
- Optional: Install a "git GUI Client" - GitKraken would be my recommendation

Install the [VS Build Tools](https://visualstudio.microsoft.com/de/downloads/)
- Scroll down on the WebPage and select "Tools for Visual Studio 2022" -> "Buildtools for Visual Studio 2022" -> "Download"
- On installation select "C++ Desktop" and from the right side-bar also add CMake and Clang for Windows
- Alternative: Install CMake and LLVM manually, but "C++ Desktop" is mandatory

Install [MinGw](https://www.msys2.org/) and follow this [tutorial](https://code.visualstudio.com/docs/cpp/config-mingw)
- Update package database: $pacman -Syu
- Start MSYS2 MSYS again and run the same command again to finish the installation
- Install the full GCC and GDB toolchain: $pacman -S --needed base-devel mingw-w64-x86_64-toolchain

Start Menu Search: "Edit environment variables" and open the program
- Select "Path" and click "Edit..."
- Select "New" and add: "C:\msys64\mingw64\bin" (if installed at the default location)
- Select "New" and add: "C:\Program Files\Git\bin" (if installed at the default location)
- Select "New" and add: "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\Llvm\bin" (if installed at the default location)
- Select "New" and add: "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
- Select "Ok" to save the env paths

### 6.2 Test the Installation

First open terminal and enter: "git", "g++", "clang++", "gdb", "cmake", ... All programs should be available now in any console. Then test a simple "Hello World"
- Write C++ "Hello World" main.cpp, write basic "CMakeLists.txt"
- Call CMake and create "MinGW Makefiles": $cmake -G "MinGW Makefiles"
- Call Make to create the exe: $mingw32-make
- Test the exe: $ .\exe-name.exe

### 6.3 Setup VS Code Tasks and Launch

Add a VS Code "Task" .json file to configure the DEBUG and RELEASE builds.
Example task below, to execute CMake in the DEBUG folder and then run Make to create the DEBUG .exe
- "label": "BUILD DEBUG (CMake + Make)",
- "type": "shell",
- "command": "cmake -G 'MinGW Makefiles' -B build/Debug -DCMAKE_BUILD_TYPE=Debug ; echo '' ; mingw32-make -C build/Debug",
- "problemMatcher": ["$gcc"]
