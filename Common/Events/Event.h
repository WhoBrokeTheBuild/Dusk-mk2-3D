#ifndef DUSK_EVENT_H
#define DUSK_EVENT_H

#include <Tracking/ITrackedObject.h>
#include <string>

using std::string;

namespace Dusk
{

namespace Events
{

typedef unsigned int EventID;

class IEventDispatcher;

class EventData :
	public Tracking::ITrackedObject
{
public:

    static const EventData BLANK_EVENT_DATA;

    inline EventData( void ) { }
    inline EventData( const EventData& rhs ) { }

    virtual inline ~EventData( void ) { }

    virtual inline string GetClassName( void ) const { return "Event Data"; }

    virtual EventData* Clone( void ) const { return New EventData(); };

}; // class EventData

class Event :
	public Tracking::ITrackedObject
{
public:

	Event( const EventID& eventId, const EventData& data = EventData::BLANK_EVENT_DATA ) :
        m_ID(eventId),
        mp_Data(nullptr),
        mp_EventTarget(nullptr)
    {
        mp_Data = data.Clone();
    }

	Event( const Event& rhs ) :
        m_ID(rhs.m_ID),
        mp_Data(nullptr),
        mp_EventTarget(nullptr)
    {
        mp_Data = (rhs.mp_Data == nullptr ? nullptr : rhs.mp_Data->Clone() );
    }

    virtual inline ~Event( void )
    {
        delete mp_Data;
    }

    virtual inline string GetClassName( void ) const { return "Event"; }

    inline EventID GetID( void ) const { return m_ID; }

    inline IEventDispatcher* GetTarget( void ) const { return mp_EventTarget; }
    template <typename T>
    inline T* GetTargetAs( void ) const { return dynamic_cast<T*>(mp_EventTarget); }

    inline void setTarget( IEventDispatcher* pTarget ) { mp_EventTarget = pTarget; }

    inline EventData* GetData( void ) const { return mp_Data; }
    template <typename T>
    inline T* GetDataAs( void ) const { return dynamic_cast<T*>(mp_Data); }

protected:

    EventID             m_ID;
    EventData*          mp_Data;
    IEventDispatcher*   mp_EventTarget;

}; // class Event

} // namespace Events

} // namespace Dusk

#endif // DUSK_EVENT_H
