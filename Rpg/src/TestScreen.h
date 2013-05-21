
#pragma once

#include "Screen.h"
#include "Game.h"
#include "Monster.h"

#include <fc/rand.h>
#include <Catastrophe/Graphics/OpenGL.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/SpriteBatch.h>
#include <Catastrophe/Input.h>
#include <Catastrophe/Input/Input.h>
#include <Catastrophe/Gui/MenuElement.h>
#include <Catastrophe/Gui/Label.h>
#include <Catastrophe/Gui/TextBox.h>
#include <Catastrophe/Gui/Frame.h>

#include "Script/ScriptClass.h"
#include "Item.h"
#include "Inventory.h"

/*
 * TestScreen
 * so I can test gamestates, data, rendering etc..
 */
/*
class TestScreen : public Screen
{
public:
	TestScreen( ScreenManager* parent ) : Screen(parent)
	{
		m_index = 0;
		bg.LoadFromFile("bg.png");
		gGetDatabase()->GetMonsterList()->DeserializeXml("monsters_psp.xml");
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

		Monster & m = gGetDatabase()->GetMonsterList()->GetMonster(m_index);
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
*/


/*
class TestScreen : public Screen // Test Scripts
{
public:
	TestScreen( ScreenManager* parent ) : Screen(parent)
	{
		script.Initialize("Main");
		script.CreateObject();
	}

	virtual void Update()
	{
		script.Update();
	}


	virtual void Render()
	{
	}


protected:
	ScriptClass script;
	SpriteBatch m_spriteBatch;

};
*/

/*
class TestScreen : public Screen //Test monster formations/troops
{
public:
	TestScreen( ScreenManager* parent ) : Screen(parent)
	{
		m_index = 0;
		bg.LoadFromFile("bg.png");

		gui.SetMagFilter(GL_LINEAR);
		gui.SetMinFilter(GL_LINEAR);
		gui.LoadFromFile("data/textures/gui.png");


		Rect r(0,64,24,24);
		frame[0].SetFromSprite( Sprite(&gui, r) );
		frame[1].SetFromSprite( Sprite(&gui, r) );
		frame[0].SetBackground( Sprite(&gui, Rect(0,0,64,64)) );
		frame[0].SetBackgroundOffset( 3.f );
		frame[0].SetPosition( Point(0,144) );
		frame[0].SetSize( Point(256,64) );
		frame[1].SetPosition( Point(112,144) );
		frame[1].SetSize( Point(144,64) );

		monsters = gGetDatabase()->GetMonsterList();
		troops = gGetDatabase()->GetMonsterPartyList();

		gGetDatabase()->GetMonsterList()->DeserializeXml("data/test/monsters.xml");
		gGetDatabase()->GetMonsterPartyList()->DeserializeXml("data/test/formations.xml");
	}

	virtual void Update()
	{
		static bool switchGroup = true;

		Keyboard* k = Input::GetKeyboard();
		if( k->IsKeyPressed(KEY_LEFT) )
		{
			m_index--;
			switchGroup = true;
		}
		else if( k->IsKeyPressed(KEY_RIGHT) )
		{
			m_index++;
			switchGroup = true;
		}

		m_index = (m_index + troops->Size()) % troops->Size();

		if(switchGroup)
		{
			switchGroup = false;
			monsterIDs.clear();

			MonsterPartyData & mp = troops->GetMonsterParty(m_index);
			foreachi(i, mp.NumGroups())
			{
				//monsterIDs
				int r = fc::rand( mp.GetGroup(i).min, mp.GetGroup(i).max );
				foreachi(j, r)
				{
					monsterIDs.push_back( mp.GetGroup(i).monster_index );
				}
			}
		}

	}


	virtual void Render()
	{
		m_spriteBatch.Begin();

		m_spriteBatch.DrawTexture( &bg, Vector2::Zero, Vector2(256.f, 156.f) );

		//Monster & m = monsters->GetMonster(m_index);
		//troops->GetMonsterParty(0);


		int large = 0, small = 0;
		int size = fc::min<int>( monsterIDs.size(), 9 );
		foreachi( i, size )
		{
			if( monsters->GetMonster(monsterIDs[i]).sprite.size.x > 32.f )
				large++;
			else if( monsters->GetMonster(monsterIDs[i]).sprite.size.x <= 32.f )
				small++;
		}

		//int sX[9] = { 32, 32, 32, 64, 64, 64, 96, 96, 96 };
		//int sY[9] = { 72, 32, 112, 72, 32, 112, 72, 32, 112 };
		//int lX[4] = { 32, 32, 96, 96 };
		//int lY[4] = { 32, 96, 32, 96 };
		int sX[9] = { 32, 32, 32, 64, 64, 64, 96, 96, 96 };
		int sY[9] = { 64, 32, 96, 64, 32, 96, 64, 32, 96 };
		int lX[4] = { 32, 32, 80, 80 };
		int lY[4] = { 32, 80, 32, 80 };

		if( large > 0)
		{
			foreachi( j, 9 )
				sX[j] += 48;

			if( small > 0 && large > 2 ) large = 2;

			if( large > 4 ) large = 4;
			if( small > 6 ) small = 6;
		}
		else
		{
			if( small > 9 ) small = 9;
		}

		int cs = 0, cl = 0;
		foreachi( i, size )
		{
			const float XOFFSET = -16.f;
			const float YOFFSET = 0.f;
			Vector2 pos = 0.f;

			AnimatedSprite & s = monsters->GetMonster(monsterIDs[i]).sprite;
			if( s.size.x > 32.f && cl < large )
			{
				pos.x = lX[cl] + XOFFSET;
				pos.y = lY[cl] + YOFFSET;
				m_spriteBatch.DrawAnimatedSprite( s, pos );
				cl++;
			}
			else if( s.size.x <= 32.f && cs < small )
			{
				pos.x = sX[cs] + XOFFSET;
				pos.y = sY[cs] + YOFFSET;
				m_spriteBatch.DrawAnimatedSprite( s, pos );
				cs++;
			}
		}

		//AnimatedSprite & s = m.sprite;
		//Vector2 center = s.size / 2.f;

		//m_spriteBatch.DrawAnimatedSprite( m.sprite, Vector2(256,156) - center );
		frame[0].Render(&m_spriteBatch);
		frame[1].Render(&m_spriteBatch);

		m_spriteBatch.Render();
		m_spriteBatch.End();
	}


protected:
	MonsterList* monsters;
	MonsterPartyList* troops;
	fc::vector<int> monsterIDs;

	Frame frame[2];
	Texture bg;
	Texture gui;
	SpriteBatch m_spriteBatch;
	int m_index;

};

*/

