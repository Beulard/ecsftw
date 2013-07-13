#ifndef SPRITESYSTEM_HPP
#define SPRITESYSTEM_HPP
#include "System.hpp"
#include "SpriteBatch.hpp"
#include "Wash.hpp"

class GraphicSystem : public System
{
    public:
        GraphicSystem();
        ~GraphicSystem();

        virtual void Attach( u32 id );
        virtual void Detach( u32 id );

        void AddSpriteBatch( const std::string& name, SpriteBatch* batch );

        void SetSpriteBatch( u32 id, const std::string& name );
        void SetSpriteBatch( u32 id, SpriteBatch* batch );
        void SetSpritePosition( u32 id, int x, int y );
        void SetSpriteSize( u32 id, int w, int h );
        void SetSpriteTexCoords( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY );

        void Draw( u32 id );
        void StopDrawing( u32 id );
        bool IsDrawn( u32 id );

        void Render();

    private:
        std::map< wash, SpriteBatch* > batches;

};

#endif // SPRITESYSTEM_HPP
