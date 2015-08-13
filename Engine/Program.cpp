#include "Program.h"

#include <Logging/Logging.h>
#include <Graphics/GraphicsSystem.h>

using namespace Dusk;
using namespace Dusk::Logging;
using namespace Dusk::Graphics;

void Program::
Run( void )
{
	if ( ! Init() )
	{
		DuskLog("error", "Program Init Failed");
		return;
	}
	DuskLog("info", "Program Init Succeeded");

	while (true) { }
}

bool Program::
Init( void )
{
	if ( ! InitGraphics() )
	{
		DuskLog("error", "Graphics Init Failed");
		return false;
	}
	DuskLog("info", "Graphics Init Succeeded");

	if ( ! InitAudio() )
	{
		DuskLog("error", "Audio Init Failed");
		return false;
	}
	DuskLog("info", "Audio Init Succeeded");

	if ( ! InitInput() )
	{
		DuskLog("error", "Input Init Failed");
		return false;
	}
	DuskLog("info", "Input Init Succeeded");

	return true;
}

void Program::
Term( void )
{
	delete mp_GraphicsSystem;
	mp_GraphicsSystem = nullptr;
}

void Program::
Update( void )
{

}

void Program::
Render( void )
{

}

bool Program::
InitGraphics( void )
{
	delete mp_GraphicsSystem;
	mp_GraphicsSystem = New Dusk::Graphics::GraphicsSystem();

	return mp_GraphicsSystem->Init();
}

bool Program::
InitInput( void )
{
	return true;
}

bool Program::
InitAudio( void )
{
	return true;
}

GraphicsSystem* Program::
GetGraphicsSystem(void)
{
	return mp_GraphicsSystem;
}
