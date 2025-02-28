#include <gtest/gtest.h>
#include "tests_utilities.hpp"
#include "Back/Game/AllowedChar.hpp"

#include <algorithm>
#include <fstream>

namespace UTILITIES
{
    using namespace std;

    void compareGrid(const board_data& board, const board_data& expected)
    {
        ASSERT_EQ(board.column, expected.column);
        ASSERT_EQ(board.line, expected.line);

        const auto& grid{board.grid};
        const auto& numColumn{board.column};

        for (size_t line = 0; line < grid.size(); line += numColumn)
        {
            for (size_t column = 0; column < numColumn; column++)
            {
                EXPECT_EQ(grid[line + column].get_isCurrentlyAlive(),
                          expected.grid[line + column].get_isCurrentlyAlive())
                    << "Board incorrect on line " << (line / numColumn) << " and column " << column;
            }
        }
    }

    string readFile(std::string_view filename)
    {
        ifstream infile{filename.data()};
        if (!infile)
        {
            throw std::runtime_error("Unable to open file: " + string(filename));
        }

        // Read the file contents into a string
        std::ostringstream contentStream;
        contentStream << infile.rdbuf();
        std::string content = contentStream.str();

        // Remove all '\r' characters (Windows-style carriage returns)
        content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
        return content;
    }

    void dumpBoardData(const board_data& board) noexcept
    {
        const auto& grid{board.grid};
        const auto& numColumn{board.column};

        for (size_t line = 0; line < grid.size(); line += numColumn)
        {
            for (size_t column = 0; column < numColumn; column++)
            {
                std::cout << boolToChar(grid[line + column].get_isCurrentlyAlive());
            }
            std::cout << std::endl;
        }
    }


};
