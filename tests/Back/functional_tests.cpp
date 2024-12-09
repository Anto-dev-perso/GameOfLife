#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>

#include "../tests/Back/tests_utilities.hpp"

#include <filesystem>

using namespace std;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#ifdef WIN32
    const string exe{std::filesystem::absolute("Debug/GameOfLife.exe").string()};
#else
const string exe{"./GameOfLife"};
#endif

const string inputPath{filesystem::canonical("../tests/Back/input_files").string()};
const string stillLifePath{filesystem::path(inputPath + "/still_lifes").string()};
const string oscillatorsPath{filesystem::path(inputPath + "/oscillators").string()};
const string spaceshipPath{filesystem::path(inputPath + "/spaceship").string()};


/****************************************  Tests Suite for static patterns ***************************************/

TEST(FTStaticPatterns, BlockPattern)
{
    constexpr unsigned int iteration{5};
    const filesystem::path filePath{stillLifePath + "/block"};
    const string fileName{filePath.string()};
    const string inputFile{UTILITIES::readFile(fileName + "_res.txt")};


    const string cmd{exe + " --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);
    for (unsigned int i = 1; i <= iteration; i++)
    {
        const string iterFile{fileName + "_" + to_string(i) + ".res"};
        EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile))
            << "ERROR with iteration " << i;
        remove(iterFile.c_str());
    }
    remove(string(fileName + ".res").c_str());
}

/****************************************  Tests Suite for oscillators patterns ***************************************/
TEST(FTOscillatorPatterns, BlinkerPattern)
{
    constexpr unsigned int iteration{4};
    const filesystem::path filePath{oscillatorsPath + "/blinkerG"};
    const string fileName{filePath.string()};

    const string inputFileOdd{UTILITIES::readFile(fileName + "2_res.txt")};
    const string inputFileEven{UTILITIES::readFile(fileName + "1_res.txt")};

    const string cmd{exe + " --input " + fileName + "1.txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);
    for (unsigned int i = 1; i <= iteration; i++)
    {
        const string inputFile{(i % 2 == 0) ? inputFileEven : inputFileOdd};
        const string iterFile{fileName + "1_" + to_string(i) + ".res"};
        EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile))
            << "ERROR with iteration " << i;
        remove(iterFile.c_str());
    }
    remove(string(fileName + ".res").c_str());
}

/****************************************  Tests Suite for spaceship patterns ***************************************/

TEST(FTSpaceshipPatterns, BlinkerPattern)
{
    constexpr unsigned int iteration{4};
    const filesystem::path filePath{spaceshipPath + "/gliderG"};
    const string fileName{filePath.string()};
    const string inputFile{UTILITIES::readFile(fileName + "5.txt")};

    const string cmd{exe + " --input " + fileName + "1.txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);
    const string iterFile{fileName + "1.res"};
    EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());
}

/****************************************  Tests Suite for random patterns ***************************************/

TEST(FTRandomPatterns, RandomPattern)
{
    constexpr unsigned int iteration{3};
    const filesystem::path filePath{inputPath + "/random"};
    const string fileName{filePath.string()};
    const string resultExpected{"-------\n---**--\n---*-*-\n-------\n-------\n---***-\n-------\n"};

    const string cmd{exe + " --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());
}

/****************************************  Tests Suite for single linging cell ***************************************/

TEST(FTSingleCell, SingleLinvingCell)
{
    constexpr unsigned int iteration{2};
    const filesystem::path filePath{inputPath + "/single"};
    const string fileName{filePath.string()};
    const string resultExpected{"---\n---\n---\n"};

    const string cmd{exe + " --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());
}

/****************************************  Tests Suite for large patterns ***************************************/

TEST(FTLargePatterns, LargePattern)
{
    constexpr unsigned int iteration{3};
    const filesystem::path filePath{inputPath + "/large"};
    const string fileName{filePath.string()};
    const string inputFile{UTILITIES::readFile(fileName + ".txt")};

    const string cmd{exe + " --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    string expected{UTILITIES::readFile(iterFile)};
    EXPECT_EQ(inputFile, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());
}

/****************************************  Tests Suite for performance scenario ***************************************/

TEST(FTPerformancePatterns, BigGridStable)
{
    constexpr unsigned int iteration{2};
    const filesystem::path filePath{inputPath + "/bigStable"};
    const string fileName{filePath.string()};
    const string resultExpected{UTILITIES::readFile(fileName + ".txt")};

    const string cmd{exe + " --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());
}

TEST(FTPerformancePatterns, RPentominoPattern)
{
    constexpr unsigned int iteration{1000};
    const filesystem::path filePath{spaceshipPath + "/rPentomino"};
    const string fileName{filePath.string()};
    const string resultExpected{UTILITIES::readFile(fileName + "G" + to_string(iteration) + ".txt")};

    const string cmd{exe + " --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());
}

TEST(FTPerformancePatterns, GosperGliderGunPattern)
{
    constexpr unsigned int iteration{500};
    const filesystem::path filePath{spaceshipPath + "/gosperGliderGun"};
    const string fileName{filePath.string()};
    const string resultExpected{UTILITIES::readFile(fileName + "G" + to_string(iteration) + ".txt")};

    const string cmd{exe + " --input " + fileName + ".txt --iterations " + to_string(iteration) + " --all"};

    const int exitCode = std::system(cmd.c_str());

    ASSERT_EQ(exitCode, 0);

    const string iterFile{fileName + ".res"};
    EXPECT_EQ(resultExpected, UTILITIES::readFile(iterFile));
    remove(iterFile.c_str());
}
