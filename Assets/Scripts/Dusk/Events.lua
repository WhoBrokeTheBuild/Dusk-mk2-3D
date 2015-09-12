
if not Dusk then

Dusk = { }

end -- Dusk

if not Dusk.Events then

Dusk.Events = { }

end -- Dusk.Events

Dusk.Events.IEventDispatcher = { }
Dusk.Events.IEventDispatcher.methods = {
	AddEventListener = function(self, func) 
	
		dusk_ievent_dispatcher_add_event_listener();
	
		end,
	RemoveEventListener = function(self, func)
	
		dusk_ievent_dispatcher_remove_event_listener();
	
		end
}