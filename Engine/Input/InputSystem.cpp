#include "InputSystem.h"
#include <Program.h>
#include <Logging/Logging.h>
#include <Events/Event.h>
#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Logging;
using namespace Dusk::Events;
using namespace Dusk::Input;
using namespace Dusk::Scripting;

EventID InputSystem::EVT_KEY_PRESS				= 1;
EventID InputSystem::EVT_KEY_RELEASE			= 2;

EventID InputSystem::EVT_MOUSE_MOVE				= 10;
EventID InputSystem::EVT_MOUSE_SCROLL           = 11;
EventID InputSystem::EVT_MOUSE_BUTTON_PRESS		= 12;
EventID InputSystem::EVT_MOUSE_BUTTON_RELEASE   = 13;

EventID InputSystem::EVT_MAPPED_INPUT_PRESS		= 20;
EventID InputSystem::EVT_MAPPED_INPUT_RELEASE	= 21;

bool InputSystem::
Init( void )
{
	m_GLFWKeyMap.Clear();
	m_MappedKeys.Clear();
	m_MappedMouseButtons.Clear();

	AddGLFWKeyMappings(m_GLFWKeyMap);

	return true;
}

void InputSystem::
Term( void )
{
	
}

void InputSystem::
MapKey( const MappedInputID & id, const Key & key )
{
	m_MappedKeys.RemoveAllValues(id);
	m_MappedKeys.Add(key, id);
}

void InputSystem::
MapMouseButton( const MappedInputID& id, const MouseButton& button )
{
	m_MappedMouseButtons.RemoveAllValues(id);
	m_MappedMouseButtons.Add(button, id);
}

Key InputSystem::
GetMappedKey(const MappedInputID& id)
{
	if (m_MappedKeys.ContainsValue(id)) {
		return m_MappedKeys.GetIndexOf(id);
	}

	return Key::INVALID_KEY;
}

MouseButton InputSystem::
GetMappedMouseButton(const MappedInputID& id)
{
	if (m_MappedMouseButtons.ContainsValue(id)) {
		return m_MappedMouseButtons.GetIndexOf(id);
	}

	return MouseButton::INVALID_MOUSE_BUTTON;
}

void InputSystem::
TriggerKeyPress( const Key& key )
{
	if ( m_MappedKeys.ContainsKey(key) )
	{
		Dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(m_MappedKeys[key])));
	}

	Dispatch(Event(EVT_KEY_PRESS, KeyEventData(key)));
}

void InputSystem::
TriggerKeyRelease( const Key& key )
{
	if ( m_MappedKeys.ContainsKey(key) ) 
	{
		Dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(m_MappedKeys[key])));
	}

	Dispatch(Event(EVT_KEY_RELEASE, KeyEventData(key)));
}

