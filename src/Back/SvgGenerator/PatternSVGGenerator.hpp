#pragma once


#include "qcoreapplication.h"
#include <QDir>
#include <QSvgGenerator>
#include <QPainter>
#include <QPen>

#include "Board.hpp"
#include "Parser.hpp"

const QColor BORDER_COLOR{"#989898"};
const QColor CELL_ALIVE_COLOR{"#ffff00"};
const QColor CELL_DEAD_COLOR{"#7e7e7e"};
static constexpr int CELL_SIZE{5};

inline QString findRootDir(const QString& startDir = QCoreApplication::applicationDirPath()) noexcept
{
    QDir dir(startDir);
    while (dir.exists() && !dir.isRoot())
    {
        if (dir.exists("CMakeLists.txt"))
        {
            return dir.absolutePath();
        }
        dir.cdUp();
    }
    return {};
}

inline bool savePatternAsSVG(const board_data& input, QDir& lexiconDir, size_t patternIndex, size_t gridIndex)
{
    // Return directly if the grid is empty (just description)
    if (input.column == 0 || input.line == 0
    )
    {
        return true;
    }
    const int width{static_cast<int>(input.column)};
    const int height{static_cast<int>(input.line)};


    QSvgGenerator generator;
    generator.setFileName(lexiconDir.filePath(std::string{
        "pattern_" + std::to_string(patternIndex) + "_" + std::to_string(gridIndex) + ".svg"
    }.data()));
    generator.setSize(QSize{width * CELL_SIZE, height * CELL_SIZE});
    generator.setViewBox(QRect(0, 0, width * CELL_SIZE, height * CELL_SIZE));

    if (generator.size().isEmpty()) { throw std::runtime_error("ERROR SVGGenerator is empty"); }

    QPainter painter;
    if (!painter.begin(&generator)) { throw std::runtime_error("ERROR Can't begin to paint"); }

    QFont defaultFont{painter.font()};
    defaultFont.setPointSizeF(CELL_SIZE * 0.5);
    painter.setFont(defaultFont);

    QPen pen(BORDER_COLOR);
    pen.setWidth(1);
    painter.setPen(pen);

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            QColor fillColor(CELL_DEAD_COLOR);
            if (input.grid[row * width + col].get_isCurrentlyAlive())
            {
                fillColor = QColor(CELL_ALIVE_COLOR);
            }
            painter.setBrush(fillColor);
            painter.drawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }

    return painter.end();
}

inline bool iterateThroughAllPatternsAndGenerateThem(const std::vector<pattern>& patterns, QDir& assetDir) noexcept
{
    size_t patternIndex{0};

    for (const auto& [patternName, descAndPattern] : patterns)
    {
        size_t gridIndex{0};
        for (const auto& [ignore, grid] : descAndPattern)
        {
            if (!savePatternAsSVG(grid, assetDir, patternIndex, gridIndex)) { return false; }
            gridIndex++;
        }
        patternIndex++;
    }
    return true;
}

inline bool generateAllFile()
{
    const QString rootSrcDir{findRootDir()};
    if (rootSrcDir.isEmpty())
    {
        throw std::runtime_error("ERROR : cannot find sources dir from current");
    }
    QDir assetDir{rootSrcDir + "/src/Front/assets"};
    if (!assetDir.exists())
    {
        throw std::runtime_error("ERROR : cannot find asset dir from sources");
    }

    QDir lexiconFile{assetDir.absolutePath() + "/lexicon.txt"};
    if (!lexiconFile.isReadable())
    {
        throw std::runtime_error("ERROR : cannot open lexicon.txt file");
    }


    Parser parser{lexiconFile.absolutePath().toStdString(), TypeOfFileToParse::LEXICON};
    const auto patterns{std::get<PatternList>(parser.parseFile()).get_list_const_ref()};


    QDir lexiconDir{assetDir.absolutePath() + "/svg/lexicon"};
    if (!lexiconDir.exists())
    {
        throw std::runtime_error("ERROR : cannot find lexicon dir from sources");
    }

    return iterateThroughAllPatternsAndGenerateThem(patterns, lexiconDir);
}
