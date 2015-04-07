#include "ConsoleLogger.h"

void Dusk::Logging::ConsoleLogger::
Log( const string& line, const LogForegroundColor& fgColor,
                         const LogBackgroundColor& bgColor )
{
#ifndef _WIN32
    printf("\033[%dm\033[%dm", fgColor, bgColor);
#endif

    printf("%s\n", line.c_str());

#ifndef _WIN32
    printf("\033[%dm\033[%dm", LOG_FG_DEFAULT, LOG_BG_DEFAULT);
#endif
}
