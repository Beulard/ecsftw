#ifndef WATER_INPUTMANAGER
#define WATER_INPUTMANAGER
#include <map>
#include "vec2.hpp"

typedef unsigned int u32;

enum InputState {
    IS_Pressed,
    IS_Released
};

enum KeyCode {
    KC_A = 'A',
    KC_B = 'B',
    KC_C = 'C',
    KC_D = 'D',
    KC_E = 'E',
    KC_F = 'F',
    KC_G = 'G',
    KC_H = 'H',
    KC_I = 'I',
    KC_J = 'J',
    KC_K = 'K',
    KC_L = 'L',
    KC_M = 'M',
    KC_N = 'N',
    KC_O = 'O',
    KC_P = 'P',
    KC_Q = 'Q',
    KC_R = 'R',
    KC_S = 'S',
    KC_T = 'T',
    KC_U = 'U',
    KC_V = 'V',
    KC_W = 'W',
    KC_X = 'X',
    KC_Y = 'Y',
    KC_Z = 'Z',

    KC_Space = 32,
    KC_Escape = 256,
    KC_Enter = 257,
    KC_Delete = 261,
    KC_Right = 262,
    KC_Left = 263,
    KC_Down = 264,
    KC_Up = 265,

    KC_CapsLock = 280,

    KC_F1 = 290,
    KC_F2 = 291,
    KC_F3 = 292,
    KC_F4 = 293,
    KC_F5 = 294,
    KC_F6 = 295,
    KC_F7 = 296,
    KC_F8 = 297,
    KC_F9 = 298,
    KC_F10 = 299,
    KC_F11 = 300,
    KC_F12 = 301,
    KC_F13 = 302,
    KC_F14 = 303,
    KC_F15 = 304,
    KC_F16 = 305,
    KC_F17 = 306,
    KC_F18 = 307,
    KC_F19 = 308,
    KC_F20 = 309,
    KC_F21 = 310,
    KC_F22 = 311,
    KC_F23 = 312,
    KC_F24 = 313,
    KC_F25 = 314,


    KC_LeftShift = 340,
    KC_LeftControl = 341,
    KC_LeftAlt = 342,

    KC_RightShift = 344,
    KC_RightControl = 345,
    KC_RightAlt = 346,

    KC_NumPad0 = 320,
    KC_NumPad1 = 321,
    KC_NumPad2 = 322,
    KC_NumPad3 = 323,
    KC_NumPad4 = 324,
    KC_NumPad5 = 325,
    KC_NumPad6 = 326,
    KC_NumPad7 = 327,
    KC_NumPad8 = 328,
    KC_NumPad9 = 329
};


const u32 keys[76] = {
    KC_A,
    KC_B,
    KC_C,
    KC_D,
    KC_E,
    KC_F,
    KC_G,
    KC_H,
    KC_I,
    KC_J,
    KC_K,
    KC_L,
    KC_M,
    KC_N,
    KC_O,
    KC_P,
    KC_Q,
    KC_R,
    KC_S,
    KC_T,
    KC_U,
    KC_V,
    KC_W,
    KC_X,
    KC_Y,
    KC_Z,

    KC_Space,
    KC_Escape,
    KC_F1,
    KC_F2,
    KC_F3,
    KC_F4,
    KC_F5,
    KC_F6,
    KC_F7,
    KC_F8,
    KC_F9,
    KC_F10,
    KC_F11,
    KC_F12,
    KC_F13,
    KC_F14,
    KC_F15,
    KC_F16,
    KC_F17,
    KC_F18,
    KC_F19,
    KC_F20,
    KC_F21,
    KC_F22,
    KC_F23,
    KC_F24,
    KC_F25,

    KC_Up,
    KC_Down,
    KC_Left,
    KC_Right,
    KC_LeftShift,
    KC_RightShift,
    KC_LeftControl,
    KC_RightControl,
    KC_LeftAlt,
    KC_RightAlt,

    KC_Enter,

    KC_Delete,

    KC_NumPad0,
    KC_NumPad1,
    KC_NumPad2,
    KC_NumPad3,
    KC_NumPad4,
    KC_NumPad5,
    KC_NumPad6,
    KC_NumPad7,
    KC_NumPad8,
    KC_NumPad9,

    KC_CapsLock
};

enum MouseCode {
    MC_Left,
    MC_Right,
    MC_Middle
};

const u32 buttons[3] = {
    MC_Left,
    MC_Right,
    MC_Middle
};

struct GLFWwindow;

class InputCallback {
    public:
        static void GLFWKeyboardCallback( GLFWwindow* win, int key, int scancode, int action, int mods );
        static void GLFWMouseButtonCallback( GLFWwindow* win, int button, int action, int mods );
        static void GLFWMousePosCallback( int x, int y );
        static void GLFWMouseWheelCallback( int pos );
        static void GLFWCharCallback( GLFWwindow* win, unsigned int input );
};

class InputManager
{
    public:
        InputManager( GLFWwindow* win );
        ~InputManager();

        void Update();
        InputState GetState( KeyCode code )  const;
        InputState GetState( MouseCode code )    const;
        bool WasPressed( KeyCode code ) const;
        bool WasPressed( MouseCode code ) const;
        bool WasReleased( KeyCode code ) const;
        bool WasReleased( MouseCode code ) const;
        const vec2i& GetMousePos()   const;
        int GetWheelPos()   const;

        //  Did the user type a character on the keyboard ?
        bool CharTyped() const;
        char GetTypedChar() const;


        bool WindowShouldClose()   const;

        friend InputCallback;

    private:
        GLFWwindow* window;

        std::map< KeyCode, InputState > keyboard;
        std::map< MouseCode, InputState > mouse;

        unsigned int typedChar;

        //  If the window got closed, the flag is set to true
        bool closed;
        //  Mouse position
        vec2i mousePos;
        int wheelPos;
};


#endif // WATER_INPUTMANAGER
