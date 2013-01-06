

#include "main.h"

#include <crtdbg.h>
#include <Catastrophe/Util/Timer.h>
#include <Catastrophe/Sound/SoundEngine.h>
#include <Catastrophe/Sound/FmodSoundEngine.h>


#include "out.cpp"

Matrix createPerspectiveFOV( float& zoff, float fov, float aspectRatio, float up, float zNear, float zFar )
{
	float h = zNear * (1.f / tanf( fov / 2.f * CE_TO_RADIANS ));
	float w = h / aspectRatio;

	const float diff = zFar - zNear;
	const float q = -((zFar + zNear) / diff);
	const float z = -2.f * ( zNear * zFar ) / diff;

	if( up <= 0.f )
		h = -h;

	zoff = w / aspectRatio;
	zoff = h / aspectRatio;
	zoff = w / zNear;
	zoff = h / zNear;
	zoff = q / diff;
	zoff = q / diff;
	zoff = 1 / h;

	return Matrix
		(
			w,		0.0f,	0.0f,   0.0f,  
			0.0f,	h,		0.0f,   0.0f,  
			0.0f,	0.0f,   q,		-1.0f,  
			0.0f,	0.0f,   z,		0.0f
		);
}


void perspectiveOrthographicProjection
( double left, double right, double bottom, double top, double fovY, double zNear, double zFar,
												float &zoff )
	{
		const double DEGTORAD = (3.1415926535897932 / 180.0);
		//const double RADTODEG = (180.0 / 3.1415926535897932);


		const double aspectRatio = (right / bottom);

		//const double tangent = tan( (fovY * DEGTORAD) / 2.0 );
		const double tangent = tan( fovY / 2.0 * DEGTORAD );//* 2.0; //hmm...have to fix this
		double height = zNear * tangent;
		double width = height * aspectRatio;

		//double texelSize = (width * 2.0) / (right - left);
		double texelSize = (width) / (right - left);
		//double texelY = (height) / (bottom - top); //same...

		double z = 1.0 / texelSize;
		zoff = z;

		// get the texel size + distance from the near plane
		Vector2 outv = Vector2( (float)texelSize, (float)z );


		height = -height;
		//FrustumProjection( left, width, height, top, zNear, zFar );
		glFrustum( -width, width, -height, height, zNear, zFar );
	}


#include "hsv_wheel.h"
#include "splines.h"
#include "glsl.h"
#include "ui.h"

HSV_Test* hsvTest = 0;
Spline_Test* splineTest = 0;
GLSL_Test* glslTest = 0;
UI_Test* uiTest;

void init_tests()
{
	hsvTest = new HSV_Test();
	splineTest = new Spline_Test();
	glslTest = new GLSL_Test();
	uiTest = new UI_Test();
}

void do_tests()
{
	int num = 3;
	if(num == 0)
	{
		hsvTest->Update();
		hsvTest->Render();
	}
	else if(num == 1)
	{
		splineTest->Update();
		splineTest->Render();
	}
	else if(num == 2)
	{
		glslTest->Update();
		glslTest->Render();
	}
	else if(num == 3)
	{
		uiTest->Update();
		uiTest->Render();
	}

};

void end_tests()
{
	delete hsvTest;
	delete splineTest;
	delete glslTest;
	delete uiTest;

}



