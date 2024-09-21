#include "InputChecker.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <unistd.h>

using namespace std;

// TODO input could be an absolute path

// Function to check the inputs arguments of the whole program
// Return <false, "", 0, false> if one or multiple inputs are invalid
tuple<bool, string_view, unsigned int, bool> InputChecker::checkInputs(int argc, char *argv[]) {

    // Check that at least one argument is given
    if ((argc <= 1) || !argv[argc - 1]) {
        cerr
                << "ERROR: No argument provided !\nInputs are ['--input <RELATIVE_FILE_PATH>'; '--iterations <NUMBER_OF_ITERATIONS>' ; '--all' (optional)]"
                << endl;
        return {false, "", 0, false};
    }

    string_view path{""};
    unsigned int iterations{0};
    bool inputsCorrect{true};
    bool outputAll{false};

    const vector<string_view> args_view(argv + 1, argv + argc);

    // Iterate by increments of 2 because at args_view[inputType] it is the argument type and at args_view[inputType+1] it is its value
    for (size_t inputType = 0; inputType < args_view.size(); inputType += 2) {

        string_view currentInput = args_view[inputType];

        if (currentInput == "--input") {
            path = args_view[inputType + 1];
        } else if (currentInput == "--iterations") {
            if (const auto iterationConverted = convertArgForIterations(
                        args_view[inputType + 1]);iterationConverted.has_value()) {
                iterations = iterationConverted.value();
            } else {
                inputsCorrect = false;
                break;
            }
        } else if (currentInput == "--all") {
            // Decrement the counter because --all doesn't has a value
            --inputType;
            outputAll = true;
        } else {
            cerr << "ERROR: Argument " << currentInput
                 << " isn't recognize.\n Allows input are ['--input <RELATIVE_FILE_PATH>'; '--iterations <NUMBER_OF_ITERATIONS>' ; '--all']"
                 << endl;
            inputsCorrect = false;
            break; // Stop the loop because we know we have to stop
        }
    }

    // Dealing with missing mandatory arguments
    if (path.empty()) {
        cerr << "ERROR: Missing mandatory argument : --input <RELATIVE_FILE_PATH>" << endl;
        inputsCorrect = false;
    }
    if (iterations == 0) {
        cerr << "ERROR: Missing mandatory argument : --iterations <NUMBER_OF_ITERATIONS>" << endl;
        inputsCorrect = false;
    }

    return {inputsCorrect, path, iterations, outputAll};

}

// Due to the number of possible way to go wrong, isolate iteration conversion to a dedicated function
optional<unsigned int> InputChecker::convertArgForIterations(std::string_view arg_path) {
    try {
        // Use stoi because it is easier to deal with the negative cases
        // Max positive value for the integer is OK (2 Billion) for the game of life
        // Workaround if the user want to do more than that : relaunch the program with the previous result as the new input
        const auto convertedIteration{stoi(arg_path.data())};
        if (convertedIteration < 0) {
            cerr << "ERROR: Iterations " << arg_path
                 << " is a negative number. Please retry with a positive number"
                 << endl;
            return {nullopt};
        }
        return {static_cast<unsigned int>(convertedIteration)};
    }
    catch (std::out_of_range &err) {
        cerr << "ERROR: Iterations " << arg_path
             << " is too high for a positive number. Please retry with a less higher number (lesser than "
             << numeric_limits<int>::max() << "), keep the result and relaunch this program"
             << endl;
        return {nullopt};
    }
    catch (...) {
        cerr << "ERROR: Iterations " << arg_path << " is not a number. Please retry with a positive number"
             << endl;
        return {nullopt};
    }
    return {nullopt};
}
