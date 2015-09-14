#pragma once

#ifndef DUSK_SCRIPTING_SCRIPTING_SYSTEM_H
#define DUSK_SCRIPTING_SCRIPTING_SYSTEM_H

#include <Scripting/Scripting.h>
#include <Utility/Types.h>
#include <Collections/Map.h>
#include <Collections/ArrayList.h>

using namespace Dusk::Collections;

namespace Dusk
{

namespace Scripting
{

class ScriptHost;

class ScriptingSystem
{
public:

	static void AddScriptHost( ScriptHost* pHost );
	static ScriptHost* GetScriptHost( lua_State* L );

	static void RemoveScriptHost( ScriptHost* pHost );
	static bool RegisterFunction( const string& funcName, LuaCallback callback );

private:

	static Map<string, LuaCallback>  s_Functions;
	static ArrayList<ScriptHost*>    s_ScriptHosts;

};

} // namespace Scripting

} // namespace Dusk

#endif // DUSK_SCRIPTING_SCRIPTING_SYSTEM_H