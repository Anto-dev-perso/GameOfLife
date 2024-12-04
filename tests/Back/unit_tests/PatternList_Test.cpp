#include <gtest/gtest.h>
#include "Back/Game/PatternList.hpp"
#include "Back/Game/Parser.hpp"

#include "../tests/Back/tests_utilities.hpp"

using namespace std;

static const auto lexicon{
    std::get<PatternList>(Parser("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON).parseFile())
};


/****************************************  Tests Suite for addPattern  ***************************************/

TEST(UTPAddPattern, AddPatternTest)
{
    PatternList patterns;
    patterns.addPattern("blinkerPatternG1", {{"blinkerPatternG1 description", UTILITIES::blinkerPatternG1}});

    EXPECT_EQ(patterns.get_numberOfPatternTotal(), 1);
    EXPECT_EQ(patterns.get_list_const_ref().at(0)._name, "blinkerPatternG1");
    EXPECT_EQ(patterns.get_list_const_ref().at(0)._descriptionAndPattern.at(0)._description,
              "blinkerPatternG1 description");
    UTILITIES::compareGrid(patterns.get_list_const_ref().at(0)._descriptionAndPattern.at(0)._gridPattern,
                           UTILITIES::blinkerPatternG1);


    patterns.addPattern("pulsarPattern", {
                            {"pulsarPatternG1 description", UTILITIES::pulsarPatternG1},
                            {"pulsarPatternG2 description", UTILITIES::pulsarPatternG2},
                            {"pulsarPatternG3 description", UTILITIES::pulsarPatternG3}
                        });

    EXPECT_EQ(patterns.get_numberOfPatternTotal(), 4);

    EXPECT_EQ(patterns.get_list_const_ref().at(1)._name, "pulsarPattern");
    EXPECT_EQ(patterns.get_list_const_ref().at(1)._descriptionAndPattern.at(0)._description,
              "pulsarPatternG1 description");
    EXPECT_EQ(patterns.get_list_const_ref().at(1)._descriptionAndPattern.at(1)._description,
              "pulsarPatternG2 description");
    EXPECT_EQ(patterns.get_list_const_ref().at(1)._descriptionAndPattern.at(2)._description,
              "pulsarPatternG3 description");

    UTILITIES::compareGrid(patterns.get_list_const_ref().at(1)._descriptionAndPattern.at(0)._gridPattern,
                           UTILITIES::pulsarPatternG1);
    UTILITIES::compareGrid(patterns.get_list_const_ref().at(1)._descriptionAndPattern.at(1)._gridPattern,
                           UTILITIES::pulsarPatternG2);
    UTILITIES::compareGrid(patterns.get_list_const_ref().at(1)._descriptionAndPattern.at(2)._gridPattern,
                           UTILITIES::pulsarPatternG3);
}

/****************************************  Tests Suite for findIndexForPatterNamed  ***************************************/

TEST(UTFindIndex, FindIndexTest)
{
    auto lexIndex{lexicon.findIndexForPatternNamed("glider")};
    EXPECT_EQ(lexIndex.patternIndex, 479);
    EXPECT_EQ(lexIndex.gridIndex, 0);

    lexIndex = lexicon.findIndexForPatternNamed("glider", 1);
    EXPECT_EQ(lexIndex.patternIndex, 479);
    EXPECT_EQ(lexIndex.gridIndex, 1);

    lexIndex = lexicon.findIndexForPatternNamed("washerwoman");
    EXPECT_EQ(lexIndex.patternIndex, 1341);
    EXPECT_EQ(lexIndex.gridIndex, 0);

    lexIndex = lexicon.findIndexForPatternNamed("Orion");
    EXPECT_EQ(lexIndex.patternIndex, 820);
    EXPECT_EQ(lexIndex.gridIndex, 0);

    lexIndex = lexicon.findIndexForPatternNamed("Orion", 1);
    EXPECT_EQ(lexIndex.patternIndex, 820);
    EXPECT_EQ(lexIndex.gridIndex, 1);

    lexIndex = lexicon.findIndexForPatternNamed("bi-loaf");
    EXPECT_EQ(lexIndex.patternIndex, 133);
    EXPECT_EQ(lexIndex.gridIndex, 0);

    lexIndex = lexicon.findIndexForPatternNamed("bi-loaf", 1);
    EXPECT_EQ(lexIndex.patternIndex, 133);
    EXPECT_EQ(lexIndex.gridIndex, 1);

    lexIndex = lexicon.findIndexForPatternNamed("bi-loaf", 2);
    EXPECT_EQ(lexIndex.patternIndex, 133);
    EXPECT_EQ(lexIndex.gridIndex, 2);

    // Index out of range
    try
    {
        lexIndex = lexicon.findIndexForPatternNamed("bi-loaf", 3);
        ASSERT_EQ(lexIndex.patternIndex, -1) <<
 "Exception shall has been raised because the index ask for is out of the bound of the pattern";
    }
    catch (const out_of_range& e1)
    {
        EXPECT_EQ(string(e1.what()),
                  "ERROR: try to find pattern named bi-loaf which exist but you ask for the index 3 but it is not in the bound [0;0]");
    }

    // Pattern name doesn't exist
    try
    {
        lexIndex = lexicon.findIndexForPatternNamed("NA");
        ASSERT_EQ(lexIndex.patternIndex, -1) <<
 "Exception shall has been raised because the pattern name doesn't exist !";
    }
    catch (const std::runtime_error& e2)
    {
        EXPECT_EQ(string(e2.what()), "ERROR: try to find pattern named NA but it doesn't exist in the lexicon !");
    }
}

/****************************************  Tests Suite for getPatternForIndices  ***************************************/

TEST(UTGetIndices, GetPatternIndicesTest)
{
    UTILITIES::compareGrid(lexicon.getPatternForIndices(479, 0), UTILITIES::gliderP1);
    UTILITIES::compareGrid(lexicon.getPatternForIndices(479, 1), UTILITIES::gliderP2);

    UTILITIES::compareGrid(lexicon.getPatternForIndices(1341, 0), UTILITIES::washerwoman);

    UTILITIES::compareGrid(lexicon.getPatternForIndices(0, 0), {});

    try
    {
        std::ignore = lexicon.getPatternForIndices(-1, 0);
        ASSERT_EQ(0, 1) << "Expected out_of_range";
    }
    catch (...)
    {
        //Test Ok
    }
    try
    {
        std::ignore = lexicon.getPatternForIndices(1380, 0);
        ASSERT_EQ(0, 1) << "Expected out_of_range";
    }
    catch (...)
    {
        //Test Ok
    }
    try
    {
        std::ignore = lexicon.getPatternForIndices(0, -1);
        ASSERT_EQ(0, 1) << "Expected out_of_range";
    }
    catch (...)
    {
        // Test Ok
    }
    UTILITIES::compareGrid(lexicon.getPatternForIndices(1378, 0), UTILITIES::zweiback);
    try
    {
        std::ignore = lexicon.getPatternForIndices(1379, 0);
        ASSERT_EQ(0, 1) << "Expected out_of_range";
    }
    catch (...)
    {
        //Test Ok
    }
}
