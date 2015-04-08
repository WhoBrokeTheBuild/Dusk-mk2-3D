#include "MemoryTracker.h"

#include <Tracking/TrackedObject.h>

using namespace Dusk::Tracking;

Map<TrackedObject*, MemoryTracker::AllocationRecord> MemoryTracker::
s_Allocations = Map<TrackedObject*, MemoryTracker::AllocationRecord>();

unsigned int MemoryTracker::s_AllocationIndex = 0;

bool MemoryTracker::
Init( void )
{
	s_AllocationIndex = 0;
	s_Allocations.Clear();

	return true;
}

void MemoryTracker::
Term(void)
{
	s_Allocations.Clear();
}

bool MemoryTracker::
AddAllocation( TrackedObject* pObject, size_t size, 
			   unsigned int lineNumber, string filename )
{
	if (s_Allocations.ContainsKey(pObject))
		return false;

	s_Allocations.Add(pObject, 
		AllocationRecord(s_AllocationIndex, size, lineNumber, filename));
	s_AllocationIndex++;

	return true;
}

bool MemoryTracker::
RemoveAllocation( TrackedObject* pObject )
{
	if ( ! s_Allocations.ContainsKey(pObject) )
		return false;

	s_Allocations.RemoveKey(pObject);

	return true;
}

void MemoryTracker::
PrintAllocations(void)
{
	printf("Allocations:\n");
	for (auto it = s_Allocations.Begin(); it != s_Allocations.End(); ++it)
	{
		printf("#%d: (address: %p) %s \n\t At %s:%d\n", 
			it->second.Number, 
			(void*)it->first, 
			it->first->ClassName().c_str(),
			it->second.Filename.c_str(),
			it->second.LineNumber);
	}
}
