#include <Program.h>

#include <Tracking/MemoryTracker.h>
#include <Logging/LoggingSystem.h>
#include <Utility/Console.h>
#include <Utility/Platform.h>

using namespace Dusk::Tracking;
using namespace Dusk::Logging;

int main(int argc, char* argv[])
{
	MemoryTracker::Init();

	LoggingSystem::AddLevel(3, "error");
	LoggingSystem::AddLevel(2, "info");
	LoggingSystem::AddLevel(1, "debug");
	LoggingSystem::AddLevel(0, "verbose");

	LoggingSystem::AddFileLogger("error",   "error.log");
	LoggingSystem::AddFileLogger("info",    "info.log");
	LoggingSystem::AddFileLogger("debug",   "info.log");
	LoggingSystem::AddFileLogger("verbose", "info.log");

	LoggingSystem::AddConsoleLogger("error");
	LoggingSystem::AddConsoleLogger("info");
	LoggingSystem::AddConsoleLogger("debug");
	LoggingSystem::AddConsoleLogger("verbose");

	LoggingSystem::SetLevelForegroundColor("error", LOG_FG_RED);
	LoggingSystem::SetLevelForegroundColor("info",  LOG_FG_BLUE);
	LoggingSystem::SetLevelForegroundColor("debug", LOG_FG_GREEN);

	LoggingSystem::SetLoggingLevel("info");

	DuskLog("verbose", "Finished LoggingSystem setup");

	Dusk::Program* pProgram = Dusk::Program::Inst();

	DuskLog("verbose", "Program instance created");

    pProgram->Run();

	DuskLog("verbose", "Program has finished running");

    delete pProgram;

	DuskLog("verbose", "Program deleted, preparing to close logs");

	LoggingSystem::CloseAllLoggers();

#ifdef DUSK_DEBUG_BUILD

	if (MemoryTracker::AllocationCount() > 0)
		MemoryTracker::PrintAllocations();

#endif // DUSK_DEBUG_BUILD

	MemoryTracker::Term();

	Dusk::Utility::ConsolePause();

    return 0;
}
