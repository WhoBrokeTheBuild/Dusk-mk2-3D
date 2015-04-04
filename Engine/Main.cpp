#include <Program.h>

#include <Logging/LoggingSystem.h>

using namespace Dusk::Logging;

int main(int argc, char* argv[])
{
	LoggingSystem::AddLevel("info",     1);
	LoggingSystem::AddLevel("debug",    2);
	LoggingSystem::AddLevel("error",    3);
	LoggingSystem::AddLevel("critical", 4);

	LoggingSystem::AddFileLogger("info",     "info.log");
	LoggingSystem::AddFileLogger("debug",    "debug.log");
	LoggingSystem::AddFileLogger("error",    "error.log");
	LoggingSystem::AddFileLogger("critical", "critical.log");

	LoggingSystem::SetLoggingLevel("error");

	DuskLog("info", "Test Info");
	DuskLog("debug", "Test Debug");
	DuskLog("error", "Test Error");
	DuskLog("critical", "Test Critical Error");

	Dusk::Program* pProgram = Dusk::Program::Inst();

    pProgram->Run();

    delete pProgram;

	LoggingSystem::CloseAllLoggers();

    return 0;
}
