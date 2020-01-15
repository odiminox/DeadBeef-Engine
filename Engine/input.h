#include <windows.h>

BOOL	keys[256];			// Array Used For The Keyboard Routine
BOOL    leftMouseButton;
BOOL	rightMouseButton;
enum gameKeys
{
	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,
	BUTTON1 = VK_XBUTTON1,
	BUTTON2 = VK_XBUTTON2,
	CTRL     = VK_CONTROL,
	ESCAPE   = VK_ESCAPE,
	SPACE    = VK_SPACE,
	ZERO     = 0x30,
	ONE      = 0x31,
	TWO      = 0x32,
	THREE    = 0x33,
	FOUR     = 0x34,
	FIVE     = 0x35,
	SIX      = 0x36,
	SEVEN    = 0x37,
	EIGHT    = 0x38,
	NINE     = 0x39,
	A        = 0x41,
	B        = 0x42,
	C		 = 0x43,
	D		 = 0x44,
	E		 = 0x45,
	F		 = 0x46,
	G		 = 0x47,
	H        = 0x48,
	I		 = 0x49,
	J		 = 0x4A,
	K	     = 0x4B,
	L		 = 0x4C,
	M		 = 0x4D,
	N		 = 0x4E,
	O		 = 0x4F,
	P		 = 0x50,
	Q		 = 0x51,
	R	     = 0x52,
	S		 = 0x53,
	T		 = 0x54,
	U		 = 0x55,
	V		 = 0x56,
	W		 = 0x57,
	X		 = 0x58,
	Y		 = 0x59,
	z		 = 0x5A,
	NUM0	 = VK_NUMPAD0,
	NUM1	 = VK_NUMPAD1,
	NUM2	 = VK_NUMPAD2,
	NUM3	 = VK_NUMPAD3,
	NUM4	 = VK_NUMPAD4,
	NUM5	 = VK_NUMPAD5,
	NUM6	 = VK_NUMPAD6,
	NUM7	 = VK_NUMPAD7,
	NUM8	 = VK_NUMPAD8,
	NUM9	 = VK_NUMPAD9,
	F1		 = VK_F1,
	F2		 = VK_F2,
	F3		 = VK_F3,
	F4		 = VK_F4,
	F5		 = VK_F5,
	F6		 = VK_F6,
	F7		 = VK_F7,
	F8		 = VK_F8,
	F9		 = VK_F9,
	F10		 = VK_F10,
	F11		 = VK_F11,
	F12		 = VK_F12,
	RSHIFT	 = VK_RSHIFT,
	LSHIFT	 = VK_LSHIFT,
	LCTRL	 = VK_LCONTROL,
	RCTRL    = VK_RCONTROL
};

enum gameMouse {
	LMBUTTON = MK_LBUTTON,
	MMBUTTON = MK_MBUTTON,
	RMBUTTON = MK_RBUTTON,
	MMOUSE   = WM_MOUSEMOVE

};