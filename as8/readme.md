# CS381 - Assignment 6

## Compilation
To compile the code, follow these steps:
Clone the repository to your local machine using Git:
"git clone https://github.com/DanielaCastorena/381raylib.git"

"cd 381raylib"

Navigate to the cloned directory:
"cd as8"
"git submodule update --init --recursive"
"rm -r build"
"mkdir build"
"cd build"
"cmake .."
"make"
"./as8"


## Running the Code
To run the code, execute the compiled executable. Controls:
- W: increases the selected entity’s velocity in the direction its facing.
- S: decreases the selected entity’s velocity in the direction its facing.
- A: smoothly increases the selected entity’s heading.
- D: smoothly decreases the selected entity’s heading.
- Q: smoothly increases the selected entity’s pitch.
- E: smoothly decreases the selected entity’s pitch. 
- R: smoothly increases the selected entity’s roll. 
- F: smoothly decreases the selected entity’s roll.
- TAB: select entity.
- SPACE: smoothly reset selected entity's velocity to zero.

