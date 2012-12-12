
#pragma once

#include "../Common.h"
#include <Catastrophe/Graphics/Animation.h>


//Maybe split this into two tile classes: one for animated..? (memory vs performance cost?)
class Tile : public Animation
{
public:
	enum TileFlags
	{
		FlipHorizontal	= 1,
		FlipVertical	= 2
	};

	//Animation	animation;
	//Color	tint;
	int		flags;

	Tile( Tileset* parent = 0 ) :
		//tint(Color::White()),
		flags(0), m_id(0),
		m_parent(parent)
	{
	}

	//void Update() { animation.Update(); }
	void SetTileset(Tileset* parent) { m_parent = parent; }
	void SetIndex(size_t index) { m_id = index; }

	Tileset* GetTileset() const { return m_parent; }
	size_t GetIndex() { return m_id; }

protected:
	Tileset*	m_parent;
	size_t		m_id;

};

