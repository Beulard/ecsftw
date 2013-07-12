#include "Game.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "PhysicsSystem.hpp"
#include "GraphicSystem.hpp"
#include "Systems.hpp"
#include "SpriteFactory.hpp"
#include "TextFactory.hpp"
#include "Time.hpp"

Game::Game() {

}

Game::~Game() {

}

bool Game::Init() {
    gamelog = fopen( "log", "w" );
    Append( "[][][][    TETRIS    ][][][]\n\n" );
    windowSize = vec2ui( 400, 600 );
    if( !glfwInit() ) {
        Error( "Could not initialize GLFW" );
        return false;
    }
    //glfwWindowHint( GLFW_ALPHA_BITS, 8 );
    //glfwWindowHint( GLFW_DEPTH_BITS, 8 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    window = glfwCreateWindow( windowSize.x, windowSize.y, ":D", NULL, NULL );
    glfwMakeContextCurrent( window );

    if( glewInit() != GLEW_OK ) {
        Error( "Could not initialize GLEW" );
        return false;
    }

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glClearColor( .7, .7, .7, 1 );


    projMatrix[0] = 2.f / windowSize.x;
    projMatrix[1] = 0.f;
    projMatrix[2] = 0.f;
    projMatrix[3] = 0.f;
    projMatrix[4] = 2.f / windowSize.y;
    projMatrix[5] = 0.f;
    projMatrix[6] = -1.f;
    projMatrix[7] = -1.f;
    projMatrix[8] = 0.f;

    ///////////////////////////////////////////////////////////////////

    inputs = new InputManager( window );

    Systems::Add( "physics", new PhysicsSystem );
    Systems::Add( "graphic", new GraphicSystem );

    ResourceManager::LoadShader( "sprite.vs", "sprite.fs", false );
    ResourceManager::LoadTexture( "tetriminos.png" );
    ResourceManager::LoadTexture( "font.png" );

    ComponentManager::AddComponentType<PhysicsComponent>();
    ComponentManager::AddComponentType<GraphicComponent>( 50 );


    GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );
    graphic->AddSpriteBatch( "tetriminos", new SpriteBatch( ResourceManager::GetTexture( "tetriminos.png" ), ResourceManager::GetShader( "sprite" ) ) );
    graphic->AddSpriteBatch( "font", new SpriteBatch( ResourceManager::GetTexture( "font.png" ), ResourceManager::GetShader( "sprite" ) ) );

    return true;
}

void Game::Run() {
    bool running = true;

    GraphicSystem* graphic = (GraphicSystem*)Systems::Get( "graphic" );

    u32 ent0 = EntityManager::Create();
    SpriteFactory::AttachSprite( ent0, "tetriminos", Pos(0, 0), Size(16, 64), TexCoord(0, 0), TexCoord(16, 64) );

    u32 ent1 = EntityManager::Create();
    TextFactory::AttachText( ent1, "0123456789", "font", Pos( 0, 64 ) );
    graphic->DrawText( ent1 );

    float oneSecTimer = 0;
    while(running) {
        inputs->Update();
        if( inputs->WindowShouldClose() )
            running = false;
        if( inputs->WasPressed( KC_Escape ) )
            running = false;

        glClear( GL_COLOR_BUFFER_BIT );
        graphic->Render();
        glfwSwapBuffers( window );

        oneSecTimer += Time::GetElapsed();
        if( oneSecTimer >= 1.f ) {
            if( graphic->IsDrawn( ent0 ) )
                graphic->StopDrawing( ent0 );
            else
                graphic->Draw( ent0 );
            oneSecTimer = 0;
        }

        Time::Update();
    }
}

void Game::Exit() {
    EntityManager::DestroyAll();
    ComponentManager::Free();
    ResourceManager::UnloadAll();
    Systems::Destroy();
    glfwDestroyWindow( window );
    glfwTerminate();
    Append( "\n\n" );
    fclose( gamelog );
}

GLFWwindow* Game::GetWindow() const {
    return window;
}

InputManager* Game::GetInputManager() const {
    return inputs;
}
