#include "Window.h"

#include <Utility/Benchmark.h>
#include <Program.h>
#include <Logging/Logging.h>
#include <Graphics/GraphicsContext.h>
#include <Graphics/GraphicsSystem.h>
#include <Input/InputSystem.h>

using namespace Dusk::Graphics;
using namespace Dusk::Logging;

using Dusk::Program;

Window::
~Window(void)
{
	delete mp_GraphicsContext;
	mp_GraphicsContext = nullptr;

	glfwHideWindow(mp_GLFWWindow);
	glfwDestroyWindow(mp_GLFWWindow);
	mp_GLFWWindow = nullptr;
}

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
Title( const string& title )
{

}

GraphicsContext* Window::
GetGraphicsContext( void )
{
	return mp_GraphicsContext;
}

void Dusk::Graphics::
glfwResize( GLFWwindow* pGLFWWindow, int width, int height )
{
	Window* pWindow = Program::Inst()->GetGraphicsSystem()->GetWindow();
	//pWindow->hookResize(width, height);
}

void Dusk::Graphics::glfwClose(GLFWwindow* pGLFWWindow)
{
	Program::Inst()->Exit();
}
