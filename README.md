# alpha1
A C++ modloader for Unity/IL2CPP games.

## Installation
### Installing alpha1
Download one of the release artefacts from the [releases]() section and extract into the intended game's installation directory. Tested Unity versions: `2021.3.5`

Once installed, run the game once before attempting to install any mods.

### Installing mods
Place any mod DLL files in the `mods` folder in the game's installation.

Also place any required libraries that the mod needs in the `libs` folder, also located in the game's installation.

## Overview
All folders mentioned are relative to the game's installation directory/folder.

* `/mods/` - Place mods here, these are what actually do stuff in the game.
* `/libs/` - Mods may depend on additional libraries, these are always loaded first. Any libraries should be placed here.
* `/alpha1/` - The modloader, core dependencies and logs are stored here.
* `/alpha1/logs/` - The modloader saves logs here, they are named after when they were last edited. `latest.log` is always the most recent log created.
* `/user_data/` - This folder is intended to be used by mods for containing files that mods may use, such as configuration files, assets ...etc.

## FAQ
Q: Is this compatible with other modloaders like MelonLoader or BepInEx? <br>
A: No. Unfortunately it is not possible for other modloaders and alpha1 to be function at the same time, nor load mods for eachother.

Q: When I install alpha1, nothing happens. <br>
A: It is likely you are trying to use alpha1 on an incompatible game, alpha1 only works on IL2CPP Unity games. If you are attempting to use this with a Unity game and it is not loading it is likely either not an IL2CPP game, or uses an unsupported version of Unity.

Q: A fatal error message box appears and forces the game to quit, how do I fix this? <br>
A: Those message boxes only appear if for whatever reason, alpha1 cannot perform any operations that are required for it to fully function. Common causes of these errors are usually due to insufficient permissions, ensure that the game is not installed in any protected folders. If the issue persists, try reinstalling alpha1. If the error still occurs, create and [issue]() detailing the target game, any relevant logs and any additional relevant steps to reproduce the error.

## Creating Mods
For information regarding developing your own mods, please see the [wiki]() for guides and documentation.
