#pragma once

#ifndef DUSK_INPUT_MOUSE_BUTTON_H
#define DUSK_INPUT_MOUSE_BUTTON_H

#include <Events/Event.h>

namespace Dusk
{

namespace Input
{

enum MouseButton
{
	INVALID_MOUSE_BUTTON = -1,

	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT,

}; // enum MouseButton

class MouseButtonEventData :
	public Events::EventData
{
public:

	MouseButtonEventData( void ) :
		m_MouseButton(MouseButton::INVALID_MOUSE_BUTTON)
	{ }

	MouseButtonEventData( const MouseButton& button ) :
		m_MouseButton(button)
	{ }

	virtual inline string GetClassName( void ) const { return "Mouse Button Event Data"; }

	virtual inline EventData* Clone( void ) const { return New MouseButtonEventData(m_MouseButton); }

	inline MouseButton GetMouseButton( void ) const { return m_MouseButton; }

private:

	MouseButton		m_MouseButton;

}; // class MouseButtonEventData

} // namespace Input

} // namespace Dusk

#endif // DUSK_INPUT_MOUSE_BUTTON_H