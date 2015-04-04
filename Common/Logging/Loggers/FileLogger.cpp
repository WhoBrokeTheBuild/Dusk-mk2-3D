#include "FileLogger.h"

Dusk::Logging::FileLogger::
FileLogger( const string& filename )
{

}

void Dusk::Logging::FileLogger::
Log( const string& line )
{
    printf("%s\n", line.c_str());
}
