#include "Program.h"

#include <Logging/Logging.h>
#include <Timing/TimeInfo.h>
#include <Graphics/GraphicsSystem.h>

#include <chrono>
#include <GLFW/glfw3.h>

using namespace Dusk;
using namespace Dusk::Logging;
using namespace Dusk::Timing;
using namespace Dusk::Graphics;

using namespace std::chrono;

void Program::
Run( void )
{
	if ( ! Init() )
	{
		DuskLog("error", "Program Init Failed");
		return;
	}
	DuskLog("info", "Program Init Succeeded");

	TimeInfo timeInfo;
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

		timeInfo.ElapsedSeconds = duration_cast<duration<double>>(elapsedTime).count();
		timeInfo.ElapsedMilliseconds = duration_cast<duration<double, std::milli>>(elapsedTime).count();
		timeInfo.TotalSeconds += timeInfo.ElapsedSeconds;
		timeInfo.TotalMilliseconds += timeInfo.ElapsedMilliseconds;

		timeInfo.Delta = timeInfo.ElapsedSeconds / m_UpdateInterval;

		secsSinceLastFrame += timeInfo.ElapsedSeconds;

		Update(timeInfo);

		if (secsSinceLastFrame >= m_UpdateInterval) {
			Render();
			++frameCount;
			m_CurrentFPS = (m_UpdateInterval / secsSinceLastFrame) * m_TargetFPS;

			secsSinceLastFrame = 0;
		}

		glfwPollEvents();
	}
}

bool Program::
Init( void )
{
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

	return true;
}

void Program::
Term( void )
{
	delete mp_GraphicsSystem;
	mp_GraphicsSystem = nullptr;
}

void Program::
Update( TimeInfo& timeInfo )
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
	return true;
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

void Program::
SetTargetFPS( double fps )
{
	m_TargetFPS = fps;
	m_UpdateInterval = (1.0 / m_TargetFPS);
}
