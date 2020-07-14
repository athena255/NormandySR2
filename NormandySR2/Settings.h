#pragma once
#define ENGINE_DLL L"engine.dll"
#define CLIENT_DLL L"client.dll"

#define TRIGGER_DELAY 150 // 150 ms delay +/- jitter
#define TRIGGER_JITTER 20 // 20 % jitter
#define SHOOT_DURATION 20 // 20 ms

#define MIN_FOV 22.0f
// When health is lower than this, Aimbot will not require the crosshairs to mark targets
#define MIN_HEALTH 50

#define TOGGLE_AIMBOT VK_UP
#define TOGGLE_WALLHACK VK_DOWN
#define TOGGLE_AUTOSTRAFE VK_RIGHT
#define TOGGLE_TRIGGER VK_LEFT
#define PANIC VK_END
