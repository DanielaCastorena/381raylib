## Simple P2P: Snake
Snake is a simple game implemented in C++ using the Raylib library. This README provides an overview of the game and instructions for playing.

### Overview
Snake is a classic game where the player controls a snake that grows in length as it consumes apples. The goal is to survive as long as possible without colliding with the snake's own body or the game window's borders.

### Gameplay
- Use the arrow keys (Up, Down, Left, Right) to control the direction of the snake.
- The snake moves continuously in the direction it's facing.
- The snake grows longer each time it consumes an apple.
- The game ends if the snake collides with its own body or the game window's borders.
- After the game ends, press Enter to restart.

### Controls
- Arrow keys: Control the direction of the snake.
- Enter: Start the game or restart after game over.

### Building and Running
To compile the code, follow these steps:
Clone the repository to your local machine using Git:
"git clone https://github.com/DanielaCastorena/381raylib.git"

"cd 381raylib"

Navigate to the cloned directory:
"cd as7"
"git submodule update --init --recursive"
"rm -r build"
"mkdir build"
"cd build"
"cmake .."
"make"
"./as7"

### Acknowledgments
Snake is based on the Raylib library, which provides the graphics and input handling functionalities. Special thanks to the Raylib development team for their work on this fantastic library.

### Extra Credit
Custom textures