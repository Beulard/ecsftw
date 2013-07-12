#include "Texture.hpp"

Texture::Texture() : id(0) {

}

Texture::~Texture() {

}

void Texture::Generate( const std::vector<u8>& bytes, const vec2ui& sz, bool rgba ) {
    size = sz;
    glActiveTexture( GL_TEXTURE0 );
    glGenTextures( 1, &id );
    glBindTexture( GL_TEXTURE_2D, id );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glTexImage2D( GL_TEXTURE_2D, 0, rgba ? 4 : 3, sz.x, sz.y, 0, rgba ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, &bytes[0] );
}

void Texture::Destroy() {
    glDeleteTextures( 1, &id );
}

void Texture::Bind() {
    glBindTexture( GL_TEXTURE_2D, id );
}

const vec2ui& Texture::GetSize() const {
    return size;
}
