
if not Dusk then

Dusk = { }

end

if not Dusk.Input then

Dusk.Input = { }

Dusk.Input.MapKey = function(inputId, key)

	dusk_input_system_map_key(inputId, key);

end

Dusk.Input.Keys = {
	INVALID_KEY					= -1,

	KEY_A						= 1,
	KEY_B						= 2,
	KEY_C						= 3,
	KEY_D						= 4,
	KEY_E						= 5,
	KEY_F						= 6,
	KEY_G						= 7,
	KEY_H						= 8,
	KEY_I						= 9,
	KEY_J						= 10,
	KEY_K						= 11,
	KEY_L						= 12,
	KEY_M						= 13,
	KEY_N						= 14,
	KEY_O						= 15,
	KEY_P						= 16,
	KEY_Q						= 17,
	KEY_R						= 18,
	KEY_S						= 19,
	KEY_T						= 20,
	KEY_U						= 21,
	KEY_V						= 22,
	KEY_W						= 23,
	KEY_X						= 24,
	KEY_Y						= 25,
	KEY_Z						= 26,
	KEY_0						= 50,
	KEY_1						= 51,
	KEY_2						= 52,
	KEY_3						= 53,
	KEY_4						= 54,
	KEY_5						= 55,
	KEY_6						= 56,
	KEY_7						= 57,
	KEY_8						= 58,
	KEY_9						= 59,
	KEY_DASH					= 100,
	KEY_EQUAL					= 101,
	KEY_ACCENT					= 102,
	KEY_SQUARE_BRACKET_OPEN		= 103,
	KEY_SQUARE_BRACKET_CLOSE	= 104,
	KEY_SEMICOLON				= 105,
	KEY_QUOTE					= 106,
	KEY_BACKSLASH				= 107,
	KEY_PERIOD					= 108,
	KEY_COMMA					= 109,
	KEY_SLASH					= 110,
	KEY_UP						= 111,
	KEY_DOWN					= 112,
	KEY_LEFT					= 113,
	KEY_RIGHT					= 114,
	KEY_CAPS_LOCK				= 115,
	KEY_SCROLL_LOCK             = 116,
	KEY_NUM_LOCK                = 117,
	KEY_BACKSPACE				= 118,
	KEY_TAB						= 119,
	KEY_ENTER					= 120,
	KEY_SPACE					= 121,
	KEY_PAUSE					= 122,
	KEY_PRINT_SCREEN			= 123,
	KEY_LEFT_SHIFT				= 124,
	KEY_RIGHT_SHIFT				= 125,
	KEY_LEFT_CTRL				= 126,
	KEY_RIGHT_CTRL				= 127,
	KEY_HOME					= 132,
	KEY_END						= 133,
	KEY_PAGE_UP					= 134,
	KEY_PAGE_DOWN				= 135,
	KEY_ESCAPE					= 136,
	KEY_MENU					= 137,
	KEY_LEFT_SUPER				= 138,
	KEY_RIGHT_SUPER				= 139,
	KEY_PAD_0					= 200,
	KEY_PAD_1					= 201,
	KEY_PAD_2					= 202,
	KEY_PAD_3					= 203,
	KEY_PAD_4					= 204,
	KEY_PAD_5					= 205,
	KEY_PAD_6					= 206,
	KEY_PAD_7					= 207,
	KEY_PAD_8					= 208,
	KEY_PAD_9					= 209,
	KEY_PAD_ADD					= 210,
	KEY_PAD_SUBTRACT			= 211,
	KEY_PAD_MULTIPLY			= 212,
	KEY_PAD_DIVIDE				= 213,
	KEY_PAD_ENTER				= 214,
	KEY_PAD_DECIMAL				= 215,
	KEY_F1						= 216,
	KEY_F2						= 217,
	KEY_F3						= 218,
	KEY_F4						= 219,
	KEY_F5						= 220,
	KEY_F6						= 221,
	KEY_F7						= 222,
	KEY_F8						= 223,
	KEY_F9						= 224,
	KEY_F10						= 225,
	KEY_F11						= 226,
	KEY_F12						= 227,
	KEY_F13						= 228,
	KEY_F14						= 229,
	KEY_F15						= 230,
	KEY_F16						= 231,
	KEY_F17						= 232,
	KEY_F18						= 233,
	KEY_F19						= 234,
	KEY_F20						= 235,
	KEY_F21						= 236,
	KEY_F22						= 237,
	KEY_F23						= 238,
	KEY_F24						= 239,
	KEY_F25						= 240,
}

