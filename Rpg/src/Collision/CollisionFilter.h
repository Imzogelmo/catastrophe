// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#pragma once

/*
	CollisionFilter - simple class
	that contains a collision category and mask property to filter out
	collisions between objects that can or cannot collide with
	other objects.
*/
struct CollisionFilter
{
	int category, mask;

	CollisionFilter() : category(0), mask(0) {}
	CollisionFilter(int _Category, int _Mask) : category(_Category), mask(_Mask) {}

	inline int GetCategory() const { return category; }
	inline int GetMask() const { return mask; }
	inline void SetCategory( int _Category ) { category = _Category; }
	inline void SetMask( int _Mask ) { mask = _Mask; }
	inline void AddCategory( int bits ) { category |= bits; }
	inline void AddMask( int bits ) { mask |= bits; }
	inline void RemoveCategory( int bits ) { category &= ~bits; }
	inline void RemoveMask( int bits ) { mask &= ~bits; }

	inline bool CanCollide( const CollisionFilter& f ) const
	{
		return ((category & f.mask) != 0 && (mask & f.category) != 0);
	}

	inline bool IsEthereal() const
	{
		return (mask == 0 || category == 0);
	}
};

