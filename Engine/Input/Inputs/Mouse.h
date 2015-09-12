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

	MOUSE_BUTTON_LEFT	 = 1,
	MOUSE_BUTTON_MIDDLE  = 2,
	MOUSE_BUTTON_RIGHT   = 3,

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

class MouseMoveEventData :
	public Events::EventData
{
public:

	MouseMoveEventData( void ) :
		m_MouseX(0),
		m_MouseY(0),
		m_DeltaX(0),
		m_DeltaY(0)
	{ }

	MouseMoveEventData( const double& x, const double& y, const double& dx, const double& dy) :
		m_MouseX(x),
		m_MouseY(y),
		m_DeltaX(dx),
		m_DeltaY(dy)
	{ }

	virtual inline string GetClassName( void ) const { return "Mouse Move Event Data"; }

	virtual inline EventData* Clone( void ) const { return New MouseMoveEventData(m_MouseX, m_MouseY, m_DeltaX, m_DeltaY); }

	inline double GetX( void ) const { return m_MouseX; }
	inline double GetY( void ) const { return m_MouseY; }
	inline double GetDeltaX( void ) const { return m_DeltaX; }
	inline double GetDeltaY( void ) const { return m_DeltaY; }

private:

	double	m_MouseX,
			m_MouseY,
			m_DeltaX,
			m_DeltaY;

}; // class MouseMoveEventData

class MouseScrollEventData :
	public Events::EventData
{
public:

	MouseScrollEventData( void ) :
		m_ScrollX(0),
		m_ScrollY(0)
	{ }

	MouseScrollEventData( const double& x, const double& y ) :
		m_ScrollX(x),
		m_ScrollY(y)
	{ }

	virtual inline string GetClassName(void) const { return "Mouse Scroll Event Data"; }

	virtual inline EventData* Clone(void) const { return New MouseScrollEventData(m_ScrollX, m_ScrollY); }

	inline double GetScrollX(void) const { return m_ScrollX; }
	inline double GetScrollY(void) const { return m_ScrollY; }

private:

	double m_ScrollX,
		   m_ScrollY;

}; // class MouseScrollEventData

} // namespace Input

} // namespace Dusk

#endif // DUSK_INPUT_MOUSE_BUTTON_H