#include "Parser.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

// Another possibility would be to return an optional (with std::move) but it makes the binary heavier for a non-significant gain
gridOfCells Parser::parseInputFile() {
    gridOfCells readGrid;

    ifstream file{_file.data()};
    size_t lineLength{0};
    if (!file.is_open()) {
        cerr << "ERROR: file " << _file << " cannot be open !" << endl;
    } else {
        string line;
        while (getline(file, line)) {

            if (lineLength > 0) {
                // Force all the line to have the same length (nb of column
                if (line.size() != lineLength) {
                    cerr << "ERROR in parsing of file " << _file << ", length of current line is " << line.size()
                         << " but previous lines was " << lineLength
                         << " .Be consistent with the length between all the lines !" << endl;
                    readGrid.clear();
                    break;
                }
            } else {
                lineLength = line.size();
            }

            // Fill directly the line of the vector
            // Use end()-1 because we won't parse the end line string
            try {
                readGrid.emplace_back(line.begin(), line.end() - 1);
            } catch (const invalid_argument &e) {
                cerr << "ERROR in parsing of following line : '" << line << "'. Allows characters are "
                     << getAliveChar()
                     << " for alive cells and " << getDeadChar() << " for dead cells.\nPlease correct the file "
                     << _file << " with these characters" << endl;
                readGrid.clear();
                break;
            }
        }
    }
    file.close();

    return readGrid;
}
