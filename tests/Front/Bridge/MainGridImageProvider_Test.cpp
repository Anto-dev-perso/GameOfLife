#include <gtest/gtest.h>
#include "Front/Bridge/MainGridImageProvider_Test.hpp"


#include "../tests_utilities.hpp"
#include "../../Back/tests_utilities.hpp"

using namespace std;


TEST(MainGridImageProviderConstructorTest, ConstructorInitializesProperly)
{
    std::shared_ptr<Game> realGame{
        std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON)
    };
    std::ignore = realGame->init();
    ASSERT_NO_THROW(MainGridImageProvider_Test{realGame});
}


/****************************************  Tests Suite for CalculateLinearValue ***************************************/

class CalculateLinearValueTest : public ::testing::Test
{
};

TEST_F(CalculateLinearValueTest, BasicCases)
{
    constexpr double x1{1.0}, y1{2.0}, x2{3.0}, y2{6.0};

    // Slope m = (y2 - y1) / (x2 - x1) = 2.0
    // Intercept c = y1 - m * x1 = 0.0
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(2.0,y1, y2, x1, x2), 4.0);
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(3.0,y1, y2, x1, x2), 6.0);
}

TEST_F(CalculateLinearValueTest, HorizontalLine)
{
    constexpr double x1{1.0}, y1{3.0}, x2{5.0}, y2{3.0};

    // Horizontal line: y = 3.0
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(2.0,y1, y2, x1, x2), 3.0);
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(10.0,y1, y2, x1, x2), 3.0);
}

TEST_F(CalculateLinearValueTest, VerticalLine)
{
    constexpr double x1 = {2.0}, y1 = {1.0}, x2 = {2.0}, y2 = {5.0};

    // Vertical line: Undefined slope, should throw an exception
    EXPECT_THROW(std::ignore= MainGridImageProvider_Test::calculateLinearValue(2.0,y1, y2, x1, x2),
                 std::invalid_argument);
}

TEST_F(CalculateLinearValueTest, Interpolation)
{
    constexpr double x1{0.0}, y1{0.0}, x2{10.0}, y2{10.0};

    // Diagonal line: y = x
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(5.0,y1, y2, x1, x2), 5.0);
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(7.5,y1, y2, x1, x2), 7.5);
}

TEST_F(CalculateLinearValueTest, Extrapolation)
{
    constexpr double x1{2.0}, y1{4.0}, x2{4.0}, y2{8.0};

    // Line equation: y = 2x
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(1.0,y1, y2, x1, x2), 2.0); // Before x1
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(5.0,y1, y2, x1, x2), 10.0); // After x2
}

TEST_F(CalculateLinearValueTest, LargeValues)
{
    constexpr double x1 = {1e6}, y1{2e6}, x2{3e6}, y2{6e6};

    // Slope m = (y2 - y1) / (x2 - x1) = 2.0
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(2e6,y1, y2, x1, x2), 4e6);
}

TEST_F(CalculateLinearValueTest, SmallAndNegativeValues)
{
    constexpr double x1{-5.0}, y1{-10.0}, x2{0.0,}, y2{-5.0};

    // Line equation: y = x + -5.0
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(-2.5,y1, y2, x1, x2), -7.5);
    EXPECT_DOUBLE_EQ(MainGridImageProvider_Test::calculateLinearValue(1.0,y1, y2, x1, x2 ), -4.0);
}

/****************************************  Tests Suite for set_zoomValue ***************************************/

