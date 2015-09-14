DuskLog("verbose", "Applying mappings");

local inputSys = Dusk.Input.GetInputSystem()

inputSys:MapKey("jump", Dusk.Input.Keys.Space);
inputSys:MapKey("remap", Dusk.Input.Keys.Tab);

local remapping = false

function mappings_onMappedInputPress(inputId)
	if inputId == "jump" then
		DuskLog("info", "Jumping!")
	elseif inputId == "remap" then
		DuskLog("info", "Remapping")
		remapping = true
	end
end

function mappings_onKeyPress(key)
	if remapping and key ~= inputSys:GetMappedKey("remap") then
		inputSys:MapKey("jump", key)
	end
end

function mappings_onMouseButtonPress(button)
	if remapping and button ~= inputSys:GetMappedMouseButton("remap") then
		inputSys:MapMouseButton("jump", key)
	end
end

inputSys:AddEventListener(inputSys.EVT_MAPPED_INPUT_PRESS, "mappings_onMappedInputPress")
inputSys:AddEventListener(inputSys.EVT_KEY_PRESS,          "mappings_onKeyPress")
inputSys:AddEventListener(inputSys.EVT_MOUSE_BUTTON_PRESS, "mappings_onMouseButtonPress")
