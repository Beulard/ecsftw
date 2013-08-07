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

INCLUDEPATH += $$PWD/include + $$PWD/src + $$PWD/src/Systems + $$PWD/src/Factories + $$PWD/src/Managers

LIBS += -L$$PWD/lib/ -lopenal -lglew32 -lglfw3 -lopengl32 -lgdi32 -lpng -lzlib -static -static-libgcc -static-libstdc++

SOURCES += \
    src/FileStream.cpp \
    src/main.cpp \
    src/Common.cpp \
    src/Game.cpp \
    src/SpriteBatch.cpp \
    src/ShaderProgram.cpp \
    src/Shader.cpp \
    src/Texture.cpp \
    src/Systems/PhysicsSystem.cpp \
    src/Wash.cpp \
    src/Systems/GraphicSystem.cpp \
    src/Camera.cpp \
    src/Factories/SpriteFactory.cpp \
    src/Time.cpp \
    src/Factories/TextFactory.cpp \
    src/Managers/ResourceManager.cpp \
    src/Managers/InputManager.cpp \
    src/Managers/EntityManager.cpp \
    src/Managers/ComponentManager.cpp \
    src/Managers/TextManager.cpp \
    src/Managers/AnimManager.cpp

HEADERS += \
    src/FileStream.hpp \
    src/Common.hpp \
    src/Game.hpp \
    src/vec2.hpp \
    src/SpriteBatch.hpp \
    src/ShaderProgram.hpp \
    src/Shader.hpp \
    src/Texture.hpp \
    src/Component.hpp \
    src/Systems/PhysicsSystem.hpp \
    src/Wash.hpp \
    src/Systems/GraphicSystem.hpp \
    src/Camera.hpp \
    src/Factories/SpriteFactory.hpp \
    src/Time.hpp \
    src/Factories/TextFactory.hpp \
    src/Factories/AnimFactory.hpp \
    src/Managers/ResourceManager.hpp \
    src/Managers/InputManager.hpp \
    src/Managers/EntityManager.hpp \
    src/Managers/ComponentManager.hpp \
    src/Managers/TextManager.hpp \
    src/Managers/AnimManager.hpp \
    src/Output.hpp

