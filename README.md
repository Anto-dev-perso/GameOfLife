
# Game of Life

This project is an implementation of John Conway's famous cellular automaton, the **Game of Life**, developed in C++.

The Game of Life is a zero-player game where an initial state (seed) evolves over time according to simple rules. The
game takes place on a 2D grid, and each cell on the grid can either be alive or dead. The evolution of the cells is
determined by the initial configuration, and they evolve based on the states of their neighbors.

This project is cut in two parts: a script that can be launched in a terminal and a Graphical User Interface (GUI)

---

## How to Build and Run

### Prerequisites

- This program is developped and maintained on `Unix` targets but Windows binaries are also available
- This program is `gcc`/`g++` oriented. Make sure to have a least a GCC 8 or higher version intalled. For Windows, this project uses MSVC to builds and test it
- `cmake` to configure and build the project

### Dependancies

- For the Release version, there are **no dependancies** outside the build chain for the terminal script but for the GUI part, it needs Qt6.5 to build. Make sure to install it first (see [Get and Install Qt] (https://doc.qt.io/qt-6/get-and-install-qt.html))
- For the Debug version, because all tests are written with the googletest framework, we uses `conan` to retrieve or build this framework. Make sure to have an Internet Connection when building the project in
  Debug mode. As this build is mostly used for development, wer will asume the developper know how to install and configure conan or at least he or she can find the information by itself.
- For RelWithDebInfo, as the Release, there are **no dependancies** added.

For profiling situation, some options are added to generate a binary linked to a heap or cpu profiler (see the build
section). The profiler choosen is gperftool. It is **not downloaded automatically** so make sure to install it first before trying to build.

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

If one want to build in another mode (Debug or RelWithDebInfo), he or she can pass the configuration as an argument of the script like the
following:

```bash
./build.sh -c Debug
```

Caraful though, this script is case sensitive.

For Debug and RelWithDebInfo configuration, address sanitizers can be added to the binary. To do so, add `-a` to
build.sh:

```bash
./build.sh -c Debug -a
```

As explain in Depandancies part, this project can also be built with profiling. There are 3 possibilities :

- `heap` will link with `tcmalloc` and add a heap dump at the end of the execution.
- `cpu` will link with `lprofiler` and add cpu sample with an export at the end of the execution
- `none` to not use a profiler

Please note that run any program with profiling will drastically impact the overall performance of the program. Do not run this project in this mode except for deep investigation about memory or performance.
---

### Launch the tests

First, make sure to have build this project in Debug mode. If the build is successfull, you should see multiple binaries
inside the build-debug directory:

- `GameOfLife` which the script binary of the game
- `appQtGameOfLife` which the GUI binary
- `GameOfLifeUnitTests` which is a binary dedicated to the unit tests of the script
- `GameOfLifeFunctionalTests` which is a binary dedicated to the functional tests of the script
- `GameOfLifeGUIUnitTests` which is a binary dedicated to the unit tests of the GUI

These different binaries serve the purpose to launch only one type of test. If you just want to launch all the tests,
you can run the command

```bash
cd build-debug
ctest --output-on-failure
```

Otherwise, simply run the binary you want and it will run all the tests of this type (unit or functional)

---

### Run the Game (script)

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


### See the Result of the Game

This game will produce one file that is located at the same place as your input file but with the `res` extension
instead of the `txt`.

If the `--all` argument is set, the game will produce as may files as there are iterations give in arguments. All the
files will be located ins the same directory as the input file.
All of these will have a prefix with the generation it is representing (beginning at 1) and has the `res` extension.

---

### Run the Game (GUI)

For Windows users, a package of the program is available in the [Release] (https://github.com/Anto-dev-perso/GameOfLife/releases). This Windows binary doesn't need to install anything. Simply launch the exe file.
For Linux users, a binary is also present in the [Release] (https://github.com/Anto-dev-perso/GameOfLife/releases) but this binary isn't bundle with Qt. So make sure to have installed Qt6.5 before running the GUI otherwise the program will crash.

Once the project is built, you can run the executable:

```bash
cd build-<release|relwithdebinfo|debug>
./appQtGameOfLife
```

There are no inputargument nor output file. Simple and clean.

By default, it opens with a glider pattern. You can make cells alive or dead by clicking on it or go to the Lexicon menu to select the pattern you want. 
From there, you just have to clikc on the `Start` button.

---

## Rules of the Game

The Game of Life operates based on the following simple rules:

1. **Any live cell with fewer than two live neighbors dies** (underpopulation).
2. **Any live cell with two or three live neighbors lives on** (survival).
3. **Any live cell with more than three live neighbors dies** (overpopulation).
4. **Any dead cell with exactly three live neighbors becomes a live cell** (reproduction).

---

## Contributing

Contributions are not allowed on this project but if you have any feedback, feel free to raise an Issue or contact the Maintainer directly.

<!-- TODO -->
<!-- ## License -->

<!-- This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information. -->

---

## Acknowledgments

- Inspired by John Conway's Game of Life.
- Built as a learning project for C++ and algorithm development.
- GUI is a re-implementation of the [Edwin Martin's website] (https://playgameoflife.com/)
