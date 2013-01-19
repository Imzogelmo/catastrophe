
#pragma once

#include <fc/parallel.h>

#include "Bullet.h"
#include "BulletPool.h"


/*
 * Bullet Manager class for non-pod type bullets which
 * uses an internal memory pool to preserve order,
 * and to avoid memory allocations and copies.
 *
 * Bullets must be derived from Indexable<size_t> class, or
 * implement GetIndex() and SetIndex() methods.
 */
class BulletManager
{
public:
	typedef fc::parallel<Bullet*>	vec_type;

	BulletManager( size_t numToAllocate, size_t maxAllocationReserve );
	~BulletManager();

	Bullet& CreateBullet();
	void DestroyBullet( Bullet& bullet );

	//void Update( ScriptCallback *scriptCallback, const Rectf& viewingRect );
	void Render();

	size_t GetBulletCount() const { return m_bullets.size(); }

	vec_type &GetBullets() { return m_bullets; }
	const vec_type &GetBullets() const { return m_bullets; }

protected:
	Bullet* InternalAquireBulletPtr();

	BulletPool	m_bulletPool;
	vec_type	m_bullets;

};


