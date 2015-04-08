#ifndef DUSK_LOGGING_LOGGER_H
#define DUSK_LOGGING_LOGGER_H

#include <Tracking/TrackedObject.h>
#include <Logging/LogColors.h>

#include <string>

using std::string;

namespace Dusk
{

namespace Logging
{

class Logger :
	public Tracking::TrackedObject
{
public:

    virtual inline ~Logger( void ) { }

    virtual void Log( const string& line,
                      const LogForegroundColor& fgColor,
                      const LogBackgroundColor& bgColor ) = 0;

}; // class Logger

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_LOGGER_H
