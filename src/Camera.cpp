#include "Camera.hpp"

namespace Camera {

    vec2i position;

    void SetPosition( vec2i pos ) {
        position = pos;
    }

    const vec2i& GetPosition() {
        return position;
    }

}
