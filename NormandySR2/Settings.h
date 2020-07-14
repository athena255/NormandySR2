#pragma once
// Name of the engine module
#define ENGINE_DLL L"engine.dll"
// Name of the client module
#define CLIENT_DLL L"client.dll"

// The minimum acceptable FOV when Aimbot searches for a visible entity
#define MIN_FOV 22.0f

// When health is lower than this, Aimbot will not require the crosshairs to mark targets
#define MIN_HEALTH 50

// Key bindings
#define TOGGLE_AIMBOT VK_UP
#define TOGGLE_WALLHACK VK_DOWN
#define TOGGLE_AUTOSTRAFE VK_RIGHT
#define TOGGLE_TRIGGER VK_LEFT
#define PANIC VK_END
