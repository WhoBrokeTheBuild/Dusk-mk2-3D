#ifndef DUSK_TRACKING_MEMORY_TRACKER_H
#define DUSK_TRACKING_MEMORY_TRACKER_H

#include <Collections/Map.h>
#include <string>

using Dusk::Collections::Map;
using std::string;

namespace Dusk
{
	
namespace Tracking
{

class ITrackedObject;

class MemoryTracker
{

	friend class ITrackedObject;

public:

	static bool Init( void );
	static void Term( void );

	static bool AddAllocation( ITrackedObject* pObject, size_t size, 
							   unsigned int lineNumber, string filename );
	static bool RemoveAllocation( ITrackedObject* pObject );

	static inline unsigned int GetAllocationCount( void ) 
		{ return (unsigned int)s_Allocations.Size(); }

	static void PrintAllocations( void );

private:

	struct AllocationRecord
	{
	public:

		unsigned int	Number,
						LineNumber;
		size_t			Size;
		string			Filename;

		AllocationRecord( int num, size_t size, int lineNum, string filename ) :
			Number(num),
			LineNumber(lineNum),
			Size(size),
			Filename(filename)
		{ }

	}; // struct AllocationRecord

	static Map<ITrackedObject*, AllocationRecord>	s_Allocations;

	static unsigned int								s_AllocationIndex;

}; // class MemoryTracker

} // namespace Tracking

} // namespace Dusk

#endif // DUSK_TRACKING_MEMORY_TRACKER_H