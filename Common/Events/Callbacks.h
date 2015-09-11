#ifndef DUSK_CALLBACKS_H
#define DUSK_CALLBACKS_H

#include <Tracking/ITrackedObject.h>

namespace Dusk
{

namespace Events
{

template <typename ReturnType, typename Param = void>
class ICallback :
	public Tracking::ITrackedObject
{
public:

    virtual inline ~ICallback( void ) { }

    friend bool operator==( const ICallback<ReturnType, Param>& lhs, const ICallback<ReturnType, Param>& rhs ) { return lhs.IsEqualTo(rhs); }
    friend bool operator!=( const ICallback<ReturnType, Param>& lhs, const ICallback<ReturnType, Param>& rhs ) { return ! lhs.IsEqualTo(rhs); }

    virtual inline string GetClassName( void ) const { return "Callback"; }

    virtual ReturnType Invoke( Param param ) = 0;
    virtual ICallback* Clone( void )          = 0;
    virtual bool IsMethodOf( void* pObject ) = 0;

protected:

    inline virtual bool IsEqualTo( const ICallback<ReturnType, Param>& rhs ) const { return false; };

private:

}; // class Callback

template <typename ReturnType, typename Param = void>
class FunctionCallback :
    public ICallback<ReturnType, Param>
{
public:

    FunctionCallback( ReturnType(*pFunction)(Param)) :
        mp_Function(pFunction)
    { }

    inline virtual ReturnType Invoke( Param param ) { return (*mp_Function)(param); }
    inline virtual FunctionCallback* Clone ( void ) { return New FunctionCallback(mp_Function); }
    inline virtual bool IsMethodOf( void* pObject ) { return false; }

    virtual inline string GetClassName( void ) const { return "Function Callback"; }

protected:

    virtual bool IsEqualTo( const ICallback<ReturnType, Param>& rhs ) const
    {
        if ( const FunctionCallback<ReturnType, Param>* pConvert = dynamic_cast<const FunctionCallback<ReturnType, Param>*>(&rhs) )
        {
            return ( mp_Function == pConvert->mp_Function );
        }
        return false;
    }

private:

    ReturnType (*mp_Function)(Param);


}; // class FunctionCallback

template <typename ReturnType, typename Param = void, typename ObjectType = void, typename Method = void>
class MethodCallback :
    public ICallback<ReturnType, Param>
{
public:

    MethodCallback( void* pObject, Method method ) :
        m_Method(method),
        mp_Object(pObject)
    { }

    inline virtual ReturnType Invoke( Param param ) { return (static_cast<ObjectType*>(mp_Object)->*m_Method)(param); }
    inline virtual MethodCallback* Clone ( void ) { return New MethodCallback(mp_Object, m_Method); }
    inline virtual bool IsMethodOf( void* pObject ) { return mp_Object == pObject; }

    virtual inline string GetClassName( void ) const { return "Method Callback"; }

protected:

    virtual bool IsEqualTo( const ICallback<ReturnType, Param>& rhs ) const
    {
        if ( const MethodCallback<ReturnType, Param, ObjectType, Method>* pConvert = dynamic_cast<const MethodCallback<ReturnType, Param, ObjectType, Method>*>(&rhs) )
        {
            return ( m_Method == pConvert->m_Method && mp_Object == pConvert->mp_Object );
        }
        return false;
    }

private:

    Method      m_Method;
    void*       mp_Object;

}; // class MethodCallback

} // namespace Events

} // namespace Dusk

#endif // DUSK_CALLBACKS_H
