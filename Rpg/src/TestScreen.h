
#pragma once

#include "Screen.h"
#include "Game.h"
#include "MonsterData.h"

#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/SpriteBatch.h>
#include <Catastrophe/Input.h>
#include <Catastrophe/Input/Input.h>

/*
 * TestScreen
 * so I can test gamestates, data, rendering etc..
 */
class TestScreen : public Screen
{
public:
	TestScreen( ScreenManager* parent ) : Screen(parent)
	{
		m_index = 0;
		bg.LoadFromFile("bg.png");
	}

	virtual void Update()
	{
		Keyboard* k = Input::GetKeyboard();
		if( k->IsKeyPressed(KEY_LEFT) )
		{
			m_index--;
		}
		else if( k->IsKeyPressed(KEY_RIGHT) )
		{
			m_index++;
		}

		m_index = (m_index + 128) % 128;
	}


	virtual void Render()
	{
		m_spriteBatch.Begin();

		m_spriteBatch.DrawTexture( &bg, Vector2::Zero );

		MonsterData & m = gGetActiveGame()->GetDatabase()->GetMonsterList()->GetMonster(m_index);
		AnimatedSprite & s = m.sprite;
		Vector2 center = s.size / 2.f;

		m_spriteBatch.DrawAnimatedSprite( m.sprite, Vector2(256,156) - center );

		m_spriteBatch.Render();
		m_spriteBatch.End();
	}


protected:
	Texture bg;
	SpriteBatch m_spriteBatch;
	int m_index;

};

