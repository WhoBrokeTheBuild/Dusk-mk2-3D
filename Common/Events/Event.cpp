#include "Event.h"

using namespace Dusk::Events;

const EventData EventData::BLANK_EVENT_DATA = EventData();

int Event::
PushDataToLua( lua_State* L ) const
{
	return mp_Data->PushDataToLua(L);
}

int EventData::
PushDataToLua( lua_State* L ) const
{
	return 0;
}
