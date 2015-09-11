#ifndef DUSK_EVENT_DISPATCHER_H
#define DUSK_EVENT_DISPATCHER_H

#include <Events/Event.h>
#include <Events/Delegate.h>

#include <Collections/ArrayList.h>
#include <Collections/Map.h>

using namespace Dusk::Collections;

namespace Dusk
{

namespace Events
{

typedef Delegate<void, const Event&> EventDelegate;

class IEventDispatcher
{
public:

    IEventDispatcher( void );
    virtual ~IEventDispatcher( void );

    void AddEventListener   ( const EventID& eventId, const EventDelegate& funcDelegate );
    void RemoveEventListener( const EventID& eventId, const EventDelegate& funcDelegate );

    void AddEventListener   ( const EventID& eventId, void (*pFunction)(const Event&) );
    void RemoveEventListener( const EventID& eventId, void (*pFunction)(const Event&) );

    template <typename ObjectType, typename Method>
    void AddEventListener   ( const EventID& eventId, ObjectType* pObject, Method method );
    template <typename ObjectType, typename Method>
    void RemoveEventListener( const EventID& eventId, ObjectType* pObject, Method method );

    template <typename ObjectType>
    void RemoveAllMethods( ObjectType* pObject );

    void RemoveAllListeners( void );
    void RemoveAllListeners( const EventID& eventId );

    void Dispatch( const Event& event );

    static void CleanEvents( void )
    {
        unsigned int length = (unsigned int)s_Dispatchers.Size();
        for (unsigned int i = 0; i < length; ++i)
            s_Dispatchers[i]->CleanMap();
    }

private:

    void CleanMap( void );
    virtual inline void NoOp( void ) { }

    static ArrayList<IEventDispatcher*>         s_Dispatchers;
    Map<EventID, ArrayList<EventDelegate*>>     m_EventMap;

    bool    m_Changed;


}; // class EventDispatcher

template <typename ObjectType, typename Method>
void IEventDispatcher::AddEventListener( const EventID& eventId, ObjectType* object, Method method )
{
    AddEventListener(eventId, EventDelegate(object, method));
}

template <typename ObjectType, typename Method>
void IEventDispatcher::RemoveEventListener( const EventID& eventId, ObjectType* object, Method method )
{
    RemoveEventListener(eventId, EventDelegate(object, method));
}

template <typename ObjectType>
void IEventDispatcher::RemoveAllMethods( ObjectType* object )
{
    bool needRepeat = true;
    Map<EventID, ArrayList<EventDelegate*>>::Iterator mapIt;
    ArrayList<EventDelegate*>::Iterator listIt;

    while(needRepeat)
    {
        needRepeat = false;
        for(mapIt = m_EventMap.Begin(); !needRepeat && mapIt != m_EventMap.End(); ++mapIt)
        {
            for(listIt = mapIt->second.Begin(); !needRepeat && listIt != mapIt->second.End(); ++listIt)
            {
                if ( *listIt == nullptr )
                    continue;

                if ( (*listIt)->isMethodOf(object) )
                {
                    (*listIt) = nullptr;
                    needRepeat = true;
                    break;
                }
            }
        }
    }
}


} // namespace Events

} // namespace Dusk

#endif // DUSK_EVENT_DISPATCHER_H
