#ifndef DUSK_GRAPHICS_GRAPHICS_SYSTEM_H
#define DUSK_GRAPHICS_GRAPHICS_SYSTEM_H

#include <Tracking/TrackedObject.h>

namespace Dusk
{

namespace Graphics
{

class GraphicsSystem :
	public Tracking::TrackedObject
{
public:

	virtual inline string ClassName( void ) const { return "Graphics System"; }

	bool Init( void );

}; // class GraphicsSystem

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_GRAPHICS_SYSTEM_H