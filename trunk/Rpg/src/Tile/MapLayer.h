
#pragma once

#include <fc/dynamic_array2d.h>


class MapLayer
{
public:
	typedef fc::dynamic_array2d<Tile*> array_type;

	MapLayer( Map* parent = 0 );

	bool IsVisible() const { return m_visible; }
	void SetVisible( bool enable = true ) { m_visible = enable; }


	Color GetColor() const { return m_color; }
	void SetColor( const Color& color ) { m_color = color; }

	void Resize( size_t w, size_t h );

	size_t Size() const { return m_tiles.size(); }
	size_t Width() const { return m_tiles.x(); }
	size_t Height() const { return m_tiles.y(); }

	Tile* GetTile(size_t x, size_t y) const { return m_tiles.at(y, x); }

	void SetMap( Map* map ) { m_map = map; }
	Map* GetMap() { return m_map; }

	array_type& GetTileArray() { return m_tiles; }
	const array_type& GetTileArray() const { return m_tiles; }

	void Update();
	void Render();

protected:
	Map*		m_map;
	array_type	m_tiles;
	BlendMode	m_blendmode;
	//float		m_opacity; //why stop at opacity only?
	Color		m_color;
	//ubyte		m_opacityBytes;
	//Point		m_offset;
	bool		m_visible;
	//bool		m_parallax;

};

