#include <gtest/gtest.h>
#include "tests_utilities.hpp"
#include "Game/AllowedChar.hpp"

#include <algorithm>


namespace UTILITIES {
    using namespace std;

    void compareGrid(const gridOfCells &grid, const gridOfCells &expected) {

        for (size_t line = 0; line < grid.size(); line++) {
            for (size_t column = 0; column < grid[line].size(); column++) {
                EXPECT_EQ(grid[line][column].get_isCurrentlyAlive(), expected[line][column].get_isCurrentlyAlive())
                                    << "Board incorrect on line " << line << " and column " << column;
            }
        }
    }

    void dumpGrid(const gridOfCells &grid) {
        for (size_t line = 0; line < grid.size(); line++) {
            for (size_t column = 0; column < grid[line].size(); column++) {
                cout << boolToChar(grid[line][column].get_isCurrentlyAlive());
            }
            cout << endl;
        }
    }
};
