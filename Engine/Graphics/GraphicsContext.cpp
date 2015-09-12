#include "GraphicsContext.h"

#include <Graphics/Window.h>
#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Graphics;
using namespace Dusk::Scripting;

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

void GraphicsContext::
InitScripting( void )
{
	ScriptingSystem::RegisterFunction("dusk_graphics_context_clear",				&GraphicsContext::Script_Clear);
	ScriptingSystem::RegisterFunction("dusk_graphics_context_reset_depth_buffer",	&GraphicsContext::Script_ResetDepthBuffer);
	ScriptingSystem::RegisterFunction("dusk_graphics_context_swap_buffers",			&GraphicsContext::Script_SwapBuffers);
}

int GraphicsContext::
Script_Clear( lua_State * pState )
{
	GraphicsContext* pContext = (GraphicsContext*)lua_tointeger(pState, 1);
	
	pContext->Clear();

	return 0;
}

int GraphicsContext::
Script_ResetDepthBuffer( lua_State* pState )
{
	GraphicsContext* pContext = (GraphicsContext*)lua_tointeger(pState, 1);

	pContext->ResetDepthBuffer();

	return 0;
}

int GraphicsContext::
Script_SwapBuffers( lua_State* pState )
{
	GraphicsContext* pContext = (GraphicsContext*)lua_tointeger(pState, 1);

	pContext->SwapBuffers();

	return 0;
}
