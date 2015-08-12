#include "FileLogger.h"

using namespace Dusk::Logging;

Map<string, ofstream*> Dusk::Logging::FileLogger::m_Streams;
Map<string, int> Dusk::Logging::FileLogger::m_StreamOwners;

FileLogger::
FileLogger( const string& filename ) :
	m_Filename(filename),
	m_Stream(nullptr)
{
	if ( m_Streams.ContainsKey(m_Filename) )
	{
		m_Stream = m_Streams[m_Filename];
		++m_StreamOwners[m_Filename];
	}
	else
	{
		m_Stream = new ofstream();
		m_Stream->open(m_Filename);

		m_Streams.Add(m_Filename, m_Stream);
		m_StreamOwners.Add(m_Filename, 1);
	}
}

FileLogger::
~FileLogger( void )
{
	if (--m_StreamOwners[m_Filename] <= 0)
	{
		ofstream* pFile = m_Streams[m_Filename];
		pFile->close();
		m_Streams.RemoveAt(m_Filename);
	}
}

void FileLogger::
Log( const string& line, const LogForegroundColor& fgColor,
                         const LogBackgroundColor& bgColor )
{
	unsigned int len = line.length();
	char* fullLine = new char[len + 1];

	memcpy(fullLine, line.c_str(), len);
	fullLine[len] = '\n';

	m_Stream->write(fullLine, len + 1);
}
