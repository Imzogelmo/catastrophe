
#pragma once



class Battle : IGameEntity
{
	Battle()
	{
	}

	//gui
	//BattleStatus;
	//BattleCommand;


	//bool Victory(){}
	//bool Defeat(){}
	//bool Flee(){}
	//bool IsDone(){}

	void Setup()
	{
	}
/*
	void SetStartingPositions()
	{
		// figure out how many of each type of monster there are.
		int largeMonsters = 0;
		int smallMonsters = 0;
		int size = battle.enemy_count;
		foreachi(i, size)
		{
			@combatant enemy = battle.enemy[i];
			if( enemy.sprite.width > 32.f )
				++largeMonsters;
			else if( enemy.sprite.width > 32.f )
				small++;
		}

		int sX[9] = { 32, 32, 32, 64, 64, 64, 96, 96, 96 };
		int sY[9] = { 64, 32, 96, 64, 32, 96, 64, 32, 96 };
		int lX[4] = { 32, 32, 80, 80 };
		int lY[4] = { 32, 80, 32, 80 };

		if( large > 0)
		{
			foreachi( j, 9 )
				sX[j] += 48;

			if( small > 0 && large > 2 ) large = 2;

			if( large > 4 ) large = 4;
			if( small > 6 ) small = 6;
		}
		else
		{
			if( small > 9 ) small = 9;
		}
*/
	}
};

