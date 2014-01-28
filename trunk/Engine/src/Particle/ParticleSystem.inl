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

#include "Particle/ParticleSystem.h"
#include "IO/AttributeWriter.h"
#include "IO/AttributeReader.h"
#include "IO/XmlWriter.h"
#include "IO/XmlReader.h"


ParticleSystem::ParticleSystem() :
	m_groups(),
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

	for( group_vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		(*it)->ReleaseRef();
	}

	m_groups.clear();
}


size_t ParticleSystem::GetParticleCount() const
{
	size_t count(0);
	for( group_vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		count += (*it)->GetParticleCount();
	}

	return count;
}


void ParticleSystem::AddGroup( ParticleGroup* group )
{
	if(!group)
		return;

	group->AddRef();
	m_groups.push_back(group);
}


void ParticleSystem::RemoveGroup( ParticleGroup* group )
{
	if(!group)
		return;

	group_vec_type::iterator it = fc::find( m_groups.begin(), m_groups.end(), group );
	if( it != m_groups.end() )
	{
		(*it)->ReleaseRef();
		m_groups.erase(it);
	}
}
/*
{
	if(!group)
		return;

	group_vec_type::iterator it = fc::find( m_groups.begin(), m_groups.end(), group );
	if( it != m_groups.end() )
	{
		(*it)->Dispose();
		m_groups.erase(it);
	}
}
*/

void ParticleSystem::SetRenderer( ParticleRenderer* renderer )
{
	if(!renderer)
		return;

	//if(m_renderer)
	//	m_renderer->Dispose();

	m_renderer = renderer;
}


void ParticleSystem::Create( const Vector2& pos )
{
	for( group_vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		(*it)->Emit(pos);
	}
}


void ParticleSystem::Update()
{
	for( group_vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		(*it)->Update();
	}
}


void ParticleSystem::Render()
{
	if(!m_renderer)
		return;

	for( group_vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		m_renderer->Render(*it);
	}
}


void ParticleSystem::Render( SpriteBatch* spriteBatch )
{
	for( group_vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		(*it)->Render(spriteBatch);
	}
}


bool ParticleSystem::Serialize( const fc::string& filename )
{
	XmlWriter xml(filename);
	//if( !xml.IsOpen() )
	//	return false;

	xml.CreateRoot("ParticleSystem");
	xml.SetString("name", m_name);
	xml.SetUInt("num_groups", m_groups.size());
	for( group_vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		xml.BeginNode("ParticleGroup");
		(*it)->Serialize(&xml);
		xml.EndNode();
	}

	//xml.EndNode();
	xml.Close();

	return true;
}


bool ParticleSystem::Deserialize( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
		return false;

	if( xml.GetCurrentNodeName() == "ParticleSystem" )
	{
		DestroyGroups();

		while( xml.NextChild() )
		{
			if( xml.GetCurrentNodeName() == "ParticleGroup" )
			{
				ParticleGroup* particleGroup = new ParticleGroup();
				particleGroup->Deserialize(&xml);
			}
			else
			{
				Log("Error parsing (%s). expected [ParticleGroup]", filename.c_str());
			}
		}
	}
	else
	{
		Log("Error parsing (%s). Root item not found", filename.c_str());
		return false;
	}

	xml.Close();

	return true;
}


