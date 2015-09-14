#ifndef DUSK_TEXTURE_H
#define DUSK_TEXTURE_H

#include <Tracking/ITrackedObject.h>
#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Graphics
{

class Texture :
	public Tracking::ITrackedObject
{
public:

    inline Texture( void ) :
        m_Texture(0)
    { }

    virtual ~Texture( void );

	virtual inline string GetClassName( void ) const { return "Texture"; }

    bool Load( const string& filename );
    void Bind( void );

private:

    GLTexture   m_Texture;

}; // class Texture

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_TEXTURE_H
