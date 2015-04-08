#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Tracking/TrackedObject.h>

namespace Dusk
{

namespace Graphics
{
	class GraphicsSystem;
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

private:

    Program( void ) :
		mp_GraphicsSystem(nullptr)
	{ };

    Program( Program const& );
    void operator=( Program const& );

	virtual inline string ClassName( void ) const { return "Program"; }

    bool Init( void );
    void Term( void );

    void Update( void );
    void Render( void );

	bool InitGraphics( void );
	bool InitInput( void );
	bool InitAudio( void );

	Graphics::GraphicsSystem*		mp_GraphicsSystem;

}; // class Program

} // namespace Dusk

#endif // DUSK_PROGRAM_H
