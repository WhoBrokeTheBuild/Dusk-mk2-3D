#pragma once

#ifndef DUSK_GRAPHICS_MATERIAL_H
#define DUSK_GRAPHICS_MATERIAL_H

#include <Tracking/ITrackedObject.h>

namespace Dusk
{

namespace Graphics
{

class Material :
	public Tracking::ITrackedObject
{
public:

	virtual inline string GetClassName( void ) const { return "Material"; }

}; // class Material

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_MATERIAL_H