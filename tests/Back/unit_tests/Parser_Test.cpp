#include <gtest/gtest.h>
#include "Back/Game/Parser.hpp"

#include "../tests/Back/tests_utilities.hpp"

using namespace std;

/****************************************  Tests Suite for all reading the input files  ***************************************/

TEST(UTParseInputFile, ParseBlockPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/still_lifes/block.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::blockPattern);
}

TEST(UTParseInputFile, BeeHivePattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/still_lifes/beeHive.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::beeHivePattern);
}

TEST(UTParseInputFile, LoafPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/still_lifes/loaf.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::loafPattern);
}

TEST(UTParseInputFile, BoatPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/still_lifes/boat.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::boatPattern);
}

TEST(UTParseInputFile, TubPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/still_lifes/tub.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::tubPattern);
}

TEST(UTParseInputFile, BlinkerPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/blinkerG1.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::blinkerPatternG1);
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/blinkerG2.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::blinkerPatternG2);
}

TEST(UTParseInputFile, ToadPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/toadG1.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::toadPatternG1);
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/toadG2.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::toadPatternG2);
}

TEST(UTParseInputFile, BeaconPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/beaconG1.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::beaconPatternG1);
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/beaconG2.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::beaconPatternG2);
}

TEST(UTParseInputFile, PulsarPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/pulsarG1.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pulsarPatternG1);
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/pulsarG2.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pulsarPatternG2);
    UTILITIES::compareGrid(
        std::get<board_data>(
            Parser("../tests/Back/input_files/oscillators/pulsarG3.txt", TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pulsarPatternG3);
}

TEST(UTParseInputFile, PentaDecathlonPattern)
{
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG1.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG1);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG2.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG2);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG3.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG3);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG4.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG4);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG5.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG5);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG6.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG6);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG7.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG7);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG8.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG8);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG9.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG9);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG10.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG10);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG11.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG11);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG12.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG12);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG13.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG13);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG14.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG14);
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/oscillators/pentaDecathlonG15.txt",
                                    TypeOfFileToParse::BOARD).parseFile()),
        UTILITIES::pentaDecathlonPatternG15);
}

/****************************************  Tests Suite for robustness in parsing input file  ***************************************/

TEST(UTRobustnessInput, EmptyFileName)
{
    UTILITIES::compareGrid(std::get<board_data>(Parser("", TypeOfFileToParse::BOARD).parseFile()), {});
}

TEST(UTRobustnessInput, BadPath)
{
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("tests/input_files/block.txt", TypeOfFileToParse::BOARD).parseFile()), {});
}

TEST(UTRobustnessInput, BadLengthOfLines)
{
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/badFile1.txt", TypeOfFileToParse::BOARD).parseFile()),
        {});
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/badFile2.txt", TypeOfFileToParse::BOARD).parseFile()),
        {});
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/badFile3.txt", TypeOfFileToParse::BOARD).parseFile()),
        {});
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/badFile4.txt", TypeOfFileToParse::BOARD).parseFile()),
        {});
}

TEST(UTRobustnessInput, BadCharacter)
{
    UTILITIES::compareGrid(
        std::get<board_data>(Parser("../tests/Back/input_files/badFile5.txt", TypeOfFileToParse::BOARD).parseFile()),
        {});
}

/****************************************  Tests Suite for lexicon reading  ***************************************/

static const auto lexicon{
    std::get<PatternList>(Parser("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON).parseFile())
};

TEST(UTLexiconInput, GliderLexiconTest)
{
    const auto gliderRead{*lexicon.findPattern("glider")};

    EXPECT_EQ(gliderRead._name, "glider");
    EXPECT_EQ(gliderRead._descriptionAndPattern.size(), 2);

    EXPECT_EQ(gliderRead._descriptionAndPattern[0]._description,
              "(c/4 diagonally, p4)  The smallest, most common and first discovered {spaceship}.  This was found by Richard Guy in 1970 while Conway's group was attempting to track the {evolution} of the {R-pentomino}.  The name is due in part to the fact that it is {glide symmetric}.  (It is often stated that Conway discovered the glider, but he himself has said it was Guy.  See also the cryptic reference (\"some guy\") in {Winning Ways}.)");
    EXPECT_EQ(gliderRead._descriptionAndPattern[1]._description,
              " The term \"glider\" is also occasionally (mis)used to mean \"spaceship\".");

    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[0]._gridPattern, UTILITIES::gliderP1);
    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[1]._gridPattern, UTILITIES::gliderP2);
}

