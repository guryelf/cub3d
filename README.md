*This project has been created as part of the 42 curriculum by fguryel, rakman.*

# cub3D - My First RayCaster

## Description
cub3D is a project inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever created. The goal of this project is to create a realistic 3D graphical representation of the inside of a maze from a first-person perspective using **Ray-Casting** principles.

The program parses a scene description file (`.cub`) and renders a dynamic view inside a maze where the user can move and rotate. It is written in C and uses the **miniLibX** graphics library.

## Key Features
* **Ray-casting Engine:** Renders 3D walls based on a 2D map grid.
* **Texture Mapping:** Supports different textures for North, South, East, and West facing walls.
* **Color Rendering:** Configurable floor and ceiling colors.
* **Movement:** Smooth movement (W, A, S, D) and camera rotation (Left/Right arrows).
* **Map Validation:** Checks for valid map structure, ensuring the maze is enclosed by walls and contains valid characters.

## Instructions

### Prerequisites
* `gcc` compiler
* `make`
* Standard system libraries (MiniLibX dependencies)

### Installation
1.  Clone the repository:
    ```bash
    git clone <repository_url> <repository_name>
    cd <repository_name>
    ```
2.  Compile the project:
    ```bash
    make
    ```
    This will generate the `cub3D` executable.

### Execution
Run the program by providing a valid map file as an argument:
```bash
./cub3D assets/maps/test.cub
```

### Resources

### Documentation & Tutorials
Lodev's Raycasting Tutorial: The primary reference used for understanding the mathematics behind raycasting, DDA algorithm, and texture mapping.

MiniLibX Documentation: Used for window management, event handling, and pixel manipulation.

42 Docs: Reference for handling the specific constraints of the subject.

#### AI Usage Acknowledgement

As per the subject requirements regarding AI usage, Artificial Intelligence tools were used in this project for the following specific tasks:

Concept Visualization & Explanation: AI was used to act as a "thought partner" to deconstruct the mathematical logic of the Raycasting engine. Specifically, it helped explain the relationship between the Direction Vector (dir_vec) and the Camera Plane (plane_vec), and how they interact with the Field of View (FOV).

Code Analysis: AI was used to analyze specific functions (perform_dda, calculate_wall, setup_ray) to ensure the implementation of the DDA algorithm correctly matched the theoretical logic of grid traversal.

Math Clarification: AI assisted in understanding the vector math required for rotating the camera and calculating perpendicular wall distances to avoid the "fisheye effect."