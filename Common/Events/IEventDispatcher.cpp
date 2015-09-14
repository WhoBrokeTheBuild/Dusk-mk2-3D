#include "IEventDispatcher.h"

#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Events;
using namespace Dusk::Scripting;

ArrayList<IEventDispatcher*> IEventDispatcher::s_Dispatchers = ArrayList<IEventDispatcher*>();

IEventDispatcher::
IEventDispatcher( void )
	: m_EventMap(),
	  m_Changed(false)
{
    s_Dispatchers.Add(this);
}

IEventDispatcher::
~IEventDispatcher( void )
{
    s_Dispatchers.RemoveAll(this);
    RemoveAllListeners();
}

void IEventDispatcher::
AddEventListener( const EventID& eventId, const EventDelegate& functionDelegate )
{
    if ( ! m_EventMap.ContainsKey(eventId))
		m_EventMap.Add(eventId, ArrayList<EventDelegate*>());

    unsigned int length = (unsigned int)m_EventMap[eventId].GetSize();

    for(unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == functionDelegate)
            return;
    }

    m_EventMap[eventId].Add(New EventDelegate(functionDelegate));
}

void IEventDispatcher::
RemoveEventListener( const EventID& eventId, const EventDelegate& functionDelegate )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        return;

	unsigned int length = (unsigned int)m_EventMap[eventId].GetSize();

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

void IEventDispatcher::
RemoveEventListener( const EventID& eventId, void (*function)(const Event&) )
{
    RemoveEventListener(eventId, EventDelegate(function));
}

void IEventDispatcher::
AddEventListener( const EventID& eventId, void (*function)(const Event&) )
{
    AddEventListener(eventId, EventDelegate(function));
}

void IEventDispatcher::
RemoveAllListeners( void )
{
    Map<EventID, ArrayList<EventDelegate*>>::Iterator mapIt;
    ArrayList<EventDelegate*>::Iterator listIt;

    unsigned int length;
    for (mapIt = m_EventMap.Begin(); mapIt != m_EventMap.End(); ++mapIt)
    {
        length = (unsigned int)mapIt->second.GetSize();
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

void IEventDispatcher::
RemoveAllListeners( const EventID& eventId )
{
    if ( ! m_EventMap.ContainsKey(eventId))
        return;

    unsigned int length = (unsigned int)m_EventMap[eventId].GetSize();
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

void IEventDispatcher::
Dispatch( const Event& event )
{
    EventID id = event.GetID();

    if ( ! m_EventMap.ContainsKey(id))
        return;

    Event tmp = Event(event);

    tmp.setTarget(this);

    unsigned int length = (unsigned int)m_EventMap[id].GetSize();
    for(unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[id][i] != nullptr)
            m_EventMap[id][i]->Invoke(event);
    }
}

void IEventDispatcher::
CleanMap(void)
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
            for (unsigned int i = 0; !needRepeat && i < list->GetSize(); ++i)
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

void IEventDispatcher::
InitScripting( void )
{
	ScriptingSystem::RegisterFunction("dusk_ievent_dispatcher_add_event_listener",    &IEventDispatcher::Script_AddEventListener);
	ScriptingSystem::RegisterFunction("dusk_ievent_dispatcher_remove_event_listener", &IEventDispatcher::Script_RemoveEventListener);
}

int IEventDispatcher::
Script_AddEventListener( lua_State* L )
{
	IEventDispatcher* pEventDispatcher = (IEventDispatcher*)lua_tointeger(L, 1);

	EventID eventId = (EventID)lua_tointeger(L, 2);
	string callback = lua_tostring(L, 3);

	EventDelegate *pDelegate = New EventDelegate(ScriptingSystem::GetScriptHost(L), callback);

	if (!pEventDispatcher->m_EventMap.ContainsKey(eventId))
		pEventDispatcher->m_EventMap.Add(eventId, ArrayList<EventDelegate*>());

	unsigned int length = (unsigned int)pEventDispatcher->m_EventMap[eventId].GetSize();

	for (unsigned int i = 0; i < length; ++i)
	{
		if (pEventDispatcher->m_EventMap[eventId][i] == nullptr)
			continue;
		if (*(pEventDispatcher->m_EventMap[eventId][i]) == *pDelegate)
			return 0;
	}

	pEventDispatcher->m_EventMap[eventId].Add(pDelegate);

	return 0;
}

int IEventDispatcher::
Script_RemoveEventListener( lua_State* L )
{
	IEventDispatcher* pEventDispatcher = (IEventDispatcher*)lua_tointeger(L, 1);

	EventID eventId = (EventID)lua_tointeger(L, 2);
	string callback = lua_tostring(L, 3);

	EventDelegate delegate = EventDelegate(ScriptingSystem::GetScriptHost(L), callback);

	if (!pEventDispatcher->m_EventMap.ContainsKey(eventId))
		return 0;

	unsigned int length = (unsigned int)pEventDispatcher->m_EventMap[eventId].GetSize();

	for (unsigned int i = 0; i < length; ++i)
	{
		if (pEventDispatcher->m_EventMap[eventId][i] == nullptr)
			continue;
		if (*(pEventDispatcher->m_EventMap[eventId][i]) == delegate)
		{
			delete pEventDispatcher->m_EventMap[eventId][i];
			pEventDispatcher->m_EventMap[eventId][i] = nullptr;
			pEventDispatcher->m_Changed = true;
			return 0;
		}
	}

	return 0;
}

