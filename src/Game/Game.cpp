#include "Game.hpp"

using namespace std;

Game::Game(const string_view &path, unsigned int iterations, bool all) : _filePath(path),
                                                                         _nbOfIterations(iterations),
                                                                         _outputAllIterations(all) {}