void InputSystem::
TriggerMouseMoveRelative( const double& dx, const double& dy )
{
	m_MouseX += dx;
	m_MouseY += dy;

	Dispatch(Event(EVT_MOUSE_MOVE, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void InputSystem::
TriggerMouseMoveAbsolute( const double& x, const double& y )
{
	double dx = x - m_MouseX,
		   dy = y - m_MouseY;

	m_MouseX = x;
	m_MouseY = y;

	Dispatch(Event(EVT_MOUSE_MOVE, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void InputSystem::
TriggerMouseScroll( double x, double y )
{
	Dispatch(Event(EVT_MOUSE_SCROLL, MouseScrollEventData(x, y)));
}

void InputSystem::
TriggerMouseButtonPress( const MouseButton& mouseButton )
{
	if ( m_MappedMouseButtons.ContainsKey(mouseButton) )
	{
		Dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
	}

	Dispatch(Event(EVT_MOUSE_BUTTON_PRESS, MouseButtonEventData(mouseButton)));
}

void InputSystem::
TriggerMouseButtonRelease( const MouseButton& mouseButton )
{
	if ( m_MappedMouseButtons.ContainsKey(mouseButton) )
	{
		Dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
	}

	Dispatch(Event(EVT_MOUSE_BUTTON_RELEASE, MouseButtonEventData(mouseButton)));
}

void InputSystem::
TriggerMappedInputPress( const MappedInputID& input )
{
	Dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(input)));
}

void InputSystem::
TriggerMappedInputRelease( const MappedInputID& input )
{
	Dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(input)));
}

Key InputSystem::
ConvertGLFWKey( const int& key )
{
	return m_GLFWKeyMap[key];
}

MouseButton InputSystem::
ConvertGLFWMouseButton( const int& mouseButton )
{
	switch ( mouseButton ) {
		case GLFW_MOUSE_BUTTON_LEFT:

			return MouseButton::MOUSE_BUTTON_LEFT;

			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:

			return MouseButton::MOUSE_BUTTON_MIDDLE;

			break;
		case GLFW_MOUSE_BUTTON_RIGHT:

			return MouseButton::MOUSE_BUTTON_RIGHT;

			break;
	}

	return INVALID_MOUSE_BUTTON;
}

void InputSystem::
InitScripting( void )
{
	ScriptingSystem::RegisterFunction("dusk_input_system_map_key",					&InputSystem::Script_MapKey);
	ScriptingSystem::RegisterFunction("dusk_input_system_map_mouse_button",			&InputSystem::Script_MapMouseButton);
	ScriptingSystem::RegisterFunction("dusk_input_system_get_mapped_key",			&InputSystem::Script_GetMappedKey);
	ScriptingSystem::RegisterFunction("dusk_input_system_get_mapped_mouse_button",	&InputSystem::Script_GetMappedMouseButton);
}

int InputSystem::
Script_MapKey( lua_State* pState )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();

	string input = lua_tostring(pState, 1);
	Key key = (Key)lua_tointeger(pState, 2);

	pInputSystem->MapKey(input, key);

	return 0;
}

int InputSystem::
Script_MapMouseButton( lua_State* pState )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();

	string input = lua_tostring(pState, 1);
	MouseButton button = (MouseButton)lua_tointeger(pState, 2);

	pInputSystem->MapMouseButton(input, button);

	return 0;
}

int InputSystem::
Script_GetMappedKey( lua_State* pState )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();

	string input = lua_tostring(pState, 1);

	Key key = pInputSystem->GetMappedKey(input);

	lua_pushinteger(pState, key);

	return 1;
}

int InputSystem::
Script_GetMappedMouseButton(lua_State* pState)
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();

	string input = lua_tostring(pState, 1);

	MouseButton button = pInputSystem->GetMappedMouseButton(input);

	lua_pushinteger(pState, button);

	return 1;
}

void Dusk::Input::
glfwKey( GLFWwindow* pGLFWWindow, int glfwKeyCode, int scancode, int action, int mods )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();

	Key key = pInputSystem->ConvertGLFWKey(glfwKeyCode);

	switch ( action ) 
	{
		case GLFW_PRESS:

			pInputSystem->TriggerKeyPress(key);

			break;
		case GLFW_RELEASE:

			pInputSystem->TriggerKeyRelease(key);

			break;
	}
}

void Dusk::Input::
glfwMouseMove( GLFWwindow* pGLFWWindow, double x, double y )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();
	pInputSystem->TriggerMouseMoveAbsolute(x, y);
}

void Dusk::Input::
glfwMouse( GLFWwindow* pGLFWWindow, int glfwButtonCode, int action, int mods )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();

	MouseButton button = pInputSystem->ConvertGLFWMouseButton(glfwButtonCode);

	switch ( action )
	{
	case GLFW_PRESS:

		pInputSystem->TriggerMouseButtonPress(button);

		break;
	case GLFW_RELEASE:

		pInputSystem->TriggerMouseButtonRelease(button);

		break;
	}
}

void Dusk::Input::
glfwMouseScroll( GLFWwindow* pGLFWWindow, double x, double y )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();
	pInputSystem->TriggerMouseScroll(x, y);
}
