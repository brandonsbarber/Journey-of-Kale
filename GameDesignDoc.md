#Kale's Escape GDD
##A Platforming Adventure by Brandon Barber

###Overview
This game will follow the initial journeys of the young man Kale as he struggles to save Norcanon from the threat of the Volcurs.
The story will progress across three levels: as Kale tries to escape the burning ruins of Nootkar, his home; Kale's defense of the Mountain Keep; and Kale's flight through the woods of the northern lands of the Great Houses until he comes to his final confrontation.

The idea for this stems from a fantasy novel I have had in development for some time.

![alt text](https://github.com/usc-csci102-spring2013/game_bsbarber/blob/master/Assets/Kale.png "Kale")

From a technical side, this game will utilize a tile-based system of rendering in order to create the world. Tiles will be generated from a 2D array of integers for all locations in the level. It will include challenges for jumping, dodging, climbing, and running.

###"Things"
This game will feature an array of enemies and different types of tiles, as well.
  1. Stationary Tiles: This "thing" will not move and will instead feature a static image. Each one will have a purpose, be they scenic or contain ladders or act as walls. They will not move but will interact with the player. I do not have images for them right now just because I have not determined all of the scenery blocks I will be using, but for the most part I will have walls, floors, ladders, and decorations.
  1. Volcur Footsoldier: The most basic of enemies that will be featured in this game. Patrols from side to side when encountered on the map. Will be given a spawn area in the array form of the map and will spawn randomly in one of those tiles.
  
  ![alt text](https://github.com/usc-csci102-spring2013/game_bsbarber/blob/master/Assets/Volcur.png "Volcur Footsoldier")
  
  1. Volcur Climber: Similar to the footsoldier, these enemies will occasionally be present on ladders and will patrol up or down. Will randomly spawn on a ladder tile and will pick a direction to move.
  
  ![alt text](https://github.com/usc-csci102-spring2013/game_bsbarber/blob/master/Assets/Climber.png "Volcur Climber")
  
  1. Volcur Chaser: Occasionally (and especially in the third level), an enemy will begin to chase after you and try to run into you. Appear at random time intervals and chase the player.
  
  ![alt text](https://github.com/usc-csci102-spring2013/game_bsbarber/blob/master/Assets/Chaser.png "Volcur Climber")
  
  1. Shadow Knight: Boss that you fight at the end of the game. he will mirror the player's Y movements and randomly lunge out at the player, attempting to strike him.
  
  ![alt text](https://github.com/usc-csci102-spring2013/game_bsbarber/blob/master/Assets/ShadowKnight.png "Shadow Knight")

###Gameplay
The game will be played through a variety of controls on keyboard and mouse:
  * Move: A and D for left and right
  * Jump: Spacebar
  * Climb: W and S for up and down
  * Pause: Esc
  * Interact with Menus: Mouse Click

###Scoring
Score will be increased based on health and number of lives at the end of each level. A full health bar equals one life worth of points.

The score cannot decrease; only increase.

###Player Lives
The player will start with three lives and a health bar. When health is depleted, the player loses a life. Health is lost by running into enemies or being hit by a shadow bolt.

###User Interface
Before playing, the user will be prompted for their name. This will be displayed at the top next to their score.

Upon pausing, the game will freeze and the word "Pause" will appear at the center of the screen. Two buttons will be present: Resume and Exit.

Main Menu of the game:
![alt text](https://github.com/usc-csci102-spring2013/game_bsbarber/blob/master/Assets/MenuMockup.jpg "Menu Image")

Gameplay Image:

![alt text](https://github.com/usc-csci102-spring2013/game_bsbarber/blob/master/Assets/GameplayMockup.jpg "Gameplay Image")

