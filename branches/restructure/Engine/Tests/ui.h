
#pragma once

#include "Catastrophe/Gui.h"
#include "Catastrophe/Gui/TextElement.h"
#include "Catastrophe/Graphics/SpriteBatch.h"
#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Graphics/Image.h"
#include "Catastrophe/Graphics/Shader.h"
#include "Catastrophe/Graphics/Sprite.h"
#include "Catastrophe/Graphics/Font.h"
#include "Catastrophe/Graphics.h"



class FrameWidget : public Widget
{
public:
	struct Patch
	{
		gluint texture;
		Rectf uv;
		Vector2 size;

		Patch( gluint texture_id = 0, const Rectf& uv = Rectf::Zero, const Vector2& size = Vector2::Zero)
			: texture(texture_id), uv(uv), size(size)
		{}
	};

	FrameWidget()
	{
		m_tiled = false;
	}

	void SetTexture( const Texture* texture )
	{
		CE_ASSERT(texture);

		if(texture)
		{
			gluint id = texture->GetTextureID();
			m_corners[0].texture = id;
			m_corners[1].texture = id;
			m_corners[2].texture = id;
			m_corners[3].texture = id;
			m_sides[0].texture = id;
			m_sides[1].texture = id;
			m_sides[2].texture = id;
			m_sides[3].texture = id;
		}
	}


	void SetFromSprite( const Sprite& sprite )
	{
		SetBlendMode(sprite.blendmode);
		SetPatchData( sprite.GetTexture(),
			sprite.GetSize(),
			sprite.GetUVRect()
		);
	}

	void SetFromSprite( const AnimatedSprite& sprite )
	{
		SetBlendMode(sprite.blendmode);
		SetPatchData( sprite.GetTexture(),
			sprite.GetSize(),
			sprite.GetUVRect()
		);
	}

	void SetPatchData( const Texture* texture, const Vector2& spriteSize, const Rectf& uv )
	{
		SetTexture(texture);
		Vector2 size = spriteSize / 3.f;
		Vector2 dist = uv.max - uv.min;
		Vector2 d = dist / 3.f;

		// split into a "9-patch" structure.
		float x[4], y[4];
		x[0] = uv.min.x;
		x[1] = uv.min.x + d.x;
		x[2] = uv.max.x - d.x;
		x[3] = uv.max.x;
		y[0] = uv.min.y;
		y[1] = uv.min.y + d.y;
		y[2] = uv.max.y - d.y;
		y[3] = uv.max.y;

		m_sides[0].uv = Rectf( x[1], y[0], x[2], y[1] );
		m_sides[1].uv = Rectf( x[0], y[1], x[1], y[2] );
		m_sides[2].uv = Rectf( x[2], y[1], x[3], y[2] );
		m_sides[3].uv = Rectf( x[1], y[2], x[2], y[3] );
		m_sides[0].size = size;
		m_sides[1].size = size;
		m_sides[2].size = size;
		m_sides[3].size = size;

		m_corners[0].uv = Rectf( x[0], y[0], x[1], y[1] );
		m_corners[1].uv = Rectf( x[2], y[0], x[3], y[1] );
		m_corners[2].uv = Rectf( x[0], y[2], x[1], y[3] );
		m_corners[3].uv = Rectf( x[2], y[2], x[3], y[3] );
		m_corners[0].size = size;
		m_corners[1].size = size;
		m_corners[2].size = size;
		m_corners[3].size = size;
	}

