#include <gtest/gtest.h>
#include "Game/OutputWriter.hpp"

using namespace std;

// Helper function to read the content of a file into a string
string readFile(const std::string &filename) {
    ifstream infile(filename);
    return {istreambuf_iterator<char>(infile), istreambuf_iterator<char>()};
}

// Declare the grid globally to keep the memory allocated by the first test to be played
gridOfCells grid;


/****************************************  Tests Suite for all instantiations of OutputWriter ***************************************/

TEST(OutputWriterInstanciantion, IntantiateWithInitial) {

    const OutputWriter writer{"initial.txt"};

    EXPECT_EQ(writer.get_fileName(), "initial");
    EXPECT_EQ(writer.get_extension(), "res");
}

TEST(OutputWriterInstanciantion, IntantiateWithUpperCase) {

    const OutputWriter writer{"UPPER.txt"};

    EXPECT_EQ(writer.get_fileName(), "UPPER");
    EXPECT_EQ(writer.get_extension(), "res");
}

TEST(OutputWriterInstanciantion, IntantiateWithLongName) {

    const OutputWriter writer{"very_very_very_long_name_input.txt"};

    EXPECT_EQ(writer.get_fileName(), "very_very_very_long_name_input");
    EXPECT_EQ(writer.get_extension(), "res");
}

/****************************************  Tests Suite for writeIteration function without the optional iteration argument ***************************************/

TEST(WriteIterationWithoutOptionalArgument, LivingCellsInFirstAndLastColumns) {

    OutputWriter writer{"first_and_last_columns.txt"};
    const string outputFileName = writer.get_fileName() + '.' + string(writer.get_extension());


    // Fill the grid with alive cells only in first and last columns
    const vector<Cell> cellValues = {{true},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {true}};
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);

    const bool result{writer.writeIteration(grid)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(WriteIterationWithoutOptionalArgument, LivingCellsInFirstAndLastLines) {

    OutputWriter writer{"first_and_last_lines.txt"};
    const string outputFileName = writer.get_fileName() + '.' + string(writer.get_extension());


    // Fill the grid with alive cells only in first and last lines
    const vector<Cell> cellAliveValues = {{true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true}};
    const vector<Cell> cellDeadValues = {{false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false}};
    grid.emplace_back(cellAliveValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellAliveValues);

    const bool result{writer.writeIteration(grid)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(WriteIterationWithoutOptionalArgument, AllDeadCells) {

    OutputWriter writer{"all_cells_are_dead.txt"};
    const string outputFileName = writer.get_fileName() + '.' + string(writer.get_extension());


    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {{false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false}};
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);

    const bool result{writer.writeIteration(grid)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(WriteIterationWithoutOptionalArgument, AllLivingCells) {

    OutputWriter writer{"all_cells_are_alive.txt"};
    const string outputFileName = writer.get_fileName() + '.' + string(writer.get_extension());


    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {{true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true}};
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);

    const bool result{writer.writeIteration(grid)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}

/****************************************  Tests Suite for writeIteration function with the optional iteration argument set ***************************************/


TEST(WriteIterationWithOptionalArgument, LivingCellsInFirstAndLastColumns) {

    OutputWriter writer{"first_and_last_columns.txt"};
    const unsigned int iteration{10};
    const string outputFileName =
            writer.get_fileName() + '_' + to_string(iteration) + '.' + string(writer.get_extension());


    // Fill the grid with alive cells only in first and last columns
    const vector<Cell> cellValues = {{true},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {true}};
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);

    const bool result{writer.writeIteration(grid, iteration)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(WriteIterationWithOptionalArgument, LivingCellsInFirstAndLastLines) {

    OutputWriter writer{"first_and_last_lines.txt"};
    const unsigned int iteration{111};
    const string outputFileName =
            writer.get_fileName() + '_' + to_string(iteration) + '.' + string(writer.get_extension());


    // Fill the grid with alive cells only in first and last lines
    const vector<Cell> cellAliveValues = {{true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true},
                                          {true}};
    const vector<Cell> cellDeadValues = {{false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false},
                                         {false}};
    grid.emplace_back(cellAliveValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellDeadValues);
    grid.emplace_back(cellAliveValues);

    const bool result{writer.writeIteration(grid, iteration)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(WriteIterationWithOptionalArgument, AllDeadCells) {

    OutputWriter writer{"all_cells_are_dead.txt"};
    const unsigned int iteration{123456789};
    const string outputFileName =
            writer.get_fileName() + '_' + to_string(iteration) + '.' + string(writer.get_extension());


    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {{false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false},
                                     {false}};
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);

    const bool result{writer.writeIteration(grid, iteration)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}

TEST(WriteIterationWithOptionalArgument, AllLivingCells) {

    OutputWriter writer{"all_cells_are_alive.txt"};
    const unsigned int iteration{0};
    const string outputFileName =
            writer.get_fileName() + '.' + string(writer.get_extension());


    // Fill the grid with only dead cells
    const vector<Cell> cellValues = {{true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true},
                                     {true}};
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);
    grid.emplace_back(cellValues);

    const bool result{writer.writeIteration(grid, iteration)};
    const string fileOutput{readFile(outputFileName)};

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

    // Clean up the generated file (if needed)
    std::remove(outputFileName.c_str());

    grid.clear();
}
