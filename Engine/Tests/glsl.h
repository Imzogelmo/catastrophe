
#pragma once

#include "Catastrophe/Graphics.h"

//
// Test custom GLSL Shaders
//
class GLSL_Test
{
public:
	Primitive p;
	float angle;
	float radius;

	VertexShader vs;
	FragmentShader fs;
	Shader* shader;

	GLSL_Test()
	{
		angle = 0.f;
		radius = 50.f;

		assert( vs.LoadFromFile("vs.vert") );
		assert( fs.LoadFromFile("fs.frag") );

		//now it logs internally
		//if( !vs.Compile() ) Log( vs.GetInfoLog().c_str() );
		//if( !fs.Compile() ) Log( fs.GetInfoLog().c_str() );

		shader = new Shader( &vs, &fs );
		if( !shader->Link() ) //will link automatically
		{
			Log(shader->GetInfoLog().c_str());
		}

		glDisable(GL_TEXTURE_2D);
		p.SetPrimitiveType( ptQUADS );
		p.SetBlendMode( BlendMode::Alpha );
		p.AddVertex( Vector2(320.f, 240.f), Color::White() );
		p.AddVertex( Vector2(370.f, 240.f), Color::Red() );
		p.AddVertex( Vector2(390.f, 290.f), Color::Beige() );
		p.AddVertex( Vector2(300.f, 270.f), Color::ForestGreen() );

	}

	~GLSL_Test()
	{
		vs.Dispose();
		fs.Dispose();
		shader->Dispose();
		delete shader;
	}

	void Update()
	{
		angle += 1.f;
	}

	void Render()
	{
		shader->SetUniform("angle", angle);
		shader->SetUniform("radius", radius);
		shader->Bind();
		p.Render();
		shader->Unbind();
	}

};

