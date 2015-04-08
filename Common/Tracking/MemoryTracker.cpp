#include "MemoryTracker.h"

#include <Tracking/MemoryTrackedObject.h>

using namespace Dusk::Tracking;

Map<MemoryTrackedObject*, MemoryTracker::AllocationRecord> MemoryTracker::
s_Allocations = Map<MemoryTrackedObject*, MemoryTracker::AllocationRecord>();

unsigned int MemoryTracker::
s_AllocationIndex = 0;

bool Dusk::Tracking::MemoryTracker::
Init( void )
{
	s_AllocationIndex = 0;
	s_Allocations.Clear();

	return true;
}

void Dusk::Tracking::MemoryTracker::
Term(void)
{
	s_Allocations.Clear();
}

bool Dusk::Tracking::MemoryTracker::
AddAllocation( MemoryTrackedObject* pObject, size_t size, 
			   unsigned int lineNumber, string filename )
{
	if (s_Allocations.ContainsKey(pObject))
		return false;

	s_Allocations.Add(pObject, 
		AllocationRecord(s_AllocationIndex, size, lineNumber, filename));

	return true;
}

bool Dusk::Tracking::MemoryTracker::
RemoveAllocation( MemoryTrackedObject* pObject )
{
	if ( ! s_Allocations.ContainsKey(pObject) )
		return false;

	s_Allocations.RemoveKey(pObject);

	return true;
}

void Dusk::Tracking::MemoryTracker::PrintAllocations(void)
{
	printf("Allocations:\n");
	for (auto it = s_Allocations.Begin(); it != s_Allocations.End(); ++it)
	{
		printf("#%d: (address: %p) \n\t At %s:%d\n", it->second.Number, (void*)it->first, it->first->getClassName(), it->second.Filename.c_str(), it->second.LineNumber);
	}
}
