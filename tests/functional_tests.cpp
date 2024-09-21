#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>

#include "../tests/tests_utilities.hpp"

using namespace std;

int main(int argc, char **argv) {
    // Run only tests beginning by FT (Functional Tests)
    ::testing::GTEST_FLAG(filter) = "FT*";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

/****************************************  Tests Suite for static patterns ***************************************/


TEST(FTStaticPatterns, BlockPattern) {
    const unsigned int iteration{5};
    const string fileName{"../tests/input_files/still_lifes/block"};
    const string inputFile{UTILITIES::readFile(fileName + ".txt")};

    const string cmd{"./GameOfLife --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);
    for (unsigned int i = 1; i <= iteration; i++) {
        const string iterFile{fileName + "_" + to_string(i) + ".res"};
        EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile))
                            << "ERROR with iteration " << i;
        remove(iterFile.c_str());
    }
}

/****************************************  Tests Suite for oscillators patterns ***************************************/
TEST(FTOscillatorPatterns, BlinkerPattern) {
    const unsigned int iteration{4};
    const string fileName{"../tests/input_files/oscillators/blinkerG"};

    const string inputFileOdd{UTILITIES::readFile(fileName + "2.txt")};
    const string inputFileEven{UTILITIES::readFile(fileName + "1.txt")};

    const string cmd{"./GameOfLife --input " + fileName + "1.txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);
    for (unsigned int i = 1; i <= iteration; i++) {
        const string inputFile{(i % 2 == 0) ? inputFileEven : inputFileOdd};
        const string iterFile{fileName + "1_" + to_string(i) + ".res"};
        EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile))
                            << "ERROR with iteration " << i;
        remove(iterFile.c_str());
    }

}

/****************************************  Tests Suite for spaceship patterns ***************************************/

TEST(FTSpaceshipPatterns, BlinkerPattern) {
    const unsigned int iteration{4};
    const string fileName{"../tests/input_files/spaceship/gliderG"};
    const string inputFile{UTILITIES::readFile(fileName + "5.txt")};

    const string cmd{"./GameOfLife --input " + fileName + "1.txt --iterations " + to_string(iteration)};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);
    const string iterFile{fileName + "1.res"};
    EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());

}

/****************************************  Tests Suite for random patterns ***************************************/

TEST(FTRandomPatterns, RandomPattern) {
    const unsigned int iteration{3};
    const string fileName{"../tests/input_files/random"};
    const string resultExpected{"-------\r\n---**--\r\n---*-*-\r\n-------\r\n-------\r\n---***-\r\n-------\r\n"};

    const string cmd{"./GameOfLife --input " + fileName + ".txt --iterations " + to_string(iteration)};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());

}
/****************************************  Tests Suite for single linging cell ***************************************/

TEST(FTSingleCell, SingleLinvingCell) {
    const unsigned int iteration{2};
    const string fileName{"../tests/input_files/single"};
    const string resultExpected{"---\r\n---\r\n---\r\n"};

    const string cmd{"./GameOfLife --input " + fileName + ".txt --iterations " + to_string(iteration)};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());

}

/****************************************  Tests Suite for large patterns ***************************************/

TEST(FTLargePatterns, LargePattern) {
    const unsigned int iteration{3};
    const string fileName{"../tests/input_files/large"};
    const string inputFile{UTILITIES::readFile(fileName + ".txt")};

    const string cmd{"./GameOfLife --input " + fileName + ".txt --iterations " + to_string(iteration)};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());

}

/****************************************  Tests Suite for performance scenario ***************************************/

TEST(FTPerformancePatterns, RPentominoPattern) {
    const unsigned int iteration{1000};
    const string fileName{"../tests/input_files/spaceship/rPentomino"};
    const string resultExpected{UTILITIES::readFile(fileName + "G" + to_string(iteration) + ".txt")}; // TODO

    const string cmd{"./GameOfLife --input " + fileName + ".txt --iterations " + to_string(iteration)};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());

}

TEST(FTPerformancePatterns, GosperGliderGunPattern) {
    const unsigned int iteration{500};
    const string fileName{"../tests/input_files/spaceship/gosperGliderGun"};
    const string resultExpected{"---\r\n---\r\n---\r\n"}; // TODO

    const string cmd{"./GameOfLife --input " + fileName + ".txt --iterations " + to_string(iteration)};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());

}
