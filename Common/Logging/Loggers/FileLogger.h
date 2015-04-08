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

	virtual inline string ClassName( void ) const { return "File Logger"; }

    virtual void Log( const string& line,
                      const LogForegroundColor& fgColor,
                      const LogBackgroundColor& bgColor );

}; // class FileLogger

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_FILE_LOGGER_H
