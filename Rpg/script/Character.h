
#pragma once

// Required engine format. This cannot be changed.
#define CHARACTER_REQUIRED_FORMAT(base, obj, decl) \
	private obj decl; \
	base() { __internal_init_character(decl); }

//todo:
#define TODO 0
#define MAX_HP 0
#define MAX_MP 0
#define HP 0
#define MP 0
#define LV 0

// stats
#define STR				24 //strength
#define AGI				25 //agility
#define INT				26 //intelligence
#define VIT				27 //vitality
#define LUCK			28 //luck

#define ATK				8
#define DEF				9
#define HIT				10
#define EVADE			11
#define MAG_ATK			12
#define MAG_DEF			13
#define MAG_HIT			14
#define MAG_EVADE		15

#define NUM_HITS		16
#define CRITICAL_RATE	17
#define MORALE			18

// Player States
#define ps_IDLE				0 // Not doing anything.
#define ps_INPUT			1 // Waiting for player to input commands.
#define ps_PREPARE_ATTACK	2 // Preparing to attack.
#define ps_ATTACK			3 // Attacking.
#define ps_PREPARE_CAST		4 // Preparing to cast a spell.
#define ps_CAST				5 // Casting a spell.
#define ps_PREPARE_ITEM		6 // Preparing to use an item.
#define ps_ITEM				7 // Using an item.
#define ps_DEAD				16 // Dead.
#define ps_STONE			17 // Turned to stone.
#define ps_WEAK				0x0100 // Flag | Player is in the kneel position.
#define ps_MOVE_ACTION		0x1000 // Flag | Player is moving to action position.
#define ps_MOVE_HOME		0x2000 // Flag | Player is moving to home position.
#define ps_DAMAGED			0x4000 // Flag | Player is taking damage.



class CharacterBase
{
	// ~ CharacterBase ~
	// * Base class is implemented through composite inheritence.
	private character parent;

	CharacterBase()
	{
		__internal_init_character(parent);
	}

	//-------------------------------------
	// * Statistics
	//-------------------------------------
	int get_stat(int i) const
	{
		return parent.attributes.stat[i];
	}

	int set_stat(int i, int value)
	{
		parent.attributes.stat[i] = value;
	}

	//-------------------------------------
	// * Strength
	//-------------------------------------
	int strength
	{
		get const
		{
			return parent.attributes.stat[STR];
		}
		set
		{
			parent.attributes.stat[STR] = value;
		}
	}

	//-------------------------------------
	// * Agility
	//-------------------------------------
	int agility
	{
		get const
		{
			return parent.attributes.stat[AGI];
		}
		set
		{
			parent.attributes.stat[AGI] = value;
		}
	}

	//-------------------------------------
	// * Int
	//-------------------------------------
	int intelligence
	{
		get const
		{
			return parent.attributes.stat[INT];
		}
		set
		{
			parent.attributes.stat[INT] = value;
		}
	}

	//-------------------------------------
	// * Vitality
	//-------------------------------------
	int vitality
	{
		get const
		{
			return parent.attributes.stat[VIT];
		}
		set
		{
			parent.attributes.stat[VIT] = value;
		}
	}

	//-------------------------------------
	// * Luck
	//-------------------------------------
	int luck
	{
		get const
		{
			return parent.attributes.stat[LUCK];
		}
		set
		{
			parent.attributes.stat[LUCK] = value;
		}
	}

	//-------------------------------------
	// * Max HP
	//-------------------------------------
	int max_hp
	{
		get const
		{
			return parent.attributes.stat[MAX_HP];
		}
		set
		{
			parent.attributes.stat[MAX_HP] = value;
		}
	}

	//-------------------------------------
	// * Max MP
	//-------------------------------------
	int max_mp
	{
		get const
		{
			return parent.attributes.stat[MAX_MP];
		}
		set
		{
			parent.attributes.stat[MAX_MP] = value;
		}
	}

	//-------------------------------------
	// * HP
	//-------------------------------------
	int hp
	{
		get const
		{
			return parent.attributes.stat[HP];
		}
		set
		{
			parent.attributes.stat[HP] = value;
		}
	}

	//-------------------------------------
	// * MP
	//-------------------------------------
	int mp
	{
		get const
		{
			return parent.attributes.stat[MP];
		}
		set
		{
			parent.attributes.stat[MP] = value;
		}
	}

	//-------------------------------------
	// * ATK
	//-------------------------------------
	int atk
	{
		get const
		{
			return parent.attributes.stat[ATK];
		}
		set
		{
			parent.attributes.stat[ATK] = value;
		}
	}

	//-------------------------------------
	// * DEF
	//-------------------------------------
	int def
	{
		get const
		{
			return parent.attributes.stat[DEF];
		}
		set
		{
			parent.attributes.stat[DEF] = value;
		}
	}

