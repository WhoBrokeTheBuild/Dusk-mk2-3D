#include <Program.h>

int main(int argc, char* argv[])
{
	Dusk::Program* pProgram = Dusk::Program::Inst();

    pProgram->run();

    delete pProgram;

    return 0;
}
