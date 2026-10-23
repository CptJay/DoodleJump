Project Advanced Programming 2023-2024
=======================================
**Note:** This is a re-upload of a project originally developed in the
AP-Lab-Sessions organization in 2024. The original repository couldn't be made
public due to organization settings, so the code is republished here without
the original commit history.

Name: Yassir Chebaa Amimou  
Student number: 20173674  


# Features

### Sprites (In case of missing sprites, the program will still run with SFML generated shapes)
- [x] Doodle Jump Player
- [x] Bonus
  - [x] Boost 
- [x] Platform (Generated through SFML)
  - [x] Static Platform (Green)
  - [x] Vertical Platform (Yellow)
  - [x] Horizontal Platform (Blue)
  - [x] Temporary Platform (White)
- [x] Background Tiles (Generated through SFML) (Can choose how many tiles to generate resulting in bigger or smaller backgroundtiles)

### Movement
- [x] Doodle Jump Player
  - [x] Left (Arrow Left)
  - [x] Right (Arrow Right)

### Game Mechanics
- [x] Doodle Jump Player
  - [x] Jump
  - [x] Fall (Gravity)
  - [x] Collision with Platforms
  - [x] Collision with Bonus
  - [x] Game Over when falling off the screen + Shows score

### Extra Features
- [x] Score
- [x] Going through wall, the player will appear on the opposite side + randomized color of the player :)
- [ ] Shake effect when hitting a certain score (half implemented)

### Not According to assignment / Bugs
- The bonus do not spawn on top of the platforms. They spawn randomly independantly. (Read this feature too late, but shouldn't be too hard to implement due to modular design choice)
- When starting the game for the **first** time, sometimes it happens that the window's position isn't set correctly (even though it should). This can be fixed by starting the game again. 