	//-------------------------------------
	// * HIT
	//-------------------------------------
	int hit
	{
		get const
		{
			return parent.attributes.stat[HIT];
		}
		set
		{
			parent.attributes.stat[HIT] = value;
		}
	}

	//-------------------------------------
	// * EVADE
	//-------------------------------------
	int evade
	{
		get const
		{
			return parent.attributes.stat[EVADE];
		}
		set
		{
			parent.attributes.stat[EVADE] = value;
		}
	}

	//-------------------------------------
	// * MAG_ATK
	//-------------------------------------
	int mag_atk
	{
		get const
		{
			return parent.attributes.stat[MAG_ATK];
		}
		set
		{
			parent.attributes.stat[MAG_ATK] = value;
		}
	}

	//-------------------------------------
	// * MAG_DEF
	//-------------------------------------
	int mag_def
	{
		get const
		{
			return parent.attributes.stat[MAG_DEF];
		}
		set
		{
			parent.attributes.stat[MAG_DEF] = value;
		}
	}

	//-------------------------------------
	// * MAG_HIT
	//-------------------------------------
	int mag_hit
	{
		get const
		{
			return parent.attributes.stat[MAG_HIT];
		}
		set
		{
			parent.attributes.stat[MAG_HIT] = value;
		}
	}

	//-------------------------------------
	// * MAG_EVADE
	//-------------------------------------
	int mag_evade
	{
		get const
		{
			return parent.attributes.stat[MAG_EVADE];
		}
		set
		{
			parent.attributes.stat[MAG_EVADE] = value;
		}
	}

	//-------------------------------------
	// * NUM_HITS
	//-------------------------------------
	int num_hits
	{
		get const
		{
			return parent.attributes.stat[NUM_HITS];
		}
		set
		{
			parent.attributes.stat[NUM_HITS] = value;
		}
	}

	//-------------------------------------
	// * CRITICAL_RATE
	//-------------------------------------
	int critical_rate
	{
		get const
		{
			return parent.attributes.stat[CRITICAL_RATE];
		}
		set
		{
			parent.attributes.stat[CRITICAL_RATE] = value;
		}
	}

	//-------------------------------------
	// * MORALE
	//-------------------------------------
	int morale
	{
		get const
		{
			return parent.attributes.stat[MORALE];
		}
		set
		{
			parent.attributes.stat[MORALE] = value;
		}
	}

};




class PlayerCharacter : public CharacterBase
{
	//todo
	//equipment
	//buffs
	//inventory
	//spritesets


	//-------------------------------------
	// * Attack
	//-------------------------------------
	int get_atk() const
	{
		int atkBonus = equipment.modifiers.stat[ATK] + buffs.modifiers.stat[ATK];
		return CharacterBase::atk + atkBonus;
	}

	//-------------------------------------
	// * Defense
	//-------------------------------------
	int get_def() const
	{
		int defBonus = equipment.modifiers.stat[DEF] + buffs.modifiers.stat[DEF];
		return CharacterBase::def + defBonus;
	}

	//-------------------------------------
	// * Hit
	//-------------------------------------
	int get_hit() const
	{
		int hitBonus = equipment.modifiers.stat[HIT] + buffs.modifiers.stat[HIT];
		return CharacterBase::evade + hitBonus;
	}

	//-------------------------------------
	// * Evade
	//-------------------------------------
	int get_evade() const
	{
		int evadeBonus = equipment.modifiers.stat[EVADE] + buffs.modifiers.stat[EVADE];
		return CharacterBase::evade + evadeBonus;
	}

};




class Fighter : public PlayerCharacter
{
	//-------------------------------------
	// * Attack
	//-------------------------------------
	int get_atk() const
	{
		return PlayerCharacter::atk + (strength / 2);
	}

	//-------------------------------------
	// * Hit
	//-------------------------------------
	int get_hit() const
	{
		return PlayerCharacter::hit + (3 * (lv - 1));
	}

	void LevelUp()
	{
		if( lv >= 99 )
			return;

		int hpIncrease = (vitality / 4) + 1;
		if( probability(50) ) //this needs some magic...
			hpIncrease = 20 + (vitality / 4) + rand(1, 6);

		max_hp += hpIncrease;
		//mp
		strength += 1;
		if( probability(6, 8) ) agility += 1;
		if( probability(4, 8) ) intelligence += 1;
		if( probability(5, 8) ) vitality += 1;
		if( probability(6, 8) ) luck += 1;

		mag_def += 2;
	}

};


class Knight : public PlayerCharacter
{
};



class RedMage : public PlayerCharacter
{
	//-------------------------------------
	// * Attack
	//-------------------------------------
	int get_atk() const
	{
		return PlayerCharacter::atk + (strength / 2);
	}

	//-------------------------------------
	// * Hit
	//-------------------------------------
	int get_hit() const
	{
		return PlayerCharacter::hit + (2 * (lv - 1));
	}

};


