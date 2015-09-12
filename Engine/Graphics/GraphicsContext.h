#ifndef DUSK_GRAPHICS_CONTEXT_H
#define DUSK_GRAPHICS_CONTEXT_H

#include <Scripting/Scripting.h>
#include <Tracking/ITrackedObject.h>
#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Graphics
{

class Window;

class GraphicsContext :
	public Tracking::ITrackedObject
{

	friend class Window;

public:

	virtual inline string GetClassName(void) const { return "Graphics Context"; }

	bool Bind( void );

	void Clear( void );
	void ResetDepthBuffer( void );

	void SwapBuffers( void );
	
	static void InitScripting( void );
	static int Script_Clear( lua_State* pState );
	static int Script_ResetDepthBuffer( lua_State* pState );
	static int Script_SwapBuffers( lua_State* pState );


private:

	inline GraphicsContext( GLFWwindow* pGLFWWindow ) :
		mp_GLFWWindow(pGLFWWindow)
	{ }

	GLFWwindow*     mp_GLFWWindow;

}; // GraphicsContext

} // Graphics

} // Dusk

#endif // DUSK_GRAPHICS_CONTEXT_H
