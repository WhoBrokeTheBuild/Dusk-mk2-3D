
if not Dusk then

Dusk = { }

end -- Dusk

if not Dusk.Graphics then

Dusk.Graphics = { }

end -- Dusk.Graphics

-- Dusk.Graphics.Window

Dusk.Graphics.Window = { }
Dusk.Graphics.Window.methods = {

	SetSize = function( self, width, height )

		local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
		return dusk_window_set_size(ptr, width, height);

		end,
    GetWidth = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_width(ptr);

        end,
    SetWidth = function( self, width )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_width(ptr, width);

        end,
    GetHeight = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_height(ptr);

        end,
    SetHeight = function( self, height )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_height(ptr, height);

        end,
    GetTitle = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_title(ptr);

        end,
    SetTitle = function( self, title )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_title(ptr, title);

        end
}

function Dusk.Graphics.Window:new_field( key, value )
	DuskLog("error", "Dusk.Graphics.Window does not support new fields");
end

function Dusk.Graphics.Window:dtor()
end

function Dusk.Graphics.Window:ctor()
	local c = { }
	local c_mt = {
					__index = Dusk.Graphics.Window.methods,
					__newindex = Dusk.Graphics.Window.new_field,
					__gc = Dusk.Graphics.Window.dtor,
					private = { }
				 }
	setmetatable(c, c_mt);

	rawset(rawget(getmetatable(c), "private"), "dusk_ptr", 0);

	return c
end

setmetatable(Dusk.Graphics.Window, {__call = Dusk.Graphics.Window.ctor});