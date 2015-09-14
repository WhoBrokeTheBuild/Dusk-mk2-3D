#include "Texture.h"

#include <Logging/LoggingSystem.h>
#include <lodepng.h>

using namespace Dusk::Logging;
using namespace Dusk::Graphics;

Dusk::Graphics::Texture::~Texture( void )
{
    if (m_Texture != 0)
        glDeleteTextures(1, &m_Texture);
}

bool Texture::
Load( const string& filename )
{
    DuskExtLog("verbose", "Load from file \"%s\"", filename.c_str());
    std::vector<unsigned char> pixels;
    unsigned int width, height;

    unsigned int error = lodepng::decode(pixels, width, height, filename.c_str());

    if (error)
    {
		DuskExtLog("error", "Failed to load file \"%s\", %s", filename.c_str(), lodepng_error_text(error));
        return false;
    }

    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    GLenum wrapMode = GL_REPEAT;
    GLenum minFilter = GL_LINEAR;
    GLenum magFilter = GL_LINEAR;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    return true;
}

void Texture::
Bind( void )
{
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}
