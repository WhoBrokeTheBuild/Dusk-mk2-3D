#include "OBJ.h"

#include <Utility/Benchmark.h>
#include <Logging/LoggingSystem.h>
#include <Math/Math.h>
#include <Data/ModelData.h>
#include <Data/MeshData.h>
#include <Data/MaterialData.h>
#include <External/tinyobj/tiny_obj_loader.h>

#include <fstream>
#include <sstream>

using namespace Dusk::Data;
using namespace Dusk::Logging;
using namespace Dusk::Math;

bool LoadMaterialFromMTL( const string& filename, Map<string, MaterialData*> materials )
{

	return true;
}

ModelData* Dusk::Data::
LoadModelDataFromOBJ( const string& filename )
{
	DuskBenchStart();

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::LoadObj(shapes, materials, filename.c_str());

	DuskBenchEnd("LoadModelDataFromOBJ");
	return nullptr;
}

bool Dusk::Data::
SaveModelDataToOBJ( ModelData* pModel, const string& filename )
{

	return true;
}
