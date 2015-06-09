// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// f the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included f
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Particle/ParticleSystem.h"
#include "Core/IO/AttributeWriter.h"
#include "Core/IO/AttributeReader.h"
#include "Core/IO/XmlWriter.h"
#include "Core/IO/XmlReader.h"


ParticleSystem::ParticleSystem() :
	m_particleGroups(),
	m_renderer(0)
{
}


ParticleSystem::~ParticleSystem()
{
	DestroyGroups();
}


void ParticleSystem::DestroyGroups()
{
	//m_renderer->Dispose();

	for(Vector<ParticleGroup*>::Iterator it = m_particleGroups.begin(); it != m_particleGroups.end(); ++it)
	{
		(*it)->ReleaseRef();
	}

	m_particleGroups.Clear();
}


u32 ParticleSystem::GetParticleCount() const
{
	u32 count(0);
	for(const ParticleGroup* const* it = m_particleGroups.begin(); it != m_particleGroups.end(); ++it)
		count += (*it)->GetParticleCount();

	return count;
}


void ParticleSystem::AddGroup(ParticleGroup* particleGroup)
{
	if(!particleGroup)
		return;

	particleGroup->AddRef();
	m_particleGroups.Add(particleGroup);
}


void ParticleSystem::RemoveGroup(ParticleGroup* particleGroup)
{
	if(particleGroup != null)
	{
		particleGroup->ReleaseRef();
		m_particleGroups.RemoveValue(particleGroup);
	}
}


void ParticleSystem::SetRenderer(ParticleRenderer* renderer)
{
	if(!renderer)
		return;

	//if(m_renderer)
	//	m_renderer->Dispose();

	m_renderer = renderer;
}


void ParticleSystem::Create(const Vector2& position)
{
	for(ParticleGroup** it = m_particleGroups.begin(); it != m_particleGroups.end(); ++it)
	{
		(*it)->Emit(position);
	}
}


void ParticleSystem::Update()
{
	for(ParticleGroup** particleGroup = m_particleGroups.begin(); particleGroup != m_particleGroups.end(); ++particleGroup)
	{
		(*particleGroup)->Update();
	}
}


void ParticleSystem::Render()
{
	if(!m_renderer)
		return;

	for(ParticleGroup** particleGroup = m_particleGroups.begin(); particleGroup != m_particleGroups.end(); ++particleGroup)
	{
		m_renderer->Render(*particleGroup);
	}
}


void ParticleSystem::Render(SpriteBatch* spriteBatch)
{
	for(ParticleGroup** particleGroup = m_particleGroups.begin(); particleGroup != m_particleGroups.end(); ++particleGroup)
	{
		(*particleGroup)->Render(spriteBatch);
	}
}


bool ParticleSystem::Serialize(const String& filename)
{
	XmlWriter xml(filename);
	//if( !xml.IsOpen() )
	//	return false;

	xml.CreateRoot("ParticleSystem");
	xml.SetString("name", m_name);
	xml.SetAttribute("num_groups", m_particleGroups.Size());
	for(ParticleGroup** it = m_particleGroups.begin(); it != m_particleGroups.end(); ++it)
	{
		xml.BeginNode("ParticleGroup");
		(*it)->Serialize(&xml);
		xml.EndNode();
	}

	//xml.EndNode();
	xml.Close();

	return true;
}


bool ParticleSystem::Deserialize(const String& filename)
{
	XmlReader xml(filename);
	if(!xml.IsOpen())
		return false;

	if(xml.GetCurrentNodeName() == "ParticleSystem")
	{
		DestroyGroups();

		while(xml.NextChild())
		{
			if(xml.GetCurrentNodeName() == "ParticleGroup")
			{
				ParticleGroup* particleGroup = new ParticleGroup();
				particleGroup->Deserialize(&xml);
			}
			else
			{
				Log("Error parsing (%s). expected [ParticleGroup]", filename.CString());
			}
		}
	}
	else
	{
		Log("Error parsing (%s). Root item not found", filename.CString());
		return false;
	}

	xml.Close();

	return true;
}


