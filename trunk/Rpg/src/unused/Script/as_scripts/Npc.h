
#define TILE_SIZE			16
#define TILE_SIZE_MASK		15



class Npc
{
	int direction;

	Npc()
	{
	}


	void UpdateMovement()
	{
		--walkCount;
		if( walkCount <= 0 )
			return;
	}

	void SnapToTileGrid()
	{
		int x = round(pos.x);
		int y = round(pos.y);
		x = x + (x & TILE_SIZE_MASK);
		y = y + (y & TILE_SIZE_MASK);
		pos = vec2(x, y);
	}






};

