#ifndef DUSK_LOGGING_FILE_LOGGER_H
#define DUSK_LOGGING_FILE_LOGGER_H

#include <Logging/Logger.h>

#include <string>

using std::string;

namespace Dusk
{

namespace Logging
{

class FileLogger :
    public Logger
{
public:

    FileLogger( const string& filename );
    virtual ~FileLogger( void ) { }

    virtual void Log( const string& line );

}; // class FileLogger

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_FILE_LOGGER_H
