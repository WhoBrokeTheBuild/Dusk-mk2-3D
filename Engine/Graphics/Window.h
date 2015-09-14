#ifndef DUSK_GRAPHICS_WINDOW_H
#define DUSK_GRAPHICS_WINDOW_H

#include <Graphics/Graphics.h>
#include <Tracking/ITrackedObject.h>
#include <Utility/Types.h>
#include <Scripting/Scripting.h>

using namespace Dusk::Tracking;
using namespace Dusk::Utility;

namespace Dusk
{

namespace Graphics
{

class GraphicsContext;

class Window :
	public Tracking::ITrackedObject
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

	~Window(void) { Term(); }

	virtual inline string GetClassName(void) const { return "Window"; }

	bool Init( const size_t& width, const size_t& height, const string& title, const Flag& flags );
	void Term( void );

	inline string GetTitle( void ) const { return m_Title; }
	void SetTitle( const string& title );

	void SetSize( const size_t& width, const size_t& height );

	inline size_t GetWidth( void ) const { return m_Width; }
	void SetWidth( const size_t& width );

	inline size_t GetHeight( void ) const { return m_Height; }
	void SetHeight( const size_t& height );

	inline bool IsFullscreen( void ) const { return m_Fullscreen; }
	inline bool IsDecorated( void ) const { return m_Decorated; }
	inline bool IsResizable ( void ) const { return m_Resizable; }

	GraphicsContext* GetGraphicsContext( void );

	static void InitScripting( void );
	static int Script_SetSize  ( lua_State* L );
	static int Script_GetWidth ( lua_State* L );
	static int Script_GetHeight( lua_State* L );
	static int Script_SetWidth ( lua_State* L );
	static int Script_SetHeight( lua_State* L );
	static int Script_GetTitle ( lua_State* L );
	static int Script_SetTitle ( lua_State* L );

	inline void TriggerResize( const size_t& width, const size_t& height )
	{
		m_Width = width;
		m_Height = height;
	}

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
void glfwClose( GLFWwindow* pGLFWWindow );

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_WINDOW_H