/*
class TestScreen : public Screen // Test Items/Menus
{
public:
	static const int FSIZE = 18;

	TestScreen( ScreenManager* parent ) : Screen(parent)
	{
		items = gGetDatabase()->GetItemList();
		items->DeserializeXml("data/test/items.xml");

		foreachi( i, items->Size() )
		{
			inventory.Add( &items->GetItem(i), 1 );
		}


		font.LoadFromFile("data/fonts/sansation.ttf", FSIZE);

		//gui.SetMagFilter(GL_LINEAR);
		//gui.SetMinFilter(GL_LINEAR);
		gui.LoadFromFile("data/textures/gui.png");

		Rect r(0,64,24,24);
		frame.SetFromSprite( Sprite(&gui, r) );
		frame.SetBackground( Sprite(&gui, Rect(0,0,64,64)) );
		frame.SetBackgroundOffset( 3.f );
		frame.SetPosition( Point(0,0) );
		frame.SetSize( Point(256,208) );
		frame.AddChild(&menu);

		menu.SetDefaultItemSize(Point(64, 16));
		menu.SetAutoItemLayout();
		menu.SetPosition(8,0);

		foreachi( i, inventory.Size() )
		{
			TextElement* w = new TextElement("", &font, AlignLeft );
			w->SetText( inventory[i].GetItem() ? inventory[i].GetItem()->GetName() : "" );
			w->AddChild( new TextElement( inventory[i].GetItem() ? fc::to_string(inventory[i].GetAmount()) : "" , &font, AlignRight ) );
			w->GetChild(0)->SetPosition(64,0);
			w->GetChild(0)->SetSize(64,16);
			menu.AddItem( w );
		}

	}

	virtual void Update()
	{
		frame.Update();
	}


	virtual void Render()
	{
		m_spriteBatch.Begin();

		frame.Render(&m_spriteBatch);

		m_spriteBatch.Render();
		m_spriteBatch.End();
	}


protected:
	MenuElement menu;
	Frame frame;
	Texture gui;
	Font font;

	ItemList* items;
	Inventory inventory;


	SpriteBatch m_spriteBatch;

};
*/


class TestScreen : public Screen
{
public:
};