	void SetBlendMode( const BlendMode& value ) { m_blendmode = value; }
	const BlendMode& GetBlendMode() const { return m_blendmode; }
/*
	void Render( SpriteBatch* spriteBatch )
	{
		Vector2 size = GetSize();
		Vector2 min = GetScreenPositionAsVector2();
		Vector2 max = min + size;
		Rectf r;

		r.min.x = min.x;
		r.min.y = min.y;
		r.max.x = min.x + m_corners[0].size.x;
		r.max.y = min.y + m_corners[0].size.y;
		spriteBatch->Draw( m_corners[0].texture, r, m_corners[0].uv, m_color );

		r.min.x = min.x + m_corners[1].size.x;
		r.min.y = min.y;
		r.max.x = max.x - m_corners[1].size.x;
		r.max.y = min.y - m_corners[1].size.y;
		spriteBatch->Draw( m_corners[1].texture, r, m_corners[1].uv, m_color );

		r.min.x = min.x;
		r.min.y = max.y - m_corners[2].size.y;
		r.max.x = min.x + m_corners[2].size.x;
		r.max.y = max.y;
		spriteBatch->Draw( m_corners[2].texture, r, m_corners[2].uv, m_color );

		r.min.x = max.x - m_corners[3].size.x;
		r.min.y = max.y - m_corners[3].size.y;
		r.max.x = max.x;
		r.max.y = max.y;
		spriteBatch->Draw( m_corners[3].texture, r, m_corners[3].uv, m_color );

		if( m_tiled )
		{
			//todo
		}
		else
		{
			r.min.x = min.x + m_sides[0].size.x;
			r.min.y = min.y;
			r.max.x = max.x - m_sides[0].size.x;
			r.max.y = min.y + m_sides[0].size.y;
			spriteBatch->Draw( m_sides[0].texture, r, m_sides[0].uv, m_color );

			r.min.x = min.x;
			r.min.y = min.y + m_sides[1].size.y;
			r.max.x = min.x + m_sides[1].size.x;
			r.max.y = max.y - m_sides[1].size.y;
			spriteBatch->Draw( m_sides[1].texture, r, m_sides[1].uv, m_color );

			r.min.x = max.x - m_sides[2].size.x;
			r.min.y = min.y + m_sides[2].size.y;
			r.max.x = max.x;
			r.max.y = max.y - m_sides[2].size.y;
			spriteBatch->Draw( m_sides[2].texture, r, m_sides[2].uv, m_color );

			r.min.x = min.x + m_sides[3].size.x;
			r.min.y = max.y - m_sides[3].size.y;
			r.max.x = max.x - m_sides[3].size.x;
			r.max.y = max.y;
			spriteBatch->Draw( m_sides[3].texture, r, m_sides[3].uv, m_color );

		}

	}
*/
	void Render( SpriteBatch* spriteBatch )
	{
		Vector2 min = GetScreenPosition();
		Vector2 max = min + GetSize();

		Rectf vtx;
		vtx.min.x = min.x;
		vtx.min.y = min.y;
		vtx.max.x = min.x + m_corners[0].size.x;
		vtx.max.y = min.y + m_corners[0].size.y;
		spriteBatch->Draw( m_corners[0].texture, vtx, m_corners[0].uv, m_color );

		vtx.min.x = max.x - m_corners[1].size.x;
		vtx.min.y = min.y;
		vtx.max.x = max.x;
		vtx.max.y = min.y + m_corners[1].size.y;
		spriteBatch->Draw( m_corners[1].texture, vtx, m_corners[1].uv, m_color );

		vtx.min.x = min.x;
		vtx.min.y = max.y - m_corners[2].size.y;
		vtx.max.x = min.x + m_corners[2].size.x;
		vtx.max.y = max.y;
		spriteBatch->Draw( m_corners[2].texture, vtx, m_corners[2].uv, m_color );

		vtx.min.x = max.x - m_corners[3].size.x;
		vtx.min.y = max.y - m_corners[3].size.y;
		vtx.max.x = max.x;
		vtx.max.y = max.y;
		spriteBatch->Draw( m_corners[3].texture, vtx, m_corners[3].uv, m_color );

		if( m_tiled )
		{
			//todo...
		}
		else
		{
			vtx.min.x = min.x + m_corners[0].size.x;
			vtx.min.y = min.y;
			vtx.max.x = max.x - m_corners[1].size.x;
			vtx.max.y = min.y + m_sides[0].size.y;
			spriteBatch->Draw( m_sides[0].texture, vtx, m_sides[0].uv, m_color );

			vtx.min.x = min.x;
			vtx.min.y = min.y + m_corners[0].size.y;
			vtx.max.x = min.x + m_sides[1].size.x;
			vtx.max.y = max.y - m_corners[2].size.y;
			spriteBatch->Draw( m_sides[1].texture, vtx, m_sides[1].uv, m_color );

			vtx.min.x = max.x - m_sides[2].size.x;
			vtx.min.y = min.y + m_corners[1].size.y;
			vtx.max.x = max.x;
			vtx.max.y = max.y - m_corners[3].size.y;
			spriteBatch->Draw( m_sides[2].texture, vtx, m_sides[2].uv, m_color );

			vtx.min.x = min.x + m_corners[2].size.x;
			vtx.min.y = max.y - m_sides[3].size.y;
			vtx.max.x = max.x - m_corners[3].size.x;
			vtx.max.y = max.y;
			spriteBatch->Draw( m_sides[3].texture, vtx, m_sides[3].uv, m_color );

		}

		/*
		spriteBatch->Draw( m_corners[0].texture, m_corners[0].vtx, m_corners[0].uv, m_color );
		spriteBatch->Draw( m_corners[1].texture, m_corners[1].vtx, m_corners[1].uv, m_color );
		spriteBatch->Draw( m_corners[2].texture, m_corners[2].vtx, m_corners[2].uv, m_color );
		spriteBatch->Draw( m_corners[3].texture, m_corners[3].vtx, m_corners[3].uv, m_color );

		if( m_tiled )
		{
			//todo
		}
		else
		{
			spriteBatch->Draw( m_sides[0].texture, m_sides[0].vtx, m_sides[0].uv, m_color );
			spriteBatch->Draw( m_sides[1].texture, m_sides[1].vtx, m_sides[1].uv, m_color );
			spriteBatch->Draw( m_sides[2].texture, m_sides[2].vtx, m_sides[2].uv, m_color );
			spriteBatch->Draw( m_sides[3].texture, m_sides[3].vtx, m_sides[3].uv, m_color );

		}
		*/

		Widget::Render(spriteBatch);
	}
/*
	void CalculateVertices()
	{
		Vector2 min = GetScreenPositionAsVector2();
		Vector2 max = min + GetSize();

		m_corners[0].vtx.min.x = min.x;
		m_corners[0].vtx.min.y = min.y;
		m_corners[0].vtx.max.x = min.x + m_corners[0].size.x;
		m_corners[0].vtx.max.y = min.y + m_corners[0].size.y;

		m_corners[1].vtx.min.x = max.x - m_corners[1].size.x;
		m_corners[1].vtx.min.y = min.y;
		m_corners[1].vtx.max.x = max.x;
		m_corners[1].vtx.max.y = min.y + m_corners[1].size.y;

		m_corners[2].vtx.min.x = min.x;
		m_corners[2].vtx.min.y = max.y - m_corners[2].size.y;
		m_corners[2].vtx.max.x = min.x + m_corners[2].size.x;
		m_corners[2].vtx.max.y = max.y;

		m_corners[3].vtx.min.x = max.x - m_corners[3].size.x;
		m_corners[3].vtx.min.y = max.y - m_corners[3].size.y;
		m_corners[3].vtx.max.x = max.x;
		m_corners[3].vtx.max.y = max.y;

		if( !m_tiled )
		{
			m_sides[0].vtx.min.x = min.x + m_corners[0].size.x;
			m_sides[0].vtx.min.y = min.y;
			m_sides[0].vtx.max.x = max.x - m_corners[0].size.x;
			m_sides[0].vtx.max.y = min.y + m_corners[0].size.y;

			m_sides[1].vtx.min.x = min.x;
			m_sides[1].vtx.min.y = min.y + m_sides[1].size.y;
			m_sides[1].vtx.max.x = min.x + m_sides[1].size.x;
			m_sides[1].vtx.max.y = max.y - m_sides[1].size.y;

			m_sides[2].vtx.min.x = max.x - m_sides[2].size.x;
			m_sides[2].vtx.min.y = min.y + m_sides[2].size.y;
			m_sides[2].vtx.max.x = max.x;
			m_sides[2].vtx.max.y = max.y - m_sides[2].size.y;

			m_sides[3].vtx.min.x = min.x + m_sides[3].size.x;
			m_sides[3].vtx.min.y = max.y - m_sides[3].size.y;
			m_sides[3].vtx.max.x = max.x - m_sides[3].size.x;
			m_sides[3].vtx.max.y = max.y;
		}
	}
*/

protected:
	BlendMode	m_blendmode;
	Patch		m_corners[4];
	Patch		m_sides[4];
	bool		m_tiled;

};


