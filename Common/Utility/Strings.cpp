#include "Strings.h"
#include <experimental/filesystem>

using namespace Dusk::Utility;
namespace fs = std::experimental::filesystem;

string Dusk::Utility::
Basename( const string& filename )
{
	fs::path tmp = filename;
	return tmp.filename().string();
}

string Dusk::Utility::
Dirname(const string& filename)
{
	fs::path tmp = filename;
	if (!tmp.has_filename())
	{
		return tmp.string();
	}
	else
	{
		return tmp.remove_filename().string();
	}
}
