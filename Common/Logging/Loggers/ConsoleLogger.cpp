#include "ConsoleLogger.h"

void Dusk::Logging::ConsoleLogger::
Log( const string& line, const LogForegroundColor& fgColor,
                         const LogBackgroundColor& bgColor )
{
    printf("\033[%dm\033[%dm", fgColor, bgColor);
    printf("%s\n", line.c_str());
    printf("\033[%dm\033[%dm", LOG_FG_DEFAULT, LOG_BG_DEFAULT);
}
