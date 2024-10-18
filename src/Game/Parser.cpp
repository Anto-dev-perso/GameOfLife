#include "Parser.hpp"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>

using namespace std;

// Another possibility would be to return an optional (with std::move) but it makes the binary heavier for a non-significant gain
std::tuple<gridOfCells, std::size_t, std::size_t> Parser::parseInputFile()
{
    gridOfCells readGrid;
    size_t lineLength{0};
    size_t columnLength{0};

    ifstream file{_file.data()};
    if (!file.is_open())
    {
        cerr << "ERROR: file " << _file << " cannot be open !" << endl;
    }
    else
    {
        string line;
        while (getline(file, line))
        {
            lineLength++;

            if (columnLength > 0)
            {
                // Force all the line to have the same length (nb of column)
                if (line.size() != columnLength)
                {
                    cerr << "ERROR in parsing of file " << _file << ", length of current line is " << line.size() << " but previous lines was " << columnLength << " .Be consistent with the length between all the lines !" << endl;
                    readGrid.clear();
                    break;
                }
            }
            else
            {
                columnLength = line.size();
            }

            // Fill directly the line of the vector
            // Use end()-1 because we won't parse the end line string
            try
            {
                readGrid.insert(readGrid.end(), line.begin(), line.end() - 1);
            }
            catch (const invalid_argument &e)
            {
                cerr << "ERROR " << e.what() << " in parsing of following line : '" << line << "'. Allows characters are "
                     << getAliveChar()
                     << " for alive cells and " << getDeadChar() << " for dead cells.\nPlease correct the file "
                     << _file << " with these characters" << endl;
                readGrid.clear();
                break;
            }
        }
    }
    file.close();

    // Reduce by 1 the column length because we didn't keep the \r column
    columnLength--;
    return {readGrid, lineLength, columnLength};
}
