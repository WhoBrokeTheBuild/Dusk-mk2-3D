#ifndef DUSK_GRAPHICS_GRAPHICS_SYSTEM_H
#define DUSK_GRAPHICS_GRAPHICS_SYSTEM_H

#include <Scripting/Scripting.h>
#include <Tracking/ITrackedObject.h>

namespace Dusk
{

namespace Graphics
{

class Window;
class ShaderManager;
class GraphicsContext;

class GraphicsSystem :
	public Tracking::ITrackedObject
{
public:

	GraphicsSystem( void ) :
		mp_Window(nullptr)
	{ }

	~GraphicsSystem( void ) { Term(); }

	virtual inline string GetClassName( void ) const { return "Graphics System"; }

	bool Init( void );
	void Term( void );

	Window* GetWindow( void ) const;
	ShaderManager* GetShaderManager( void ) const;
	GraphicsContext* GetGraphicsContext( void ) const;

	static void InitScripting( void );
	static int Script_GetWindow( lua_State* L );
	static int Script_GetShaderManager( lua_State* L );
	static int Script_GetGraphicsContext( lua_State* L );

private:

	Window*			mp_Window;
	ShaderManager*	mp_ShaderManager;

}; // class GraphicsSystem

void glfwError( int error, const char* description );

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_GRAPHICS_SYSTEM_H