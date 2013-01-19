
#pragma once

#include <fc/math.h>
#include <fc/rand.h>


template <class T, class ManagerType>
class BulletFactory
{
public:
	typedef fc::vector<T>		vec_type;

	BulletFactory( ManagerType* parent = 0 )
		: m_bulletManager(parent), m_descriptors()
	{
	}

	void Initialize( ManagerType* parent )
	{
		m_bulletManager = parent;
	}

	T& Create( int type, const Vector2& pos, const Vector2& velocity )
	{
		T& b = m_bulletManager->CreateBullet();
		InitBulletFromType(type, &b);

		b.pos = pos;
		b.velocity = velocity;

		return b;
	}

	T& CreateFromAngle( int type, const Vector2& pos, float speed, float angle )
	{
		T& b = m_bulletManager->CreateBullet();
		InitBulletFromType(type, &b);

		b.pos = pos;
		b.sprite.angle = angle;
		fc::fast_sincos( angle, b.velocity.y, b.velocity.x );
		b.velocity *= speed;

		return b;
	}

	T& CreateFromBullet( const T& descriptor )
	{
		T& b = m_bulletManager->CreateBullet();
		b = descriptor;

		return b;
	}

	int CreateDescriptorType( const T& descriptor )
	{
		m_descriptors.push_back(descriptor);
		return int(m_descriptors.size() - 1);
	}

	void SetDescriptorType( int type, const T& descriptor )
	{
		if( size_t(type) < m_descriptors.size() )
		{
			m_descriptors[type] = descriptor;
		}
	}

	void InitBulletFromType( int type, T* b )
	{
		if( size_t(type) < m_descriptors.size() )
		{
			*b = m_descriptors[type];
			b->is_alive = true;
		}
		else
		{
			b->InitializeToZero();
			b->is_alive = true;
		}
	}

	T& GetDescriptorType( int type )
	{
		return m_descriptors[type];
	}

	void ClearDescriptorTypes()
	{
		m_descriptors.clear();
	}

private:
	ManagerType*	m_bulletManager;
	vec_type		m_descriptors;

};

