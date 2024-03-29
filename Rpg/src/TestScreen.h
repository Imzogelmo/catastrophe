
#pragma once

#include "Screen.h"
#include "Game.h"
#include "MonsterData.h"

#include <fc/rand.h>
#include <Catastrophe/Graphics/OpenGL.h>
#include <Catastrophe/Graphics/Font.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/SpriteBatch.h>
#include <Catastrophe/Input.h>
#include <Catastrophe/Input/Input.h>
#include <Catastrophe/Gui.h>
#include <Catastrophe/Gui/MenuElement.h>
#include <Catastrophe/Gui/Label.h>
#include <Catastrophe/Gui/TextBox.h>
#include <Catastrophe/Gui/ListBox.h>
#include <Catastrophe/Gui/Frame.h>
#include <Catastrophe/Gui/BackgroundImage.h>
#include <Catastrophe/Math/Matrix.h>
#include <Catastrophe/Core/StringUtils.h>

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


#include "Catastrophe/Graphics/FBORenderTarget.h"

/*
class TestScreen : public Screen
{
public:
	Font f;

	FBORenderTarget rt;
	Texture rtTex;

	//Font f2[12];
	TextBox tb;
	SpriteBatch m_spriteBatch;

	TestScreen()
	{
		f.LoadFromFile("data/fonts/ff1_gba_font.png", 8);
	//	f.LoadFromFile("data/fonts/sansation.ttf", 12);
	//	f.GetTexture()->SaveToFile("fnt.png");
		tb.SetFont(&f);
		tb.SetText("Test of the \n emergency FONT system.");
		tb.SetSize(128,64);

		rtTex.SetFilterMode(0x2601);
		rtTex.CreateBlank(Color::ForestGreen(), 256, 224);
		rt.AttachTexture(&rtTex);
		foreachi(i, 8)
		{
			//f2[i].LoadFromFile("data/fonts/ff_7.ttf", 32 + i);
		}
	}

	void Update()
	{
		if( Input::GetKeyboard()->IsKeyPressed(KEY_T) )
			rtTex.SetFilterMode(0x2600);

		tb.Update();
	}

	void Render()
	{
		rt.Bind();

		m_spriteBatch.Begin();

		//tb.Render(&m_spriteBatch);
		m_spriteBatch.DrawString(&f, "ABCDEFGHIJKLmnopqrstuvwxyz\n<>':-+1234567890", Vector2(0, 0), Color(255,255,255,255));
		m_spriteBatch.DrawString(&f, "ABCDEFGHIJKLmnopqrstuvwxyz\n<>':-+1234567890", Vector2(0, 48), Color(255,255,255,255), AlignLeft, 16);
		m_spriteBatch.DrawString(&f, "ABCDEFGHIJKLmnopqrstuvwxyz\n<>':-+1234567890", Vector2(0, 128), Color(255,255,255,255), AlignLeft, 32);

		foreachi(i, 8)
		{
			//Vector2 pos_ = Vector2(0, (float)(i * 16 + 16));
			//m_spriteBatch.DrawString(&f2[i], "ABCDEFGHIJKLmnopqrstuvwxyz 1234567890", pos_);
		}


		//m_spriteBatch.Render( Matrix::CreateScale(Vector3(1,-1,1)) );
		m_spriteBatch.Render();
		m_spriteBatch.End();

		rt.Unbind();
		m_spriteBatch.Begin();
		m_spriteBatch.DrawTexture(rt.GetTexture(), 0.f);
		m_spriteBatch.Render();
		m_spriteBatch.End();
	}

};
*/


