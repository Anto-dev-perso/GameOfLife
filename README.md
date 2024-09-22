
# Game of Life

This project is an implementation of John Conway's famous cellular automaton, the **Game of Life**, developed in C++.

The Game of Life is a zero-player game where an initial state (seed) evolves over time according to simple rules. The game takes place on a 2D grid, and each cell on the grid can either be alive or dead. The evolution of the cells is determined by the initial configuration, and they evolve based on the states of their neighbors.

---

## How to Build and Run

### Prerequisites

- This program is developped and maintained on `Unix` targets. If you are interested in a Windows version, please raise an Issue.
- This program is `gcc`/`g++` oriented. Make sure to have a least a GCC 8 or higher version intalled
- `cmake` to configure and build the project

### Dependancies

- For the Release version, there are **no dependancies** outside the build chain. 
- For the Debug version, because all tests are written with the googletest framework, `cmake` will first **download** the archive of the framework before building it. Make sure to have an Internet Connection when building the project in Debug mode.
- For RelWithDebInfo, as the Release, there are **no dependancies** outside the build chain. 
 
For profiling situation, some options are added to generate a binary linked to a heap or cpu profiler (see the build section). The profiler choosen is gperftool. It is **not downloaded automatically** so make sure to install it first before trying to build.

On Ubuntu, you can launch this command to install the profiler:
```bash
sudo apt-get install google-perftools libunwind-dev
```

---
### Build the Project

You can build the project using the build script:

```bash
./build.sh
```

By default, it will create a build-release directory and will build the project in Release mode. 

If one want to build in another mode (Debug or RelWithDebInfo), he or she can pass as an argument of the script like the following:

```bash
./build.sh -c Debug
```
Caraful though, this script is case sensitive.


As explain in Depandancies part, this project can also be built with profiling. There are 3 possibilities :
 - `heap` will link with `tcmalloc` and add a heap dump at the end of the execution.
 - `cpu` will link with `lprofiler` and add cpu sample with an export at the end of the execution
 -  `none` to not use a profiler

Please note that run any program with profiling will drastically impact the overall performance of the program. Do not run this project in this mode except for deep investigation about memory or performance.

---
### Run the Game

Once the project is built, you can run the executable:

```bash
cd build-<release|relwithdebinfo|debug>
./GameOfLife
```

This program has 2 mandatory arguments and 1 optional:
- `--input path/to/the/file`: will define the initial state of the game
- `--iterations NUMBER_OF_GENERATION`: will define how many generation this game will run.
- `--all` (optional): will export all iterations instead of the last one

One can try with the datasets of the tests with the following:
```bash
./GameOfLife --input tests/input_files/oscillators/tub.txt --iterations 1
```
---
### See the Result of the Game

This game will produce one file that is located at the same place as your input file but with the `res` extension instead of the `txt`.

If the `--all` argument is set, the game will produce as may files as there are iterations give in arguments. All the files will be located ins the same directory as the input file. 
All of these will have a prefix with the generation it is representing (beginning at 1) and has the `res` extension.  

---

## Rules of the Game

The Game of Life operates based on the following simple rules:

1. **Any live cell with fewer than two live neighbors dies** (underpopulation).
2. **Any live cell with two or three live neighbors lives on** (survival).
3. **Any live cell with more than three live neighbors dies** (overpopulation).
4. **Any dead cell with exactly three live neighbors becomes a live cell** (reproduction).

---
## Contributing

Contributions are not allowed on this project but I you have any feedback, feel free to raise an Issue

Feel free to submit issues or pull requests to help improve the project. All contributions are welcome!

<!-- TODO -->
<!-- ## License -->

<!-- This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information. -->

---

## Acknowledgments

- Inspired by John Conway's Game of Life.
- Built as a learning project for C++ and algorithm development.
