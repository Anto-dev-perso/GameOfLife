#include "InputChecker.hpp"
#include "Game/Game.hpp"

#ifdef ENABLE_PROFILING
#include <gperftools/profiler.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{

#ifdef ENABLE_PROFILING
    ProfilerStart("profiler_output.pprof");
#endif

    static InputChecker checker;
    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    if (!inputsValids)
    {
        return 1;
    }

    static Game gameOfLife(filePath, nbOfIterations, outputAllIterations);

    const bool processReturn = gameOfLife.process();
#ifdef ENABLE_PROFILING
    ProfilerStop(); // Stop the profiler
#endif

    // True==1 but 1 is an error return so return the opposite of the return
    return !processReturn;
}
