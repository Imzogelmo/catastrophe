
#pragma once

#include "Catastrophe/Graphics.h"


// Draw a color wheel using HSL and a primitive object.
//
// @Tests: primitive arrays, color conversion, primitive rendering, matrix tranformations.
//
class HSV_Test
{
public:
	PrimitiveObject p;
	float a; //angle, in radians

	HSV_Test()
	{
		a = 0.f;
		glDisable(GL_TEXTURE_2D);

		p.SetPrimitiveType( ptTRIANGLE_FAN );
		p.SetBlendMode( BlendMode::Alpha );
		p.Reserve( 362 );
		p.AddVertex( Vector2(320.f, 240.f), Color::White() ); //center of the fan.

		for( float i(0.f); i <= 360.f; i += 0.5f )
		{
			//HSLColor hsl = HSLColor(i, 1.f, 1.f, 1.f); //there's a bug with hsl.
			HSVColor hsv = HSVColor(i, 1.f, 1.f, 1.f);
			Color color = hsv.ToColor();

			p.AddVertex( Vector2(320,240).Polar(240.f, -Math::ToRadians(i)), color );
		}
	}

	void Update()
	{
		a += 0.01745f; 
		p.SetAngle(a);
	}

	void Render()
	{
		p.Render();
	}

};






