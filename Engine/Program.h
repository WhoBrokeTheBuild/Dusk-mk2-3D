#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

namespace Dusk
{

namespace Graphics
{
	class GraphicsSystem;
}

class Program
{
public:

    static inline Program* Inst()
    {
        static Program* pProgram = new Program();

        return pProgram;
    }

    virtual inline ~Program() { }

    void Run( void );

private:

    Program( void ) { };
    Program( Program const& );
    void operator=( Program const& );

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
