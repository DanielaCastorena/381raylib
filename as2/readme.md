# CS381 - Assignment 2

## Compilation
To compile the code, follow these steps:
Clone the repository to your local machine using Git:
"git clone https://github.com/DanielaCastorena/381raylib.git"

"cd 381raylib"

Navigate to the cloned directory:
"cd as1"
"git submodule update --init --recursive"
"rm -r build"
"mkdir build"
"cd build"
"cmake .."
"make"
"./as1"


## Running the Code
To run the code, execute the compiled executable. Controls:
- W: Increase velocity away from the camera.
- S: Increase velocity towards the camera.
- A: Increase velocity to the left of the camera.
- D: Increase velocity to the right of the camera.
- Q: Increase velocity upwards from the camera's perspective.
- E: Increase velocity downwards from the camera's perspective.

Question: Can we simplify the problem by remapping camera directions to specific world axes (e.g. W moves along say -Z)? Why or why not can we use this simplification in this assignment?

Answer: Yes, we can simplify the problem by remapping camera directions to specific world axes. We can use this simplification because it enhances user intuitiveness and simplifies control by aligning camera movement with familiar spatial directions. This approach maintains clarity and predictability in navigation, ultimately improving the overall user experience in the 3D environment.