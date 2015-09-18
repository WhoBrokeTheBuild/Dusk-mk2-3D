#ifndef DUSK_INTER_TEXTURE_H
#define DUSK_INTER_TEXTURE_H

#include <Tracking/ITrackedObject.h>
#include <Collections/ArrayList.h>

namespace Dusk
{

namespace Data
{

using namespace Dusk::Collections;

struct TextureData :
	public Tracking::ITrackedObject
{
public:

	virtual inline string GetClassName( void ) const { return "Texture Data"; }

    unsigned int                Width,
                                Height;

    ArrayList<unsigned char>    Pixels;

}; // struct TextureData

} // namespace Data

} // namespace Dusk

#endif // DUSK_INTER_TEXTURE_H
