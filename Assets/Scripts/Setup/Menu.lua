--[[ DuskLog("verbose", "Starting Menu");

local inputSys = Dusk.Input.GetInputSystem()
local win = Dusk.Graphics.GetWindow();

inputSys:MapKey("menu_up", Dusk.Input.Keys.Up);
inputSys:MapKey("menu_down", Dusk.Input.Keys.Down);
inputSys:MapKey("menu_select", Dusk.Input.Keys.Enter);
inputSys:MapKey("menu_back", Dusk.Input.Keys.Backspace);

local mainMenu = { "Start Game", "Options", "Quit Game" }
local optionsMenu = { "Volume", "Fullscreen", "Resolution", "Back" }
local resolutionMenu = { "640x480", "800x600", "1024x768", "1600x900", "1920x1080" }
local resolutions = { { ['w'] = 640, ['h'] = 480 },
                      { ['w'] = 800, ['h'] = 600 },
                      { ['w'] = 1024, ['h'] = 768 },
                      { ['w'] = 1600, ['h'] = 900 },
                      { ['w'] = 1920, ['h'] = 1080 } }

local menuIndex = 1
local currentMenu = mainMenu
local menuSize = 3

function showMenu()
    print('----------------------')
    for key, value in pairs(currentMenu) do
        if key == menuIndex then
            print("[x] " .. value)
        else
            print("[ ] " .. value)
        end
    end
end

function menuSelect()
    local menuItem = currentMenu[menuIndex]
    if currentMenu == mainMenu then
        if menuItem == "Start Game" then

        elseif menuItem == "Options" then
            currentMenu = optionsMenu
            menuSize = 4
            menuIndex = 1
            showMenu()
        elseif menuItem == "Quit Game" then
            Dusk.GetProgram():Exit()
        end
    elseif currentMenu == optionsMenu then
        if menuItem == "Resolution" then
            currentMenu = resolutionMenu
            menuSize = 5
            menuIndex = 1
            showMenu()
        elseif menuItem == "Back" then
            menuBack()
        end
    elseif currentMenu == resolutionMenu then
        local res = resolutions[menuIndex]
        win:SetSize(res.w, res.h)
        menuBack()
    end
end

function menuBack()
    if currentMenu == mainMenu then

    elseif currentMenu == optionsMenu then
        currentMenu = mainMenu
        menuSize = 3
        menuIndex = 1
        showMenu()
    elseif currentMenu == resolutionMenu then
        currentMenu = optionsMenu
        menuSize = 4
        menuIndex = 1
        showMenu()
    end
end

function menu_onMappedInputPress(inputId)
    if inputId == "menu_up" then
        menuIndex = menuIndex - 1
        if menuIndex < 1 then
            menuIndex = menuSize
        end
        showMenu()
    elseif inputId == "menu_down" then
        menuIndex = menuIndex + 1
        if menuIndex > menuSize then
            menuIndex = 1
        end
        showMenu()
    elseif inputId == "menu_select" then
        menuSelect()
    elseif inputId == "menu_back" then
        menuBack()
    end
end

inputSys:AddEventListener(inputSys.EVT_MAPPED_INPUT_PRESS, "menu_onMappedInputPress")

showMenu()
--]]