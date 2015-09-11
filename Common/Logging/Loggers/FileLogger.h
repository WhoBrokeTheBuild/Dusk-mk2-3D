#ifndef DUSK_LOGGING_FILE_LOGGER_H
#define DUSK_LOGGING_FILE_LOGGER_H

#include <Logging/ILogger.h>
#include <Collections/Map.h>
#include <Collections/ArrayList.h>

#include <string>
#include <fstream>

using Dusk::Collections::Map;
using Dusk::Collections::ArrayList;
using std::string;
using std::ofstream;

namespace Dusk
{

namespace Logging
{

class FileLogger :
    public ILogger
{
public:

    FileLogger( const string& filename );
    virtual ~FileLogger( void );

	virtual inline string GetClassName( void ) const { return "File Logger"; }

    virtual void Log( const string& line,
                      const LogForegroundColor& fgColor,
                      const LogBackgroundColor& bgColor );

private:

	static Map<string, ofstream*>	s_Streams;
	static Map<string, int>			s_StreamOwners;

	string		m_Filename;
	ofstream*	m_Stream;

}; // class FileLogger

} // namespace Logging

} // namespace Dusk

#endif // DUSK_LOGGING_FILE_LOGGER_H
