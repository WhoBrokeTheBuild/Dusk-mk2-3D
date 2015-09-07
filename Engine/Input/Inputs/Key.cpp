#include "Key.h"

void Dusk::Input::AddGLFWKeyMappings( Collections::Map<int, Key>& map )
{
	for (unsigned int i = 0; i < 10; ++i) {
		map.Add(GLFW_KEY_0 + i, (Key)(Key::KEY_0 + i));
	}

	for (unsigned int i = 0; i < 26; ++i) {
		map.Add(GLFW_KEY_A + i, (Key)(Key::KEY_A + i));
	}
	
	map.Add(GLFW_KEY_MINUS, Key::KEY_DASH);
	map.Add(GLFW_KEY_EQUAL, Key::KEY_EQUAL);
	map.Add(GLFW_KEY_GRAVE_ACCENT, Key::KEY_ACCENT);
	map.Add(GLFW_KEY_LEFT_BRACKET, Key::KEY_SQUARE_BRACKET_OPEN);
	map.Add(GLFW_KEY_RIGHT_BRACKET, Key::KEY_SQUARE_BRACKET_CLOSE);
	map.Add(GLFW_KEY_SEMICOLON, Key::KEY_SEMICOLON);
	map.Add(GLFW_KEY_APOSTROPHE, Key::KEY_QUOTE);
	map.Add(GLFW_KEY_BACKSLASH, Key::KEY_BACKSLASH);
	map.Add(GLFW_KEY_PERIOD, Key::KEY_PERIOD);
	map.Add(GLFW_KEY_COMMA, Key::KEY_COMMA);
	map.Add(GLFW_KEY_SLASH, Key::KEY_SLASH);
	map.Add(GLFW_KEY_UP, Key::KEY_UP);
	map.Add(GLFW_KEY_DOWN, Key::KEY_DOWN);
	map.Add(GLFW_KEY_LEFT, Key::KEY_LEFT);
	map.Add(GLFW_KEY_RIGHT, Key::KEY_RIGHT);
	map.Add(GLFW_KEY_CAPS_LOCK, Key::KEY_CAPS_LOCK);
	map.Add(GLFW_KEY_SCROLL_LOCK, Key::KEY_SCROLL_LOCK);
	map.Add(GLFW_KEY_NUM_LOCK, Key::KEY_NUM_LOCK);
	map.Add(GLFW_KEY_BACKSPACE, Key::KEY_BACKSPACE);
	map.Add(GLFW_KEY_TAB, Key::KEY_TAB);
	map.Add(GLFW_KEY_ENTER, Key::KEY_ENTER);
	map.Add(GLFW_KEY_SPACE, Key::KEY_SPACE);
	map.Add(GLFW_KEY_PAUSE, Key::KEY_PAUSE);
	map.Add(GLFW_KEY_PRINT_SCREEN, Key::KEY_PRINT_SCREEN);
	map.Add(GLFW_KEY_LEFT_SHIFT, Key::KEY_LEFT_SHIFT);
	map.Add(GLFW_KEY_RIGHT_SHIFT, Key::KEY_RIGHT_SHIFT);
	map.Add(GLFW_KEY_LEFT_CONTROL, Key::KEY_LEFT_CTRL);
	map.Add(GLFW_KEY_RIGHT_CONTROL, Key::KEY_RIGHT_CTRL);
	map.Add(GLFW_KEY_LEFT_ALT, Key::KEY_LEFT_ALT);
	map.Add(GLFW_KEY_RIGHT_ALT, Key::KEY_RIGHT_ALT);
	map.Add(GLFW_KEY_INSERT, Key::KEY_INSERT);
	map.Add(GLFW_KEY_DELETE, Key::KEY_DELETE);
	map.Add(GLFW_KEY_HOME, Key::KEY_HOME);
	map.Add(GLFW_KEY_END, Key::KEY_END);
	map.Add(GLFW_KEY_PAGE_UP, Key::KEY_PAGE_UP);
	map.Add(GLFW_KEY_PAGE_DOWN, Key::KEY_PAGE_DOWN);
	map.Add(GLFW_KEY_MENU, Key::KEY_MENU);
	map.Add(GLFW_KEY_LEFT_SUPER, Key::KEY_LEFT_SUPER);
	map.Add(GLFW_KEY_RIGHT_SUPER, Key::KEY_RIGHT_SUPER);

	for (unsigned int i = 0; i < 10; ++i) {
		map.Add(GLFW_KEY_KP_0 + i, (Key)(Key::KEY_PAD_0 + i));
	}

	map.Add(GLFW_KEY_KP_ADD, Key::KEY_PAD_ADD);
	map.Add(GLFW_KEY_KP_SUBTRACT, Key::KEY_PAD_SUBTRACT);
	map.Add(GLFW_KEY_KP_MULTIPLY, Key::KEY_PAD_MULTIPLY);
	map.Add(GLFW_KEY_KP_DIVIDE, Key::KEY_PAD_DIVIDE);
	map.Add(GLFW_KEY_KP_ENTER, Key::KEY_PAD_ENTER);
	map.Add(GLFW_KEY_KP_DECIMAL, Key::KEY_PAD_DECIMAL);

	for (unsigned int i = 0; i < 12; ++i) {
		map.Add(GLFW_KEY_F1 + i, (Key)(Key::KEY_F1 + i));
	}
}