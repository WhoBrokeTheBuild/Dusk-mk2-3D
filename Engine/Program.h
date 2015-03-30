#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <string>

using std::string;

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

    void run( void );

private:

    Program() {};
    Program(Program const&);
    void operator=(Program const&);

    bool init( void );
    void term( void );

    void update( void );
    void render( void );

}; // class Program

} // namespace Dusk

#endif // DUSK_PROGRAM_H
