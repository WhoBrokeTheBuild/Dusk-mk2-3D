#pragma once

#ifndef DUSK_SCRIPTING_SCRIPTING_SYSTEM_H
#define DUSK_SCRIPTING_SCRIPTING_SYSTEM_H

#include <Scripting/Scripting.h>
#include <Utility/Types.h>

namespace Dusk
{

namespace Scripting
{

typedef int(*LuaCallback)(lua_State* pState);

class ScriptingSystem
{
public:

	static bool Init( void );
	static void Term( void );

	static bool RegisterFunction( const string& funcName, LuaCallback callback );
	static bool RunFile( const string& filename );

private:

	static lua_State*		mp_LuaState;

};

} // namespace Scripting

} // namespace Dusk

#endif // DUSK_SCRIPTING_SCRIPTING_SYSTEM_H