#include "stdafx.h"

#include <bwcontrol/BwControllerEvent.h>

char BwControllerEvent::getKeyChar()
{
	int keyCode = getKey() ;
	int modifiers = getModifiers() ;

	if (modifiers == 0)
	{
		switch (keyCode) {
		case KC_1: return '1';
		case KC_2: return '2';
		case KC_3: return '3';
		case KC_4: return '4';
		case KC_5: return '5';
		case KC_6: return '6';
		case KC_7: return '7';
		case KC_8: return '8';
		case KC_9: return '9';
		case KC_0: return '0';
		case KC_MINUS: return '-';			/* - on main keyboard */
		case KC_EQUALS: return '=';
		case KC_Q: return 'q';
		case KC_W: return 'w';
		case KC_E: return 'e';
		case KC_R: return 'r';
		case KC_T: return 't';
		case KC_Y: return 'y';
		case KC_U: return 'u';
		case KC_I: return 'i';
		case KC_O: return 'o';
		case KC_P: return 'p';
		case KC_LBRACKET: return '[';
		case KC_RBRACKET: return ']';
		case KC_A: return 'a';
		case KC_S: return 's';
		case KC_D: return 'd';
		case KC_F: return 'f';
		case KC_G: return 'g';
		case KC_H: return 'h';
		case KC_J: return 'j';
		case KC_K: return 'k';
		case KC_L: return 'l';
		case KC_SEMICOLON: return ';';
		case KC_APOSTROPHE: return '\'';
		case KC_GRAVE: return '`';			/* accent grave */
		case KC_BACKSLASH: return '\\';
		case KC_Z: return 'z';
		case KC_X: return 'x';
		case KC_C: return 'c';
		case KC_V: return 'v';
		case KC_B: return 'b';
		case KC_N: return 'n';
		case KC_M: return 'm';
		case KC_COMMA: return ',';
		case KC_PERIOD: return '.';			/* . on main keyboard */
		case KC_SLASH: return '/';			/* '/' on main keyboard */
		case KC_MULTIPLY: return '*';		/* * on numeric keypad */
		case KC_SPACE: return ' ';
		case KC_NUMPAD7: return '7';
		case KC_NUMPAD8: return '8';
		case KC_NUMPAD9: return '9';
		case KC_SUBTRACT: return '-';		/* - on numeric keypad */
		case KC_NUMPAD4: return '4';
		case KC_NUMPAD5: return '5';
		case KC_NUMPAD6: return '6';
		case KC_ADD: return '+';			/* + on numeric keypad */
		case KC_NUMPAD1: return '1';
		case KC_NUMPAD2: return '2';
		case KC_NUMPAD3: return '3';
		case KC_NUMPAD0: return '0';
		case KC_DECIMAL: return '.';		/* . on numeric keypad */
		case KC_NUMPADEQUALS: return '=';	/* = on numeric keypad (NEC PC98) */
		case KC_AT: return '@';				/*                     (NEC PC98) */
		case KC_COLON: return ':';			/*                     (NEC PC98) */
		case KC_UNDERLINE: return '_';		/*                     (NEC PC98) */
		case KC_NUMPADCOMMA: return ',';	/* , on numeric keypad (NEC PC98) */
		case KC_DIVIDE: return '/';			/* / on numeric keypad */
		}
	}
	else if (modifiers == SHIFT_MASK)
	{
		switch (keyCode) {
		case KC_1: return '!';
		case KC_2: return '@';
		case KC_3: return '#';
		case KC_4: return '$';
		case KC_5: return '%';
		case KC_6: return '^';
		case KC_7: return '&';
		case KC_8: return '*';
		case KC_9: return '(';
		case KC_0: return ')';
		case KC_MINUS: return '_';
		case KC_EQUALS: return '+';
		case KC_Q: return 'Q';
		case KC_W: return 'W';
		case KC_E: return 'E';
		case KC_R: return 'R';
		case KC_T: return 'T';
		case KC_Y: return 'Y';
		case KC_U: return 'U';
		case KC_I: return 'I';
		case KC_O: return 'O';
		case KC_P: return 'P';
		case KC_LBRACKET: return '{';
		case KC_RBRACKET: return '}';
		case KC_A: return 'A';
		case KC_S: return 'S';
		case KC_D: return 'D';
		case KC_F: return 'F';
		case KC_G: return 'G';
		case KC_H: return 'H';
		case KC_J: return 'J';
		case KC_K: return 'K';
		case KC_L: return 'L';
		case KC_SEMICOLON: return ':';
		case KC_APOSTROPHE: return '"';
		case KC_GRAVE: return '~';			/* accent grave */
		case KC_BACKSLASH: return '|';
		case KC_Z: return 'Z';
		case KC_X: return 'X';
		case KC_C: return 'C';
		case KC_V: return 'V';
		case KC_B: return 'B';
		case KC_N: return 'N';
		case KC_M: return 'M';
		case KC_COMMA: return '<';
		case KC_PERIOD: return '>';			/* . on main keyboard */
		case KC_SLASH: return '?';			/* '/' on main keyboard */
		case KC_MULTIPLY: return '*';		/* * on numeric keypad */
		case KC_SPACE: return ' ';
		}
	}
	return 0;  
}
int BwControllerEvent::getCharKey(char c) {
	switch(c) {
		case 'a' :
		case 'A' :
			return KC_A ;
		case 'b' :
		case 'B' :
			return KC_B ;
		case 'c' :
		case 'C' :
			return KC_C ;
		case 'd' :
		case 'D' :
			return KC_D ;
		case 'e' :
		case 'E' :
			return KC_E ;
		case 'f' :
		case 'F' :
			return KC_F ;
		case 'g' :
		case 'G' :
			return KC_G ;
		case 'h' :
		case 'H' :
			return KC_H ;
		case 'i' :
		case 'I' :
			return KC_I ;
		case 'j' :
		case 'J' :
			return KC_J ;
		case 'k' :
		case 'K' :
			return KC_K ;
		case 'l' :
		case 'L' :
			return KC_L ;
		case 'm' :
		case 'M' :
			return KC_M ;
		case 'n' :
		case 'N' :
			return KC_N ;
		case 'o' :
		case 'O' :
			return KC_O ;
		case 'p' :
		case 'P' :
			return KC_P ;
		case 'q' :
		case 'Q' :
			return KC_Q ;
		case 'r' :
		case 'R' :
			return KC_R ;
		case 's' :
		case 'S' :
			return KC_S ;
		case 't' :
		case 'T' :
			return KC_T ;
		case 'u' :
		case 'U' :
			return KC_U ;
		case 'v' :
		case 'V' :
			return KC_V ;
		case 'w' :
		case 'W' :
			return KC_W ;
		case 'x' :
		case 'X' :
			return KC_X ;
		case 'y' :
		case 'Y' :
			return KC_Y ;
		case 'z' :
		case 'Z' :
			return KC_Z ;
		//
		case '1' :
			return KC_1 ;
		case '2' :
			return KC_2 ;
		case '3' :
			return KC_3 ;
		case '4' :
			return KC_4 ;
		case '5' :
			return KC_5 ;
		case '6' :
			return KC_6 ;
		case '7' :
			return KC_7 ;
		case '8' :
			return KC_8 ;
		case '9' :
			return KC_9 ;
		case '0' :
			return KC_0 ;
		//
		case 27 :
			return KC_ESCAPE ;
		case '-' :
			return KC_MINUS ;
		case '=' :
			return KC_EQUALS ;
		case 8 :
			return KC_BACK ;
		case 9 :
			return KC_TAB ;
	}
	return 0 ;
}