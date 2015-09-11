#ifndef DUSK_LOGGING_LOGGER_H
#define DUSK_LOGGING_LOGGER_H

#include <Logging/Logging.h>
#include <Tracking/ITrackedObject.h>
#include <Logging/LogColors.h>

#include <string>

using std::string;

namespace Dusk
{

namespace Logging
{

class ILogger :
	public Tracking::ITrackedObject
{
public:

    virtual inline ~ILogger( void ) { }

    virtual void Log( const string& line,
                      const LogForegroundColor& fgColor,
                      const LogBackgroundColor& bgColor ) = 0;

}; // class Logger

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_LOGGER_H
