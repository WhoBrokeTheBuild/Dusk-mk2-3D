#include <Program.h>

#include <Logging/LoggingSystem.h>

using namespace Dusk::Logging;

int main(int argc, char* argv[])
{
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
	LoggingSystem::SetLevelForegroundColor("info", LOG_FG_BLUE);
	LoggingSystem::SetLevelForegroundColor("debug", LOG_FG_GREEN);

	LoggingSystem::SetLoggingLevel("verbose");

	DuskLog("verbose", "Finished LoggingSystem setup");

	Dusk::Program* pProgram = Dusk::Program::Inst();

	DuskLog("verbose", "Program instance created");

    pProgram->Run();

	DuskLog("verbose", "Program has finished running");

    delete pProgram;

	DuskLog("verbose", "Program deleted, preparing to close logs");

	LoggingSystem::CloseAllLoggers();

    return 0;
}
