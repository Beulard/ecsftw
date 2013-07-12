#ifndef WATER_SHADER
#define WATER_SHADER
#include <GL/glew.h>

enum ShaderType {
    ST_Vertex,
    ST_Fragment
};

class Shader
{
    public:
        Shader();
        virtual ~Shader();

        virtual void Load( const char* code ) = 0;

    protected :
        GLuint id;
        ShaderType type;
};

#endif // WATER_SHADER