class UI_Test
{
public:
	SpriteBatch sb;
	Sprite sprite;
	Sprite bg;
	Texture tex;
	Font font;

	FrameWidget frame;
	TextElement te1;


	UI_Test()
	{
		//te1 = TextElement("", &font); te1.SetPosition(Point(32,400));
		te1 = TextElement("", &font);
		//te1.SetPosition(Point(32,432));
		te1.SetPosition(Point(32,8));
		te1.SetText("Wow that's a lotta nuts! ..Kupo.");

		assert( font.LoadFromFile("fonts/final_fantasy_36.ttf", 18) == 0 );
		//assert( font.LoadFromFile("sansation.ttf", 36) == 0 );
		font.SetLineHeight(18);
		assert( tex.LoadFromFile("gui.png") );
		sprite.SetTexture(&tex);
		sprite.SetSize(24.f);
		sprite.SetSourceRect(Rect(0,0,24,24));
		//sprite.SetSourceRect(Rect(64,0,64,64));

		bg.SetTexture(&tex);
		bg.SetSize(Vector2(256.f, 128));
		bg.SetSourceRect(Rect(64,0,64,64));
		bg.tint.a = 100;

		frame.SetSize(640, 50);
		frame.SetPosition(Point(0,430));
		frame.SetFromSprite(sprite);

		frame.AddChild(&te1);
	}

	void Update()
	{
	}

	void Render()
	{
		sb.Begin();

		FrameWidget f[64];
		for( int i(0); i < 64; ++i )
		{
			Point p = Point( fc::rand(0, 400), fc::rand(0, 360) );
			Point s = Point( fc::rand(64, 400), fc::rand(32, 200) );
			f[i].SetSize(s);
			f[i].SetPosition(p);
			f[i].SetFromSprite(sprite);

			sb.Draw( bg.GetTextureID(), Rectf(p, p+s), bg.GetUVRect(), Color::White(100));
			f[i].Render(&sb);
		}

		//sb.DrawSprite( bg, 32.f );
		//sb.Draw( bg.GetTextureID(), Rectf(Vector2(32.f,32.f), Vector2(32.f,32.f) + bg.size), bg.GetUVRect());


		sb.Draw( bg.GetTextureID(), 
			Rectf(frame.GetPosition(), frame.GetPosition()+frame.GetSize()), 
			bg.GetUVRect(), Color::White()
			);
		frame.SetColor(Color::White());
		frame.Render(&sb);

		te1.SetColor(Color::White());
		//te1.Render(&sb);

		sb.Render();
		sb.End();
	}

};






