#include "IEventDispatcher.h"

ArrayList<Dusk::Events::IEventDispatcher*> Dusk::Events::IEventDispatcher::s_Dispatchers = ArrayList<Dusk::Events::IEventDispatcher*>();

Dusk::Events::IEventDispatcher::IEventDispatcher( void )
	: m_EventMap(),
	  m_Changed(false)
{
    s_Dispatchers.Add(this);
}

Dusk::Events::IEventDispatcher::~IEventDispatcher( void )
{
    s_Dispatchers.Remove(this);
    removeAllListeners();
}

void Dusk::Events::IEventDispatcher::addEventListener( const EventID& eventId, const EventDelegate& functionDelegate )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        m_EventMap[eventId] = ArrayList<EventDelegate*>();

    int length = m_EventMap[eventId].Size();

    for(int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == functionDelegate)
            return;
    }

    m_EventMap[eventId].Add(new EventDelegate(functionDelegate));
}

void Dusk::Events::IEventDispatcher::removeEventListener( const EventID& eventId, const EventDelegate& functionDelegate )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        return;

    int length = m_EventMap[eventId].Size();

    for(int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == functionDelegate)
        {
            delete m_EventMap[eventId][i];
            m_EventMap[eventId][i] = nullptr;
            m_Changed = true;
            return;
        }
    }
}

void Dusk::Events::IEventDispatcher::removeEventListener( const EventID& eventId, void (*function)(const Event&) )
{
    removeEventListener(eventId, EventDelegate(function));
}

void Dusk::Events::IEventDispatcher::addEventListener( const EventID& eventId, void (*function)(const Event&) )
{
    addEventListener(eventId, EventDelegate(function));
}

void Dusk::Events::IEventDispatcher::removeAllListeners( void )
{
    Map<EventID, ArrayList<EventDelegate*>>::Iterator mapIt;
    ArrayList<EventDelegate*>::Iterator listIt;

    int length;
    for (mapIt = m_EventMap.Begin(); mapIt != m_EventMap.End(); ++mapIt)
    {
        length = mapIt->second.Size();
        for (int i = 0; i < length; ++i)
        {
            if (mapIt->second[i] != nullptr)
            {
                delete mapIt->second[i];
                mapIt->second[i] = nullptr;
            }
        }
    }

    m_EventMap.Clear();
}

void Dusk::Events::IEventDispatcher::removeAllListeners( const EventID& eventId )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        return;

    int length = m_EventMap[eventId].Size();
    for(int i = 0; i < length; ++i)
    {
        if ( m_EventMap[eventId][i] != nullptr )
        {
            delete m_EventMap[eventId][i];
            m_EventMap[eventId][i] = nullptr;
        }
    }

    m_EventMap.RemoveKey(eventId);

    m_Changed = true;
}

void Dusk::Events::IEventDispatcher::dispatch( const Event& event )
{
    EventID id = event.getID();

    if ( ! m_EventMap.ContainsKey(id))
        return;

    Event tmp = Event(event);

    tmp.setTarget(this);

    unsigned int length = m_EventMap[id].Size();
    for(unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[id][i] != nullptr)
            m_EventMap[id][i]->invoke(event);
    }
}

void Dusk::Events::IEventDispatcher::cleanMap( void )
{
    if ( ! m_Changed)
        return;

    bool needRepeat = true;
    Map<EventID, ArrayList<EventDelegate*>>::Iterator mapIt;
    ArrayList<EventDelegate*>* list;

    while (needRepeat)
    {
        needRepeat = false;
        for (mapIt = m_EventMap.Begin(); !needRepeat && mapIt != m_EventMap.End(); ++mapIt)
        {
            list = &mapIt->second;
            for (unsigned int i = 0; !needRepeat && i < list->Size(); ++i)
            {
                if (list->At(i) == nullptr)
                {
                    list->RemoveAt(i);
                    needRepeat = true;
                    break;
                }
            }
        }
    }

    m_Changed = false;
}

