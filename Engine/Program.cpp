#include "Program.h"

#include <Logging/Logging.h>
#include <Graphics/GraphicsSystem.h>

using namespace Dusk::Logging;
using namespace Dusk::Graphics;

void Dusk::Program::Run( void )
{
	if ( ! Init() )
	{
		DuskLog("error", "Program Init Failed");
		return;
	}
	DuskLog("info", "Program Init Succeeded");
}

bool Dusk::Program::Init( void )
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

void Dusk::Program::Term( void )
{

}

void Dusk::Program::Update( void )
{

}

void Dusk::Program::Render( void )
{

}

bool Dusk::Program::InitGraphics( void )
{
	delete mp_GraphicsSystem;
	mp_GraphicsSystem = new GraphicsSystem();

	return mp_GraphicsSystem->Init();
}

bool Dusk::Program::InitInput( void )
{
	return true;
}

bool Dusk::Program::InitAudio( void )
{
	return true;
}
