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


#include "Particle/Particle.h"
#include "Particle/ParticleManager.h"
#include "Particle/Emitters/ParticleEmitter.h"
#include "Particle/Modifiers/ParticleModifier.h"

//renderers
//#include "Renderers/SpriteBatchRenderer.inl"



void ParticleManager::AddSystem( ParticleSystem* system )
{
	if(!system)
		return;

//	map_type::iterator it = m_systems.find( effect->GetString() );
//	if( it != m_systems.end() )
	{
		//m_systems...
		//it->second = effect;
	}
}


size_t ParticleManager::GetParticleCount()
{
	size_t count = 0;
	for( map_type::iterator it = m_systems.begin(); it != m_systems.end(); ++it )
	{
		count += it->second->GetParticleCount();
	}

	return count;
}


void ParticleManager::Update()
{
	for( map_type::iterator it = m_systems.begin(); it != m_systems.end(); ++it )
	{
		it->second->Update();
	}
}


void ParticleManager::Render()
{
	for( map_type::iterator it = m_systems.begin(); it != m_systems.end(); ++it )
	{
		it->second->Render();
	}
}


void ParticleManager::Serialize( AttributeWriter* out )
{
}


void ParticleManager::Deserialize( AttributeReader* in )
{
}


