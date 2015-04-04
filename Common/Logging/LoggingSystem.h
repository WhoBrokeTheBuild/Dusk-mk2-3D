#ifndef DUSK_LOGGING_LOGGING_SYSTEM_H
#define DUSK_LOGGING_LOGGING_SYSTEM_H

#include <Collections/Map.h>
#include <Collections/ArrayList.h>

#include <string>
#include <fstream>

using namespace Dusk::Collections;
using std::string;
using std::ostream;

#define DUSK_LOGGING_MAX_BUFFER_SIZE 4096

namespace Dusk
{

namespace Logging
{

class Logger;

class LoggingSystem
{
public:

    static inline bool AddLevel( const string& level )
    {
        if (m_Loggers.ContainsKey(level))
            return false;
        m_Loggers.Add(level, ArrayList<Logger*>());
        return true;
    }

    static inline bool HasLevel( const string& level )
        { return (m_Loggers.ContainsKey(level)); }

    static bool AddFileLogger    ( const string& level, const string& filename );
    static bool AddStreamLogger  ( const string& level, ostream& stream );
    static bool AddStdOutLogger  ( const string& level );
    static bool AddStdErrorLogger( const string& level );

    static void CloseAllLoggers( void );

    static void Log   ( const string& level, const string& message,
                        const string& file, const int& line );
    static void ExtLog( const string& level, const string& format,
                        const string& file, const int& line, va_list args );

private:

    static void Format( const char* level, const char*,
                        const char* file,  const int& line );

    static void DispatchLog( const string& level );

    static char  m_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE],
                 m_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

    static Map<string, ArrayList<Logger*>>     m_Loggers;

}; // class LoggingSystem

#define DuskLog( LVL, MSG ) \
LoggingSystem::Log(LVL, MSG, string(__FILE__), __LINE__)

#define DuskExtLog( LVL, FMT, ... ) \
LoggingSystem::ExtLog(LVL, FMT, string(__FILE__), __LINE__, __VA_ARGS__)

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_LOGGING_SYSTEM_H
