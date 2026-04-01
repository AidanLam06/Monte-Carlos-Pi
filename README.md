## Description:
A program that estimates pi via the Monte Carlo method.

## Versions:
### v1: 
Ultra-basic heap allocated vector that stores Dot objects in one for loop and then performs a rolling calculation in another for loop and prints the estimated pi result. Very slow

### v2: 
Removed printing all the numbers, limiting to only printing the current estimation at every 100k values in the main for loop.
Full calculation performed while points are generated. Changed compiler to release mode for compiler optimizations (cmake -DCMAKE_BUILD_TYPE=Release ..).
Added a timer as well. 1 mil dots takes ~0.025s, 10 mil dots takes ~0.25s, 100 mil dots takes ~25s.

### v3: 
Re-uses calculation logic from v2 (with slight performance improvements) and now shows a visual demonstration of the points being thrown onto an image of a circle enclosed within a square.
The live estimation shown in the top left of the display is recalculated every 100 iterations.
Uses the SDL2 library
