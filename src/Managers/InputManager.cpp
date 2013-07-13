#include "InputManager.hpp"
#include "Game.hpp"
#include "GLFW/glfw3.h"

InputManager::InputManager( GLFWwindow* win ) : window(win), typedChar('\0'), closed(false), mousePos(vec2i(0,0)), wheelPos(0) {
    for( u32 i = 0; i < 76; ++i )
        keyboard.insert( std::pair< KeyCode, InputState >( (KeyCode)keys[i], IS_Released ) );
    for( u32 i = 0; i < 3; ++i )
        mouse.insert( std::pair< MouseCode, InputState >( (MouseCode)buttons[i], IS_Released ) );

    glfwSetMouseButtonCallback( window, (GLFWmousebuttonfun)&InputCallback::GLFWMouseButtonCallback );
    //glfwSetMousePosCallback( game.GetWindow(), (GLFWmouseposfun)&InputCallbacks::GLFWMousePosCallback );
    glfwSetKeyCallback( window, (GLFWkeyfun)&InputCallback::GLFWKeyboardCallback );
    //glfwSetMouseWheelCallback( game.GetWindow(), (GLFWmousewheelfun)&InputCallbacks::GLFWMouseWheelCallback );
    glfwSetCharCallback( window, (GLFWcharfun)&InputCallback::GLFWCharCallback );
}

InputManager::~InputManager(){

}

void InputManager::Update() {
    typedChar = '\0';
    glfwPollEvents();
    if( glfwWindowShouldClose( window ) )
        closed = true;
}

bool InputManager::CharTyped() const {
    return (typedChar != '\0' );
}

char InputManager::GetTypedChar()   const {
    return typedChar;
}

void InputCallback::GLFWKeyboardCallback( GLFWwindow* win, int key, int scancode, int action, int mods ) {
    auto it = game.GetInputManager()->keyboard.find( (KeyCode)key );
    if( it != game.GetInputManager()->keyboard.end() ) {
        switch( action ) {
            case GLFW_PRESS :
            case GLFW_REPEAT :
                it->second = IS_Pressed;
            break;
            case GLFW_RELEASE :
                it->second= IS_Released;
            break;
        }
    }
}

void InputCallback::GLFWMouseButtonCallback( GLFWwindow* win, int button, int action, int mods ) {
    auto it = game.GetInputManager()->mouse.find( (MouseCode)button );
    if( it != game.GetInputManager()->mouse.end() ) {
        switch( action ) {
            case GLFW_PRESS :
                it->second = IS_Pressed;
            break;
            case GLFW_RELEASE :
                it->second = IS_Released;
            break;
        }
    }
}

void InputCallback::GLFWMousePosCallback( int x, int y ) {
    game.GetInputManager()->mousePos.x = x;
    game.GetInputManager()->mousePos.y = y;
}

void InputCallback::GLFWMouseWheelCallback( int pos ) {
    game.GetInputManager()->wheelPos = pos;
}

void InputCallback::GLFWCharCallback( GLFWwindow* win, unsigned int code ) {
    game.GetInputManager()->typedChar = code;
}

const vec2i& InputManager::GetMousePos() const {
    return mousePos;
}

InputState InputManager::GetState( KeyCode code )    const {
    auto it = keyboard.find( code );
    if( it != keyboard.end() )
        return it->second;
    return IS_Released;
}

InputState InputManager::GetState( MouseCode code )  const {
    auto it = mouse.find( code );
    if( it != mouse.end() )
        return it->second;
    return IS_Released;
}

bool InputManager::WasPressed( KeyCode code ) const {
    auto it = keyboard.find( code );
    if( it != keyboard.end() ) {
        return (it->second == IS_Pressed);
    }
    return false;
}

bool InputManager::WasPressed( MouseCode code ) const {
    auto it = mouse.find( code );
    if( it != mouse.end() )
        return (it->second == IS_Pressed);
    return false;
}

bool InputManager::WasReleased( KeyCode code ) const {
    auto it = keyboard.find( code );
    if( it != keyboard.end() )
        return (it->second == IS_Released);
    return false;
}

bool InputManager::WasReleased( MouseCode code ) const {
    auto it = mouse.find( code );
    if( it != mouse.end() )
        return (it->second == IS_Released);
    return false;
}

int InputManager::GetWheelPos() const {
    return wheelPos;
}

bool InputManager::WindowShouldClose() const {
    return closed;
}
