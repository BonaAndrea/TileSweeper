<p align="center">
  <img src="Assets/GameLogo.png" alt="TileSweeper Logo" />
</p>
TileSweeper is a game developed using Unreal Engine 5.4.4, where the player navigates a grid of tiles, aiming to find green tiles and avoid red ones. The game is based on a simple tile system that reacts to the player's movements. The game ends when all green tiles are found or when all red tiles are stepped on.

## Features

- **Tile Grid**: At the beginning of the game, a grid of tiles is generated around the player's starting platform. The grid size is customizable via the `TileGameModeBP` blueprint.
- **Green Tiles**: These represent the main objective of the game. The player must try to find all the green tiles. Once a green tile is stepped on, it turns green and stays in that state even after the player moves off it.
- **Red Tiles**: These tiles are dangerous, and the player should avoid stepping on them. If the player steps on all the red tiles, the game ends. Red tiles turn red when stepped on and stay red once the player leaves them.
- **Blue Tiles**: A new type of tile has been added. When the player steps on a blue tile:
  - All green tiles become revealed.
  - Once the player steps off the blue tile, all previously undiscovered green tiles return to their unpressed gray state.
- **Visual Feedback**: Each tile changes appearance when the player steps on it:
  - Normal tiles turn white when stepped on and revert to their initial state when the player moves off them.
  - Green tiles remain green even after the player steps off them.
  - Red tiles remain red after being stepped on.
  - Blue tiles reveal green tiles while stepped on, and return to their normal state when left.
  
- **End of Game**: The game ends when the player has found all the green tiles or has stepped on all the red tiles. After the game ends, a simple end screen is shown, which lasts for about 5 seconds before the game is reset.

## Gameplay

1. **Initial Setup**: When the game starts, load the `TileLevel` map and hit "Play" to begin. The tile grid is generated around the player's starting platform.
2. **Tile Management**: The gameplay logic is handled by the `TileSweeperGameMode` class. This class defines all the necessary actions to be taken when the player interacts with the tiles.
3. **End Screen and Reset**: Once the game ends (either by finding all green tiles or stepping on all red tiles), the end screen is shown using `TileHUD::ShowEndScreen()`. After 5 seconds, the game resets using the `TileSweeperGameMode::ResetGame()` method.

## Instructions

1. **Requirements**:
   - Unreal Engine 5.4.4 (free to download)
   - A PC or Mac that supports Unreal Engine.

2. **Installation**:
   - Clone this repository to your local machine.
   - Open the project in Unreal Engine 5.4.4.
   - Load the `TileLevel` map and press "Play" to start the game.

3. **Development**:
   - Modify the game logic in the `TileSweeperGameMode` class to implement tile behaviors and game-ending logic.
   - The `ATile` class has been enhanced with inheritance to manage different tile types effectively (normal, green, red, and blue).

## Contact

If you have any questions or feedback, feel free to open an **Issue** on this repository.

Enjoy playing!
