#include "Time.hpp"
#include "GLFW/glfw3.h"

namespace Time {

    float lastTime;

    void Update() {
        lastTime = Get();
    }

    float Get() {
        return glfwGetTime();
    }

    float GetElapsed() {
        return Get() - lastTime;
    }

}