TEST(SetZoomValue, CheckValue)
{
    std::shared_ptr<Game> realGame{
        std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON)
    };
    std::ignore = realGame->init();
    auto provider{MainGridImageProvider_Test{realGame}};

    provider.set_zoomValue(0);
    EXPECT_DOUBLE_EQ(provider.get_zoomValue(), 0);
    EXPECT_DOUBLE_EQ(provider.get_scaleFactor(), 1);

    provider.set_zoomValue(100);
    EXPECT_DOUBLE_EQ(provider.get_zoomValue(), 100);
    EXPECT_DOUBLE_EQ(provider.get_scaleFactor(), 10);

    provider.set_zoomValue(12.5);
    EXPECT_DOUBLE_EQ(provider.get_zoomValue(), 12.5);
    EXPECT_DOUBLE_EQ(provider.get_scaleFactor(), 2.125);

    provider.set_zoomValue(70);
    EXPECT_DOUBLE_EQ(provider.get_zoomValue(), 70);
    EXPECT_DOUBLE_EQ(provider.get_scaleFactor(), 7.2999999999999998);
}

TEST(SetZoomValue, ValueUnchanged)
{
    std::shared_ptr<Game> realGame{
        std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON)
    };
    std::ignore = realGame->init();
    auto provider{MainGridImageProvider_Test{realGame}};

    const auto valueBefore{provider.get_zoomValue()};
    const auto scaleBefore{provider.get_scaleFactor()};
    provider.set_zoomValue(provider.get_zoomValue());
    EXPECT_DOUBLE_EQ(provider.get_zoomValue(), valueBefore);
    EXPECT_DOUBLE_EQ(provider.get_scaleFactor(), scaleBefore);
}


/****************************************  Tests Suite for UpdateGridCounters ***************************************/

class UpdateGridCountersTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }
};

TEST_F(UpdateGridCountersTest, NormalCase)
{
    provider->updateGridCounters();

    EXPECT_EQ(provider->_gridFirstRow, 122);
    EXPECT_EQ(provider->_gridFirstColumn, 247);

    realGame->updateBoard(UTILITIES::loafPattern);

    provider->updateGridCounters();
    EXPECT_EQ(provider->_gridFirstRow, 122);
    EXPECT_EQ(provider->_gridFirstColumn, 247);

    realGame->updateBoard(UTILITIES::beaconPatternG2);

    provider->updateGridCounters();
    EXPECT_EQ(provider->_gridFirstRow, 122);
    EXPECT_EQ(provider->_gridFirstColumn, 247);

    realGame->updateBoard(UTILITIES::zweiback);

    provider->updateGridCounters();
    EXPECT_EQ(provider->_gridFirstRow, 112);
    EXPECT_EQ(provider->_gridFirstColumn, 228);
}

TEST_F(UpdateGridCountersTest, ZeroDimensions)
{
    realGame->updateBoard({});
    provider->updateGridCounters();

    EXPECT_EQ(provider->_gridFirstRow, -1);
    EXPECT_EQ(provider->_gridFirstColumn, -1);
}

TEST_F(UpdateGridCountersTest, BackendLargerThanUIGrid)
{
    realGame->updateBoard({
        grid_of_cells(provider->NB_UI_LINES_AT_MAX * (provider->NB_UI_COLUMNS_AT_MAX + 1), {'*'}),
        provider->NB_UI_LINES_AT_MAX, provider->NB_UI_COLUMNS_AT_MAX + 1
    });
    provider->updateGridCounters();

    EXPECT_EQ(provider->_gridFirstRow, -1);
    EXPECT_EQ(provider->_gridFirstColumn, -1);
}

// Test effect of grid counters on subsequent calculations
TEST_F(UpdateGridCountersTest, EffectOnSubsequentCalculations)
{
    provider->updateGridCounters();

    // Calculate a UI index
    constexpr Game::line_column backendIndex{1, 1};
    constexpr Game::line_column expected{123, 248};
    auto uiIndex = provider->calculateUIIndexFromBackId(backendIndex);

    ASSERT_TRUE(uiIndex.has_value());
    EXPECT_EQ(uiIndex.value(), expected);
}

/****************************************  Tests Suite for CalculateIndexFromUIRow ***************************************/

class CalculateIndexFromUIRowTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }
};

