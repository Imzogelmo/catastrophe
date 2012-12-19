
#include <angelscript.h>
#include "ScriptGarbage.h"



ScriptGarbage::ScriptGarbage() :
	m_enginePtr(0),
	m_statistics(),
	m_counter(0)
{
}


void ScriptGarbage::Update()
{
	GCStatistics current = GetCurrentStatistices();

	m_counter++;
	int d = int(m_statistics.objects - current.objects);

	//todo: get a detailed measurement here.
	if( m_counter > current.objects && m_counter > 0 )
	{
		GarbageCollect();
		m_counter = 0;
	}
}


void ScriptGarbage::GarbageCollect()
{
	m_statistics = GetCurrentStatistices();
	m_enginePtr->GarbageCollect(asGC_ONE_STEP);

	LogStatistics(m_statistics);
}


GCStatistics ScriptGarbage::GetCurrentStatistices() const
{
	GCStatistics s;
	m_enginePtr->GetGCStatistics(
		&s.size,
		&s.total_destroyed,
		&s.total_detected,
		&s.objects,
		&s.destroyed
	);

	return s;
}


void ScriptGarbage::LogStatistics( const GCStatistics& s ) const
{
	LogInfo("GC Statistics: time(%i), size(%d), total_destroyed(%d), total_detected(%d), objects(%d), destroyed(%d).",
		m_counter,
		s.size,
		s.total_destroyed,
		s.total_detected,
		s.objects,
		s.destroyed
	);
}

