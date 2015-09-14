#include "ScriptingSystem.h"

#include <Utility/Benchmark.h>
#include <Logging/LoggingSystem.h>
#include <Scripting/ScriptHost.h>

using namespace Dusk::Scripting;
using namespace Dusk::Logging;

Map<string, LuaCallback> Dusk::Scripting::ScriptingSystem::s_Functions;
ArrayList<ScriptHost*> Dusk::Scripting::ScriptingSystem::s_ScriptHosts;

void Dusk::Scripting::ScriptingSystem::AddScriptHost( ScriptHost* pHost )
{
	s_ScriptHosts.Add(pHost);

	for (auto it : s_Functions) {
		pHost->RegisterFunction(it.first, it.second);
	}
}

ScriptHost* Dusk::Scripting::ScriptingSystem::GetScriptHost( lua_State* L )
{
	for (auto it : s_ScriptHosts)
	{
		if (it->GetState() == L)
			return it;
	}

	return nullptr;
}

void Dusk::Scripting::ScriptingSystem::RemoveScriptHost( ScriptHost* pHost )
{
	s_ScriptHosts.RemoveAll(pHost);
}

bool Dusk::Scripting::ScriptingSystem::RegisterFunction( const string& funcName, LuaCallback callback )
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

	if (s_Functions.ContainsKey(funcName))
	{
		DuskLog("error", "Cannot register a function twice");
		return false;
	}

	s_Functions.Add(funcName, callback);

	for (auto it : s_ScriptHosts) {
		it->RegisterFunction(funcName, callback);
	}

	return true;
}
