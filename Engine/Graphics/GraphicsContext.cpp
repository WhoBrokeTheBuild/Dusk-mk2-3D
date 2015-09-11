#include "GraphicsContext.h"

#include <Graphics/Window.h>

using namespace Dusk::Graphics;

bool GraphicsContext::
Bind( void )
{
	if ( mp_GLFWWindow == nullptr )
		return false;

	glfwMakeContextCurrent(mp_GLFWWindow);

	glfwSwapInterval(0);

	return true;
}


void GraphicsContext::
Clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearDepth(1.0f);
}

void GraphicsContext::
ResetDepthBuffer(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsContext::
SwapBuffers( void )
{
	glfwSwapBuffers(mp_GLFWWindow);
}
