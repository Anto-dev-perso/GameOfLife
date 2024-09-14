#include "InputChecker.hpp"
#include <string>
#include <unistd.h>
#include <iostream>

#include <optional>
#include <tuple>

using namespace std;

// Function to check the inputs arguments of the whole program
// Return <false, "", 0, false> if one or multiple inputs are invalid
tuple<bool, string, unsigned int, bool> InputChecker::checkInputs(int argc, char **argv) const {

    // Code copy/paste from https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
    int opt;
    string input = "";
    bool flagA = false;
    bool flagB = false;

    // Retrieve the (non-option) argument:
    if ((argc <= 1) || (argv[argc - 1] == NULL) || (argv[argc - 1][0] == '-')) {  // there is NO input...
        cerr << "No argument provided!" << endl;
        //return 1;
    } else {  // there is an input...
        input = argv[argc - 1];
    }

    // Debug:
    cout << "input = " << input << endl;

    // Shut GetOpt error messages down (return '?'):
    opterr = 0;

    // Retrieve the options:
    while ((opt = getopt(argc, argv, "ab")) != -1) {  // for each option...
        switch (opt) {
            case 'a':
                flagA = true;
                break;
            case 'b':
                flagB = true;
                break;
            default:  // unknown option...
                cerr << "Unknown option: '" << char(optopt) << "'!" << endl;
                break;
        }
    }

    // Debug:
    cout << "flagA = " << flagA << endl;
    cout << "flagB = " << flagB << endl;

}
