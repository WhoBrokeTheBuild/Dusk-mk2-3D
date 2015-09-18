#pragma once

#ifndef DUSK_GRAPHICS_MODEL_H
#define DUSK_GRAPHICS_MODEL_H

#include <Tracking/ITrackedObject.h>

namespace Dusk
{

namespace Graphics
{

class Model :
	public Tracking::ITrackedObject
{
public:

	virtual inline string GetClassName( void ) const { return "Model"; }


}; // class Model

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_MODEL_H