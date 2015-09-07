#include "Program.h"

#include <Utility/Benchmark.h>
#include <Logging/Logging.h>
#include <Timing/FrameTimeInfo.h>
#include <Graphics/GraphicsSystem.h>
#include <Input/InputSystem.h>

#include <chrono>
#include <GLFW/glfw3.h>

using namespace Dusk;
using namespace Dusk::Logging;
using namespace Dusk::Events;
using namespace Dusk::Timing;
using namespace Dusk::Input;
using namespace Dusk::Graphics;

using namespace std::chrono;

EventID Program::EVT_UPDATE	= 1;
EventID Program::EVT_RENDER = 2;

bool Program::
Init( void )
{
	DuskBenchStart();

	if ( ! InitGraphics() )
	{
		DuskLog("error", "Graphics Init Failed");
		return false;
	}
	DuskLog("info", "Graphics Init Succeeded");

	if ( ! InitAudio() )
	{
		DuskLog("error", "Audio Init Failed");
		return false;
	}
	DuskLog("info", "Audio Init Succeeded");

	if ( ! InitInput() )
	{
		DuskLog("error", "Input Init Failed");
		return false;
	}
	DuskLog("info", "Input Init Succeeded");

	SetTargetFPS(60.0);


	GetInputSystem()->MapKey("jump", Key::KEY_SPACE);
	GetInputSystem()->MapKey("remap", Key::KEY_ENTER);

	GetInputSystem()->addEventListener(InputSystem::EVT_MAPPED_INPUT_PRESS, this, &Program::MappedInputPressCallback);
	GetInputSystem()->addEventListener(InputSystem::EVT_KEY_PRESS, this, &Program::KeyPressCallback);


	DuskBenchEnd("Program::Init");
	return true;
}

void Program::
Term( void )
{
	GetInputSystem()->removeEventListener(InputSystem::EVT_KEY_PRESS, this, &Program::KeyPressCallback);
	GetInputSystem()->removeEventListener(InputSystem::EVT_MAPPED_INPUT_PRESS, this, &Program::MappedInputPressCallback);

	delete mp_GraphicsSystem;
	mp_GraphicsSystem = nullptr;

	delete mp_InputSystem;
	mp_InputSystem = nullptr;
}

void Program::
Run(void)
{
	if ( ! Init() )
	{
		DuskLog("error", "Program Init Failed");
		return;
	}
	DuskLog("info", "Program Init Succeeded");

	FrameTimeInfo timeInfo;
	unsigned long long frameCount = 0;

	auto startTime = high_resolution_clock::now();
	auto lastTime = startTime;

	double secsSinceLastFrame = 0;

	m_Running = true;
	while ( m_Running )
	{
		auto time = high_resolution_clock::now();
		auto elapsedTime = time - lastTime;
		lastTime = time;

		timeInfo.TargetFPS = m_TargetFPS;
		timeInfo.ElapsedSeconds = duration_cast<duration<double>>(elapsedTime).count();
		timeInfo.ElapsedMilliseconds = duration_cast<duration<double, std::milli>>(elapsedTime).count();
		timeInfo.TotalSeconds += timeInfo.ElapsedSeconds;
		timeInfo.TotalMilliseconds += timeInfo.ElapsedMilliseconds;

		timeInfo.Delta = timeInfo.ElapsedSeconds / m_UpdateInterval;

		secsSinceLastFrame += timeInfo.ElapsedSeconds;

		Update(timeInfo);

		if ( secsSinceLastFrame >= m_UpdateInterval )
		{
			Render();
			++frameCount;
			m_CurrentFPS = (m_UpdateInterval / secsSinceLastFrame) * m_TargetFPS;

			secsSinceLastFrame = 0;
		}

		glfwPollEvents();
	}
}

void Program::
Update( FrameTimeInfo& timeInfo )
{
}

void Program::
Render( void )
{

}

bool Program::
InitGraphics( void )
{
	delete mp_GraphicsSystem;
	mp_GraphicsSystem = New Dusk::Graphics::GraphicsSystem();

	return mp_GraphicsSystem->Init();
}

bool Program::
InitInput( void )
{
	delete mp_InputSystem;
	mp_InputSystem = New Dusk::Input::InputSystem();

	return mp_InputSystem->Init();
}

bool Program::
InitAudio( void )
{
	return true;
}

GraphicsSystem* Program::
GetGraphicsSystem(void)
{
	return mp_GraphicsSystem;
}

InputSystem* Program::
GetInputSystem(void)
{
	return mp_InputSystem;
}

void Program::
SetTargetFPS( double fps )
{
	m_TargetFPS = fps;
	m_UpdateInterval = (1.0 / m_TargetFPS);
}

void Dusk::Program::MappedInputPressCallback(const Event& event)
{
	const MappedInputEventData* pData = event.GetDataAs<MappedInputEventData>();
	MappedInputID input = pData->GetMappedInput();

	if (input == "jump")
	{
		DuskLog("debug", "Jumping!");
	}
	else if (input == "remap") 
	{
		DuskLog("debug", "Remapping jump");
		m_Remap = true;
	}
}

void Dusk::Program::KeyPressCallback(const Events::Event& event)
{
	const KeyEventData* pData = event.GetDataAs<KeyEventData>();
	Key key = pData->GetKey();

	if (m_Remap && key != Key::KEY_ENTER) {
		GetInputSystem()->MapKey("jump", key);
		DuskExtLog("debug", "Remapped jump to %d", key);
		m_Remap = false;
	}
}
