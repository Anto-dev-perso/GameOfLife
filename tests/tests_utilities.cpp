#include <gtest/gtest.h>
#include "tests_utilities.hpp"
#include "Game/AllowedChar.hpp"

#include <algorithm>
#include <fstream>

namespace UTILITIES
{
    using namespace std;

    void compareGrid(tuple<gridOfCells, size_t, size_t> board, const gridOfCells& expected)
    {
        const auto& grid{get<0>(board)};
        const auto& numColumn{get<2>(board)};
        for (size_t line = 0; line < grid.size(); line += numColumn)
        {
            for (size_t column = 0; column < numColumn; column++)
            {
                EXPECT_EQ(grid[line + column].get_isCurrentlyAlive(), expected[line + column].get_isCurrentlyAlive())
                    << "Board incorrect on line " << (line / numColumn) << " and column " << column;
            }
        }
    }

    string readFile(const std::string& filename)
    {
        ifstream infile(filename);
        if (!infile)
        {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        // Read the file contents into a string
        std::ostringstream contentStream;
        contentStream << infile.rdbuf();
        std::string content = contentStream.str();

        // Remove all '\r' characters (Windows-style carriage returns)
        content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
        return content;
    }
};
