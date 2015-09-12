
if not Dusk then

Dusk = { }

end -- Dusk

Dusk.GetProgram = function() 

	local prog = Dusk.Program()
	rawset(rawget(getmetatable(win), "private"), "dusk_ptr", dusk_get_program());
	return prog;

end

Dusk.Program = class(Dusk.Events.IEventDispatcher)

function Dusk.Program:new_field( key, value )
	DuskLog("error", "Dusk.Program does not support new fields");
end

function Dusk.Program:dtor()
end

function Dusk.Program:ctor()
	local c = { }
	local c_mt = {
					__index = Dusk.Program.methods,
					__newindex = Dusk.Program.new_field,
					__gc = Dusk.Program.dtor,
					private = { }
				 }
	setmetatable(c, c_mt);

	rawset(rawget(getmetatable(c), "private"), "dusk_ptr", 0);

	return c
end

setmetatable(DuskProgram, {__call = Program.ctor});