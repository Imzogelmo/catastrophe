
#pragma once

#include "Character.h"


#define FIGHTER		0
#define KNIGHT		1
#define THIEF		2
#define NINJA		3
#define BLACK_BELT	4
#define MASTER		5
#define RED_MAGE	6
#define RED_WIZ		7
#define WHITE_MAGE	8
#define WHITE_WIZ	9
#define BLACK_MAGE	10
#define BLACK_WIZ	11


#define FI		FIGHTER
#define TH		THIEF
#define BB		BLACK_BELT
#define RM		RED_MAGE
#define WM		WHITE_MAGE
#define BM		BLACK_MAGE
#define KN		KNIGHT
#define NI		NINJA
#define MA		MASTER
#define RW		RED_WIZ
#define WW		WHITE_WIZ
#define BW		BLACK_WIZ


#define FIGHTER_FLAG	0x0001
#define KNIGHT_FLAG		0x0002
#define THIEF_FLAG		0x0004
#define NINJA_FLAG		0x0008
#define BLACK_BELT_FLAG	0x0010
#define MASTER_FLAG		0x0020
#define RED_MAGE_FLAG	0x0040
#define RED_WIZ_FLAG	0x0080
#define WHITE_MAGE_FLAG	0x0100
#define WHITE_WIZ_FLAG	0x0200
#define BLACK_MAGE_FLAG	0x0400
#define BLACK_WIZ_FLAG	0x0800
#define CLASS_FLAG_ALL	0xFFFF




class Fighter : Character
{
	Fighter()
	{
		//SetStartingStats( 35, 0, 20, 5, 1, 5, 5, 10, 10 );
	}

	void LevelUp()
	{
		//return LevelUpFighter(self.actor);
	}
}


class Thief : Character
{
	Thief()
	{
		//SetStartingStats( 30, 0, 5, 10, 5, 5, 15, 5, 15 );
	}

	void LevelUp()
	{
		//return LevelUpThief(self.actor);
	}
}


class BlackBelt : Character
{
	BlackBelt()
	{
		//SetStartingStats( 33, 0, 5, 5, 5, 20, 5, 5, 10 );
	}

	void LevelUp()
	{
		//return LevelUpBlackBelt(self.actor);
	}
}


class RedMage : Character
{
	RedMage()
	{
		//SetStartingStats( 30, 10, 10, 10, 10, 5, 5, 7, 20 );
	}

	void LevelUp()
	{
		//return LevelUpRedMage(self.actor);
	}
}


class WhiteMage : Character
{
	WhiteMage()
	{
		//SetStartingStats( 28, 10, 5, 5, 15, 10, 5, 5, 25 );
	}

	void LevelUp()
	{
		//return LevelUpWhiteMage(self.actor);
	}
}


class BlackMage : Character
{
	BlackMage()
	{
		//SetStartingStats( 25, 10, 1, 10, 20, 1, 10, 5, 25 );
	}

	void LevelUp()
	{
		//return LevelUpBlackMage(self.actor);
	}
}


class BlueMage : Character
{
	BlueMage()
	{
		//SetStartingStats( 30, 10, 5, 5, 10, 5, 5, 5, 20 );
	}

	void LearnEnemySkill()
	{
	}

	void LevelUp()
	{
		//return LevelUpBlueMage(self.actor);
	}
}



