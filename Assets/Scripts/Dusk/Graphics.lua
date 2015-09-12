
if not Dusk then

Dusk = { }

end -- Dusk

if not Dusk.Graphics then

Dusk.Graphics = { }

end -- Dusk.Graphics

Dusk.Graphics.GetWindow = function()

	local win = Dusk.Graphics.Window();
	rawset(rawget(getmetatable(win), "private"), "dusk_ptr", dusk_graphics_system_get_window());

	return win;

end -- GetWindow

Dusk.Graphics.GetContext = function() 

	local ctx = Dusk.Graphics.GraphicsContext();
	rawset(rawget(getmetatable(ctx), "private"), "dusk_ptr", dusk_graphics_system_get_graphics_context());

end