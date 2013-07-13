#ifndef ANIMMANAGER_HPP
#define ANIMMANAGER_HPP
#include <string>

typedef unsigned int u32;
class SpriteBatch;

struct FrameInfo {
    int topLeftX, topLeftY, bottomRightX, bottomRightY;
    float time;
};

struct AnimInfo {
    std::string batch;
    int x, y;
    u32 w, h;
    u32 currentFrame;
    float currentTime;
};

namespace AnimManager {

    void Create( u32 id, const AnimInfo& anim );
    void Destroy( u32 id );

    void AddFrame( u32 id, const FrameInfo& frame );

    void Draw( u32 id );
    void StopDrawing( u32 id );

    void Update();

}

#endif // ANIMMANAGER_HPP
