DuskLog("verbose", "Loading Shaders")

local sm = Dusk.Graphics.GetShaderManager()

sm:LoadProgram("flat", "Assets/Shaders/flat.fs.glsl", "Assets/Shaders/flat.vs.glsl")
