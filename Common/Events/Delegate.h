#ifndef DUSK_DELEGATE_H
#define DUSK_DELEGATE_H

#include <Tracking/ITrackedObject.h>
#include <Events/Callbacks.h>

namespace Dusk
{

namespace Scripting 
{
	class ScriptHost;
}

namespace Events
{

template <typename ReturnType, typename Param = void>
class Delegate :
	public Tracking::ITrackedObject
{
public:

    Delegate( ReturnType (*pFunction)(Param) )
    {
        mp_Callback = New FunctionCallback<ReturnType, Param>(pFunction);
    }

    template <typename ObjectType, typename Method>
    Delegate( ObjectType* pObject, Method method )
    {
		mp_Callback = New MethodCallback<ReturnType, Param, ObjectType, Method>(pObject, method);
    }

    Delegate( Scripting::ScriptHost* pScriptHost, const string& callback )
    {
        mp_Callback = New LuaFucntionCallback(pScriptHost, callback);
    }

    Delegate( const Delegate<ReturnType, Param>& rhs )
    {
        mp_Callback = rhs.mp_Callback->Clone();
    }

    virtual inline ~Delegate( void ) { delete mp_Callback; mp_Callback = nullptr; }

    virtual inline string GetClassName( void ) const { return "Delegate"; }

    inline ReturnType Invoke( Param param ) { return mp_Callback->Invoke(param); }
    inline ReturnType operator()( Param param ) { return Invoke(param); }

    inline bool IsMethodOf( void* pObject )
    {
        if (!mp_Callback) return false;
        return mp_Callback->IsMethodOf(pObject);
    }

    bool operator==( const Delegate<ReturnType, Param>& rhs )
    {
        if (!mp_Callback || !rhs.mp_Callback)
            return false;

        if (mp_Callback == rhs.mp_Callback)
            return true;

        return ( *(mp_Callback) == *(rhs.mp_Callback) );
    }

    bool operator!=( const Delegate<ReturnType, Param>& rhs ) { return !((*this) == rhs); }

private:

    ICallback<ReturnType, Param>*    mp_Callback;


}; // class Delegate

} // namespace Events

} // namespace Dusk

#endif // DUSK_DELEGATE_H
