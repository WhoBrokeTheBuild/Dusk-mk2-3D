#include "GraphicsSystem.h"

#include <Program.h>
#include <Utility/Benchmark.h>
#include <Logging/Logging.h>
#include <Graphics/Window.h>
#include <Graphics/GraphicsContext.h>
#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Graphics;
using namespace Dusk::Logging;
using namespace Dusk::Scripting;

bool GraphicsSystem::
Init( void )
{
	DuskBenchStart();

	if ( ! glfwInit() )
	{
		DuskLog("error", "Failed to initialize GLFW");
		return false;
	}

	DuskExtLog("info", "Running GLFW Version %s", glfwGetVersionString());

	glfwSetErrorCallback(glfwError);

	delete mp_Window;
	mp_Window = New Window();
	mp_Window->Init(800, 600, "Test", Window::DECORATED | Window::RESIZABLE);

	GetGraphicsContext()->Bind();

	DuskBenchEnd("GraphicsSystem::Init");
	return true;
}

void GraphicsSystem::
Term( void )
{
	delete mp_Window;
	mp_Window = nullptr;
}

Window* GraphicsSystem::
GetWindow( void ) const
{
	return mp_Window;
}

GraphicsContext* GraphicsSystem::
GetGraphicsContext( void ) const
{
	return (mp_Window == nullptr ? nullptr : mp_Window->GetGraphicsContext());
}

void GraphicsSystem::
InitScripting( void )
{
	ScriptingSystem::RegisterFunction("dusk_graphics_system_get_window",           &GraphicsSystem::Script_GetWindow);
	ScriptingSystem::RegisterFunction("dusk_graphics_system_get_graphics_context", &GraphicsSystem::Script_GetGraphicsContext);

	Window::InitScripting();
	GraphicsContext::InitScripting();
}

int GraphicsSystem::
Script_GetWindow( lua_State* pState )
{
	lua_pushinteger(pState, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetWindow());

	return 1;
}

int GraphicsSystem::
Script_GetGraphicsContext( lua_State* pState )
{
	lua_pushinteger(pState, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetGraphicsContext());

	return 1;
}

void Dusk::Graphics::
glfwError( int error, const char* description )
{
	DuskExtLog("error", "GLFW Error: %s (%d)", description, error);
}
