#pragma once

#ifndef DUSK_INPUT_INPUT_SYSTEM_H
#define DUSK_INPUT_INPUT_SYSTEM_H

#include <Scripting/Scripting.h>
#include <Tracking/ITrackedObject.h>
#include <Events/IEventDispatcher.h>

#include <Input/Inputs/Key.h>
#include <Input/Inputs/Mouse.h>

#include <GLFW/glfw3.h>

namespace Dusk
{

namespace Input
{

typedef string MappedInputID;

class MappedInputEventData :
	public Events::EventData
{
public:

	MappedInputEventData(const MappedInputID& mappedInput) :
		m_MappedInput(mappedInput)
	{ }

	virtual inline string GetClassName( void) const { return "Mapped Input Event Data"; }

	virtual inline EventData* Clone( void ) const { return New MappedInputEventData(m_MappedInput); }

	inline MappedInputID GetMappedInput( void ) const { return m_MappedInput; }

private:

	MappedInputID		m_MappedInput;

}; // class MappedInputEventData

class InputSystem :
	public Tracking::ITrackedObject,
	public Events::IEventDispatcher
{
public:

	static Events::EventID
		EVT_KEY_PRESS,
		EVT_KEY_RELEASE,

		EVT_MOUSE_MOVE,
		EVT_MOUSE_SCROLL,
		EVT_MOUSE_BUTTON_PRESS,
		EVT_MOUSE_BUTTON_RELEASE,

		EVT_MAPPED_INPUT_PRESS,
		EVT_MAPPED_INPUT_RELEASE;

	InputSystem( void ) :
		m_MouseX(0),
		m_MouseY(0),
		m_GLFWKeyMap(),
		m_MappedKeys(),
		m_MappedMouseButtons()
	{ }

	~InputSystem( void ) { Term(); }

	virtual inline string GetClassName( void ) const { return "Input System"; }

	bool Init( void );
	void Term( void );

	void MapKey( const MappedInputID& id, const Key& key );
	void MapMouseButton( const MappedInputID& id, const MouseButton& button );

	Key GetMappedKey( const MappedInputID& id );
	MouseButton GetMappedMouseButton( const MappedInputID& id );

	void TriggerKeyPress( const Key& key );
	void TriggerKeyRelease(const Key& key);

	void TriggerMouseMoveRelative( const double& dX, const double& dY );
	void TriggerMouseMoveAbsolute( const double& x, const double& y );
	void TriggerMouseScroll( double x, double y );
	void TriggerMouseButtonPress( const MouseButton& mouseButton );
	void TriggerMouseButtonRelease( const MouseButton& mouseButton );

	void TriggerMappedInputPress( const MappedInputID& input );
	void TriggerMappedInputRelease( const MappedInputID& input );

	Key ConvertGLFWKey( const int& key );
	MouseButton ConvertGLFWMouseButton( const int& mouseButton );

	static void InitScripting( void );
	static int Script_MapKey( lua_State* pState );
	static int Script_MapMouseButton( lua_State* pState );
	static int Script_GetMappedKey( lua_State* pState );
	static int Script_GetMappedMouseButton( lua_State* pState );

private:

	double	m_MouseX,
			m_MouseY;

	Map<int, Key> m_GLFWKeyMap;

	Map<Key, MappedInputID>				m_MappedKeys;
	Map<MouseButton, MappedInputID>		m_MappedMouseButtons;


}; // class InputSystem

void glfwKey(GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mods);
void glfwMouseMove(GLFWwindow* pGLFWWindow, double x, double y);
void glfwMouse(GLFWwindow* pGLFWWindow, int button, int action, int mods);
void glfwMouseScroll(GLFWwindow* pGLFWWindow, double x, double y);

} // namespace Input

} // namespace Dusk


#endif // DUSK_INPUT_INPUT_SYSTEM_H