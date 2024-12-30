#include <gtest/gtest.h>
#include "Back/Game/OutputWriter.hpp"
#include "../tests/Back/tests_utilities.hpp"

using namespace std;

// Declare the grid globally to keep the memory allocated by the first test to be played
grid_of_cells grid;

/****************************************  Tests Suite for all instantiations of OutputWriter ***************************************/

TEST(UTOutputWriterInstanciantion, IntantiateWithInitial)
{
    const OutputWriter writer{"initial.txt"};

    EXPECT_EQ(writer.get_fileName(), "initial");
    EXPECT_EQ(writer.get_extension(), "res");
}

TEST(UTOutputWriterInstanciantion, IntantiateWithUpperCase)
{
    const OutputWriter writer{"UPPER.txt"};

    EXPECT_EQ(writer.get_fileName(), "UPPER");
    EXPECT_EQ(writer.get_extension(), "res");
}

TEST(UTOutputWriterInstanciantion, IntantiateWithLongName)
{
    const OutputWriter writer{"very_very_very_long_name_input.txt"};

    EXPECT_EQ(writer.get_fileName(), "very_very_very_long_name_input");
    EXPECT_EQ(writer.get_extension(), "res");
}

/****************************************  Tests Suite for writeIteration function without the optional iteration argument ***************************************/

TEST(UTWriteIterationWithoutOptionalArgument, LivingCellsInFirstAndLastColumns)
{
    OutputWriter writer{"first_and_last_columns.txt"};
    const string outputFileName = string(writer.get_fileName()) + '.' + string(writer.get_extension());

    // Fill the grid with alive cells only in first and last columns
    const vector<Cell> cellValues = {
        {'*'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'*'},
    };
    const size_t gridColSize{cellValues.size()};

    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());

    const bool result{writer.writeIteration(grid, gridColSize)};
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n");

    // Clean up the generated file
    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(UTWriteIterationWithoutOptionalArgument, LivingCellsInFirstAndLastLines)
{
    OutputWriter writer{"first_and_last_lines.txt"};
    const string outputFileName = string(writer.get_fileName()) + '.' + string(writer.get_extension());

    // Fill the grid with alive cells only in first and last lines
    const vector<Cell> cellAliveValues = {
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'}
    };
    const vector<Cell> cellDeadValues = {
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'}
    };
    const size_t gridColSize{cellAliveValues.size()};

    grid.insert(grid.end(), cellAliveValues.begin(), cellAliveValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellAliveValues.begin(), cellAliveValues.end());

    const bool result{writer.writeIteration(grid, gridColSize, 0)}; // Alive and Dead cells share the same column size
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "**********\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "**********\n");

    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(UTWriteIterationWithoutOptionalArgument, AllDeadCells)
{
    OutputWriter writer{"all_cells_are_dead.txt"};
    const string outputFileName = string(writer.get_fileName()) + '.' + string(writer.get_extension());

    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'}
    };
    const size_t gridColSize{cellValues.size()};

    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());

    const bool result{writer.writeIteration(grid, gridColSize)};
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n");

    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(UTWriteIterationWithoutOptionalArgument, AllLivingCells)
{
    OutputWriter writer{"all_cells_are_alive.txt"};
    const string outputFileName = string(writer.get_fileName()) + '.' + string(writer.get_extension());

    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'}
    };
    const size_t gridColSize{cellValues.size()};

    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());

    const bool result{writer.writeIteration(grid, gridColSize)};
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n");

    std::remove(outputFileName.c_str());

    grid.clear();
}

/****************************************  Tests Suite for writeIteration function with the optional iteration argument set ***************************************/

TEST(UTWriteIterationWithOptionalArgument, LivingCellsInFirstAndLastColumns)
{
    OutputWriter writer{"first_and_last_columns.txt"};
    const unsigned int iteration{10};
    const string outputFileName =
        string(writer.get_fileName()) + '_' + to_string(iteration) + '.' + string(writer.get_extension());

    // Fill the grid with alive cells only in first and last columns
    const vector<Cell> cellValues{
        {'*'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'*'}
    };
    const size_t gridColSize{cellValues.size()};

    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());

    const bool result{writer.writeIteration(grid, gridColSize, iteration)};
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n"
              "*--------*\n");

    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(UTWriteIterationWithOptionalArgument, LivingCellsInFirstAndLastLines)
{
    OutputWriter writer{"first_and_last_lines.txt"};
    const unsigned int iteration{111};
    const string outputFileName =
        string(writer.get_fileName()) + '_' + to_string(iteration) + '.' + string(writer.get_extension());

    // Fill the grid with alive cells only in first and last lines
    const vector<Cell> cellAliveValues = {
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'}
    };
    const vector<Cell> cellDeadValues = {
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'}
    };
    const size_t gridColSize{cellAliveValues.size()};

    grid.insert(grid.end(), cellAliveValues.begin(), cellAliveValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellDeadValues.begin(), cellDeadValues.end());
    grid.insert(grid.end(), cellAliveValues.begin(), cellAliveValues.end());

    const bool result{writer.writeIteration(grid, gridColSize, iteration)};
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "**********\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "**********\n");

    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(UTWriteIterationWithOptionalArgument, AllDeadCells)
{
    OutputWriter writer{"all_cells_are_dead.txt"};
    const unsigned int iteration{123456789};
    const string outputFileName =
        string(writer.get_fileName()) + '_' + to_string(iteration) + '.' + string(writer.get_extension());

    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'},
        {'-'}
    };
    const size_t gridColSize{cellValues.size()};

    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());

    const bool result{writer.writeIteration(grid, gridColSize, iteration)};
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n"
              "----------\n");

    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(UTWriteIterationWithOptionalArgument, AllLivingCells)
{
    OutputWriter writer{"all_cells_are_alive.txt"};
    const unsigned int iteration{0};
    const string outputFileName =
        string(writer.get_fileName()) + '.' + string(writer.get_extension());

    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'},
        {'*'}
    };
    const size_t gridColSize{cellValues.size()};

    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());
    grid.insert(grid.end(), cellValues.begin(), cellValues.end());

    const bool result{writer.writeIteration(grid, gridColSize, iteration)};
    const string fileOutput{UTILITIES::readFile(outputFileName)};

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileOutput,
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n"
              "**********\n");

    std::remove(outputFileName.c_str());

    grid.clear();
}
