# Doom Nukem

A 2.5D raycasting engine inspired by Doom and Duke Nukem 3D. The project consists of 2 executables: doom-nukem (the game) and editor for creating maps.

With the engine, it is possible to create rather complex worlds featuring polygonal areas, detailed textures, objects, decorations, slopes, lighting, enemies and custom interactactions.

For rendering, audio and event handling we used cross-platform SDL2 library. SDL2 source code is included unmodified.

## Editor
* Sectors
	* Modify elevations, shapes, heights, light, textures, floor and ceiling slopes
* Portal linking
	* Link sectors to each other automatically or manually to create continuous world
* Decorations
	* Add or edit wall decorations
* Interactions / events
	* Modify interactions triggerable by:
		* entering a sector
		* interacting with a decoration
		* killing an enemy
		* picking up a pickable object
	* Interactions can trigger events which can:
		* Change sectors floor or ceiling height (or both)
		* Change sectors lighting level
		* Trigger a text popup
		* Play a sound
		* End level / Load new level
	* Interactions can also require player to have a key to be able to trigger the event
* Objects
	* Add or edit objects and enemies
	* Objects can also have interactions that will trigger events
* World/Level constants
	* Player starting health, armor and inventory
	* World gravity
* Map can be saved with or without game assets. When saving with assets, the data is compressed with lossles run length encoding compression.



https://user-images.githubusercontent.com/4020810/218316566-2672e570-f932-4b9f-9a1b-d6b8710bce23.mp4



## Optimization
The project was done without GPU acceleration (like the original Duke Nukem 3D), so it was crucial to keep optimization for performance in mind during the whole project. Modern CPUs are also considerably faster than the ones in 1996, so we wanted to achieve high FPS with also much more pixels on screen.

400-450 FPS on average on Intel i9 12900k with 1280x720 resolution:


https://user-images.githubusercontent.com/4020810/218318247-b6b01d8b-64dd-4376-8caa-c0f77173c53c.mp4


## Authors
<a href="https://github.com/Danielmdc94">Daniel Palacio</a>

<a href="https://github.com/HenTah">HenTah</a>

<a href="https://github.com/ssulkuma">Sarita Sulkumäki</a>

<a href="https://github.com/samuaaltonen">Samu Aaltonen</a>