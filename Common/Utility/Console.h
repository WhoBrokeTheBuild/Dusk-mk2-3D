#ifndef DUSK_UTILITY_CONSOLE_H
#define DUSK_UTILITY_CONSOLE_H

#include <iostream>
#include <string>

using std::string;

namespace Dusk
{

namespace Utility
{

inline void ConsolePause( const string& msg = "Press enter to continue..." )
{
	std::cout << msg;
	std::cin.sync();
	std::cin.ignore();
}

}; // namespace Utility

}; // namespace Dusk

#endif // DUSK_UTILITY_CONSOLE_H