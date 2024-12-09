#pragma once
#include "../InputsBoards.hpp"

#include "Front/Bridge/LexiconModel.hpp"
#include "Front/Bridge/MainGridImageProvider_Test.hpp"

namespace UTILITIES
{
    [[nodiscard]] QImage generateImage(const board_data& inputGrid, MainGridImageProvider_Test& provider) noexcept;

    void compareQImage(const board_data& inputGrid, MainGridImageProvider_Test& provider);

    [[nodiscard]] board_data getGridFromModel(int lexiconId, int gridId,
                                              const LexiconGridModel& gridModel) noexcept;
}