Dusk.Input.Keys.KEY_EXCLAMATION				= Dusk.Input.Keys.KEY_0;
Dusk.Input.Keys.KEY_AT						= Dusk.Input.Keys.KEY_1;
Dusk.Input.Keys.KEY_HASHTAG					= Dusk.Input.Keys.KEY_2;
Dusk.Input.Keys.KEY_POUND					= Dusk.Input.Keys.KEY_HASHTAG;
Dusk.Input.Keys.KEY_DOLLAR					= Dusk.Input.Keys.KEY_3;
Dusk.Input.Keys.KEY_PERCENT					= Dusk.Input.Keys.KEY_4;
Dusk.Input.Keys.KEY_CARROT					= Dusk.Input.Keys.KEY_5;
Dusk.Input.Keys.KEY_STAR					= Dusk.Input.Keys.KEY_6;
Dusk.Input.Keys.KEY_ASTERISK				= Dusk.Input.Keys.KEY_STAR;
Dusk.Input.Keys.KEY_AMPERSAND				= Dusk.Input.Keys.KEY_7;
Dusk.Input.Keys.KEY_PARENTHESIS_OPEN		= Dusk.Input.Keys.KEY_8;
Dusk.Input.Keys.KEY_PARENTHESIS_CLOSE		= Dusk.Input.Keys.KEY_9;
Dusk.Input.Keys.KEY_MINUS					= Dusk.Input.Keys.KEY_DASH;
Dusk.Input.Keys.KEY_UNDERSCORE				= Dusk.Input.Keys.KEY_MINUS;
Dusk.Input.Keys.KEY_PLUS					= Dusk.Input.Keys.KEY_EQUAL;
Dusk.Input.Keys.KEY_TILDE					= Dusk.Input.Keys.KEY_ACCENT;
Dusk.Input.Keys.KEY_CURLY_BRACE_OPEN		= Dusk.Input.Keys.KEY_SQUARE_BRACKET_OPEN;
Dusk.Input.Keys.KEY_CURLY_BRACE_CLOSE		= Dusk.Input.Keys.KEY_SQUARE_BRACKET_CLOSE;
Dusk.Input.Keys.KEY_COLON					= Dusk.Input.Keys.KEY_SEMICOLON;
Dusk.Input.Keys.KEY_APOSTROPHE				= Dusk.Input.Keys.KEY_QUOTE;
Dusk.Input.Keys.KEY_DOUBLE_QUOTE			= Dusk.Input.Keys.KEY_QUOTE;
Dusk.Input.Keys.KEY_PIPE					= Dusk.Input.Keys.KEY_BACKSLASH;
Dusk.Input.Keys.KEY_LESS_THAN				= Dusk.Input.Keys.KEY_PERIOD;
Dusk.Input.Keys.KEY_ANGLE_BRACKET_OPEN		= Dusk.Input.Keys.KEY_LESS_THAN;
Dusk.Input.Keys.KEY_CHEVRON_LEFT			= Dusk.Input.Keys.KEY_LESS_THAN;
Dusk.Input.Keys.KEY_GREATER_THAN			= Dusk.Input.Keys.KEY_COMMA;
Dusk.Input.Keys.KEY_ANGLE_BRACKET_CLOSE		= Dusk.Input.Keys.KEY_GREATER_THAN;
Dusk.Input.Keys.KEY_CHEVRON_RIGHT			= Dusk.Input.Keys.KEY_GREATER_THAN;
Dusk.Input.Keys.KEY_FORWARD_SLASH			= Dusk.Input.Keys.KEY_SLASH;
Dusk.Input.Keys.KEY_QUESTION_MARK			= Dusk.Input.Keys.KEY_SLASH;
Dusk.Input.Keys.KEY_BREAK					= Dusk.Input.Keys.KEY_PAUSE;
Dusk.Input.Keys.KEY_SYS_REQ					= Dusk.Input.Keys.KEY_PRINT_SCREEN;
Dusk.Input.Keys.KEY_LEFT_CONTROL			= Dusk.Input.Keys.KEY_LEFT_CTRL;
Dusk.Input.Keys.KEY_RIGHT_CONTROL			= Dusk.Input.Keys.KEY_RIGHT_CTRL;
Dusk.Input.Keys.KEY_LEFT_ALTERNATE			= Dusk.Input.Keys.KEY_LEFT_ALT;
Dusk.Input.Keys.KEY_RIGHT_ALTERNATE			= Dusk.Input.Keys.KEY_RIGHT_ALT;
Dusk.Input.Keys.KEY_LEFT_WINDOWS			= Dusk.Input.Keys.KEY_LEFT_SUPER;
Dusk.Input.Keys.KEY_RIGHT_WINDOWS			= Dusk.Input.Keys.KEY_RIGHT_SUPER;
Dusk.Input.Keys.KEY_PAD_INSERT				= Dusk.Input.Keys.KEY_PAD_0;
Dusk.Input.Keys.KEY_PAD_END					= Dusk.Input.Keys.KEY_PAD_1;
Dusk.Input.Keys.KEY_PAD_DOWN				= Dusk.Input.Keys.KEY_PAD_2;
Dusk.Input.Keys.KEY_PAD_PAGE_DOWN			= Dusk.Input.Keys.KEY_PAD_3;
Dusk.Input.Keys.KEY_PAD_LEFT				= Dusk.Input.Keys.KEY_PAD_4;
Dusk.Input.Keys.KEY_PAD_RIGHT				= Dusk.Input.Keys.KEY_PAD_6;
Dusk.Input.Keys.KEY_PAD_HOME				= Dusk.Input.Keys.KEY_PAD_7;
Dusk.Input.Keys.KEY_PAD_UP					= Dusk.Input.Keys.KEY_PAD_8;
Dusk.Input.Keys.KEY_PAD_PAGE_UP				= Dusk.Input.Keys.KEY_PAD_9;
Dusk.Input.Keys.KEY_PAD_DELETE				= Dusk.Input.Keys.KEY_PAD_DECIMAL;

end -- Dusk.Input