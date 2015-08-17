#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Tracking/TrackedObject.h>

namespace Dusk
{

namespace Graphics
{
	class GraphicsSystem;
}

namespace Timing
{
	class TimeInfo;
}

class Program :
	public Tracking::TrackedObject
{
public:

    static inline Program* Inst()
    {
        static Program* pProgram = New Program();

        return pProgram;
    }

	virtual inline ~Program() { Term(); }

    void Run( void );

	inline void Exit( void ) { m_Running = false; }
	
	double GetCurrentFPS( void ) const { return m_CurrentFPS; }

	double GetTargetFPS( void ) const { return m_TargetFPS; }
	void   SetTargetFPS( double fps );

	Graphics::GraphicsSystem* GetGraphicsSystem( void );

private:

    Program( void ) :
		m_Running(),
		m_TargetFPS(),
		m_CurrentFPS(),
		m_UpdateInterval(),
		mp_GraphicsSystem(nullptr)
	{ };

    Program( Program const& );
    void operator=( Program const& );

	virtual inline string GetClassName( void ) const { return "Program"; }

    bool Init( void );
    void Term( void );

    void Update( Timing::TimeInfo& timeInfo );
    void Render( void );

	bool InitGraphics( void );
	bool InitInput( void );
	bool InitAudio( void );

	bool		m_Running;

	double		m_TargetFPS,
				m_CurrentFPS,
				m_UpdateInterval;

	Graphics::GraphicsSystem*		mp_GraphicsSystem;

}; // class Program

} // namespace Dusk

#endif // DUSK_PROGRAM_H
