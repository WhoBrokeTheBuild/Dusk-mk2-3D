#include <Program.h>

#include <Logging/LoggingSystem.h>

using namespace Dusk::Logging;

int main(int argc, char* argv[])
{
	LoggingSystem::AddLevel("info");
	LoggingSystem::AddLevel("debug");
	LoggingSystem::AddLevel("error");
	LoggingSystem::AddLevel("critical");

	LoggingSystem::AddFileLogger("info", "info.log");

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
