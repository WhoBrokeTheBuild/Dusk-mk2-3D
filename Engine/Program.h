#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Tracking/TrackedObject.h>

#include <Events/Event.h>

namespace Dusk
{

namespace Graphics
{
	class GraphicsSystem;
}

namespace Input
{
	class InputSystem;
}

namespace Timing
{
	class FrameTimeInfo;
}

class Program :
	public Tracking::TrackedObject
{
public:

	static Events::EventID 
		EVT_UPDATE,
		EVT_RENDER;

    static inline Program* Inst()
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

	Input::InputSystem* GetInputSystem( void );

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
	bool InitInput( void );
	bool InitAudio( void );

	bool		m_Running;

	double		m_TargetFPS,
				m_CurrentFPS,
				m_UpdateInterval;

	Graphics::GraphicsSystem*		mp_GraphicsSystem;

	Input::InputSystem*				mp_InputSystem;



	bool m_Remap;


}; // class Program

} // namespace Dusk

#endif // DUSK_PROGRAM_H
