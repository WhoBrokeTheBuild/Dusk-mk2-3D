#ifndef DUSK_UTILITY_STRINGS_H
#define DUSK_UTILITY_STRINGS_H

#include <iostream>
#include <string>

using std::string;

namespace Dusk
{

namespace Utility
{

string Basename( const string& filename );
string Dirname ( const string& filename );

}; // namespace Utility

}; // namespace Dusk

#endif // DUSK_UTILITY_STRINGS_H