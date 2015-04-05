#ifndef DUSK_LOGGING_LOG_COLORS_H
#define DUSK_LOGGING_LOG_COLORS_H

namespace Dusk
{

namespace Logging
{

enum LogForegroundColor
{
    LOG_FG_BLACK         = 30,
    LOG_FG_RED           = 31,
    LOG_FG_GREEN         = 32,
    LOG_FG_YELLOW        = 33,
    LOG_FG_BLUE          = 34,
    LOG_FG_MAGENTA       = 35,
    LOG_FG_CYAN          = 36,
    LOG_FG_GRAY          = 37,
    LOG_FG_GREY          = 37,
    LOG_FG_WHITE         = 97,
    LOG_FG_DEFAULT       = 39
};

enum LogBackgroundColor
{
    LOG_BG_RED     = 41,
    LOG_BG_GREEN   = 42,
    LOG_BG_YELLOW  = 43,
    LOG_BG_BLUE    = 44,
    LOG_BG_MAGENTA = 45,
    LOG_BG_CYAN    = 46,
    LOG_BG_GRAY    = 100,
    LOG_BG_GREY    = 100,
    LOG_BG_WHITE   = 47,
    LOG_BG_DEFAULT = 49
};

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_LOG_COLORS_H
