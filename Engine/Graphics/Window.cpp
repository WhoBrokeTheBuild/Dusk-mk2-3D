#include "Window.h"

#include <Utility/Benchmark.h>
#include <Program.h>
#include <Logging/Logging.h>
#include <Graphics/GraphicsContext.h>
#include <Graphics/GraphicsSystem.h>
#include <Input/InputSystem.h>
#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Graphics;
using namespace Dusk::Logging;
using namespace Dusk::Scripting;

bool Window::
Init(const size_t& width, const size_t& height, const string& title, const Flag& flags)
{
	DuskBenchStart();
	DuskLog("info", "Initializing Window");

	m_Width = width;
	m_Height = height;

	m_Title = title;

	m_Fullscreen = (flags & Window::FULLSCREEN) > 0;
	m_Decorated = (flags & Window::DECORATED) > 0;
	m_Resizable = (flags & Window::RESIZABLE) > 0;

	bool res = CreateGLFWWindow();

	DuskBenchEnd("Window::Init");
	return res;
}

void Window::
Term( void )
{
	delete mp_GraphicsContext;
	mp_GraphicsContext = nullptr;

	glfwHideWindow(mp_GLFWWindow);
	glfwDestroyWindow(mp_GLFWWindow);
	mp_GLFWWindow = nullptr;
}

bool Window::
CreateGLFWWindow( void )
{
	DuskBenchStart();
	DuskLog("verbose", "Setting GLFW Window Hints");

	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
	glfwWindowHint(GLFW_DECORATED, m_Decorated);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();

	bool isContextCurrent = (mp_GraphicsContext ? mp_GraphicsContext->mp_GLFWWindow == mp_GLFWWindow : false);

	DuskLog("verbose", "Creating GLFW Window");

	glfwDestroyWindow(mp_GLFWWindow);
	mp_GLFWWindow = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title.c_str(), (m_Fullscreen ? pMonitor : NULL), NULL);

	if ( ! mp_GLFWWindow )
	{
		DuskLog("error", "glfwCreateWindow failed");
		return false;
	}

	DuskLog("verbose", "Updating GLFW Context");

	delete mp_GraphicsContext;
	mp_GraphicsContext = New Dusk::Graphics::GraphicsContext(mp_GLFWWindow);

	if ( isContextCurrent )
	{
		if (!mp_GraphicsContext->Bind())
		{
			DuskLog("error", "Binding Graphics Context Failed");
		}
	}

	DuskLog("verbose", "Attaching GLFW Callbacks");

	glfwSetWindowCloseCallback(mp_GLFWWindow, glfwClose);
	glfwSetFramebufferSizeCallback(mp_GLFWWindow, glfwResize);

	glfwSetKeyCallback(mp_GLFWWindow, Dusk::Input::glfwKey);
	glfwSetMouseButtonCallback(mp_GLFWWindow, Dusk::Input::glfwMouse);
	glfwSetCursorPosCallback(mp_GLFWWindow, Dusk::Input::glfwMouseMove);
	glfwSetScrollCallback(mp_GLFWWindow, Dusk::Input::glfwMouseScroll);

	DuskBenchEnd("Window::CreateGLFWWindow");
	return true;
}

void Window::
SetTitle( const string& title )
{
	glfwSetWindowTitle(mp_GLFWWindow, title.c_str());
}

void Window::
SetSize(const size_t& width, const size_t& height)
{
	m_Width = width;
	m_Height = height;
	glfwSetWindowSize(mp_GLFWWindow, (int)m_Width, (int)m_Height);
}

void Window::
SetWidth( const size_t& width )
{
	m_Width = width;
	glfwSetWindowSize(mp_GLFWWindow, (int)m_Width, (int)m_Height);
}

void Window::
SetHeight( const size_t& height )
{
	m_Height = height;
	glfwSetWindowSize(mp_GLFWWindow, (int)m_Width, (int)m_Height);
}

GraphicsContext* Window::
GetGraphicsContext( void )
{
	return mp_GraphicsContext;
}

void Window::
InitScripting(void)
{
	ScriptingSystem::RegisterFunction("dusk_window_set_size",   &Window::Script_SetSize);

	ScriptingSystem::RegisterFunction("dusk_window_get_width",  &Window::Script_GetWidth);
	ScriptingSystem::RegisterFunction("dusk_window_set_width",  &Window::Script_SetWidth);

	ScriptingSystem::RegisterFunction("dusk_window_get_height", &Window::Script_GetHeight);
	ScriptingSystem::RegisterFunction("dusk_window_set_height", &Window::Script_SetHeight);

	ScriptingSystem::RegisterFunction("dusk_window_get_title",  &Window::Script_GetTitle);
	ScriptingSystem::RegisterFunction("dusk_window_set_title",  &Window::Script_SetTitle);
}

int Window::
Script_SetSize( lua_State* L )
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	int width = (int)lua_tointeger(L, 2);
	int height = (int)lua_tointeger(L, 3);
	pWindow->SetSize(width, height);

	return 0;
}

int Window::
Script_GetWidth( lua_State* L )
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushinteger(L, (int)pWindow->GetWidth());

	return 1;
}

int Window::
Script_SetWidth( lua_State* L )
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	int width = (int)lua_tointeger(L, 2);
	pWindow->SetWidth(width);

	return 0;
}

int Window::
Script_GetHeight( lua_State* L )
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushinteger(L, (int)pWindow->GetHeight());

	return 1;
}

int Window::
Script_SetHeight( lua_State* L )
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	int height = (int)lua_tointeger(L, 2);
	pWindow->SetHeight(height);

	return 0;
}

int Window::
Script_GetTitle( lua_State* L )
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushstring(L, pWindow->GetTitle().c_str());

	return 1;
}

int Window::
Script_SetTitle( lua_State* L )
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	string title = lua_tostring(L, 2);
	pWindow->SetTitle(title);

	return 0;
}

void Dusk::Graphics::
glfwResize( GLFWwindow* pGLFWWindow, int width, int height )
{
	Window* pWindow = Dusk::Program::Inst()->GetGraphicsSystem()->GetWindow();
	pWindow->TriggerResize(width, height);
}

void Dusk::Graphics::
glfwClose( GLFWwindow* pGLFWWindow )
{
	Dusk::Program::Inst()->Exit();
}