int main(int argc, char* argv[])
{
	//enable memory leak checking
	static int crtDebugflags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	crtDebugflags |= (crtDebugflags & 0x0000FFFF) | _CRTDBG_CHECK_ALWAYS_DF;
	_CrtSetDbgFlag(crtDebugflags);

	if(!System::Init()) exit(1);
	System::InitLogging("debug.log", true);
	Window* window = System::CreateWindow();
	if(!window->IsOpen()) exit(2);



	Texture tex;
	Image image;
	Font font;
	const char* fontName = "sansation.ttf";
	//const char* fontName = "fonts/final_fantasy_36.ttf";
	//const char* fontName = (const char*)__system_font_string_;
	//fc::string fontStr(fontName, fontName + 28912);
	if( font.LoadFromFile(fontName, 24) != 0 )
	//if( font.LoadFromFile(fontName, 24) != 0 )
		exit(9);

	/*
	font.SetAdvance(20);
	font.SetLineHeight(20);
	font.GetGlyph('i').translation.x += 3;
	font.GetGlyph('I').translation.x += 3;
	font.GetGlyph('j').translation.x += 3;
	font.GetGlyph('J').translation.x += 3;
	font.GetGlyph('f').translation.x += 2;
	font.GetGlyph('F').translation.x += 2;
	font.GetGlyph('t').translation.x += 2;
	font.GetGlyph('T').translation.x += 2;
*/
	if(!tex.LoadFromFile("tiles.png"))
	{
		int yfdg=0;
	}

	init_tests();

	Timer timer;

	PrimitiveObject prim;
	prim.SetPrimitiveType(ptQUADS);
	prim.AddVertex( Vector2(-100,-100), Color::Wheat() );
	prim.AddVertex( Vector2(500,-100), Color::Red() );
	prim.AddVertex( Vector2(500,500), Color::Green() );
	prim.AddVertex( Vector2(-100,500), Color::Blue() );
	
	prim.SetPosition(0.f);
	prim.SetScale(1.f);
	prim.SetAngle(0.f);

	SpriteBatch sb;

	AnimatedSprite sprite;
	sprite.SetTexture(&tex);
	sprite.SetFrameData( Rect(0,0,16,16), 64, 16, 0 );
	sprite.SetAnimationSpeed( 12.76f );
	sprite.SetSize( Vector2(32.f) );

float z = -10.00f;


fc::string textstr = "Hi \nweryuib\n dv fd efvbhfd sbhufidh bifndjsb fdsbhudfg sbhuifgudh \n"
"g y HBDVFGIEDBGVFRBED FRDV GRTG H YJH YJ J J JUJUJ    GBGF "
"h  HCBH  uhv VHDIVDn dvhdi324 546 76756 7";

MessageElement* text = new MessageElement();
text->SetFont(&font);
text->SetPosition( Point(64,64) );
text->SetSize(Point(400,256));
text->SetText(textstr);
text->SetColor(Color::LightBlue());

MenuElement menu;
TextElement te1("MenuItem1", &font); te1.SetPosition(Point(0,0));
TextElement te2("MenuItem2", &font); te2.SetPosition(Point(0,32));
TextElement te3("MenuItem3", &font); te3.SetPosition(Point(0,64));
TextElement te4("MenuItem4", &font); te4.SetPosition(Point(0,96));

menu.AddItem(&te1);
menu.AddItem(&te2);
menu.AddItem(&te3);
menu.AddItem(&te4);
menu.SetPosition(100,0);

	//test sound;
	FmodSoundEngine se;
	se.Initialize();
	//Sound* sound = se.LoadFromFile( Sound::TypeMidi, "wtcf2.mid" );
	Sound* sound = se.LoadFromFile( Sound::TypeStream, "DTA.mp3" );
	assert(sound);
	//sound->Play();

	while(!window->RequestClose())
	{
		window->ClearColor();
		window->Update();


		//glEnable( GL_DEPTH_TEST );
		glDisable(GL_TEXTURE_2D);
	//	prim.Render();
	//	prim2.Render();
	//	glEnable(GL_TEXTURE_2D);

		//glPopMatrix();

		sb.Begin();

		Keyboard* k = Input::GetKeyboard();
		if( k->IsKeyDown(KEY_X) )
		{
			sb.DrawString( &font, "KEY_X", Vector2(0.f, 0.f) );
			prim.SetAngle( prim.GetAngle() - 0.01745f );
		}
		if( k->IsKeyDown(KEY_C) )
		{
			sb.DrawString( &font, "KEY_C", Vector2(0.f, 0.f) );
			prim.SetAngle( prim.GetAngle() + 0.01745f );
		}
		if( k->IsKeyDown(KEY_A) )
		{
			sb.DrawString( &font, "KEY_A", Vector2(0.f, 0.f) );
			Vector2 _pos = prim.GetPosition(); _pos.x--;
			prim.SetPosition(_pos);
		}
		if( k->IsKeyDown(KEY_D) )
		{
			sb.DrawString( &font, "KEY_D", Vector2(0.f, 0.f) );
			Vector2 _pos = prim.GetPosition(); _pos.x++;
			prim.SetPosition(_pos);
		}
		if( k->IsKeyDown(KEY_W) )
		{
			sb.DrawString( &font, "KEY_W", Vector2(0.f, 0.f) );
			Vector2 _pos = prim.GetPosition(); _pos.y--;
			prim.SetPosition(_pos);
		}
		if( k->IsKeyDown(KEY_S) )
		{
			sb.DrawString( &font, "KEY_S", Vector2(0.f, 0.f) );
			Vector2 _pos = prim.GetPosition(); _pos.y++;
			prim.SetPosition(_pos);
		}
		if( k->IsKeyDown(KEY_Q) )
		{
			sb.DrawString( &font, "KEY_Q", Vector2(0.f, 0.f) );
			Vector2 _pos = prim.GetScale(); _pos-=0.02f;
			prim.SetScale(_pos);
		}
		if( k->IsKeyDown(KEY_Z) )
		{
			sb.DrawString( &font, "KEY_Z", Vector2(0.f, 0.f) );
			Vector2 _pos = prim.GetScale(); _pos+=0.02f;
			prim.SetScale(_pos);
		}

		sb.Render();
		sb.End();


		sb.Begin();
		//
	//	sb.Draw( tex.GetTextureID(),
	//		Rectf(0.f, 0.f, 128.f, 512.f),
	//		Rectf(0.f, 0.f, 1.f, 1.f)
	//		);
		//sb.Draw( tex.GetTextureID(),
		//	Rectf(-128.f, -512.f, 128.f, 512.f),
		//	Rectf(0.f, 0.f, 1.f, 1.f)
		//	);

		//sb.DrawSprite(sprite, Vector2(200.f));
	//	sprite.Update();

		//sb.DrawString( &font, "Test text CAPS. .. \n A newline?", Vector2(200.f, 0.f) );
	//	sb.DrawTexture(font.GetTexture(), Vector2(0.f));

		//

		//text->Update();
		//text->Render(&sb);
		//menu.Render(&sb);

		sb.Render();
		sb.End();

		static int _cnt = 0;
		_cnt++;
		//if(_cnt % 240 == 230)
		//	sound->Play();

		//sound->Stop();

		se.Update();
		glDisable(GL_TEXTURE_2D);
		do_tests();
/*
		glEnable(GL_TEXTURE_2D);
		sb.Begin();
		text->Update();
		text->Render(&sb);
		sb.Render();
		sb.End();
*/
Input::Update();

		//timer.Reset();
		//Log("start");
		window->Sleep(16);
		/*
		Log(" ticks %i, ms: %d, milli: %d, seconds %0.5f, minutes %0.5f, ",
			(int)timer.ElapsedTicks(),
			(int)timer.ElapsedMicroseconds(),
			(int)timer.ElapsedMilliseconds(),
			(float)timer.ElapsedSeconds(),
			(float)timer.ElapsedMinutes()
			);
		*/
		window->SwapBuffers();
	}

	end_tests();
	System::Terminate();


	se.Shutdown();
	delete text;
	//...
	_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    crtDebugflags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(crtDebugflags);

	return 0;
}

