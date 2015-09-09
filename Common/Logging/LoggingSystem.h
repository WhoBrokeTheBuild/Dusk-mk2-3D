#ifndef DUSK_LOGGING_LOGGING_SYSTEM_H
#define DUSK_LOGGING_LOGGING_SYSTEM_H

#include <Scripting/Scripting.h>
#include <Collections/Map.h>
#include <Collections/ArrayList.h>

#include <Logging/LogColors.h>

#include <string>
#include <fstream>

using namespace Dusk::Collections;
using std::string;
using std::ostream;

#define DUSK_LOGGING_MAX_BUFFER_SIZE 4096

#ifdef _WIN32
#define snprintf _snprintf
#endif

namespace Dusk
{

namespace Logging
{

class Logger;

class LoggingSystem
{
public:

    static bool AddLevel( const int& index, const string& level );

    static inline bool HasLevel( const string& level )
        { return (m_Loggers.ContainsKey(level)); }

    static inline bool LevelShown( const string& level )
        { return (m_Levels[level] >= m_CurrentLevel); }

    static inline void SetLoggingLevel( const string& level )
        { m_CurrentLevel = m_Levels[level]; }

    static inline void SetLoggingLevel( const int& index )
        { m_CurrentLevel = index; }

    static inline int GetLoggingLevel( void )
        { return m_CurrentLevel; }

    static bool AddConsoleLogger ( const string& level );
    static bool AddFileLogger    ( const string& level, const string& filename );
    static bool AddStreamLogger  ( const string& level, ostream& stream );

    static void SetLevelForegroundColor( const string& level,
                                         const LogForegroundColor& color );
    static void SetLevelBackgroundColor( const string& level,
                                         const LogBackgroundColor& color );

    static void CloseAllLoggers( void );

    static void Log   ( const string& level, const string& message,
                        const string& file, const int& line );
    static void ExtLog( const string& level, const string& format,
                        const string& file, const int line, ... );

	static void InitScripting( void );
	static int Script_Log( lua_State* pState );

private:

    static void Format( const char* level, const char*,
                        const char* file,  const int& line );

    static void DispatchLog( const string& level );

    static char  m_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE],
                 m_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

    static int                                  m_CurrentLevel;

    static Map<string, int>                     m_Levels;

    static Map<string, LogForegroundColor>      m_ForegroundColors;
    static Map<string, LogBackgroundColor>      m_BackgroundColors;

    static Map<string, ArrayList<Logger*>>      m_Loggers;

}; // class LoggingSystem

#define DuskLog( LVL, MSG ) \
LoggingSystem::Log(LVL, MSG, string(__FILE__), __LINE__)

#define DuskExtLog( LVL, FMT, ... ) \
LoggingSystem::ExtLog(LVL, FMT, string(__FILE__), __LINE__, __VA_ARGS__)

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_LOGGING_SYSTEM_H
