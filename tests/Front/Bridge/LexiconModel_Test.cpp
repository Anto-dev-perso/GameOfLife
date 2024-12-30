#include <gtest/gtest.h>
#include "Front/Bridge/LexiconModel.hpp"
#include "Back/Game/Game.hpp"

#include "../tests_utilities.hpp"
#include "../tests/Back/tests_utilities.hpp"

class LexiconModelTest : public ::testing::Test
{
protected:
    std::vector<pattern> mockPatterns;
    std::unique_ptr<LexiconNameModel> nameModel;

    void SetUp() override
    {
        // Initialize mock patterns
        for (int i = 0; i < 3; ++i)
        {
            pattern p;
            p._name = "Pattern " + std::to_string(i + 1);

            if (i == 1)
            {
                // Second pattern: populated grid data
                for (int j = 0; j < 2; ++j)
                {
                    board_data gridData{
                        {{'*'}, {'-'}, {'-'}, {'*'},}, 2, 2
                    };
                    p._descriptionAndPattern.push_back({
                        "Description " + std::to_string(i + 1) + " " + std::to_string(j + 1), gridData
                    });
                }
            }
            else if (i == 2)
            {
                // Third pattern: large grid data
                board_data gridData{grid_of_cells(100 * 100, {'-'}), 100, 100}; // Large 100x100 grid
                for (size_t index = 0; index < gridData.line * gridData.column; ++index)
                {
                    if (index % 2 == 0)
                    {
                        gridData.grid[index] = {'*'};
                    }
                }
                p._descriptionAndPattern.push_back({"Large Description", gridData});
            }

            mockPatterns.push_back(std::move(p));
        }

        nameModel = std::make_unique<LexiconNameModel>(mockPatterns);
    }
};

TEST_F(LexiconModelTest, LexiconNameModel)
{
    ASSERT_EQ(nameModel->rowCount(), 3);

    EXPECT_EQ(nameModel->data(nameModel->index(0, 0), LexiconNameModel::NameRole).toString().toStdString(),
              "Pattern 1");
    EXPECT_EQ(nameModel->data(nameModel->index(1, 0), LexiconNameModel::NameRole).toString().toStdString(),
              "Pattern 2");
    EXPECT_EQ(nameModel->data(nameModel->index(2, 0), LexiconNameModel::NameRole).toString().toStdString(),
              "Pattern 3");

    //Bound check
    EXPECT_FALSE(nameModel->data(nameModel->index(-1, 0)).isValid());
    EXPECT_FALSE(nameModel->data(nameModel->index(3, 0)).isValid());
}


TEST_F(LexiconModelTest, LexiconDescriptionModel)
{
    const auto descriptionModel = nameModel->get_descriptionModel();

    // Test rowCount
    ASSERT_EQ(descriptionModel->rowCount(), 3);


    // Test data retrieval
    ASSERT_FALSE(descriptionModel->data(descriptionModel->index(0, 0), LexiconGridModel::GridRole).isValid());

    EXPECT_EQ(descriptionModel->getSizeForIndex(0), 0);
    EXPECT_FALSE(descriptionModel->checkIfGridIsntEmpty(0,0));

    EXPECT_EQ(descriptionModel->getSizeForIndex(1), 2);
    EXPECT_TRUE(descriptionModel->checkIfGridIsntEmpty(1,0));
    EXPECT_EQ(descriptionModel->getData(1, 0, LexiconGridModel::GridRole).toString().toStdString(), "Description 2 1");

    EXPECT_TRUE(descriptionModel->checkIfGridIsntEmpty(1,1));
    EXPECT_EQ(descriptionModel->getData(1, 1, LexiconGridModel::GridRole).toString().toStdString(), "Description 2 2");

    EXPECT_EQ(descriptionModel->getSizeForIndex(2), 1);
    EXPECT_TRUE(descriptionModel->checkIfGridIsntEmpty(2,0));
    EXPECT_EQ(descriptionModel->getData(2, 0, LexiconGridModel::GridRole).toString().toStdString(),
              "Large Description");

    //Out of bound check
    EXPECT_FALSE(descriptionModel->checkIfGridIsntEmpty(-1,0));
    EXPECT_EQ(descriptionModel->getSizeForIndex(3), -1);
    EXPECT_FALSE(descriptionModel->getData(3, 0, LexiconGridModel::GridRole).isValid());
}

