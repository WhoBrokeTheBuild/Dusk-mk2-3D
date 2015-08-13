#ifndef DUSK_GRAPHICS_WINDOW_H
#define DUSK_GRAPHICS_WINDOW_H

#include <Graphics/Graphics.h>
#include <Tracking/TrackedObject.h>
#include <Utility/Types.h>

using namespace Dusk::Tracking;
using namespace Dusk::Utility;

namespace Dusk
{

namespace Graphics
{

class GraphicsContext;

class Window :
	public Tracking::TrackedObject
{
public:

	static const Flag FULLSCREEN = 1;
	static const Flag RESIZABLE  = 2;
	static const Flag DECORATED  = 4;

	inline Window(void) :
		mp_GLFWWindow(nullptr),
		mp_GraphicsContext(nullptr),
		m_Width(0),
		m_Height(0),
		m_Fullscreen(false),
		m_Decorated(false),
		m_Resizable(false)
	{ }

	~Window(void);

	virtual inline string GetClassName(void) const { return "Window"; }

	bool Init( const size_t& width, const size_t& height, const string& title, const Flag& flags );

	inline string Title( void ) const { return m_Title; }
	void Title( const string& title );

	inline bool Fullscreen( void ) const { return m_Fullscreen; }
	inline void Fullscreen( const bool& fullscreen ) { m_Fullscreen = fullscreen; }

	inline bool Decorated( void ) const { return m_Decorated; }
	inline void Decorated( const bool& decorated ) { m_Decorated = decorated; }

	inline bool Resizable ( void ) const { return m_Resizable; }
	inline void Resizable ( const bool& resizable ) { m_Resizable = resizable; }

	GraphicsContext* GetGraphicsContext( void );

private:

	bool CreateGLFWWindow( void );

	GLFWwindow			*mp_GLFWWindow;
	GraphicsContext		*mp_GraphicsContext;

	size_t			m_Width,
					m_Height;

	string			m_Title;

	bool			m_Fullscreen,
					m_Decorated,
					m_Resizable;

}; // class Window

void glfwResize( GLFWwindow* pGLFWWindow, int width, int height );

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_WINDOW_H