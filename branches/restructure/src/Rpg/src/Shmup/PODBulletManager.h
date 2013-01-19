
#pragma once

#include <fc/parallel.h>

#include "PODBullet.h"


class PODBulletManager
{
public:
	typedef fc::parallel<PODBullet> vec_type;

	enum : size_t
	{
		BulletCapacity = 4096
	};

	PODBulletManager() : m_bullets()
	{
		m_bullets.reserve(BulletCapacity);
	}

	vec_type& GetBullets()
	{
		return m_bullets;
	}

	void DestroyBullet( size_t bulletIndex )
	{
		if( bulletIndex < m_bullets.size() )
		{
			PODBullet& b = m_bullets[bulletIndex];
			if( b.is_alive )
			{
				b.is_alive = false;
				m_bullets.bind(bulletIndex);
			}
		}
	}

	PODBullet& CreateBullet()
	{
		ASSERT(!m_bullets.full());
		PODBullet& b = m_bullets.push_back_uninitialized();
		b.is_alive = true;

		return b;
	}

	void Update()
	{
		const size_t bSize = m_bullets.size();
		for( size_t i(0); i < bSize; ++i )
		{
			PODBullet& b = m_bullets[i];
			if( !b.Update() )
			{
				m_bullets.bind(i);
			}
		}

		m_bullets.execute();
	}

	void Render()
	{
		for( vec_type::iterator it = m_bullets.begin(); it != m_bullets.end(); ++it )
		{
			it->Render();
		}
	}

protected:
	vec_type m_bullets;

};
