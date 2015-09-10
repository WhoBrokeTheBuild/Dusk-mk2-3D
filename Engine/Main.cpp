#include <Program.h>

#include <Utility/Benchmark.h>
#include <Scripting/ScriptingSystem.h>
#include <Tracking/MemoryTracker.h>
#include <Logging/LoggingSystem.h>
#include <Utility/Console.h>
#include <Utility/Platform.h>

using namespace Dusk::Tracking;
using namespace Dusk::Logging;
using namespace Dusk::Scripting;

void initLoggingSystem(void) {
	DuskBenchStart();

	LoggingSystem::AddLevel(4, "error");
	LoggingSystem::AddLevel(3, "info");
	LoggingSystem::AddLevel(2, "debug");
	LoggingSystem::AddLevel(1, "perf");
	LoggingSystem::AddLevel(0, "verbose");

	LoggingSystem::AddConsoleLogger("error");
	LoggingSystem::AddConsoleLogger("info");
	LoggingSystem::AddConsoleLogger("debug");
	LoggingSystem::AddConsoleLogger("perf");
	LoggingSystem::AddConsoleLogger("verbose");

	LoggingSystem::AddFileLogger("error", "error.log");
	LoggingSystem::AddFileLogger("error", "info.log");
	LoggingSystem::AddFileLogger("info", "info.log");
	LoggingSystem::AddFileLogger("debug", "info.log");
	LoggingSystem::AddFileLogger("perf", "info.log");
	LoggingSystem::AddFileLogger("perf", "perf.log");
	LoggingSystem::AddFileLogger("verbose", "info.log");

	LoggingSystem::SetLevelForegroundColor("error", LOG_FG_RED);
	LoggingSystem::SetLevelForegroundColor("info", LOG_FG_BLUE);
	LoggingSystem::SetLevelForegroundColor("debug", LOG_FG_GREEN);
	LoggingSystem::SetLevelForegroundColor("perf", LOG_FG_YELLOW);

	LoggingSystem::SetLoggingLevel("verbose");

	DuskLog("verbose", "Finished LoggingSystem setup");
	DuskBenchEnd("main::initLoggingSystem");
}

int main(int argc, char* argv[])
{
	MemoryTracker::Init();

	initLoggingSystem();

	LoggingSystem::InitScripting();

	Dusk::Program* pProgram = Dusk::Program::Inst();

	DuskLog("verbose", "Program instance created");

    pProgram->Run();

	DuskLog("verbose", "Program has finished running");

    delete pProgram;

	DuskLog("verbose", "Program deleted, preparing to close logs");

	LoggingSystem::CloseAllLoggers();

#ifdef DUSK_DEBUG_BUILD

	if (MemoryTracker::AllocationCount() > 0)
	{
		MemoryTracker::PrintAllocations();
		Dusk::Utility::ConsolePause();
	}

#endif // DUSK_DEBUG_BUILD

	MemoryTracker::Term();

    return 0;
}
