# Assignment 2 - Gravity Simulation
> By George Padron

- *Video included in the repo* 

This module is a simple physics N-Body simulation for orbiting celestial bodies. Alongside it is a simple project with an interactive project showcasing a simple system. The module implements *two* new nodes: an **N-Body System** node which controls the main simulation, as well as a **Celestial Body** which reacts to other Celestial bodies under the same *N-Body System*, allowing for the simulation of solar systems.  

The *N-Body System* node exposes parameters allowing for control of the gravitational constant, the amount of steps per frame, the collision handling, and whether or not the simulation is running or not. It also features simplistic logging for debugging purposes - showing the different phases of the simulation as well as the new position of the planets on each frame. 

The other game object enabled is the *Celestial Body*. This is a simplistic object that is controlled by the *N-Body System* and moves in accordance to the gravitational forces applied on it by other bodies. It holds information about its *radius, mass, velocity, and acceleration*, which is used by the N-Body System for its calculations. These objects can also be made to be *static* - so that the forces applied by other bodies do not affect them. In order to make an interesting simulation, one should try playing with the different mass, velocity, and acceleration properties, as well as the gravitational constant. The attached Godot project provides a simple scene that allows one to experiment with the engine with preset "Planet" and "Star" scenes based on the Celestial Object node.


The actual simulation runs in Godot's physics loop and involves three stages. First the forces applied onto each planet by all other planets are calculated using a simple summation algorithm. Next, the forces caused by collisions are calculated. Once all of these forces have been calculated, the position of the planet in the next step is determined and the planet is moved to that position.

## Controls 
- Use the scroll wheel to zoom in and out 
- Drag the view with the left mouse button.

## Compilation Instructions
**NOTE**: Build was only tested on Linux with GCC and windows with MSVC.

1. Ensure all necessary dependencies needed to build and compile Godot are installed

2. Clone the repository
```bash
git clone https://github.com/Vanderbilt-GameDev-2025/george-padron-assignment2.git
```
3. cd into the `godot` directory and run the following command 

```bash 
scons platform=YOUR_PLAFORM
```
with `YOUR_PLAFORM` replaced with your choice of `windows`, `macos`, or `linuxbsd`

If you are on Mac, make sure to include your architecture: 
```bash 
scons platform=macos arch=ARCH
```
With `ARCH` being `arm64` if on Apple Silicon and `x86_64` if on Intel.

4. Run the binary located within the `/godot/bin/` folder.