/*
// Test the BESTIARY
class TestScreen : public Screen
{
public:
	Font f;
	Texture frameTex;
	Texture bgTex;
	Sprite frameSprite;
	Sprite bgSprite;
	AnimatedSpriteSet curMonsterSprite;

	SpriteBatch m_spriteBatch;

	Widget mainMenu;
	Frame frame[3];
	Widget infoContainer;
	Label monsterName;

	Label attribNames[12];
	Label monsterStats[12];

	BackgroundImage bgImage;

	int curID;
	bool needsUpdate;

	TestScreen()
	{
		curID = 0;
		needsUpdate = true;

		f.LoadFromFile("data/fonts/ff1_gba_font.png", 8);
		bgTex.LoadFromFile("data/textures/gui.png");
		//bgTex.SetFilterMode(0x2601);

		frameSprite.Create( &bgTex, Rect(0,64,24,24) );
		bgSprite.Create( &bgTex, Rect(64,0,64,64) );

		bgImage.SetSize(256,224);
		bgImage.SetSprite( bgSprite );
		bgImage.SetAutoFitSprite(true);

		foreachi(i, 3) {
			frame[i].SetFromSprite(frameSprite);
			//frame[i].SetBackground(bgSprite);
		}

		monsterName.SetFont(&f);
		monsterName.SetPosition(12,12);
		monsterName.SetSize(20, 80);
		monsterName.SetTextAlignment(AlignCenter);
		frame[0].AddChild(&monsterName);

		frame[0].SetSize( 128, 32 );
		frame[1].SetSize( 128, 224 );
		frame[2].SetSize( 128, 32 );
		frame[0].SetPosition( 0, 0 );
		frame[1].SetPosition( 128, 0 );
		frame[2].SetPosition( 0, 224-32 );

		infoContainer.SetPosition(16,16);
		infoContainer.SetSize(frame[1].GetSize() - 32.f);

		const char* attr[12] = {
			"Defeated",
			"HP",
			"Attack",
			"Accuracy",
			"Defense",
			"Agility",
			"Intelligence",
			"Evasion",
			"Magic Defense",
			"Gil",
			"EXP",
			"Treasure"
		};

		foreachi(i, 12) {
			//TODO: Implement a default "skin" for all parent GUI objects to make these go away.
			attribNames[i].SetFont(&f);
			attribNames[i].SetText(attr[i]);
			monsterStats[i].SetFont(&f);
			monsterStats[i].SetColor( Color::Yellow() );
			monsterStats[i].SetTextAlignment(AlignRight);

			//TODO improve ListBox to easily handle this kind of crap.
			attribNames[i].SetPosition(0, i * 16);
			monsterStats[i].SetPosition(80, i * 16);

			attribNames[i].SetSize(80, 16);
			monsterStats[i].SetSize(20, 16);

			infoContainer.AddChild(&attribNames[i]);
			infoContainer.AddChild(&monsterStats[i]);
		}

		frame[1].AddChild(&infoContainer);

		mainMenu.AddChild(&bgImage);
		mainMenu.AddChild(&frame[0]);
		mainMenu.AddChild(&frame[1]);
		mainMenu.AddChild(&frame[2]);


	}

	void Update()
	{
		if( Input::GetKeyboard()->IsKeyPressed(KEY_LEFT) )
		{
			if( --curID < 0 )
				curID = 127;
			needsUpdate = true;
		}
		else if( Input::GetKeyboard()->IsKeyPressed(KEY_RIGHT) )
		{
			if( ++curID > 127 )
				curID = 0;
			needsUpdate = true;
		}

		if(needsUpdate)
		{
			needsUpdate = false;
			MonsterData* m = GetDatabase()->GetMonster(curID);
			ASSERT(m);
 
			AnimatedSpriteSetAsset* as = GetDatabase()->GetMonsterBattleSpriteSetAsset(m->battle_spriteset_id);
			bool isLoaded = as->LoadAnimatedSpriteSet(curMonsterSprite);
			ASSERT(isLoaded);

			int i(0);
			monsterName.SetText( m->name );
			monsterStats[i++].SetText("0");
			monsterStats[i++].SetText( ToString(m->attributes.max_params[0]) );
			monsterStats[i++].SetText( ToString(m->attributes.stats[0]) );
			monsterStats[i++].SetText( ToString(m->attributes.stats[2]) );
			monsterStats[i++].SetText( ToString(m->attributes.stats[1]) );
			monsterStats[i++].SetText( ToString(m->attributes.stats[3]) );
			monsterStats[i++].SetText( ToString(m->attributes.stats[4]) );
			monsterStats[i++].SetText( ToString(m->attributes.stats[3]) );
			monsterStats[i++].SetText( ToString(m->attributes.stats[5]) );

			monsterStats[i++].SetText( ToString(m->gold) );
			monsterStats[i++].SetText( ToString(m->exp) );
			monsterStats[i++].SetText(""); //treasure
		}

		mainMenu.Update();
		curMonsterSprite.Update();
	}

	void Render()
	{
		m_spriteBatch.Begin();

		// draw it
		mainMenu.Render(&m_spriteBatch);
		m_spriteBatch.DrawAnimatedSpriteSet( curMonsterSprite, Vector2(64,112) - (curMonsterSprite.size/2.f) );

		m_spriteBatch.Render();
		m_spriteBatch.End();

	}

};
*/


/*
class ItemListBox : public AbstractListBox
{
public:
	class Item
	{
	public:
		fc::string name;
		fc::string amount;

		void Render( SpriteBatch* spriteBatch, Font* f )
		{
			spriteBatch->DrawString(f, name, pos, Color::White(), AlignLeft );
			spriteBatch->DrawString(f, amount, pos + Vector2(80,0), Color::White(), AlignRight );
		}

	};

	typedef fc::vector_base<Item> vec_type;


	void Update()
	{
		Keyboard* k = Input::GetKeyboard();

		if( k->IsKeyPressed(KEY_LEFT) )
			MoveSelection(-1);
		else if( k->IsKeyPressed(KEY_RIGHT) )
			MoveSelection(1);
		else if( k->IsKeyPressed(KEY_UP) )
			MoveSelection(-2);
		else if( k->IsKeyPressed(KEY_DOWN) )
			MoveSelection(2);
	}

	void Render( SpriteBatch* spriteBatch )
	{
		spriteBatch->DrawString(
	}

	vec_type m_items;

};



class TestScreen : public Screen
{
public:
	Font f;
	Texture frameTex;
	Sprite frameSprite;
	Sprite bgSprite;

	SpriteBatch m_spriteBatch;

	Frame frame;
	BackgroundImage bgImage;
	TextBox tb;
	Texture t;

	ItemListBox l;


	TestScreen()
	{
		f.LoadFromFile("data/fonts/ff1_gba_font.png", 8);
		t.LoadFromFile("data/textures/gui.png");

		frameSprite.Create( &t, Rect(0,64,24,24) );
		bgSprite.Create( &t, Rect(0,0,64,64) );

		bgImage.SetSize(120,120);
		bgImage.SetSprite( bgSprite );
		bgImage.SetAutoFitSprite(true);
		frame.SetFromSprite(frameSprite);
		frame.SetSize(120,120);

		tb.SetFont(&f);
		tb.SetSize(120,120);
		tb.SetPosition(32,32);

		//tb.AddChild(&bgImage);
		//tb.AddChild(&frame);

		const char* text = "This is some text, blah blah... it should be auto formatted and junk! ..blah blah... 123456789.";
		tb.SetText(text);

	}

	void Update()
	{
		tb.Update();
	}

	void Render()
	{
		m_spriteBatch.Begin();

		// draw it
		tb.Render(&m_spriteBatch);

		m_spriteBatch.Render();
		m_spriteBatch.End();

	}

};

*/


class TestScreen : public Screen
{
	void Update()
	{
	}

	void Render()
	{
	}
};