TEST_F(CalculateIndexFromUIRowTest, ValidMapping)
{
    constexpr size_t uiRow{122};
    constexpr size_t uiCol{247};

    const auto backendIndex{provider->calculateIndexFromUIRow(uiRow, uiCol)};
    ASSERT_TRUE(backendIndex.has_value());
    EXPECT_EQ(backendIndex.value(), 0);
}

TEST_F(CalculateIndexFromUIRowTest, PatternsSampling)
{
    realGame->updateBoard(UTILITIES::zweiback);
    constexpr size_t uiRow{122};
    constexpr size_t uiCol{247};

    auto backendIndex{provider->calculateIndexFromUIRow(uiRow, uiCol)};
    ASSERT_TRUE(backendIndex.has_value());
    EXPECT_EQ(backendIndex.value(), 0);

    realGame->updateBoard(UTILITIES::tubPattern);

    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_TRUE(backendIndex.has_value());
    EXPECT_EQ(backendIndex.value(), 0);
}

TEST_F(CalculateIndexFromUIRowTest, BoundaryConditions)
{
    size_t uiRow{124};
    size_t uiCol{249};

    auto backendIndex{provider->calculateIndexFromUIRow(uiRow, uiCol)};
    ASSERT_TRUE(backendIndex.has_value());
    EXPECT_EQ(backendIndex.value(), 12);


    uiRow = 126;
    uiCol = 251;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_TRUE(backendIndex.has_value());
    EXPECT_EQ(backendIndex.value(), 24);
}

TEST_F(CalculateIndexFromUIRowTest, OutOfBounds)
{
    size_t uiRow{127};
    size_t uiCol{252};

    auto backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 127;
    uiCol = 251;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 127;
    uiCol = 247;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 127;
    uiCol = 246;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 121;
    uiCol = 247;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 121;
    uiCol = 246;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 121;
    uiCol = 251;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 121;
    uiCol = 252;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());

    uiRow = 122;
    uiCol = 246;
    backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    ASSERT_FALSE(backendIndex.has_value());
}

TEST_F(CalculateIndexFromUIRowTest, NegativeOffsets)
{
    provider->_gridFirstRow = -1;
    provider->_gridFirstColumn = -1;

    size_t uiRow = 0, uiCol = 0;
    auto backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    EXPECT_FALSE(backendIndex.has_value());
}

TEST_F(CalculateIndexFromUIRowTest, OffsetEffect)
{
    provider->_gridFirstRow = 0;
    provider->_gridFirstColumn = 0;

    size_t uiRow = 3, uiCol = 3;
    auto backendIndex = provider->calculateIndexFromUIRow(uiRow, uiCol);
    EXPECT_TRUE(backendIndex.has_value());
    EXPECT_EQ(backendIndex.value(), 18);
}

/****************************************  Tests Suite for ReDrawMainGrid ***************************************/

class ReDrawMainGridTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }
};

TEST_F(ReDrawMainGridTest, BasicRedraw)
{
    realGame->updateBoard(UTILITIES::pulsarPatternG2);
    provider->reDrawMainGrid();

    UTILITIES::compareQImage(UTILITIES::pulsarPatternG2, *provider);

    realGame->updateBoard(UTILITIES::tubPattern);
    provider->reDrawMainGrid();

    UTILITIES::compareQImage(UTILITIES::tubPattern, *provider);

    realGame->updateBoard(UTILITIES::pentaDecathlonPatternG11);
    provider->reDrawMainGrid();

    UTILITIES::compareQImage(UTILITIES::pentaDecathlonPatternG11, *provider);
}

TEST_F(ReDrawMainGridTest, EmptyBackEnd)
{
    realGame->updateBoard({});
    provider->reDrawMainGrid();

    UTILITIES::compareQImage({}, *provider);
}

/****************************************  Tests Suite for resetMainGrid ***************************************/

class ResetMainGridTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }

    void runIteration(int times = 1) const noexcept
    {
        for (int i = 0; i < times; ++i)
        {
            realGame->increment_nbOfIterations();
            std::ignore = realGame->applyRulesToTheBoard();
        }
    }
};

TEST_F(ResetMainGridTest, PatternsSampling)
{
    realGame->changeBoard(1378, 0);
    runIteration(100);
    provider->resetMainGrid();
    ASSERT_EQ(realGame->get_nbOfIterations(), 0);
    UTILITIES::compareGrid(realGame->get_board_data(), UTILITIES::zweiback);
}

/****************************************  Tests Suite for clearMainGrid ***************************************/

class ClearMainGridTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }
};

TEST_F(ClearMainGridTest, PatternsSampling)
{
    provider->clearMainGrid();
    UTILITIES::compareQImage({}, *provider);

    realGame->updateBoard(UTILITIES::pentaDecathlonPatternG4);
    provider->clearMainGrid();
    UTILITIES::compareQImage({}, *provider);

    realGame->updateBoard(UTILITIES::washerwoman);
    provider->clearMainGrid();
    UTILITIES::compareQImage({}, *provider);
}

TEST_F(ClearMainGridTest, AlreadyClearedGrid)
{
    provider->clearMainGrid();
    UTILITIES::compareQImage({}, *provider);

    provider->clearMainGrid();
    UTILITIES::compareQImage({}, *provider);
}

/****************************************  Tests Suite for CalculateUIIndexFromBackId ***************************************/

class CalculateUIIndexFromBackIdTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }
};

TEST_F(CalculateUIIndexFromBackIdTest, BasicMapping)
{
    constexpr Game::line_column backendIndex{1, 1};
    constexpr Game::line_column expectedUIIndex{123, 248};

    const auto uiIndex = provider->calculateUIIndexFromBackId(backendIndex);

    ASSERT_TRUE(uiIndex.has_value());
    EXPECT_EQ(uiIndex.value(), expectedUIIndex);
}

TEST_F(CalculateUIIndexFromBackIdTest, RealPatterns)
{
    realGame->updateBoard(UTILITIES::beaconPatternG1);
    Game::line_column backendIndex{5, 5};
    Game::line_column expectedUIIndex{127, 252};

    auto uiIndex{provider->calculateUIIndexFromBackId(backendIndex)};

    ASSERT_TRUE(uiIndex.has_value());
    EXPECT_EQ(uiIndex.value(), expectedUIIndex);


    realGame->updateBoard(UTILITIES::washerwoman);
    backendIndex = {3, 30};
    expectedUIIndex = {125, 277};

    uiIndex = provider->calculateUIIndexFromBackId(backendIndex);

    ASSERT_TRUE(uiIndex.has_value());
    EXPECT_EQ(uiIndex.value(), expectedUIIndex);
}


TEST_F(CalculateUIIndexFromBackIdTest, BoundaryConditions)
{
    constexpr Game::line_column backendIndex{0, 0};
    constexpr Game::line_column expectedUIIndex{122, 247};

    const auto uiIndex = provider->calculateUIIndexFromBackId(backendIndex);

    ASSERT_TRUE(uiIndex.has_value());
    EXPECT_EQ(uiIndex.value(), expectedUIIndex);
}

TEST_F(CalculateUIIndexFromBackIdTest, OutOfBoundsBackendIndex)
{
    const Game::line_column backendIndex{
        realGame->get_board_const()->get_lineLength(), realGame->get_board_const()->get_colLength()
    };

    const auto uiIndex = provider->calculateUIIndexFromBackId(backendIndex);

    ASSERT_FALSE(uiIndex.has_value());
}

TEST_F(CalculateUIIndexFromBackIdTest, GridCounterEffect)
{
    provider->_gridFirstRow = 0;
    provider->_gridFirstColumn = 0;
    constexpr Game::line_column backendIndex{1, 1};
    constexpr Game::line_column expectedUIIndex{1, 1};

    const auto uiIndex = provider->calculateUIIndexFromBackId(backendIndex);

    ASSERT_TRUE(uiIndex.has_value());
    EXPECT_EQ(uiIndex.value(), expectedUIIndex);
}

