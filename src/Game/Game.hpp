#pragma once

#include "OutputWriter.hpp"

#include <string>
#include <memory>

class Game {

public:
    Game(std::string_view path, unsigned int iterations, bool all);

    [[nodiscard]] bool process();

private:

    std::string_view _filePath{};
    unsigned int _nbOfIterations{0};
    bool _outputAllIterations{false};

    std::unique_ptr<Board> _board;
    std::unique_ptr<OutputWriter> _outputWriter;

};
