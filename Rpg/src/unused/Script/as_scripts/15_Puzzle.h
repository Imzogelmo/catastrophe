

const int PIECE_TILE = 100;


class _15_Puzzle_
{
	array<int> piece;
	//int piece[16];
	int selected;
	int pm_dir;


	void update()
	{
		Init15();

		UpdateInput();
		KeepTime();

		RenderBoard15();
		if( IsComplete15() ) 
		{
			Init15();
		}
	}


	void UpdateInput()
	{
		if( input.press(UP) )
		{
			if( selected - 4 < 0 ) selected += 12;
			else selected -= 4;
		}
		if( input.press(DOWN) )
		{
			if( selected + 4 > 15 ) selected -= 12;
			else selected += 4;
		}
		if( input.press(LEFT) )
		{
			if( selected % 4 == 0 ) selected += 3;
			else selected -= 1;
		}
		if( input.press(RIGHT) )
		{
			if( selected % 4 == 3) selected -= 3;
			else selected += 1;
		}

		if( input.press(A) )
			MovePiece();
	}

	void Init15()
	{
		InitClock();
		
		piece[15] = 0;
		for( int i = 0; i < 15; i++ )
			piece[i] = i + 1;
			
		selected = 0;
		int loop = 0;
		while( loop < 15000 )
		{
			loop = Randomize15( loop );
		}
	}


	int Randomize15( int loop )
	{
		int r;
		if( piece[0] == 0 ) r = 1 << ( Rand(2) * 2 );
		else if( piece[3] == 0 ) r = 2 + ( Rand(2) * 5 );
		else if( piece[12] == 0 ) r = 8 + ( Rand(2) * 5 );
		else if( piece[15] == 0 ) r = 11 + ( Rand(2) * 3 );
		else r = Rand(16);
		
		int v = Move15( r, 1, 4 );
		if ( v != -1 && IsInRow15( r, v ) )
		{
			Swap15( r, v );
		}

		return loop + 1;
	}

	void InitClock()
	{
		global_timer = 0;
		seconds = 0;
		minutes = 0;
	}


	int Move15( int i, int x, int y )
	{
		if( i - x >= 0 ) 
			if( piece[ i - x ] == 0 )
			{
				pm_dir = 2;
				return i - x;
			}
		if( i + x < 16 )
			if( piece[ i + x ] == 0 )
			{
				pm_dir = 3;
				return i + x;
			}
		if( i - y >= 0 ) 
			if( piece[ i - y ] == 0 )
			{
				pm_dir = 0;
				return i - y;
			}
		if( i + y < 16 )
			if( piece[ i + y ] == 0 )
			{
				pm_dir = 1;
				return i + y;
			}
		return -1;
	}


	int Swap15( int p1, int p2 )
	{
		int tmp = piece[ p1 ];
		piece[ p1 ] = piece[ p2 ];
		piece[ p2 ] = tmp;
	}


	bool IsInRow15( int source, int n )
	{
		if( source < 4 )
		{
			if( pm_dir > 1 ) return ( n < 4 );
			else return ( ( n % 4 ) == source );
		}
		else if( source < 8 )
		{
			if( pm_dir > 1 ) return ( n > 3 && n < 8 );
			else return ( ( n % 4 ) == ( source - 4 ) );
		}
		else if( source < 12 )
		{
			if( pm_dir > 1 ) return ( n > 7 && n < 12 );
			else return ( ( n % 4 ) == ( source - 8 ) );
		}
		else
		{
			if( pm_dir > 1 ) return ( n > 11 );
			else return ( ( n % 4 ) == ( source - 12 ) );
		}
		return false;
	}


