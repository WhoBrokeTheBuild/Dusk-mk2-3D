DuskLog("verbose", "Applying mappings");

local inputSys = Dusk.Input.GetInputSystem()

inputSys:MapKey("jump", Dusk.Input.Keys.Space);
inputSys:MapKey("remap", Dusk.Input.Keys.Enter);

local remapping = false

function onMappedInputPress(inputId)
	if inputId == "jump" then
		DuskLog("info", "Jumping!")
	elseif inputId == "remap" then
		DuskLog("info", "Remapping")
		remapping = true
	end
end

function onKeyPress(key)
	if remapping and key ~= inputSys:GetMappedKey("remap") then
		inputSys:MapKey("jump", key)
	end
end

function onMouseButtonPress(button)
	if remapping and button ~= inputSys:GetMappedMouseButton("remap") then
		inputSys:MapMouseButton("jump", key)
	end
end

inputSys:AddEventListener(inputSys.EVT_MAPPED_INPUT_PRESS, "onMappedInputPress")
inputSys:AddEventListener(inputSys.EVT_KEY_PRESS,          "onKeyPress")
inputSys:AddEventListener(inputSys.EVT_MOUSE_BUTTON_PRESS, "onMouseButtonPress")
