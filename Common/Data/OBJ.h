#pragma once

#ifndef DUSK_DATA_OBJ_H
#define DUSK_DATA_OBJ_H

#include <Utility/Types.h>

namespace Dusk
{

namespace Data
{

struct ModelData;

ModelData* LoadModelDataFromOBJ( const string& filename );
bool SaveModelDataToOBJ( ModelData* pModel, const string& filename );

} // namespace Data

} // namespace Dusk

#endif // DUSK_DATA_OBJ_H