	void MovePiece15()
	{
		int v = Move15( selected, 1, 4 );
		if ( v != -1 && IsInRow15( selected, v ) )
		{
			Swap15( selected, v );
			return;
		}
		// No good? Let's try and move up to a whole row then.
		v = Move15( selected, 2, 8 );
		if ( v != -1  && IsInRow15( selected, v ) )
		{
			if( pm_dir == 0 ) Swap15( selected - 4, v );
			else if( pm_dir == 1 ) Swap15( selected + 4, v );
			else if( pm_dir == 2 ) Swap15( selected - 1, v );
			else if( pm_dir == 3 ) Swap15( selected + 1, v );
			MovePiece15();
			return;
		}
		v = Move15( selected, 3, 12 );
		if ( v != -1  && IsInRow15( selected, v ) )
		{
			if( pm_dir == 0 ) Swap15( selected - 8, v );
			else if( pm_dir == 1 ) Swap15( selected + 8, v );
			else if( pm_dir == 2 ) Swap15( selected - 2, v );
			else if( pm_dir == 3 ) Swap15( selected + 2, v );
			MovePiece15();
			return;
		}
	}


	int PieceElement( int row, int column )
	{
		return ( row + ( column * 4 ) );
	}


	bool IsComplete15()
	{
		int complete = 0;
		if( piece[15] == 0 )
		{
			for( int j; j < 15; j++ )
				if( piece[j] == j + 1 ) 
					complete++;
		}
		return ( complete == 15 );
	}


	int getY15( int i )
	{
		if( i < 4 ) return 0;
		else if( i < 8 ) return 1;
		else if( i < 12 ) return 2;
		return 3;
	}


	void RenderBoard15()
	{
		int x_off = 64;
		int y_off = 32;
		
		// Draw the border
		Screen->Rectangle( 5, x_off-1, y_off-1, x_off + 65, y_off + 65, 15, 1, 0, 0, 0, false, 128 );
		
		for( int i = 0; i < 4; i++ )
			for( int j = 0; j < 4; j++ )
				Screen->DrawTile( 5, ( i * 16 ) + x_off, ( j * 16 ) + y_off, 
									PIECE_TILE + piece[ PieceElement( i, j ) ], 
									1, 1, 0, -1, -1, 0, 0, 0, 0, true, 128 );
		// Draw the cursor
		Screen->Rectangle( 6, x_off + (( selected % 4 ) * 16), y_off + ( getY15( selected ) * 16 ), 
							16 + x_off + (( selected % 4 ) * 16), 16 + y_off + ( getY15( selected ) * 16 ), 
							15, 1, 0, 0, 0, true, 64 );
		
		// Draw the timer
		int str[1] = ":";
		if( minutes < 10  )
		{
			Screen->DrawInteger( 6, x_off, 8, 0, 10, 1, -1, -1, 0, 0, 128 );
			Screen->DrawInteger( 6, x_off + 8 , 8, 0, 15, 1, -1, -1, minutes, 0, 128 );
		}
		else Screen->DrawInteger( 6, x_off, 8, 0, 15, 1, -1, -1, minutes, 0, 128 );
		if( seconds < 10  )
		{
			Screen->DrawInteger( 6, x_off + 20, 8, 0, 10, 1, -1, -1, 0, 0, 128 );
			Screen->DrawInteger( 6, x_off + 28, 8, 0, 15, 1, -1, -1, seconds, 0, 128 );
		}
		else Screen->DrawInteger( 6, x_off + 20, 8, 0, 15, 1, -1, -1, seconds, 0, 128 );
		if( ( global_timer % 60 ) < 10 )
		{
			Screen->DrawInteger( 6, x_off + 40, 8, 0, 15, 1, -1, -1, 0, 0, 128 );
			Screen->DrawInteger( 6, x_off + 48, 8, 0, 15, 1, -1, -1, global_timer * 1.6, 0, 128 );
		}
		else Screen->DrawInteger( 6, x_off + 40, 8, 0, 15, 1, -1, -1, global_timer * 1.6, 0, 128 );
		
		Screen->DrawCharacter(	6, x_off + 14, 8, 0, 12, -1, -1, -1, str[0], 64 );
		Screen->DrawCharacter(	6, x_off + 35, 8, 0, 12, -1, -1, -1, str[0], 64 );
	}


};

