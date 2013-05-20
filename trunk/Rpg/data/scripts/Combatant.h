
#pragma once

// Required engine format. This cannot be changed.
#define CHARACTER_REQUIRED_FORMAT(base, obj, decl) \
	private obj decl; \
	base() { __internal_init_character__(decl); }


#define HP 0
#define MP 1

// stats ...misc???
#define STR				24 //strength
#define AGI				25 //agility
#define INT				26 //intelligence
#define VIT				27 //vitality
#define LUCK			28 //luck

#define ATK				0
#define DEF				1
#define HIT				2
#define EVADE			3
#define MAG_ATK			4
#define MAG_DEF			5
#define MAG_HIT			6
#define MAG_EVADE		7

// ...misc???
#define NUM_HITS		8
#define CRITICAL_RATE	9
#define MORALE			10



class Combatant
{
	// ~ Combatant ~
	// * Base class is implemented through composite inheritence.
	private combatant self;

	Combatant()
	{
		__internal_init_character(self);
	}

	//-------------------------------------
	// * BASE ATTRIBUTES
	//-------------------------------------
	int base_max_hp
	{
		get const
		{
			return self.base_max_param[HP];
		}
		set
		{
			self.base_max_param[HP] = value;
		}
	}

	int base_max_mp
	{
		get const
		{
			return self.base_max_param[MP];
		}
		set
		{
			self.base_max_param[MP] = value;
		}
	}

	int base_hp
	{
		get const
		{
			return self.base_param[HP];
		}
		set
		{
			self.base_param[HP] = value;
		}
	}

	int base_mp
	{
		get const
		{
			return self.base_param[MP];
		}
		set
		{
			self.base_param[MP] = value;
		}
	}

	int base_atk
	{
		get const
		{
			return self.base_stat[ATK];
		}
		set
		{
			self.base_stat[ATK] = value;
		}
	}

	int base_def
	{
		get const
		{
			return self.base_stat[DEF];
		}
		set
		{
			self.base_stat[DEF] = value;
		}
	}

	int base_hit
	{
		get const
		{
			return self.base_stat[HIT];
		}
		set
		{
			self.base_stat[HIT] = value;
		}
	}

	int base_evade
	{
		get const
		{
			return self.base_stat[EVADE];
		}
		set
		{
			self.base_stat[EVADE] = value;
		}
	}

	int base_mag_atk
	{
		get const
		{
			return self.base_stat[MAG_ATK];
		}
		set
		{
			self.base_stat[MAG_ATK] = value;
		}
	}

	int base_mag_def
	{
		get const
		{
			return self.base_stat[MAG_DEF];
		}
		set
		{
			self.base_stat[MAG_DEF] = value;
		}
	}

	int base_mag_hit
	{
		get const
		{
			return self.base_stat[MAG_HIT];
		}
		set
		{
			self.base_stat[MAG_HIT] = value;
		}
	}

	int base_mag_evade
	{
		get const
		{
			return self.base_stat[MAG_EVADE];
		}
		set
		{
			self.base_stat[MAG_EVADE] = value;
		}
	}

	int base_critical_rate
	{
		get const
		{
			return self.base_stat[CRITICAL_RATE];
		}
		set
		{
			self.base_stat[CRITICAL_RATE] = value;
		}
	}

	//-------------------------------------
	// * ATTRIBUTES
	//-------------------------------------
	int max_hp
	{
		get const
		{
			return self.max_param[HP];
		}
	}

	int max_mp
	{
		get const
		{
			return self.max_param[MP];
		}
	}

	int hp
	{
		get const
		{
			return self.param[HP];
		}
	}

	int mp
	{
		get const
		{
			return self.param[MP];
		}
	}

	int atk
	{
		get const
		{
			return self.stat[ATK];
		}
	}

	int def
	{
		get const
		{
			return self.stat[DEF];
		}
	}

	int hit
	{
		get const
		{
			return self.stat[HIT];
		}
	}

	int evade
	{
		get const
		{
			return self.stat[EVADE];
		}
	}

	int mag_atk
	{
		get const
		{
			return self.stat[MAG_ATK];
		}
	}

	int mag_def
	{
		get const
		{
			return self.stat[MAG_DEF];
		}
	}

	int mag_hit
	{
		get const
		{
			return self.stat[MAG_HIT];
		}
	}

	int mag_evade
	{
		get const
		{
			return self.stat[MAG_EVADE];
		}
	}

	int critical_rate
	{
		get const
		{
			return self.stat[CRITICAL_RATE];
		}
	}













	//////////////////////////////////////////
	vec2 pos
	{
		get const
		{
			return self.pos;
		}
		set
		{
			self.pos = value;
		}
	}

	vec2 GetCenter()
	{
		return self.pos + self.spriteset.size / 2f;
	}



};



