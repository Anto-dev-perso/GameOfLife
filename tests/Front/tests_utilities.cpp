#include <gtest/gtest.h>
#include "tests_utilities.hpp"

namespace UTILITIES
{
    QImage generateImage(const board_data& inputGrid, MainGridImageProvider& provider) noexcept
    {
        const auto firstGridCol{
            provider.get_gridFirstColumn() >= 0
                ? static_cast<size_t>(provider.get_gridFirstColumn())
                : provider.get_UIColumnCount()
        };
        const auto firstGridRow{
            provider.get_gridFirstRow() >= 0
                ? static_cast<size_t>(provider.get_gridFirstRow())
                : provider.get_UILineCount()
        };

        QImage returnedImage{
            MainGridImageProvider::NB_UI_COLUMNS_AT_MAX * CELL_SIZE,
            MainGridImageProvider::NB_UI_LINES_AT_MAX * CELL_SIZE,
            QImage::Format_ARGB32
        };

        QPen pen{BORDER_COLOR};
        QPainter painter;
        painter.begin(&returnedImage);

        pen.setWidth(1);
        painter.setPen(pen);

        for (size_t row = 0; row < provider.get_UILineCount(); row++)
        {
            for (size_t column = 0; column < provider.get_UIColumnCount(); column++)
            {
                if (row >= firstGridRow && row < firstGridRow + inputGrid.line && column >=
                    firstGridCol && column < firstGridCol + inputGrid.column)
                {
                    painter.setBrush(inputGrid.grid.at(
                                                   (row - firstGridRow) * inputGrid.column + (column - firstGridCol)).
                                               get_isCurrentlyAlive()
                                         ? CELL_ALIVE_COLOR
                                         : CELL_DEAD_COLOR);
                }
                else
                {
                    painter.setBrush(CELL_DEAD_COLOR);
                }

                painter.drawRect(static_cast<int>(column) * CELL_SIZE, static_cast<int>(row) * CELL_SIZE, CELL_SIZE,
                                 CELL_SIZE);
            }
        }
        return returnedImage;
    }

    void compareQImage(const board_data& inputGrid, MainGridImageProvider& provider)
    {
        const auto imageExpected{generateImage(inputGrid, provider)};
        QImage imageToTest{provider.requestImage("", nullptr, QSize())};
        ASSERT_FALSE(imageToTest.isNull());

        EXPECT_EQ(imageToTest, imageExpected);
    }

    board_data getGridFromModel(int lexiconId, int gridId,
                                const LexiconGridModel& gridModel) noexcept
    {
        if (const auto size = gridModel.getSizeForIndex(lexiconId, gridId); size < 0) { return {}; }
        else
        {
            board_data result{
                {}, static_cast<size_t>(gridModel.getLineCountForIndex(lexiconId, gridId)),
                static_cast<size_t>(gridModel.getColumnCountForIndex(lexiconId, gridId))
            };
            result.grid.reserve(static_cast<size_t>(size));
            for (size_t i = 0; i < result.line * result.column; i++)
            {
                result.grid.emplace_back(
                    boolToChar(gridModel.getData(
                        lexiconId, gridId, i, LexiconGridModel::GridRole).value<bool>()));
            }
            return result;
        }
    }
}
