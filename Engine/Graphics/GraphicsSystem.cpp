#include "GraphicsSystem.h"

#include <Program.h>
#include <Utility/Benchmark.h>
#include <Logging/Logging.h>
#include <Graphics/Window.h>
#include <Graphics/ShaderManager.h>
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

	glewExperimental = GL_TRUE;
	GLenum ret = glewInit();
	if ( ret != GLEW_OK )
	{
		DuskExtLog("error", "Failed to initialize GLEW (Error #%d, %s)", ret, glewGetErrorString(ret));
		return false;
	}

	DuskExtLog("info", "Running GLEW Version %s", glewGetString(GLEW_VERSION));
	DuskExtLog("info", "Running OpenGL Version %s", glGetString(GL_VERSION));
	DuskExtLog("info", "Running OpenGL Shading Language Version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mp_ShaderManager = New ShaderManager();
	mp_ShaderManager->Init();

	DuskBenchEnd("GraphicsSystem::Init");
	return true;
}

void GraphicsSystem::
Term( void )
{
	delete mp_ShaderManager;
	mp_ShaderManager = nullptr;

	delete mp_Window;
	mp_Window = nullptr;
}

Window* GraphicsSystem::
GetWindow( void ) const
{
	return mp_Window;
}

ShaderManager* GraphicsSystem::
GetShaderManager( void ) const
{
	return mp_ShaderManager;
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
	ScriptingSystem::RegisterFunction("dusk_graphics_system_get_shader_manager",   &GraphicsSystem::Script_GetShaderManager);
	ScriptingSystem::RegisterFunction("dusk_graphics_system_get_graphics_context", &GraphicsSystem::Script_GetGraphicsContext);

	Window::InitScripting();
	ShaderManager::InitScripting();
	GraphicsContext::InitScripting();
}

int GraphicsSystem::
Script_GetWindow( lua_State* L )
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetWindow());
	return 1;
}

int GraphicsSystem::
Script_GetShaderManager( lua_State* L )
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetShaderManager());
	return 1;
}

int GraphicsSystem::
Script_GetGraphicsContext( lua_State* L )
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetGraphicsContext());
	return 1;
}

void Dusk::Graphics::
glfwError( int error, const char* description )
{
	DuskExtLog("error", "GLFW Error: %s (%d)", description, error);
}
