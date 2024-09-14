#pragma once

#include <string>
#include <memory>

class Game {

public:
    Game(const std::string_view &path, unsigned int iterations, bool all);

private:

    std::string _filePath{};
    unsigned int _nbOfIterations{0};
    bool _outputAllIterations{false};

};
