#include "Parser.hpp"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>

using namespace std;

bool Parser::parseLineOfGrid(board_data& boardRead, std::string& line) const noexcept
{
    boardRead.line++;
    // Check if the last character is '\r' and remove it if present (for Windows compatibility)
    if (!line.empty() && line.back() == '\r')
    {
        line.pop_back();
    }

    if (boardRead.column > 0)
    {
        // Force all the line to have the same length (nb of column)
        if (line.size() != boardRead.column - 2)
        {
            cerr << "ERROR in parsing of file " << _file << ", length of current line is " << line.size() <<
                " but previous lines was " << boardRead.column <<
                " .Be consistent with the length between all the lines !" << endl;
            return false;
        }
    }
    else
    {
        // +2 because we will add a column of dead cell at first and last
        boardRead.column = line.size() + 2;
        // Insert a line of empty cells at first
        boardRead.grid.insert(boardRead.grid.begin(), boardRead.column, getDeadChar());
        boardRead.line++;
    }

    // Fill directly the line of the vector
    try
    {
        boardRead.grid.emplace_back(getDeadChar());
        boardRead.grid.insert(boardRead.grid.end(), line.begin(), line.end());
        boardRead.grid.emplace_back(getDeadChar());
    }
    catch (const invalid_argument& e)
    {
        cerr << "ERROR " << e.what() << " in parsing of following line : '" << line <<
            "'. Allows characters are "
            << getAliveChar()
            << " for alive cells and " << getDeadChar() << " for dead cells.\nPlease correct the file "
            << _file << " with these characters" << endl;
        boardRead.grid.clear();
        return false;
    }
    return true;
}


// Another possibility would be to return an optional (with std::move) but it makes the binary heavier for a non-significant gain
board_data Parser::parseBoardFile() const noexcept
{
    board_data readGrid;
    if (ifstream file{_file}; !file.is_open())
    {
        cerr << "ERROR: file " << _file << " cannot be open !" << endl;
    }
    else
    {
        string line;

        while (getline(file, line))
        {
            if (!parseLineOfGrid(readGrid, line))
            {
                readGrid = {};

                return readGrid;
            }
        }
        // Insert a line of empty cells at last
        readGrid.grid.insert(readGrid.grid.end(), readGrid.column, getDeadChar());
        readGrid.line++;
    }

    return readGrid;
}

PatternList Parser::parseLexiconFile() const noexcept
{
    PatternList readPatterns{};
    if (ifstream file{_file}; !file.is_open())
    {
        cerr << "ERROR: file " << _file << " cannot be open !" << endl;
    }
    else
    {
        string line{}, patternName{}, patternDescription{};
        board_data patternGrid{};
        description_and_pattern_type readDescriptionsAndPatterns{};


        bool introBlaBlaIsSkipped{false};
        bool readOk{true};
        while (std::getline(file, line) && readOk)
        {
            // Empty line mean that we have finished the current pattern
            if (line.empty())
            {
                if (!patternName.empty())
                {
                    // Push one last line of dead cells
                    if (!patternGrid.grid.empty())
                    {
                        patternGrid.grid.insert(patternGrid.grid.end(), patternGrid.column, getDeadChar());
                        patternGrid.line++;
                    }
                    readDescriptionsAndPatterns.push_back({patternDescription, patternGrid});
                    readPatterns.addPattern(patternName, readDescriptionsAndPatterns);
                }
                patternName.clear();
                patternDescription.clear();
                patternGrid.clear();
                readDescriptionsAndPatterns.clear();
                continue;
            }

            // Check for the separator line first (line of '-')
            // this separator marj the beginning and the end of the pattern list
            if (std::all_of(line.begin(), line.end(), [](char c)
            {
                // If the line is entirely composed of '-', it means that we found the separator
                return c == LEXICON_INTRO_SEPARATOR;
            }))
            {
                if (!introBlaBlaIsSkipped)
                {
                    introBlaBlaIsSkipped = true;
                    continue;
                }
                else
                {
                    break;
                }
            }
            if (!introBlaBlaIsSkipped)
            {
                continue;
            }

            if (line.at(0) == LEXICON_NAME_SEPARATOR)
            {
                const auto endSeparatorPos = line.find(LEXICON_NAME_SEPARATOR, 1);
                patternName = line.substr(1, endSeparatorPos - 1);
                patternDescription = line.substr(endSeparatorPos + 1);
                trimLeadingSpaces(patternDescription);
            }

            else
            {
                // Remove first spaces from the line
                trimLeadingSpaces(line);
                // Search if it is the pattern of the description
                if (std::all_of(line.begin(), line.end(), [](char c)
                {
                    return c == '.' || c == '*';
                }))
                {
                    readOk = parseLineOfGrid(patternGrid, line);
                }
                else
                {
                    if (!patternGrid.empty())
                    {
                        // Insert a line of empty cells at last
                        patternGrid.grid.insert(patternGrid.grid.end(), patternGrid.column, getDeadChar());
                        patternGrid.line++;
                        readDescriptionsAndPatterns.push_back({patternDescription, patternGrid});
                        patternDescription.clear();
                        patternGrid.clear();
                    }
                    patternDescription += " " + line;
                }
            }
        }
    }
    return readPatterns;
}
