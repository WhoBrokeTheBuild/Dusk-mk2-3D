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
    RemoveAllListeners();
}

void Dusk::Events::IEventDispatcher::AddEventListener( const EventID& eventId, const EventDelegate& functionDelegate )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        m_EventMap[eventId] = ArrayList<EventDelegate*>();

    unsigned int length = (unsigned int)m_EventMap[eventId].Size();

    for(unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == functionDelegate)
            return;
    }

    m_EventMap[eventId].Add(New EventDelegate(functionDelegate));
}

void Dusk::Events::IEventDispatcher::RemoveEventListener( const EventID& eventId, const EventDelegate& functionDelegate )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        return;

	unsigned int length = (unsigned int)m_EventMap[eventId].Size();

    for(unsigned int i = 0; i < length; ++i)
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

void Dusk::Events::IEventDispatcher::RemoveEventListener( const EventID& eventId, void (*function)(const Event&) )
{
    RemoveEventListener(eventId, EventDelegate(function));
}

void Dusk::Events::IEventDispatcher::AddEventListener( const EventID& eventId, void (*function)(const Event&) )
{
    AddEventListener(eventId, EventDelegate(function));
}

void Dusk::Events::IEventDispatcher::RemoveAllListeners( void )
{
    Map<EventID, ArrayList<EventDelegate*>>::Iterator mapIt;
    ArrayList<EventDelegate*>::Iterator listIt;

    unsigned int length;
    for (mapIt = m_EventMap.Begin(); mapIt != m_EventMap.End(); ++mapIt)
    {
        length = (unsigned int)mapIt->second.Size();
        for (unsigned int i = 0; i < length; ++i)
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

void Dusk::Events::IEventDispatcher::RemoveAllListeners( const EventID& eventId )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        return;

    unsigned int length = (unsigned int)m_EventMap[eventId].Size();
    for(unsigned int i = 0; i < length; ++i)
    {
        if ( m_EventMap[eventId][i] != nullptr )
        {
            delete m_EventMap[eventId][i];
            m_EventMap[eventId][i] = nullptr;
        }
    }

    m_EventMap.RemoveAt(eventId);

    m_Changed = true;
}

void Dusk::Events::IEventDispatcher::Dispatch( const Event& event )
{
    EventID id = event.GetID();

    if ( ! m_EventMap.ContainsKey(id))
        return;

    Event tmp = Event(event);

    tmp.setTarget(this);

    unsigned int length = (unsigned int)m_EventMap[id].Size();
    for(unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[id][i] != nullptr)
            m_EventMap[id][i]->Invoke(event);
    }
}

void Dusk::Events::IEventDispatcher::CleanMap( void )
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