TEST_F(LexiconModelTest, LexiconGridModel)
{
    const auto gridModel = nameModel->get_descriptionModel()->get_gridModel();
    const board_data line1Grid{{{'*'}, {'-'}, {'-'}, {'*'},}, 2, 2};
    board_data line2Grid{grid_of_cells(100 * 100, {'-'}), 100, 100}; // Large 100x100 grid
    for (size_t i = 0; i < line2Grid.line * line2Grid.column; ++i)
    {
        if (i % 2 == 0)
        {
            line2Grid.grid[i] = {'*'};
        }
    }

    // Test rowCount
    ASSERT_EQ(gridModel->rowCount(), 3);

    // Test data retrieval
    ASSERT_FALSE(gridModel->data(gridModel->index(0, 0), LexiconGridModel::GridRole).isValid());


    EXPECT_EQ(gridModel->getSizeForIndex(0,0), -1);
    EXPECT_EQ(gridModel->getLineCountForIndex(0,0), -1);
    EXPECT_EQ(gridModel->getColumnCountForIndex(0,0), -1);
    UTILITIES::compareGrid(UTILITIES::getGridFromModel(0, 0, *gridModel), {});

    EXPECT_EQ(gridModel->getSizeForIndex(1,0), 4);
    EXPECT_EQ(gridModel->getLineCountForIndex(1,0), 2);
    EXPECT_EQ(gridModel->getColumnCountForIndex(1,0), 2);
    UTILITIES::compareGrid(UTILITIES::getGridFromModel(1, 0, *gridModel), line1Grid);

    EXPECT_EQ(gridModel->getSizeForIndex(1,1), 4);
    EXPECT_EQ(gridModel->getLineCountForIndex(1,1), 2);
    EXPECT_EQ(gridModel->getColumnCountForIndex(1,1), 2);
    UTILITIES::compareGrid(UTILITIES::getGridFromModel(1, 1, *gridModel), line1Grid);

    EXPECT_EQ(gridModel->getSizeForIndex(2,0), 10000);
    EXPECT_EQ(gridModel->getLineCountForIndex(2,0), 100);
    EXPECT_EQ(gridModel->getColumnCountForIndex(2,0), 100);
    UTILITIES::compareGrid(UTILITIES::getGridFromModel(2, 0, *gridModel), line2Grid);

    //Out of bound check
    EXPECT_EQ(gridModel->getSizeForIndex(3,0), -1);
    EXPECT_EQ(gridModel->getSizeForIndex(-1,0), -1);
    EXPECT_EQ(gridModel->getSizeForIndex(0,1), -1);
    EXPECT_EQ(gridModel->getSizeForIndex(0,-1), -1);

    EXPECT_EQ(gridModel->getLineCountForIndex(3,0), -1);
    EXPECT_EQ(gridModel->getLineCountForIndex(-1,0), -1);
    EXPECT_EQ(gridModel->getLineCountForIndex(0,1), -1);
    EXPECT_EQ(gridModel->getLineCountForIndex(0,-1), -1);

    EXPECT_EQ(gridModel->getColumnCountForIndex(3,0), -1);
    EXPECT_EQ(gridModel->getColumnCountForIndex(-1,0), -1);
    EXPECT_EQ(gridModel->getColumnCountForIndex(0,1), -1);
    EXPECT_EQ(gridModel->getColumnCountForIndex(0,-1), -1);

    EXPECT_FALSE(gridModel->getData(3, 0, LexiconGridModel::GridRole).isValid());
    EXPECT_FALSE(gridModel->getData(-1, 0, LexiconGridModel::GridRole).isValid());
    EXPECT_FALSE(gridModel->getData(0, 1, LexiconGridModel::GridRole).isValid());
    EXPECT_FALSE(gridModel->getData(0, -1, LexiconGridModel::GridRole).isValid());
}


// Test using real backend data
TEST(BackendData, RealBackendData)
{
    auto backend = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
    if (!backend->init())
    {
        throw std::ios_base::failure("Failed to initialize backend");
    }
    const LexiconNameModel nameModelWithBackend{backend->get_lexiconPatterns()};
    const auto descriptionModel{nameModelWithBackend.get_descriptionModel()};
    const auto gridModel{descriptionModel->get_gridModel()};


    // Validate the model with real data

    constexpr int lexiconId{1378};
    constexpr int gridId{0};
    ASSERT_EQ(nameModelWithBackend.rowCount(), lexiconId+1);
    ASSERT_EQ(descriptionModel->rowCount(), lexiconId+1);
    ASSERT_EQ(gridModel->rowCount(), lexiconId+1);

    EXPECT_EQ(nameModelWithBackend.data(nameModelWithBackend.index(lexiconId), LexiconNameModel::NameRole).
              toString().toStdString(), "zweiback");
    EXPECT_EQ(descriptionModel->getData(lexiconId, gridId, LexiconDescriptionModel::DescriptionRole).toString().
              toStdString(),
              "(p30)  An oscillator in which two {HW volcano}es {hassle} a {loaf}.  This was found by Mark Niemiec in February 1995.  A smaller version using Scot Ellison's reduced HW volcano is shown below.");


    UTILITIES::compareGrid(UTILITIES::getGridFromModel(lexiconId, gridId, *gridModel), UTILITIES::zweiback);
}
