
#include "BulletManager.h"


BulletManager::BulletManager( size_t numToAllocate, size_t maxAllocationReserve ) :
	m_bulletPool(numToAllocate, maxAllocationReserve),
	m_bullets()
{
	m_bullets.reserve( numToAllocate );
}


BulletManager::~BulletManager()
{
}


Bullet& BulletManager::CreateBullet()
{
	return *InternalAquireBulletPtr();
}


void BulletManager::DestroyBullet( Bullet& bullet )
{
	bullet.is_alive = false;
}


Bullet* BulletManager::InternalAquireBulletPtr()
{
	m_bullets.push_back( m_bulletPool.AquireBullet() );
	return m_bullets.back();
}




/*

void BulletManager::Update( const Rectf& viewingRect, ScriptCallback *collisionCallback )
{

	//const Vector<Rectf>& playerRect = playerCollisionRects;
	const size_t size = m_bullets.size();

	for( size_t i(0); i < size; ++i ) 
	{
		Bullet* b = m_bullets[ i ];

		if( !b->is_alive )
		{
			m_bullets.bind( i );
			continue;
		}

		b->Update();

		//EnemyBullet* b = m_bullets[ i ];
		const Rectf spriteRect( b->pos, b->sprite.size );

		if( !viewingRect.Intersects( spriteRect ) )
		{
			m_bullets.bind( i );
			m_bullets[ i ]->is_alive = false;
			continue;
		}

	}

}
*/


void BulletManager::Render()
{
	for( vec_type::iterator it = m_bullets.begin(); it != m_bullets.end(); ++it )
	{
		(*it)->Render();
	}
}

