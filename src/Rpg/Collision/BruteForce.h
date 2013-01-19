
#pragma once

#include "CollisionFilter.h"


template <class T, class Pred>
class BruteForceCollision
{
public:

	// O(n^2/2) complexity 
	void TestObjects( T* begin, T* end )
	{
		ASSERT(begin <= end);
		for( ; begin != end; ++begin )
		{
			const CollisionFilter& filter = begin->filter;
			if( filter.IsEthereal() )
			{
				//it is impossible for this object to collide with another.
				return;
			}

			const Rectf aabb = begin->GetBoundingRect();
			for( T* it(begin + 1); it != end; ++it )
			{
				if( filter.CanCollide(it->filter) )
				{
					if( aabb.Intersects( it->GetBoundingRect() ) )
					{
						//collision... 
						pred( *begin, *it );
					}
				}
			}
		}
	}

	// O(n) complexity 
	void TestObjectAgainstRange( T& obj, T* begin, T* end )
	{
		ASSERT(begin <= end);

		const CollisionFilter& filter = begin->filter;
		if( filter.IsEthereal() )
		{
			//it is impossible for this object to collide with another.
			return;
		}

		const Rectf aabb = obj.GetBoundingRect();
		for( ; begin != end; ++begin )
		{
			if( filter.CanCollide(begin->filter) )
			{
				if( aabb.Intersects( begin->GetBoundingRect() ) )
				{
					//collision...
					pred( obj, *begin );
				}
			}
		}
	}

protected:
	Pred pred;

};

