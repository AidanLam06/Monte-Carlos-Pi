## Description:
A program that estimates pi via a Monte Carlo simulation.

The setup consists of a square with a side length x, and a circle placed inside that square with a diameter of x. The ratio of the areas of the circle and square is:

$$\frac{A_{circle}}{A_{square}} = \frac{\pi r^2}{4r^2} = \frac{\pi}{4}$$

When you generate random points uniformly across the square, the probability that a point falls within the circle is proportional to the circle's area. By generating N total random points, you can count how many points (M) are located inside the circle

$$x^2 + y^2 \le r^2$$

As the number of points N becomes very large, the ratio of points inside the circle to the total points approximates the ratio of their areas

$$\frac{M}{N} \approx \frac{\pi}{4}$$

And then to solve for $\pi$ you simply move the 4 to the other side

$$\pi \approx 4 \times \frac{M}{N}$$

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
Uses the SDL2 library to show the "animation"
