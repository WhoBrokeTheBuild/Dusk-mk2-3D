#include "Window.h"

using namespace Dusk::Graphics;

Window::
~Window(void)
{
	glfwHideWindow(mp_GLFWWindow);
	glfwDestroyWindow(mp_GLFWWindow);
	mp_GLFWWindow = nullptr;
}

bool Window::
Init(const size_t& width, const size_t& height, const string& title, const Flag& flags)
{
	return false;
}

bool Window::
Init( void )
{
	return false;
}

void Window::
Title(const string& title)
{

}
