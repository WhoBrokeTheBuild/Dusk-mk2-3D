#include "LoggingSystem.h"

#include <Logging/Logger.h>
#include <Logging/Loggers/ConsoleLogger.h>
#include <Logging/Loggers/FileLogger.h>
#include <Logging/Loggers/StreamLogger.h>
#include <Utility/Strings.h>
#include <Scripting/ScriptingSystem.h>

#include <cstdarg>
#include <chrono>

using namespace Dusk::Logging;
using namespace Dusk::Scripting;
using Dusk::Utility::Basename;

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

    Format(level.c_str(), message.c_str(), Basename(file).c_str(), line);
    DispatchLog(level);
}

void LoggingSystem::
ExtLog( const string& level, const string& format,
     const string& file, const int line, ... )
{
	if (!LevelShown(level)) return;

	va_list args;

	va_start(args, line);
	vsnprintf(m_FormatBuffer, DUSK_LOGGING_MAX_BUFFER_SIZE, format.c_str(), args);
	va_end(args);

    Format(level.c_str(), m_FormatBuffer, Basename(file).c_str(), line);
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

void LoggingSystem::
InitScripting( void )
{
	ScriptingSystem::RegisterFunction("dusk_log", &LoggingSystem::Script_Log);
}

int LoggingSystem::
Script_Log( lua_State* pState )
{
	lua_Debug ar;
	lua_getstack(pState, 1, &ar);
	lua_getinfo(pState, "nSl", &ar);

	string level = lua_tostring(pState, 1);
	string message = lua_tostring(pState, 2);

	LoggingSystem::Log(level.c_str(), message.c_str(), ar.source, ar.currentline);

	return 0;
}
