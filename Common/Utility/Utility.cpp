#include "Utility.h"
#include <experimental/filesystem>

using namespace Dusk::Utility;
namespace fs = std::experimental::filesystem;

string Dusk::Utility::
Basename( const string& fullpath )
{
	fs::path tmp = fullpath;
	return tmp.filename().string();
}

