
if not Dusk then

Dusk = { }

end -- Dusk

if not Dusk.Graphics then

Dusk.Graphics = { }

end -- Dusk.Graphics

-- Dusk.Graphics.GraphicsContext

Dusk.Graphics.GraphicsContext = { }
Dusk.Graphics.GraphicsContext.methods = {
    Clear = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_graphics_context_clear(ptr);

        end,
    ResetDepthBuffer = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_graphics_context_reset_depth_buffer(ptr);

        end,
    SwapBuffers = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_graphics_context_swap_buffers(ptr);

        end
}

function Dusk.Graphics.GraphicsContext:new_field( key, value )
	DuskLog("error", "Dusk.Graphics.GraphicsContext does not support new fields");
end

function Dusk.Graphics.GraphicsContext:dtor()
end

function Dusk.Graphics.GraphicsContext:ctor()
	local c = { }
	local c_mt = {
					__index = Dusk.Graphics.GraphicsContext.methods,
					__newindex = Dusk.Graphics.GraphicsContext.new_field,
					__gc = Dusk.Graphics.GraphicsContext.dtor,
					private = { }
				 }
	setmetatable(c, c_mt);

	rawset(rawget(getmetatable(c), "private"), "dusk_ptr", 0);

	return c
end

setmetatable(Dusk.Graphics.GraphicsContext, {__call = Dusk.Graphics.GraphicsContext.ctor});