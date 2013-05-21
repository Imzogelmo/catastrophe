
#pragma once


// Player States
#define ps_ENTER_IDLE				0 // Not doing anything.
#define ps_IDLE				0 // Not doing anything.
#define ps_ENTER_INPUT			1 // Waiting for player to input commands.
#define ps_INPUT			1 // Waiting for player to input commands.
#define ps_PREPARE_ATTACK	2 // Preparing to attack.
#define ps_ENTER_ATTACK			3 // Attacking.
#define ps_ATTACK			3 // Attacking.
#define ps_PREPARE_CAST		4 // Preparing to cast a spell.
#define ps_ENTER_CAST				5 // Casting a spell.
#define ps_CAST				5 // Casting a spell.
#define ps_PREPARE_ITEM		6 // Preparing to use an item.
#define ps_ENTER_ITEM				7 // Using an item.
#define ps_ITEM				7 // Using an item.

//these might not be needed.
#define ps_DEAD				16 // Dead.
#define ps_STONE			17 // Turned to stone.

//fixme: these should be seperate.
#define ps_WEAK				0x0100 // Flag | Player is in the kneel position.
#define ps_MOVE_ACTION		0x1000 // Flag | Player is moving to action position.
#define ps_MOVE_HOME		0x2000 // Flag | Player is moving to home position.
#define ps_DAMAGED			0x4000 // Flag | Player is taking damage.

enum PlayerAnimationState
{
	as_IDLE,
	as_READY,
	as_WALKING,
	as_RUNNING,
	as_ATTACKING,
	as_CHANTING,
	as_CASTING,
	as_VICTORY,
	as_CRITICAL,
	as_HIT,
	as_DEAD

	//standing
	//ready position
	//walking
	//running
	//attack
	//chanting
	//cast
	//victory
	//crit
	//hit
	//dead
};


//something like this
class CombatActionState
{
	int state = 0;

	bool IsFinished() const
	{
		return state == ACTION_COMPLETE;
	}

	void UpdateState()
	{
		switch(state)
		{
			case ACTION_PREPARE:
			{
			}
			break;

			case ACTION_ADVANCE:
			{
			}
			break;

			case ACTION_EXECUTE:
			{
			}
			break;

			case ACTION_RETURN:
			{
			}
			break;

			case ACTION_COMPLETE:
			{
			}
			break;

			default:
			{
				throw("invalid state : " + state);
			}
		}
	}
};



class Character : public Combatant
{
	vec2 home;
	int state;

	Character()
	{
		state = ps_IDLE;
	}

	void run()
	{
	}

	// things that are maybe useful later on
	void OnDamage(){}
	void OnHit(){}


	void MoveToHomePosition( float speed = 2f )
	{
		vec2 dist = vec2(pos - home).abs();
		if( dist.x < speed && dist.y < speed )
		{
			pos = home;
		}
		else
		{
			pos += pos.direction(home) * speed;
		}
	}


};





};

