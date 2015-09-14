#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Events/IEventDispatcher.h>
#include <Tracking/ITrackedObject.h>

#include <Scripting/Scripting.h>
#include <Events/Event.h>

namespace Dusk
{

namespace Graphics
{
	class GraphicsSystem;
	class GraphicsContext;
}

namespace Input
{
	class InputSystem;
}

namespace Scripting
{
	class ScriptingSystem;
	class ScriptHost;
}

namespace Timing
{
	class FrameTimeInfo;
}

class Program :
	public Events::IEventDispatcher,
	public Tracking::ITrackedObject
{
public:

	static Events::EventID 
		EVT_UPDATE,
		EVT_RENDER;

    static inline Program* Inst( void )
    {
        static Program* pProgram = New Program();

        return pProgram;
    }

	virtual inline ~Program( void ) { Term(); }

    void Run( void );

	inline void Exit( void ) { m_Running = false; }
	
	double GetCurrentFPS( void ) const { return m_CurrentFPS; }

	double GetTargetFPS( void ) const { return m_TargetFPS; }
	void   SetTargetFPS( double fps );

	Graphics::GraphicsSystem* GetGraphicsSystem( void );
	Input::InputSystem*		  GetInputSystem( void );

	static void InitScripting( void );
	static int Script_GetProgram( lua_State* L );
	static int Script_GetGraphicsSystem( lua_State* L );
	static int Script_GetInputSystem( lua_State* L );
	static int Script_AddEventListener( lua_State* L );

	// Temporary

	void MappedInputPressCallback(const Events::Event& event);
	void KeyPressCallback(const Events::Event& event);
	void MouseButtonPressCallback(const Events::Event& event);

private:

    Program( void ) :
		m_Running(),
		m_TargetFPS(),
		m_CurrentFPS(),
		m_UpdateInterval(),
		mp_GraphicsSystem(nullptr),
		mp_InputSystem(nullptr),
		mp_ScriptHost(nullptr),

		m_Remap(false)
	{ };

    Program( Program const& );
    void operator=( Program const& );

	virtual inline string GetClassName( void ) const { return "Program"; }

    bool Init( void );
    void Term( void );

    void Update( Timing::FrameTimeInfo& timeInfo );
    void Render( void );

	bool InitGraphics( void );
	void TermGraphics( void );

	bool InitInput( void );
	void TermInput( void );

	bool InitAudio( void );
	void TermAudio( void );

	bool		m_Running;

	double		m_TargetFPS,
				m_CurrentFPS,
				m_UpdateInterval;

	Graphics::GraphicsSystem*		mp_GraphicsSystem;
	Input::InputSystem*				mp_InputSystem;

	Scripting::ScriptHost*		mp_ScriptHost;

	// Temporary

	bool m_Remap;

}; // class Program

class UpdateEventData :
	public Events::EventData
{
public:

	UpdateEventData( Timing::FrameTimeInfo* timeInfo ) :
		mp_TimeInfo(timeInfo)
	{ }

	virtual inline string GetClassName( void ) const { return "Update Event Data"; }

	virtual inline EventData* Clone(void) const { return New UpdateEventData(mp_TimeInfo); }

	Timing::FrameTimeInfo* GetTimeInfo( void );

	virtual int PushDataToLua( lua_State* L ) const;

private:

	Timing::FrameTimeInfo*	mp_TimeInfo;

};

class RenderEventData :
	public Events::EventData
{
public:

	RenderEventData(Graphics::GraphicsContext* context) :
		mp_GraphicsContext(context)
	{ }

	virtual inline string GetClassName(void) const { return "Render Event Data"; }

	virtual inline EventData* Clone(void) const { return New RenderEventData(mp_GraphicsContext); }

	Graphics::GraphicsContext* GetGraphicsContext( void );

	virtual int PushDataToLua( lua_State* L ) const;

private:

	Graphics::GraphicsContext*	mp_GraphicsContext;

};

} // namespace Dusk

#endif // DUSK_PROGRAM_H
