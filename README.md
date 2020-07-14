# NormandySR2
Internal CSGO Cheat (Undetected)

- Does not create a new thread in the game process
- Hooks CreateMove in IClientShared and executes enabled cheats everytime this function is called
- Exiting the cheat amounts to restoring the old CreateMove function
- valve_sdk headers are modified from CSGOSimple (https://github.com/spirthack/CSGOSimple/tree/master/CSGOSimple)

Keybindings
------------
Key bindings can be changed in Settings.h

Features
---------
- Silent Aim (Up arrow)
- Wallhack (Down arrow)
- Autostrafe (Right arrow)
- Trigger bot (Left arrow) -- likely to be detected
- Exit Cheat (End)

Silent Aim
----------
The target enemy is selected based on the last enemy that the player's crosshairs touched.

If the player's health is below MIN_HEALTH (default is 50), then the aimbot will check whether the current target is visible.
If the current target is not visible, then the current target will be updated to the closest visible enemy in our FOV.
The aimbot only executes when the user presses the right or left mouse buttons. 

Wallhack
---------
Allies are highlighted in blue.
Enemies are highligted in pink/purple.
Visible enemies will glow brighter than invisible enemies. 
If SilentAim is enabled, then the currently targeted enemy will glow red rather than pink/purple
