
#pragma once

//#include <fc/type_traits.h>


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
	int		id;

	Tile( Tileset* parent = 0 ) :
		//tint(Color::White()),
		flags(0), id(0),
		m_parent(parent)
	{
	}

	//void Update() { animation.Update(); }
	void SetTileset(Tileset* parent) { m_parent = parent; }
	void SetIndex(int index) { id = index; }

	Tileset* GetTileset() const { return m_parent; }
	int GetIndex() { return id; }

protected:
	Tileset* m_parent;

};

