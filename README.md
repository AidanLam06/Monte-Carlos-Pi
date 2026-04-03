## Description:
A program that estimates pi via a Monte Carlo simulation.

The setup consists of a square with a side length x, and a circle placed inside that square with a diameter of x. The ratio of the areas of the circle and square is
$\ A_circle/A_square = (&pir^2)/(4r^2) = &pi/4 \$

## Versions:
### v1: 
Ultra-basic heap allocated vector that stores Dot objects in one for loop and then performs a rolling calculation in another for loop and prints the estimated pi result. Very slow

### v2: 
Removed printing all the numbers, limiting to only printing the current estimation at every 100k values in the main for loop.
Full calculation performed while points are generated. Changed compiler to release mode for compiler optimizations (cmake -DCMAKE_BUILD_TYPE=Release ..).
Added a timer as well. 1 mil dots takes ~0.025s, 10 mil dots takes ~0.25s, 100 mil dots takes ~25s.

### v3 (FINAL): 
Re-uses calculation logic from v2 (with slight performance improvements) and now shows a visual demonstration of the points being thrown onto an image of a circle enclosed within a square.
The live estimation shown in the top left of the display is recalculated every 100 iterations.
Uses the SDL2 library
