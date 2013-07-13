#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <string>

struct Component{ };
struct PhysicsComponent : public Component{
        int x, y, velX, velY;
};

class SpriteBatch;
struct GraphicComponent : public Component{
        int x, y, width, height;
        float topLeftX, topLeftY, bottomRightX, bottomRightY;
        SpriteBatch* batch;
        int batchID;
};

#endif // COMPONENT_HPP
