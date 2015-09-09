#include "InputSystem.h"
#include <Program.h>
#include <Logging/Logging.h>
#include <Events/Event.h>

using namespace Dusk::Logging;
using namespace Dusk::Events;
using namespace Dusk::Input;

EventID InputSystem::EVT_KEY_PRESS				= 1;
EventID InputSystem::EVT_KEY_RELEASE			= 2;

EventID InputSystem::EVT_MOUSE_MOVE				= 10;
EventID InputSystem::EVT_MOUSE_SCROLL           = 11;
EventID InputSystem::EVT_MOUSE_BUTTON_PRESS		= 12;
EventID InputSystem::EVT_MOUSE_BUTTON_RELEASE   = 13;

EventID InputSystem::EVT_MAPPED_INPUT_PRESS		= 20;
EventID InputSystem::EVT_MAPPED_INPUT_RELEASE	= 21;

Dusk::Input::InputSystem::
InputSystem( void ) :
	m_GLFWKeyMap(),
	m_MappedKeys(),
	m_MappedMouseButtons()
{
}

Dusk::Input::InputSystem::
~InputSystem( void )
{
}

bool Dusk::Input::InputSystem::
Init( void )
{
	m_GLFWKeyMap.Clear();
	m_MappedKeys.Clear();
	m_MappedMouseButtons.Clear();

	AddGLFWKeyMappings(m_GLFWKeyMap);

	return true;
}

void Dusk::Input::InputSystem::
MapKey( const MappedInputID & id, const Key & key )
{
	m_MappedKeys.RemoveAllValues(id);
	m_MappedKeys.Add(key, id);
}

void Dusk::Input::InputSystem::
MapMouseButton( const MappedInputID& id, const MouseButton& button )
{
	m_MappedMouseButtons.RemoveAllValues(id);
	m_MappedMouseButtons.Add(button, id);
}

void Dusk::Input::InputSystem::
TriggerKeyPress( const Key& key )
{
	if (m_MappedKeys.ContainsKey(key))
	{
		dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(m_MappedKeys[key])));
	}

	dispatch(Event(EVT_KEY_PRESS, KeyEventData(key)));
}

void Dusk::Input::InputSystem::
TriggerKeyRelease( const Key& key )
{
	if (m_MappedKeys.ContainsKey(key)) 
	{
		dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(m_MappedKeys[key])));
	}

	dispatch(Event(EVT_KEY_RELEASE, KeyEventData(key)));
}

void Dusk::Input::InputSystem::
TriggerMouseMoveRelative( const double& dx, const double& dy )
{
	m_MouseX += dx;
	m_MouseY += dy;

	dispatch(Event(EVT_MOUSE_MOVE, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void Dusk::Input::InputSystem::
TriggerMouseMoveAbsolute( const double& x, const double& y )
{
	double dx = x - m_MouseX,
		   dy = y - m_MouseY;

	m_MouseX = x;
	m_MouseY = y;

	dispatch(Event(EVT_MOUSE_MOVE, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void Dusk::Input::InputSystem::
TriggerMouseScroll( double x, double y )
{
	dispatch(Event(EVT_MOUSE_SCROLL, MouseScrollEventData(x, y)));
}

void Dusk::Input::InputSystem::
TriggerMouseButtonPress( const MouseButton& mouseButton )
{
	if (m_MappedMouseButtons.ContainsKey(mouseButton))
	{
		dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
	}

	dispatch(Event(EVT_MOUSE_BUTTON_PRESS, MouseButtonEventData(mouseButton)));
}

void Dusk::Input::InputSystem::
TriggerMouseButtonRelease( const MouseButton& mouseButton )
{
	if (m_MappedMouseButtons.ContainsKey(mouseButton))
	{
		dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
	}

	dispatch(Event(EVT_MOUSE_BUTTON_RELEASE, MouseButtonEventData(mouseButton)));
}

void Dusk::Input::InputSystem::
TriggerMappedInputPress( const MappedInputID& input )
{
	dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(input)));
}

void Dusk::Input::InputSystem::
TriggerMappedInputRelease( const MappedInputID& input )
{
	dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(input)));
}

Dusk::Input::Key Dusk::Input::InputSystem::
ConvertGLFWKey( const int& key )
{
	return m_GLFWKeyMap[key];
}

Dusk::Input::MouseButton Dusk::Input::InputSystem::
ConvertGLFWMouseButton( const int& mouseButton )
{
	switch (mouseButton) {
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

void Dusk::Input::
glfwKey( GLFWwindow* pGLFWWindow, int glfwKeyCode, int scancode, int action, int mods )
{
	InputSystem* pInputSystem = Program::Inst()->GetInputSystem();

	Key key = pInputSystem->ConvertGLFWKey(glfwKeyCode);

	switch (action) 
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

	switch (action)
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
