#include "GraphicsSystem.h"

#include <Utility/Benchmark.h>
#include <Logging/Logging.h>
#include <Graphics/Window.h>
#include <Graphics/GraphicsContext.h>

using namespace Dusk::Graphics;
using namespace Dusk::Logging;

GraphicsSystem::
~GraphicsSystem(void)
{
	delete mp_Window;
	mp_Window = nullptr;
}

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

	GetWindow()->GetGraphicsContext()->Bind();

	DuskBenchEnd("GraphicsSystem::Init");
	return true;
}

Window*
GraphicsSystem::GetWindow( void ) const
{
	return mp_Window;
}

void Dusk::Graphics::glfwError( int error, const char* description )
{
	DuskExtLog("error", "GLFW Error: %s (%d)", description, error);
}
