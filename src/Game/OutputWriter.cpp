#include "OutputWriter.hpp"
#include "AllowedChar.hpp"

#include <iostream>

using namespace std;

OutputWriter::OutputWriter(std::string_view nameWithExtension) : _fileName(
        nameWithExtension.substr(0, nameWithExtension.find_last_of('.'))) {}

// This method is in charge of writing the output file
// It needs to take the gridOfCells as inputs
// The function take an optional int value corresponding to the iteration wanted in case of --all
bool OutputWriter::writeIteration(const gridOfCells &grid, unsigned int iteration) {

    const string outputFileName = (iteration == 0) ? (_fileName + '.' + _extension) : (_fileName + '_' +
                                                                                       to_string(iteration) + '.' +
                                                                                       _extension);

    // TODO warn the user that a file with that name already exist and as been backup (eventually)
    ofstream file(outputFileName);
    if (!file.is_open()) {
        cerr << "ERROR: Failed to create file: " << outputFileName
             << endl;
        return false;
    } else {
        for (const auto &line: grid) {
            for (const auto &column: line) {
                file << boolToChar(column.get_isCurrentlyAlive());
            }
            file << "\n";
        }
        file.close();
        cout << "File created successfully: " << outputFileName << endl;
        return true;
    }

}

std::string_view OutputWriter::get_fileName() const { return _fileName; }

std::string_view OutputWriter::get_extension() const { return _extension; }