TEST_F(CalculateUIIndexFromBackIdTest, EmptyBackend)
{
    provider->_gridFirstRow = -1;
    provider->_gridFirstColumn = -1;
    constexpr Game::line_column backendIndex{1, 1};

    const auto uiIndex = provider->calculateUIIndexFromBackId(backendIndex);

    ASSERT_FALSE(uiIndex.has_value());
}

/****************************************  Tests Suite for CalculateLinearValue ***************************************/

class PrintANewGridImageTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }

    void updateBoardAndGenerateNewImage(const board_data& inputGrid) const noexcept
    {
        realGame->updateBoard(inputGrid);

        provider->updateGridCounters();
        provider->printANewGridImage();
    }
};

TEST_F(PrintANewGridImageTest, BasicGridRendering)
{
    provider->printANewGridImage();
    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(realGame->get_board_data(), *provider);
}


TEST_F(PrintANewGridImageTest, MinimumGridSize)
{
    const board_data testGrid{
        {{'-'}},
        1, 1
    };
    realGame->updateBoard(testGrid);

    provider->updateGridCounters();
    provider->printANewGridImage();

    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(testGrid, *provider);
}


TEST_F(PrintANewGridImageTest, LargeGridSize)
{
    constexpr line_size rows{100};
    constexpr column_size cols{100};
    grid_of_cells toTest{};
    toTest.reserve(rows * cols);
    for (size_t id = 0; id < rows * cols; ++id)
    {
        toTest.emplace_back(id % 2 == 0 ? '*' : '-');
    }

    const board_data testGrid{toTest, rows, cols};

    realGame->updateBoard(testGrid);

    provider->reDrawMainGrid();

    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(testGrid, *provider);
}


TEST_F(PrintANewGridImageTest, FullyAliveAndFullyDeadGrids)
{
    // Fully alive grid
    board_data testGrid{
        {{'*'}, {'*'}, {'*'}, {'*'}},
        2, 2
    };
    updateBoardAndGenerateNewImage(testGrid);
    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(testGrid, *provider);

    // Fully dead grid
    testGrid.grid = {{'-'}, {'-'}, {'-'}, {'-'}};
    updateBoardAndGenerateNewImage(testGrid);
    EXPECT_EQ(provider->_cacheBuster, 3);
    UTILITIES::compareQImage(testGrid, *provider);
}


TEST_F(PrintANewGridImageTest, EmptyGrid)
{
    const board_data testGrid{};
    updateBoardAndGenerateNewImage(testGrid);
    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(testGrid, *provider);
}

TEST_F(PrintANewGridImageTest, PatterndsVerifications)
{
    board_data testGrid{UTILITIES::zweiback};
    updateBoardAndGenerateNewImage(testGrid);
    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(testGrid, *provider);

    testGrid = UTILITIES::orionP2;
    updateBoardAndGenerateNewImage(testGrid);
    EXPECT_EQ(provider->_cacheBuster, 3);
    UTILITIES::compareQImage(testGrid, *provider);

    testGrid = UTILITIES::gosperGliderGunPattern;
    updateBoardAndGenerateNewImage(testGrid);
    EXPECT_EQ(provider->_cacheBuster, 4);
    UTILITIES::compareQImage(testGrid, *provider);
}

/****************************************  Tests Suite for ChangeCellColors ***************************************/

class ChangeCellColorsTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }

    void updateBoardDataAtIndices(const std::vector<Game::indices_with_value>& indices) const noexcept
    {
        auto backBoard{realGame->get_board()};
        for (const auto& [indices,newValue] : indices)
        {
            std::ignore = backBoard->changeCellValue(indices.line * backBoard->get_colLength() + indices.column,
                                                     newValue);
        }
    }

    void updateDatas(const std::vector<Game::indices_with_value>& toUpdate) const
    {
        provider->changeCellColors(toUpdate);
        updateBoardDataAtIndices(toUpdate);
    }
};

