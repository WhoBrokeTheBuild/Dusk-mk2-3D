#pragma once

#ifndef DUSK_SCRIPTING_SCRIPT_HOST_H
#define DUSK_SCRIPTING_SCRIPT_HOST_H

#include <Scripting/Scripting.h>
#include <Utility/Types.h>
#include <Tracking/ITrackedObject.h>

namespace Dusk
{

namespace Scripting
{

class ScriptHost :
	public Tracking::ITrackedObject
{
public:

	ScriptHost( void ) :
		mp_LuaState(nullptr)
	{ }

	~ScriptHost( void ) { Term(); }

	virtual inline string GetClassName( void ) const { return "Script Host"; }

	bool Init( void );
	void Term( void );

	bool RunFile( const string& filename );
	bool RegisterFunction( const string& funcName, LuaCallback callback );

	inline lua_State* GetState( void ) { return mp_LuaState; }

private:

	lua_State*		mp_LuaState;

}; // class ScriptHost

} // namespace Scripting

} // namespace Dusk

#endif // DUSK_SCRIPTING_SCRIPT_HOST_H