
#pragma once

#include "Catastrophe/Graphics.h"
#include <fc/rand.h>


struct Lazors
{
	Vector2 pos, p1, p2, p3, p4;
	Colorf c;
	float t;
	uint n;
	Primitive p;

	Lazors() {}
	Lazors( Vector2 p1, Vector2 t1, Vector2 t2, Vector2 p2, Colorf c )
		: pos(), p1(p1), p2(t1), p3(t2), p4(p2), c(c), t(0.f), n(0), p()
	{
		//p.Reserve(64);
		p.SetPrimitiveType( ptLINE_STRIP );
		p.SetBlendMode( BlendMode::Additive );
	}

	int Update()
	{
		if(p.Empty())
			p.Reserve(64);

		if( t > 1.f )
		{
			n++;
			uint size = p.Size();
			if( n >= size )
				return -1;

			return 0;
		}

		pos = Math::Bezier(p1, p2, p3, p4, t);
	//	pos = Vector2::Bezier(p1, t1, p2, t);
	//	pos = Vector2::Cubic(p2, p1, p4, p3, t);
		p.AddVertex( pos, c.Lerp( Colorf(0.3f,0.f,0.85f,0.3f), t ) );
		t += 0.03f;

		return 0;
	}

	void Render()
	{
		//draw range
		p.Render( n, p.Size()-n );
	}

};



class Spline_Test
{
public:
	fc::vector<Lazors> lasers;
	float rot;

	Spline_Test() : lasers(), rot(0.0f) 
	{
		glDisable(GL_TEXTURE_2D);
		//glLineWidth( 3.0f );

		lasers.reserve( 1024 );
	}

	void Update()
	{
		const int numToAdd = 1; //add n objects per frame.
		for(int i(0); i < numToAdd; ++i)
		{
			rot += fc::randf(180.f);
			Vector2 center(320.f, 240.f);
			Vector2 dest = center.Polar( center, Math::ToRadians(rot) );
			Vector2 t1 = center.Polar( center / 2.0f, fc::randf(CE_PI * 2.f) );
			Vector2 t2 = center.Polar( center, fc::randf(CE_PI * 2.f) );

			lasers.push_back( Lazors( center, t1, t2, dest, Colorf( 0.95f, 0.3f, 0.58f, 0.98f ) ) );
		}

		for( fc::vector<Lazors>::iterator it = lasers.begin(); it != lasers.end(); ++it )
		{
			int c = it->Update();
			if( c != 0 )
				lasers.erase(it), --it;
		}
	}

	void Render()
	{
		for( fc::vector<Lazors>::iterator it = lasers.begin(); it != lasers.end(); ++it )
		{
			it->Render();
		}
	}

};