TEST(UTLexiconInput, WasherWomanLexiconTest)
{
    const auto gliderRead{*lexicon.findPattern("washerwoman")};

    EXPECT_EQ(gliderRead._name, "washerwoman");
    EXPECT_EQ(gliderRead._descriptionAndPattern.size(), 1);

    EXPECT_EQ(gliderRead._descriptionAndPattern[0]._description,
              "(2c/3 p18 fuse)  A {fuse} discovered by Earl Abbe, published in {LifeLine} Vol 3, September 1971.");

    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[0]._gridPattern, UTILITIES::washerwoman);
}

TEST(UTLexiconInput, OrionLexiconTest)
{
    const auto gliderRead{*lexicon.findPattern("Orion")};

    EXPECT_EQ(gliderRead._name, "Orion");
    EXPECT_EQ(gliderRead._descriptionAndPattern.size(), 2);

    EXPECT_EQ(gliderRead._descriptionAndPattern[0]._description,
              "(c/4 diagonally, p4)  Found by Hartmut Holzwart, April 1993.");
    EXPECT_EQ(gliderRead._descriptionAndPattern[1]._description,
              " In May 1999, Jason Summers found the following smaller variant:");

    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[0]._gridPattern, UTILITIES::orionP1);
    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[1]._gridPattern, UTILITIES::orionP2);
}

TEST(UTLexiconInput, 2c3LexiconTest)
{
    const auto gliderRead{*lexicon.findPattern("2c/3")};

    EXPECT_EQ(gliderRead._name, "2c/3");
    EXPECT_EQ(gliderRead._descriptionAndPattern.size(), 1);

    EXPECT_EQ(gliderRead._descriptionAndPattern[0]._description,
              "Two thirds of the speed of light - the speed of signals in a {2c/3 wire} or of some {against the grain} {negative spaceship} signals in the {zebra stripes} {agar}, and also the speed of {burn}ing of the {blinker fuse} and the {bi-block fuse}.");

    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[0]._gridPattern, {});
}


TEST(UTLexiconInput, BiLoafLexiconTest)
{
    const auto gliderRead{*lexicon.findPattern("bi-loaf")};

    EXPECT_EQ(gliderRead._name, "bi-loaf");
    EXPECT_EQ(gliderRead._descriptionAndPattern.size(), 3);

    EXPECT_EQ(gliderRead._descriptionAndPattern[0]._description,
              "This term has been used in at least three different senses. A bi-loaf can be half a {bakery}:");
    EXPECT_EQ(gliderRead._descriptionAndPattern[1]._description,
              " or it can be the following much less common {still life}:");
    EXPECT_EQ(gliderRead._descriptionAndPattern[2]._description,
              " or the following {pure glider generator}:");

    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[0]._gridPattern, UTILITIES::biLoafP1);
    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[1]._gridPattern, UTILITIES::biLoafP2);
    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[2]._gridPattern, UTILITIES::biLoafP3);
}

TEST(UTLexiconInput, SpaceshipLexiconTest)
{
    const auto gliderRead{*lexicon.findPattern("spaceship")};

    EXPECT_EQ(gliderRead._name, "spaceship");
    EXPECT_EQ(gliderRead._descriptionAndPattern.size(), 1);

    EXPECT_EQ(gliderRead._descriptionAndPattern[0]._description,
              "Any finite pattern that reappears (without additions or losses) after a number of generations and displaced by a non-zero amount.  By far the most {natural} spaceships are the {glider}, {LWSS}, {MWSS} and {HWSS}, followed by the {Coe ship} which has also evolved multiple times from random asymmetric {soup} starting conditions.  See also the entries on individual spaceship speeds: {c/2 spaceship}, {c/3 spaceship}, {c/4 spaceship}, {c/5 spaceship}, {c/6 spaceship}, {c/7 spaceship}, {c/10 spaceship}, {c/12 spaceship}, {2c/5 spaceship},  {2c/7 spaceship}, {3c/7 spaceship}, {(2,1)c/6 spaceship}, and {17c/45 spaceship}. It is known that there exist spaceships travelling in all rational directions and at arbitrarily slow speeds (see {universal constructor}).  Before 1989, however, the only known examples travelled at c/4 diagonally (gliders) or c/2 orthogonally (everything else). In 1989 Dean Hickerson started to use automated searches to look for new {elementary} spaceships, and had considerable success.  Other people have continued these searches using tools such as {lifesrc} and {gfind}, and as a result we now have a great variety of elementary spaceships travelling at sixteen different velocities. The following table details the discovery of elementary spaceships with new velocities as of July 2018.");

    UTILITIES::compareGrid(gliderRead._descriptionAndPattern[0]._gridPattern, {});
}
