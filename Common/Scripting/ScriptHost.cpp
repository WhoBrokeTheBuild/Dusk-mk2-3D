#include "ScriptHost.h"
#include <Utility/Benchmark.h>
#include <Logging/LoggingSystem.h>
#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Logging;
using namespace Dusk::Scripting;

bool ScriptHost::
Init( void )
{
	DuskBenchStart();

	mp_LuaState = luaL_newstate();

	if (!mp_LuaState)
	{
		DuskLog("error", "Failed to create Lua State");
		return false;
	}

	luaL_openlibs(mp_LuaState);

	ScriptingSystem::AddScriptHost(this);
	RunFile("Assets/Scripts/Dusk.luac");

	DuskBenchEnd("ScriptingSystem::Init");
	return true;
}

void ScriptHost::
Term( void )
{
	ScriptingSystem::RemoveScriptHost(this);

	lua_close(mp_LuaState);
}

bool ScriptHost::
RegisterFunction(const string& funcName, LuaCallback callback)
{
	if (funcName.empty())
	{
		DuskLog("error", "Cannot register a function with no name");
		return false;
	}

	if (callback == nullptr)
	{
		DuskLog("error", "Cannot register a fucntion with no callback");
	}

	lua_register(mp_LuaState, funcName.c_str(), callback);
	return true;
}

bool ScriptHost::
RunFile( const string& filename )
{
	int status = luaL_loadfile(mp_LuaState, filename.c_str());

	if (status)
		goto error;

	status = lua_pcall(mp_LuaState,
		0,
		LUA_MULTRET,
		0); // Set the error callback to 0, this means errors will be pushed onto the stack

	if (status)
		goto error;

	return true;

error:

	DuskExtLog("error", "%s", lua_tostring(mp_LuaState, -1)); // get error message from stack
	lua_pop(mp_LuaState, 1); // remove error message
	return false;
}
