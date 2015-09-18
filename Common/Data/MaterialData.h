#ifndef DUSK_INTER_MATERIAL_H
#define DUSK_INTER_MATERIAL_H

#include <Tracking/ITrackedObject.h>
#include <Math/Math.h>

namespace Dusk
{

namespace Data
{

using namespace Dusk::Math;

struct MaterialData :
	public Tracking::ITrackedObject
{
public:

	virtual inline string GetClassName( void ) const { return "Material Data"; }

	string  Name;

	string  DiffuseMap,
			AmbientMap,
			SpecularMap,
			SpecularHilightMap,
			AlphaMap,
			BumpMap;

	float   Specular,
			Transparency;

	vec3    AmbientColor,
			DiffuseColor,
			SpecularColor;

}; // struct MaterialData

} // namespace Data

} // namespace Dusk

#endif // DUSK_INTER_MATERIAL_H
