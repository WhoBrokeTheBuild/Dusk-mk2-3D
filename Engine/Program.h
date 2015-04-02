#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <string>

using std::string;

/// Parent namespace for all of Dusk
namespace Dusk
{

class Program
{
public:

    static inline Program* Inst()
    {
        static Program* pProgram = new Program();

        return pProgram;
    }

    virtual inline ~Program() { }

    virtual inline string getClassName( void )
        const { return "Program"; }

    void Run( void );

private:

    Program() {};
    Program(Program const&);
    void operator=(Program const&);

    bool Init( void );
    void Term( void );

    void Update( void );
    void Render( void );

}; // class Program

} // namespace Dusk

#endif // DUSK_PROGRAM_H
