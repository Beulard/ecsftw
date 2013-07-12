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
        void AttachText( u32 id );
        void DetachText( u32 id );
        void AttachAnim( u32 id );
        void DetachAnim( u32 id );

        void AddSpriteBatch( const std::string& name, SpriteBatch* batch );

        void SetSpriteBatch( u32 id, const std::string& name );
        void SetSpriteBatch( u32 id, SpriteBatch* batch );
        void SetSpritePosition( u32 id, int x, int y );
        void SetSpriteSize( u32 id, int w, int h );
        void SetSpriteTexCoords( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY );

        void SetTextString( u32 id, const std::string& s );
        void SetTextPosition( u32 id, int x, int y );

        void SetAnimPosition( u32 id, int x, int y );
        void SetAnimSize( u32 id, int w, int h );
        void AddFrame( u32 id, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, float time );
        void SetFrameTime( u32 id, u32 frameID, float time );

        void Draw( u32 id );
        void StopDrawing( u32 id );
        bool IsDrawn( u32 id );

        void DrawText( u32 id );
        void StopDrawingText( u32 id );
        bool IsTextDrawn( u32 id );

        void DrawAnim( u32 id );
        void StopDrawingAnim( u32 id );
        bool IsAnimDrawn( u32 id );

        void Render();

    private:
        std::map< wash, SpriteBatch* > batches;

        //  Links a text-entity with all its sprite-entities
        std::map< u32, std::vector<u32> > texts;

        //  Links an anim-entity with all its frame-entities
        std::map< u32, std::vector<u32> > anims;

        //  Makes a correspondance between characters and their position in the texture
        std::map< char, char > ids;
};

#endif // SPRITESYSTEM_HPP
