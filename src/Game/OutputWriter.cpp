#include "OutputWriter.hpp"
#include "AllowedChar.hpp"

#include <iostream>
#include <string>
#include <string_view>

using namespace std;

OutputWriter::OutputWriter(string_view nameWithExtension) : _fileName(
                                                                nameWithExtension.substr(0, nameWithExtension.find_last_of('.'))) {}

// This method is in charge of writing the output file
// It needs to take the gridOfCells as inputs
// The function take an optional int value corresponding to the iteration wanted in case of --all
bool OutputWriter::writeIteration(const gridOfCells &grid, size_t numColumn, unsigned int iteration)
{

    const string outputFileName = (iteration == 0) ? (string(_fileName) + '.' + _extension) : (string(_fileName) + '_' + to_string(iteration) + '.' + _extension);

    // TODO warn the user that a file with that name already exist and has been backup (eventually)
    ofstream file{outputFileName};
    if (!file.is_open())
    {
        cerr << "ERROR: Failed to create file: " << outputFileName << endl;
        return false;
    }
    else
    {
        for (size_t line = 0; line < grid.size(); line += numColumn)
        {
            for (size_t column = 0; column < numColumn; column++)
            {
                file << boolToChar(grid[line + column].get_isCurrentlyAlive());
            }
            file << "\n";
        }
    }
    file.close();
    cout << "File created successfully: " << outputFileName << endl;
    return true;
}

string_view OutputWriter::get_fileName() const { return _fileName; }

string OutputWriter::get_extension() const { return _extension; }
