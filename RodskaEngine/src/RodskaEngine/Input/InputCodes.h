
/* from glfw3.h*/#pragma once


/* The unknown key */
#define RDSK_KEY_UNKNOWN            -1

/* Printable keys */
#define RDSK_KEY_SPACE              32
#define RDSK_KEY_APOSTROPHE         39  /* ' */
#define RDSK_KEY_COMMA              44  /* , */
#define RDSK_KEY_MINUS              45  /* - */
#define RDSK_KEY_PERIOD             46  /* . */
#define RDSK_KEY_SLASH              47  /* / */
#define RDSK_KEY_0                  48
#define RDSK_KEY_1                  49
#define RDSK_KEY_2                  50
#define RDSK_KEY_3                  51
#define RDSK_KEY_4                  52
#define RDSK_KEY_5                  53
#define RDSK_KEY_6                  54
#define RDSK_KEY_7                  55
#define RDSK_KEY_8                  56
#define RDSK_KEY_9                  57
#define RDSK_KEY_SEMICOLON          59  /* ; */
#define RDSK_KEY_EQUAL              61  /* = */
#define RDSK_KEY_A                  65
#define RDSK_KEY_B                  66
#define RDSK_KEY_C                  67
#define RDSK_KEY_D                  68
#define RDSK_KEY_E                  69
#define RDSK_KEY_F                  70
#define RDSK_KEY_G                  71
#define RDSK_KEY_H                  72
#define RDSK_KEY_I                  73
#define RDSK_KEY_J                  74
#define RDSK_KEY_K                  75
#define RDSK_KEY_L                  76
#define RDSK_KEY_M                  77
#define RDSK_KEY_N                  78
#define RDSK_KEY_O                  79
#define RDSK_KEY_P                  80
#define RDSK_KEY_Q                  81
#define RDSK_KEY_R                  82
#define RDSK_KEY_S                  83
#define RDSK_KEY_T                  84
#define RDSK_KEY_U                  85
#define RDSK_KEY_V                  86
#define RDSK_KEY_W                  87
#define RDSK_KEY_X                  88
#define RDSK_KEY_Y                  89
#define RDSK_KEY_Z                  90
#define RDSK_KEY_LEFT_BRACKET       91  /* [ */
#define RDSK_KEY_BACKSLASH          92  /* \ */
#define RDSK_KEY_RIGHT_BRACKET      93  /* ] */
#define RDSK_KEY_GRAVE_ACCENT       96  /* ` */
#define RDSK_KEY_WORLD_1            161 /* non-US #1 */
#define RDSK_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define RDSK_KEY_ESCAPE             256
#define RDSK_KEY_ENTER              257
#define RDSK_KEY_TAB                258
#define RDSK_KEY_BACKSPACE          259
#define RDSK_KEY_INSERT             260
#define RDSK_KEY_DELETE             261
#define RDSK_KEY_RIGHT              262
#define RDSK_KEY_LEFT               263
#define RDSK_KEY_DOWN               264
#define RDSK_KEY_UP                 265
#define RDSK_KEY_PAGE_UP            266
#define RDSK_KEY_PAGE_DOWN          267
#define RDSK_KEY_HOME               268
#define RDSK_KEY_END                269
#define RDSK_KEY_CAPS_LOCK          280
#define RDSK_KEY_SCROLL_LOCK        281
#define RDSK_KEY_NUM_LOCK           282
#define RDSK_KEY_PRINT_SCREEN       283
#define RDSK_KEY_PAUSE              284
#define RDSK_KEY_F1                 290
#define RDSK_KEY_F2                 291
#define RDSK_KEY_F3                 292
#define RDSK_KEY_F4                 293
#define RDSK_KEY_F5                 294
#define RDSK_KEY_F6                 295
#define RDSK_KEY_F7                 296
#define RDSK_KEY_F8                 297
#define RDSK_KEY_F9                 298
#define RDSK_KEY_F10                299
#define RDSK_KEY_F11                300
#define RDSK_KEY_F12                301
#define RDSK_KEY_F13                302
#define RDSK_KEY_F14                303
#define RDSK_KEY_F15                304
#define RDSK_KEY_F16                305
#define RDSK_KEY_F17                306
#define RDSK_KEY_F18                307
#define RDSK_KEY_F19                308
#define RDSK_KEY_F20                309
#define RDSK_KEY_F21                310
#define RDSK_KEY_F22                311
#define RDSK_KEY_F23                312
#define RDSK_KEY_F24                313
#define RDSK_KEY_F25                314
#define RDSK_KEY_KP_0               320
#define RDSK_KEY_KP_1               321
#define RDSK_KEY_KP_2               322
#define RDSK_KEY_KP_3               323
#define RDSK_KEY_KP_4               324
#define RDSK_KEY_KP_5               325
#define RDSK_KEY_KP_6               326
#define RDSK_KEY_KP_7               327
#define RDSK_KEY_KP_8               328
#define RDSK_KEY_KP_9               329
#define RDSK_KEY_KP_DECIMAL         330
#define RDSK_KEY_KP_DIVIDE          331
#define RDSK_KEY_KP_MULTIPLY        332
#define RDSK_KEY_KP_SUBTRACT        333
#define RDSK_KEY_KP_ADD             334
#define RDSK_KEY_KP_ENTER           335
#define RDSK_KEY_KP_EQUAL           336
#define RDSK_KEY_LEFT_SHIFT         340
#define RDSK_KEY_LEFT_CONTROL       341
#define RDSK_KEY_LEFT_ALT           342
#define RDSK_KEY_LEFT_SUPER         343
#define RDSK_KEY_RIGHT_SHIFT        344
#define RDSK_KEY_RIGHT_CONTROL      345
#define RDSK_KEY_RIGHT_ALT          346
#define RDSK_KEY_RIGHT_SUPER        347
#define RDSK_KEY_MENU               348

