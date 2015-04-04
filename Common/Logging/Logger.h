#ifndef DUSK_LOGGING_LOGGER_H
#define DUSK_LOGGING_LOGGER_H

#include <string>

using std::string;

namespace Dusk
{

namespace Logging
{

class Logger
{
public:

    virtual inline ~Logger( void ) { }

    virtual void Log( const string& line ) = 0;

}; // class Logger

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_LOGGER_H
