#include "FileLogger.h"

using namespace Dusk::Logging;

Map<string, ofstream*> Dusk::Logging::FileLogger::s_Streams;
Map<string, int> Dusk::Logging::FileLogger::s_StreamOwners;

FileLogger::
FileLogger( const string& filename ) :
	m_Filename(filename),
	m_Stream(nullptr)
{
	if (s_Streams.ContainsKey(m_Filename) )
	{
		m_Stream = s_Streams[m_Filename];
		++s_StreamOwners[m_Filename];
	}
	else
	{
		m_Stream = new ofstream();
		m_Stream->open(m_Filename);

		s_Streams.Add(m_Filename, m_Stream);
		s_StreamOwners.Add(m_Filename, 1);
	}
}

FileLogger::
~FileLogger( void )
{
	if (--s_StreamOwners[m_Filename] <= 0)
	{
		ofstream* pFile = s_Streams[m_Filename];
		pFile->close();
		s_Streams.RemoveAt(m_Filename);
	}
}

void FileLogger::
Log( const string& line, const LogForegroundColor& fgColor,
                         const LogBackgroundColor& bgColor )
{
	size_t len = line.length();
	char* fullLine = new char[len + 1];

	memcpy(fullLine, line.c_str(), len);
	fullLine[len] = '\n';

	m_Stream->write(fullLine, len + 1);
	m_Stream->flush();
}
