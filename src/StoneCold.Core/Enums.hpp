
#ifndef STONECOLD_CORE_ENUMS_H
#define STONECOLD_CORE_ENUMS_H

namespace StoneCold::Core {

enum class SceneType {
	None,
	MainMenu,
	GamePlay
};

//
// Event Code send via a custom SceneEvent callback (from Scene to GameCore)
//
enum SceneEvent {
	ChangeScene,
	QuitGame
};

//
// UI Element State
//
enum class UiWidgetState {
	Idle,
	Hover,
	Pressed
};

//
// All the available Level Types
// (Maybe replace with a runtime-check of which Map-Textures are available)
//
enum class LevelType {
	Grassland,
	Desert,
	Castle,
	Highlands,
	Arctic
};

//
// MapTiles used by the Random Map Generator
// These TileTypes will be mapped to a part of the Level-Texture
//
enum class MapTileType {
	Placeholder,
	Portal,

	Top_Default,
	Top_Special,

	Floor_Default,
	Floor_Special_1,
	Floor_Special_2,
	Floor_Special_3,
	Floor_Special_4,
	Floor_Shadow,

	Wall_Top,
	Wall_Left,
	Wall_Right,
	Wall_Bottom,

	Corner_Top_Left,
	Corner_Top_Right,
	Corner_Bottom_Left,
	Corner_Bottom_Right,

	Endblock_Top,
	Endblock_Left,
	Endblock_Right,
	Endblock_Bottom,

	Middle_Block_Horizontal,
	Middle_Block_Vertical,
};

//
// Scene Action Types
//
enum class ActionType {
	Start,
	End
};

//
// ActionMap based on sc_settings.json
// (First 100 Actions match the sf::Keyboard key codes exactly)
//
enum ActionMap {
	// SFML Keyboard based Action IDs
	Unknown = -1,
	Keyboard_A = 0,
	Keyboard_B = 1,
	Keyboard_C = 2,
	Keyboard_D = 3,
	Keyboard_E = 4,
	Keyboard_F = 5,
	Keyboard_G = 6,
	Keyboard_H = 7,
	Keyboard_I = 8,
	Keyboard_J = 9,
	Keyboard_K = 10,
	Keyboard_L = 11,
	Keyboard_M = 12,
	Keyboard_N = 13,
	Keyboard_O = 14,
	Keyboard_P = 15,
	Keyboard_Q = 16,
	Keyboard_R = 17,
	Keyboard_S = 18,
	Keyboard_T = 19,
	Keyboard_U = 20,
	Keyboard_V = 21,
	Keyboard_W = 22,
	Keyboard_X = 23,
	Keyboard_Y = 24,
	Keyboard_Z = 25,
	Keyboard_Num0 = 26,
	Keyboard_Num1 = 27,
	Keyboard_Num2 = 28,
	Keyboard_Num3 = 29,
	Keyboard_Num4 = 30,
	Keyboard_Num5 = 31,
	Keyboard_Num6 = 32,
	Keyboard_Num7 = 33,
	Keyboard_Num8 = 34,
	Keyboard_Num9 = 35,
	Keyboard_Escape = 36,
	Keyboard_LControl = 37,
	Keyboard_LShift = 38,
	Keyboard_LAlt = 39,
	Keyboard_LSystem = 40,
	Keyboard_RControl = 41,
	Keyboard_RShift = 42,
	Keyboard_RAlt = 43,
	Keyboard_RSystem = 44,
	Keyboard_Menu = 45,
	Keyboard_LBracket = 46,
	Keyboard_RBracket = 47,
	Keyboard_Semicolon = 48,
	Keyboard_Comma = 49,
	Keyboard_Period = 50,
	Keyboard_Quote = 51,
	Keyboard_Slash = 52,
	Keyboard_Backslash = 53,
	Keyboard_Tilde = 54,
	Keyboard_Equal = 55,
	Keyboard_Hyphen = 56,
	Keyboard_Space = 57,
	Keyboard_Enter = 58,
	Keyboard_Backspace = 59,
	Keyboard_Tab = 60,
	Keyboard_PageUp = 61,
	Keyboard_PageDown = 62,
	Keyboard_End = 63,
	Keyboard_Home = 64,
	Keyboard_Insert = 65,
	Keyboard_Delete = 66,
	Keyboard_Add = 67,
	Keyboard_Subtract = 68,
	Keyboard_Multiply = 69,
	Keyboard_Divide = 70,
	Keyboard_Left = 71,
	Keyboard_Right = 72,
	Keyboard_Up = 73,
	Keyboard_Down = 74,
	Keyboard_Numpad0 = 75,
	Keyboard_Numpad1 = 76,
	Keyboard_Numpad2 = 77,
	Keyboard_Numpad3 = 78,
	Keyboard_Numpad4 = 79,
	Keyboard_Numpad5 = 80,
	Keyboard_Numpad6 = 81,
	Keyboard_Numpad7 = 82,
	Keyboard_Numpad8 = 83,
	Keyboard_Numpad9 = 84,
	Keyboard_F1 = 85,
	Keyboard_F2 = 86,
	Keyboard_F3 = 87,
	Keyboard_F4 = 88,
	Keyboard_F5 = 89,
	Keyboard_F6 = 90,
	Keyboard_F7 = 91,
	Keyboard_F8 = 92,
	Keyboard_F9 = 93,
	Keyboard_F10 = 94,
	Keyboard_F11 = 95,
	Keyboard_F12 = 96,
	Keyboard_F13 = 97,
	Keyboard_F14 = 98,
	Keyboard_F15 = 99,
	Keyboard_Pause = 100,
	// Custom Action IDs
	Mouse_Left = 200,
	Mouse_Right = 201,
	Mouse_Moved = 202,
};

}

#endif
