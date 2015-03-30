#include <Program.h>

int main(int argc, char* argv[])
{
	Dusk::Program* pProgram = Dusk::Program::Inst();

    pProgram->Run();

    delete pProgram;

    return 0;
}
