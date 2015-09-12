
if not Dusk then

Dusk = { }

end -- Dusk

if not Dusk.Input then

Dusk.Input = { }

end -- Dusk.Input

Dusk.Input.MapKey = function(inputId, key)

	dusk_input_system_map_key(inputId, key);

end

Dusk.Input.MapMouseButton = function(inputId, button)

	dusk_input_system_map_mouse_button(inputId, button);

end

Dusk.Input.GetMappedKey = function(inputId)

	return dusk_input_system_get_mapped_key(inputId);

end

Dusk.Input.GetMappedMouseButton = function(inputId)

	return dusk_input_system_get_mapped_mouse_button(inputId);

end