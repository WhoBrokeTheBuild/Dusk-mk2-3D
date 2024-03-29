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

class ILogger;

class LoggingSystem
{
public:

    static bool AddLevel( const int& index, const string& level );

    static inline bool HasLevel( const string& level )
        { return (s_Loggers.ContainsKey(level)); }

    static inline bool IsLevelShown( const string& level )
        { return (s_Levels[level] >= s_CurrentLevel); }

    static inline void SetLoggingLevel( const string& level )
        { s_CurrentLevel = s_Levels[level]; }

    static inline int GetLoggingLevel( void )
        { return s_CurrentLevel; }

    static bool AddConsoleLogger ( const string& level );
    static bool AddFileLogger    ( const string& level, const string& filename );
    //static bool AddStreamLogger  ( const string& level, ostream& stream );

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
	static int Script_Log( lua_State* L );

private:

    static void Format( const char* level, const char* message,
                        const char* file,  const int& line );

    static void DispatchLog( const string& level );

    static char  m_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE],
                 m_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

    static int                                  s_CurrentLevel;

    static Map<string, int>                     s_Levels;

    static Map<string, LogForegroundColor>      s_ForegroundColors;
    static Map<string, LogBackgroundColor>      s_BackgroundColors;

    static Map<string, ArrayList<ILogger*>>     s_Loggers;

}; // class LoggingSystem

#define DuskLog( LVL, MSG ) \
LoggingSystem::Log(LVL, MSG, string(__FILE__), __LINE__)

#define DuskExtLog( LVL, FMT, ... ) \
LoggingSystem::ExtLog(LVL, FMT, string(__FILE__), __LINE__, __VA_ARGS__)

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_LOGGING_SYSTEM_H
