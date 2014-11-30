// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "../Particle.h"
#include "../ParticleSystemEntity.h"

#include <fc/rand.h>
#include <fc/math.h>



class ParticleEmitter : public ParticleSystemEntity
{
public:
	ParticleEmitter();
	ParticleEmitter(
		float minLife,
		float maxLife,
		float minSpeed,
		float maxSpeed,
		float minFriction,
		float maxFriction,
		float minAngle,
		float maxAngle,
		float minRotationSpeed,
		float maxRotationSpeed,
		const Vector2& minSize,
		const Vector2& maxSize,
		const Vector2& minEndScale,
		const Vector2& maxEndScale,
		const Color& minColor,
		const Color& maxColor
	);

	virtual ~ParticleEmitter() {}

	virtual void ValidateAttributes();
	virtual void SetMinLife( float minLife );
	virtual void SetMaxLife( float maxLife );
	virtual void SetMinSpeed( float minSpeed );
	virtual void SetMaxSpeed( float maxSpeed );
	virtual void SetMinFriction( float minFriction );
	virtual void SetMaxFriction( float maxFriction );
	virtual void SetMinAngle( float minAngle );
	virtual void SetMaxAngle( float maxAngle );
	virtual void SetMinRotationSpeed( float minSpeed );
	virtual void SetMaxRotationSpeed( float maxSpeed );
	virtual void SetMinSize( const Vector2& minSize );
	virtual void SetMaxSize( const Vector2& maxSize );
	virtual void SetMinEndScale( const Vector2& minScale );
	virtual void SetMaxEndScale( const Vector2& maxScale );
	virtual void SetMinColor( const Color& minColor );
	virtual void SetMaxColor( const Color& maxColor );
	virtual void SetGenerateParticleAngle( bool enable );

	virtual float GetMinLife() const { return m_minLife; }
	virtual float GetMaxLife() const { return m_maxLife; }
	virtual float GetMinSpeed() const { return m_minSpeed; }
	virtual float GetMaxSpeed() const { return m_maxSpeed; }
	virtual float GetMinFriction() const { return m_minFriction; }
	virtual float GetMaxFriction() const { return m_maxFriction; }
	virtual float GetMinAngle() const { return m_minAngle; }
	virtual float GetMaxAngle() const { return m_maxAngle; }
	virtual float GetMinRotationSpeed() const { return m_minRotationSpeed; }
	virtual float GetMaxRotationSpeed() const { return m_maxRotationSpeed; }
	virtual const Vector2& GetMinSize() const { return m_minSize; }
	virtual const Vector2& GetMaxSize() const { return m_maxSize; }
	virtual const Vector2& GetMinEndScale() const { return m_minEndScale; }
	virtual const Vector2& GetMaxEndScale() const { return m_maxEndScale; }
	virtual const Color& GetMinColor() const { return m_minColor; }
	virtual const Color& GetMaxColor() const { return m_maxColor; }
	virtual bool GetGenerateParticleAngle() const { return m_generateParticleAngle; }

	/// Initializes basic particle values : life, size, and color.
	virtual void GenerateInitialValues( Particle* particles, u32 count );

	/// Emits 'count' particles from this emitter at pos.
	virtual void Emit( const Vector2& pos, Particle* particles, u32 count );

	virtual void Serialize( AttributeWriter* out );
	virtual void Deserialize( AttributeReader* in );

protected:
	float			m_minLife;
	float			m_maxLife;
	float			m_minSpeed;
	float			m_maxSpeed;
	float			m_minFriction;
	float			m_maxFriction;
	float			m_minAngle;
	float			m_maxAngle;
	float			m_minRotationSpeed;
	float			m_maxRotationSpeed;
	Vector2			m_minSize;
	Vector2			m_maxSize;
	Vector2			m_minEndScale;
	Vector2			m_maxEndScale;
	Color			m_minColor;
	Color			m_maxColor;

	bool			m_generateParticleAngle;
	bool			m_hasScaleFactor;
	bool			m_hasSizeVariation;
	bool			m_hasScaleVariation;
	bool			m_hasColorVariation;

};

