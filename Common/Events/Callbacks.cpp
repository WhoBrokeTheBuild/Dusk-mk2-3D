#include "Callbacks.h"

#include <Events/Event.h>
#include <Scripting/ScriptHost.h>

using namespace Dusk::Events;
using namespace Dusk::Scripting;

LuaFucntionCallback::
LuaFucntionCallback( ScriptHost* pScriptHost, const string& callback ) :
	mp_ScriptHost(pScriptHost),
	m_Callback(callback)
{ }

void LuaFucntionCallback::
Invoke( const Event& event )
{
	lua_State* L = mp_ScriptHost->GetState();

	lua_getglobal(L, m_Callback.c_str());
	
	int argCount = event.PushDataToLua(L);
	
	lua_pcall(L, argCount, 0, 0);
}

bool LuaFucntionCallback::
IsEqualTo( const ICallback<void, const Event&>& rhs ) const
{
	if (const LuaFucntionCallback* pConvert = dynamic_cast<const LuaFucntionCallback*>(&rhs))
	{
		return (mp_ScriptHost == pConvert->mp_ScriptHost && m_Callback == pConvert->m_Callback);
	}
	return false;
}