#ifndef DUSK_TRACKING_MEMORY_TRACKED_OBJECT_H
#define DUSK_TRACKING_MEMORY_TRACKED_OBJECT_H

#include <Utility/Platform.h>
#include <string>

using std::string;

namespace Dusk
{

namespace Tracking
{

class TrackedObject
{
public:

	virtual string ClassName( void ) const = 0;

	// Normal new operator
	void* operator new  ( size_t size );
	void* operator new[]( size_t size );

	// Operator for placement new, takes in the filename and line number
	void* operator new  ( size_t size, int lineNumber, const char *filename );
	void* operator new[]( size_t size, int lineNumber, const char *filename );

	// Normal delete operator
	void operator delete  ( void *ptr );
	void operator delete[]( void *ptr );

	// Required because of the placement new operator, should not be used
	inline void operator delete  ( void *ptr, int lineNumber, const char *filename ) { ::operator delete(ptr); }
	inline void operator delete[]( void *ptr, int lineNumber, const char *filename ) { ::operator delete[](ptr); }

}; // class MemoryTrackedObject

#ifdef DUSK_DEBUG_BUILD

#define New new(__LINE__, __FILE__)

#else

#define New new

#endif

} // namespace Tracking

} // namespace Dusk

#endif // DUSK_TRACKING_MEMORY_TRACKED_OBJECT_H