#define RDSK_KEY_LAST               RDSK_KEY_MENU

#define RDSK_MOUSE_BUTTON_1         0
#define RDSK_MOUSE_BUTTON_2         1
#define RDSK_MOUSE_BUTTON_3         2
#define RDSK_MOUSE_BUTTON_4         3
#define RDSK_MOUSE_BUTTON_5         4
#define RDSK_MOUSE_BUTTON_6         5
#define RDSK_MOUSE_BUTTON_7         6
#define RDSK_MOUSE_BUTTON_8         7
#define RDSK_MOUSE_BUTTON_LAST      RDSK_MOUSE_BUTTON_8
#define RDSK_MOUSE_BUTTON_LEFT      RDSK_MOUSE_BUTTON_1
#define RDSK_MOUSE_BUTTON_RIGHT     RDSK_MOUSE_BUTTON_2
#define RDSK_MOUSE_BUTTON_MIDDLE    RDSK_MOUSE_BUTTON_3

namespace RodskaEngine {
	namespace InputCode {
		enum KeyCode {
			Unknown = -1,
			Space = 32,
			Apostrophe = 39,
			Comma = 44,
			Minus,
			Period,
			Slash,
			Zero,
			One,
			Two,
			Three,
			Four,
			Five,
			Six,
			Seven,
			Eight,
			Nine,
			SemiColon = 59,
			Equal = 61,
			A = 65,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			LeftBracket = 91,
			BackSlash,
			RightBracket,
			GraveAccent = 96,
			World1 = 161,
			World2,
			Escape = 256,
			Enter,
			Tab,
			Backspace,
			Insert,
			Delete,
			Right,
			Left,
			Down,
			Up,
			PageUp,
			PageDown,
			Home,
			End,
			CapsLock = 280,
			ScrollLock,
			NumLock,
			PrintScreen,
			Pause,
			F1 = 290,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,
			F25,
			KeyPad0 = 320,
			KeyPad1,
			KeyPad2,
			KeyPad3,
			KeyPad4,
			KeyPad5,
			KeyPad6,
			KeyPad7,
			KeyPad8,
			KeyPad9,
			KeyPadDecimal,
			KeyPadDivide,
			KeyPadMultiply,
			KeyPadSubtract,
			KeyPadAdd,
			KeyPadEnter,
			KeyPadEqual,
			LeftShift = 340,
			LeftControl,
			LeftAlt,
			LeftSuper,
			RightShift,
			RightControl,
			RightAlt,
			RightSuper,
			Menu
		};
	};
}