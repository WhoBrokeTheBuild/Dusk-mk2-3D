#ifndef DUSK_INTER_MESH_H
#define DUSK_INTER_MESH_H

#include <Collections/ArrayList.h>
#include <Tracking/ITrackedObject.h>
#include <Data/MaterialData.h>
#include <Math/Math.h>

namespace Dusk
{

namespace Data
{

using namespace Dusk::Collections;
using namespace Dusk::Math;

struct MeshData :
	public Tracking::ITrackedObject
{
public:

	virtual inline string GetClassName( void ) const { return "Mesh Data"; }

    string              Name;
	MaterialData        Material;

    ArrayList<vec3>     Verts,
						Norms;

	ArrayList<vec2>		TexCoords;

    ArrayList<int>      VertInds,
						NormInds,
						TexCoordInds;

}; // struct MeshData

} // namespace Data

} // namespace Dusk

#endif // DUSK_INTER_MESH_H
