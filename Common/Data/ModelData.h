#ifndef DUSK_INTER_MODEL_H
#define DUSK_INTER_MODEL_H

#include <Tracking/ITrackedObject.h>
#include <Collections/ArrayList.h>
#include <Data/MeshData.h>

namespace Dusk
{

namespace Data
{

using namespace Dusk::Collections;

struct ModelData :
	public Tracking::ITrackedObject
{
public:

    virtual inline string GetClassName( void ) const { return "Model Data"; }

    string               Name;
    ArrayList<MeshData>  Meshes;

}; // struct ModelData

} // namespace Data

} // namespace Dusk

#endif // DUSK_INTER_MODEL_H
