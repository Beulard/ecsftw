TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR = bin
OBJECTS_DIR = obj
QMAKE_CXXFLAGS += -std=c++0x

DEFINES += GLEW_STATIC
CONFIG(debug) {
    DEFINES += WATER_DEBUG
}

INCLUDEPATH += $$PWD/include + $$PWD/src + $$PWD/src/Systems + $$PWD/src/Factories

LIBS += -L$$PWD/lib/ -lglew32 -lglfw3 -lopengl32 -lgdi32 -lpng -lzlib -static -static-libgcc -static-libstdc++

SOURCES += \
    src/FileStream.cpp \
    src/main.cpp \
    src/Common.cpp \
    src/Game.cpp \
    src/SpriteBatch.cpp \
    src/VertexShader.cpp \
    src/ShaderProgram.cpp \
    src/Shader.cpp \
    src/FragmentShader.cpp \
    src/InputManager.cpp \
    src/ResourceManager.cpp \
    src/Texture.cpp \
    src/Systems/System.cpp \
    src/Systems/PhysicsSystem.cpp \
    src/ComponentManager.cpp \
    src/EntityManager.cpp \
    src/Wash.cpp \
    src/Systems/GraphicSystem.cpp \
    src/Camera.cpp \
    src/Factories/SpriteFactory.cpp \
    src/Systems/Systems.cpp \
    src/Time.cpp \
    src/Factories/TextFactory.cpp \
    src/Factories/AnimFactory.cpp

HEADERS += \
    src/FileStream.hpp \
    src/Common.hpp \
    src/Game.hpp \
    src/vec2.hpp \
    src/SpriteBatch.hpp \
    src/VertexShader.hpp \
    src/ShaderProgram.hpp \
    src/Shader.hpp \
    src/InputManager.hpp \
    src/ResourceManager.hpp \
    src/Texture.hpp \
    src/Component.hpp \
    src/ComponentManager.hpp \
    src/Systems/System.hpp \
    src/Systems/PhysicsSystem.hpp \
    src/EntityManager.hpp \
    src/Wash.hpp \
    src/Systems/GraphicSystem.hpp \
    src/Camera.hpp \
    src/Factories/SpriteFactory.hpp \
    src/Systems/Systems.hpp \
    src/Time.hpp \
    src/Factories/TextFactory.hpp \
    src/Factories/AnimFactory.hpp

