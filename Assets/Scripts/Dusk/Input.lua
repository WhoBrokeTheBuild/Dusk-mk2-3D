
Dusk.Input = { }

-- Dusk::Input::InputSystem

Dusk.Input.InputSystem = { }
Dusk.Input.InputSystem.methods = {

	MapKey = function( self )
	
		end

}

function Dusk.Input.InputSystem:dtor()
end

function Dusk.Input.InputSystem:ctor()
	local c = { }
	local c_mt = {
					__index = Dusk.Input.InputSystem.methods,
					__newindex = Dusk.Input.InputSystem.new_field,
					__gc = Dusk.Input.InputSystem.dtor,
					private = { }
				 }
	setmetatable(c, c_mt);

	rawset(rawget(getmetatable(c), "private"), "dusk_ptr", 0);

	return c
end

function Dusk.Input.InputSystem:new_field( key, value )
	dusk_log("error", "Dusk.Input.InputSystem does not support new fields");
end