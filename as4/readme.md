# CS381 - Assignment 4

## Compilation
To compile the code, follow these steps:
Clone the repository to your local machine using Git:
"git clone https://github.com/DanielaCastorena/381raylib.git"

"cd 381raylib"

Navigate to the cloned directory:
"cd as4"
"git submodule update --init --recursive"
"rm -r build"
"mkdir build"
"cd build"
"cmake .."
"make"
"./as4"

Space Invaders Remake!
I decided to recreate the classic arcade game, Space Invaders! Your goal is to protect Earth from invading aliens and score as high as you can.

How to Play:
You control a spaceship at the bottom of the screen. Move it left and right with the arrow keys to dodge enemy attacks and aim your shots. Press the spacebar to shoot at the aliens.

The game has different levels that get harder as you move forward. Defeat all aliens in order to advance. They will become faster and shoot more often as you progress.

Controls:
- Left Arrow Key: Move left
- Right Arrow Key: Move right
- Spacebar: Shoot

Scoring:
Earn points by shooting aliens and a special big red alien:
- Regular aliens: 10 points each
- Big red alien: 100 points

Try to beat your high score and challenge your friends!

Barricades:
You'll find barricades on the battlefield. They give you temporary cover from enemy shots but can be destroyed. Use them wisely to protect yourself.

Big Red Alien:
Keep an eye out for the big red alien! It appears sometimes and moves across the screen. Destroy it for bonus points and to clear the way.

Game Over:
You lose if:
- You run out of lives.
- Any alien reaches the bottom of the screen.

Restarting:
If you lose, press Enter to restart and try again. See if you can beat your previous score!
