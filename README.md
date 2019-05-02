# fractal

Graphical project that demonstrates the use of mathimatical notions with the example of complex numbers.

Term "fractal" became really popular after work done by Benoit Mandelbrot, and I'm going to show the Mandelbrot set and its variations.

Good starting point to understand what fractals are is a wikipedia page, which I included in references.

Minimal version of mlx library was used for drawing images on screen and handling events (is included in project).

Most of the options are supported while in GPU mode. Please press 'g' to change mode from CPU.

Enjoy the beauty of fractals!

[UPD] GPU only works on macOS up to version 10.14, since Apple doesnt support OpenCL and OpenGL starting from 10.14. Rewriting in progress

### UI

- 1 - return to default position
- g - go to GPU mode
- 2/3 - color modes
- s/m - more color modes
- =/- - add/decrease iterations (depth of fractal)
- scroll in/out - zoom in/out
- mouse right-click / arrows - move around
- mouse left-click - change constants in julia set

### Usage

compile the project with make command

run ./fractal [mandelbrot/julia/burning_ship/tricorn]

### Project commands

make - compile executable

make clean - remove object files

make fclean - make clean plus remove library and executable

make re - remove all temporary files and compile the project again

### References

Fractal:

- https://en.wikipedia.org/wiki/Fractal
- https://en.wikipedia.org/wiki/Mandelbrot_set
- https://youtu.be/NGMRB4O922I

OpenCL:

- https://habr.com/ru/post/72650/
- https://habr.com/ru/post/73526/
- https://www.youtube.com/watch?v=73G4eWRqxlU
- http://phycomp.technion.ac.il/~comphy/classfiles/hellocl.c

Zoom issue:

- https://math.stackexchange.com/questions/377169/calculating-a-value-inside-one-range-to-a-value-of-another-range
