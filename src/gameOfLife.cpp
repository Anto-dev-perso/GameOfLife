#include "InputChecker.hpp"
#include "Game/Game.hpp"

#ifdef ENABLE_CPU_PROFILING
#include <gperftools/profiler.h>
#endif

#ifdef ENABLE_HEAP_PROFILING
#include <gperftools/heap-profiler.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{

#ifdef ENABLE_CPU_PROFILING
    ProfilerStart("cpu_profiling.prof");
#endif

#ifdef ENABLE_HEAP_PROFILING
    HeapProfilerStart("heap_profiling.prof");
#endif

    static InputChecker checker;
    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    if (!inputsValids) { return 1; }

    static Game gameOfLife(filePath, nbOfIterations, outputAllIterations);
    if (!gameOfLife.init()) { return 1; }

    const bool processReturn = gameOfLife.process();
#ifdef ENABLE_CPU_PROFILING
    ProfilerStop(); 
#endif

#ifdef ENABLE_HEAP_PROFILING
    HeapProfilerDump("Heap profiling") ;
    HeapProfilerStop();
#endif

    // True==1 but 1 is an error return so return the opposite of the return
    return !processReturn;
}
