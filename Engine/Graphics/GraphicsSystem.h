#ifndef DUSK_GRAPHICS_GRAPHICS_SYSTEM_H
#define DUSK_GRAPHICS_GRAPHICS_SYSTEM_H

#include <Tracking/TrackedObject.h>

namespace Dusk
{

namespace Graphics
{

class Window;

class GraphicsSystem :
	public Tracking::TrackedObject
{
public:

	GraphicsSystem( void ) :
		mp_Window(nullptr)
	{ }

	~GraphicsSystem( void );

	virtual inline string GetClassName( void ) const { return "Graphics System"; }

	bool Init( void );

	Graphics::Window * GetWindow( void ) const;

private:

	Graphics::Window	*mp_Window;

}; // class GraphicsSystem

void glfwError( int error, const char* description );

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_GRAPHICS_SYSTEM_H