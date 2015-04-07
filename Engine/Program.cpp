#include "Program.h"

#include <Logging/Logging.h>

using namespace Dusk::Logging;

void Dusk::Program::Run( void )
{
	if ( ! Init())
	{
		DuskLog("error", "Program Initialization Failed");
		return;
	}
}

bool Dusk::Program::Init( void )
{

	return true;
}

void Dusk::Program::Term( void )
{

}

void Dusk::Program::Update( void )
{

}

void Dusk::Program::Render( void )
{

}
