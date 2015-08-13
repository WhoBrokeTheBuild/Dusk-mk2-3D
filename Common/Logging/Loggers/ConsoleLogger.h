#ifndef DUSK_LOGGING_CONSOLE_LOGGER_H
#define DUSK_LOGGING_CONSOLE_LOGGER_H

#include <Logging/Logger.h>

#include <string>

using std::string;

namespace Dusk
{

namespace Logging
{

class ConsoleLogger :
    public Logger
{
public:

    inline ConsoleLogger( void ) { }
    virtual ~ConsoleLogger( void ) { }

	virtual inline string GetClassName( void ) const { return "Console Logger"; }

    virtual void Log( const string& line,
                      const LogForegroundColor& fgColor,
                      const LogBackgroundColor& bgColor );

}; // class ConsoleLogger

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_CONSOLE_LOGGER_H
