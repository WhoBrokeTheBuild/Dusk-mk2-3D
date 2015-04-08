#include "LoggingSystem.h"

#include <Logging/Logger.h>
#include <Logging/Loggers/ConsoleLogger.h>
#include <Logging/Loggers/FileLogger.h>
#include <Logging/Loggers/StreamLogger.h>

#include <chrono>

using namespace Dusk::Logging;

char LoggingSystem::m_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];
char LoggingSystem::m_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

int LoggingSystem::
m_CurrentLevel = 0;

Map<string, int> 
LoggingSystem::m_Levels = Map<string, int>();

Map<string, LogForegroundColor>
LoggingSystem::m_ForegroundColors = Map<string, LogForegroundColor>();

Map<string, LogBackgroundColor>
LoggingSystem::m_BackgroundColors = Map<string, LogBackgroundColor>();

Map<string, ArrayList<Logger*>>
LoggingSystem::m_Loggers = Map<string, ArrayList<Logger*>>();

bool LoggingSystem::
AddLevel( const int& index, const string& level )
{
    if (m_Loggers.ContainsKey(level) || m_Levels.ContainsKey(level))
        return false;

    m_Loggers.Add(level, ArrayList<Logger*>());
    m_Levels.Add(level, index);
    m_ForegroundColors.Add(level, LOG_FG_DEFAULT);
    m_BackgroundColors.Add(level, LOG_BG_DEFAULT);

    return true;
}

void LoggingSystem::
CloseAllLoggers( void )
{
    for (auto it = m_Loggers.Begin(); it != m_Loggers.End(); ++it)
    {
        ArrayList<Logger*>& loggers = it->second;
        for (auto jt = loggers.Begin(); jt != loggers.End(); ++jt)
        {
			delete *jt;
        }
        loggers.Clear();
    }
    m_Loggers.Clear();
}

void LoggingSystem::
SetLevelForegroundColor( const string& level, const LogForegroundColor& color )
{
    if ( ! HasLevel(level)) return;

    m_ForegroundColors[level] = color;
}

void LoggingSystem::
SetLevelBackgroundColor( const string& level, const LogBackgroundColor& color )
{
    if ( ! HasLevel(level)) return;

    m_BackgroundColors[level] = color;
}

void LoggingSystem::
Log( const string& level, const string& message,
     const string& file, const int& line )
{
    if ( ! LevelShown(level)) return;

    Format(level.c_str(), message.c_str(), file.c_str(), line);
    DispatchLog(level);
}

void LoggingSystem::
ExtLog( const string& level, const string& format,
     const string& file, const int& line, va_list args )
{
    if ( ! LevelShown(level)) return;

    vsnprintf(m_FormatBuffer, DUSK_LOGGING_MAX_BUFFER_SIZE, format.c_str(), args);
    Format(level.c_str(), m_FormatBuffer, file.c_str(), line);
    DispatchLog(level);
}

void LoggingSystem::
Format( const char* level, const char* message,
        const char* file, const int& line )
{
    snprintf(m_LogBuffer, DUSK_LOGGING_MAX_BUFFER_SIZE,
             "+%d.%d.%d.%d <%s:%d> [%s]: %s",
             0, 0, 0, 0,
             file, line,
             level, message);
}

void LoggingSystem::
DispatchLog( const string& level )
{
    if ( ! HasLevel(level)) return;

    LogForegroundColor fgColor = m_ForegroundColors[level];
    LogBackgroundColor bgColor = m_BackgroundColors[level];

    ArrayList<Logger*>& loggers = m_Loggers[level];
    for (auto it = loggers.Begin(); it != loggers.End(); ++it)
    {
        Logger* pLogger = (*it);
        if (pLogger == nullptr)
            continue;

        pLogger->Log(m_LogBuffer, fgColor, bgColor);
    }
}

bool LoggingSystem::
AddConsoleLogger( const string& level )
{
    if ( ! m_Loggers.ContainsKey(level))
        return false;
    m_Loggers[level].Add(New ConsoleLogger());
    return true;
}

bool LoggingSystem::
AddFileLogger( const string& level, const string& filename )
{
    if ( ! m_Loggers.ContainsKey(level))
        return false;
	m_Loggers[level].Add(New FileLogger(filename));
    return true;
}

/*
    static bool AddFileLogger    ( const string& level, const string& filename );
    static bool AddStreamLogger  ( const string& level, ostream& stream );
    static bool AddStdOutLogger  ( const string& level );
    static bool AddStdErrorLogger( const string& level );



    static void Log( const string& level, const string& format const string& file, const int& line, ... );
*/
