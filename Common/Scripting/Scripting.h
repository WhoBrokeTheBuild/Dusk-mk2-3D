#pragma once

#ifndef DUSK_SCRIPTING_H
#define DUSK_SCRIPTING_H

#include <lua.hpp>

namespace Dusk
{

namespace Scripting
{

typedef int(*LuaCallback)(lua_State* pState);

} // namespace Scripting

} // namespace Dusk

#endif // DUSK_SCRIPTING_H