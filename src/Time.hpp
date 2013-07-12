#ifndef TIME_HPP
#define TIME_HPP

namespace Time {

    //  Updates the game time
    void Update();
    //  Gets the current time as defined by glfw
    float Get();
    //  Gets the elapsed time since the last call to Update() -> the time since the last frame
    float GetElapsed();

}

#endif // TIME_HPP