TEST_F(ChangeCellColorsTest, BasicUpdate)
{
    // Define backend indices to change
    std::vector<Game::indices_with_value> updates = {
        {{0, 0}, true},
        {{1, 1}, true},
        {{2, 2}, true}
    };

    updateDatas(updates);
    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(realGame->get_board_data(), *provider);
}

TEST_F(ChangeCellColorsTest, BoundaryConditions)
{
    // Define backend indices to change
    std::vector<Game::indices_with_value> updates = {
        {{0, realGame->get_board_data().column}, true},
        {{realGame->get_board_data().line, 0}, true},
        {{realGame->get_board_data().line + 1, realGame->get_board_data().column + 1}, true}
    };

    const auto previousImage{provider->requestImage({}, {}, {})};
    provider->changeCellColors(updates);
    EXPECT_EQ(provider->_cacheBuster, 1);
    EXPECT_EQ(previousImage, provider->requestImage({}, {}, {}));
}

TEST_F(ChangeCellColorsTest, StressTest)
{
    realGame->updateBoard(UTILITIES::pentaDecathlonPatternG15);

    std::vector<Game::indices_with_value> updates;
    updates.reserve(UTILITIES::pentaDecathlonPatternG15.grid.size());
    // Create a large list of updates
    for (line_size row = 0; row < UTILITIES::pentaDecathlonPatternG15.line; ++row)
    {
        for (column_size col = 0; col < UTILITIES::pentaDecathlonPatternG15.column; ++col)
        {
            updates.push_back({
                {row, col}, !UTILITIES::pentaDecathlonPatternG15.grid.at(
                    row * UTILITIES::pentaDecathlonPatternG15.column + col).get_isCurrentlyAlive()
            });
        }
    }

    updateDatas(updates);
    EXPECT_EQ(provider->_cacheBuster, 2);
    UTILITIES::compareQImage(realGame->get_board_data(), *provider);

    updateDatas(updates);
    EXPECT_EQ(provider->_cacheBuster, 3);
    UTILITIES::compareQImage(realGame->get_board_data(), *provider);
}

TEST_F(ChangeCellColorsTest, EmptyUpdates)
{
    std::vector<Game::indices_with_value> updates{};

    updateDatas(updates);
    EXPECT_EQ(provider->_cacheBuster, 1);
    UTILITIES::compareQImage(realGame->get_board_data(), *provider);
}

/****************************************  Tests Suite for changeMainGridWithPatternIndices ***************************************/

class ChangeMainGridWithPatternIndicesTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> realGame;
    std::unique_ptr<MainGridImageProvider_Test> provider;

    void SetUp() noexcept override
    {
        realGame = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = realGame->init();
        provider = std::make_unique<MainGridImageProvider_Test>(realGame);
    }
};

TEST_F(ChangeMainGridWithPatternIndicesTest, InvalidPatternIndex)
{
    try
    {
        provider->changeMainGridWithPatternIndices(1379, 0);
        ASSERT_EQ(1, 0) << "Expect exception raised";
    }
    catch (...)
    {
    }

    try
    {
        provider->changeMainGridWithPatternIndices(-1, -1);
        ASSERT_EQ(1, 0) << "Expect exception raised";
    }
    catch (...)
    {
    }

    try
    {
        provider->changeMainGridWithPatternIndices(50000, -1);
        ASSERT_EQ(1, 0) << "Expect exception raised";
    }
    catch (...)
    {
    }
}

TEST_F(ChangeMainGridWithPatternIndicesTest, PatternsSampling)
{
    provider->changeMainGridWithPatternIndices(1378, 0);
    UTILITIES::compareGrid(realGame->get_board_data(), UTILITIES::zweiback);
}
