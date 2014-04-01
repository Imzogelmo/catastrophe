
#pragma once


// Player States
#define ps_ENTER_IDLE		0 // Not doing anything.
#define ps_IDLE				0 // Not doing anything.
#define ps_ENTER_INPUT		1 // Waiting for player to input commands.
#define ps_INPUT			1 // Waiting for player to input commands.
#define ps_PREPARE_ATTACK	2 // Preparing to attack.
#define ps_ENTER_ATTACK		3 // Attacking.
#define ps_ATTACK			3 // Attacking.
#define ps_PREPARE_CAST		4 // Preparing to cast a spell.
#define ps_ENTER_CAST		5 // Casting a spell.
#define ps_CAST				5 // Casting a spell.
#define ps_PREPARE_ITEM		6 // Preparing to use an item.
#define ps_ENTER_ITEM		7 // Using an item.
#define ps_ITEM				7 // Using an item.

//these might not be needed.
#define ps_DEAD				16 // Dead.
#define ps_STONE			17 // Turned to stone.

//fixme: these should be seperate.
#define ps_WEAK				0x0100 // Flag | Player is in the kneel position.
#define ps_MOVE_ACTION		0x1000 // Flag | Player is moving to action position.
#define ps_MOVE_HOME		0x2000 // Flag | Player is moving to home position.
#define ps_DAMAGED			0x4000 // Flag | Player is taking damage.

/*
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
*/

#define PlayerAction_PREPARE	0
#define PlayerAction_ADVANCE	1
#define PlayerAction_EXECUTE	2
#define PlayerAction_RETURN		3
#define PlayerAction_COMPLETE	4


//something like this
class CombatActionState
{
	int state;

	CombatActionState()
	{
		state = 0;
	}

	bool IsFinished() const
	{
		return state == PlayerAction_COMPLETE;
	}

	void UpdateState()
	{
		switch(state)
		{
			case PlayerAction_PREPARE:
			{
			}
			break;

			case PlayerAction_ADVANCE:
			{
			}
			break;

			case PlayerAction_EXECUTE:
			{
			}
			break;

			case PlayerAction_RETURN:
			{
			}
			break;

			case PlayerAction_COMPLETE:
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

float px = 200;
float py = 40;

class PlayerCombatant : public Combatant
{
	vec2 home;
	int state;

	PlayerCombatant()
	{
		state = ps_IDLE;
		self.pos.x = px;
		self.pos.y = py;
		px += 10;
		py += 28;
	}

	void run()
	{
	}

	void update()
	{
		self.pos.x += randf(-0.3f, 0.3f);
	}

	// things that are maybe useful later on
	void OnDamage(){}
	void OnHit(){}


	void MoveToHomePosition( float speed = 2.f )
	{
		vec2 dist = vec2(self.pos - home).abs();
		if( dist.x < speed && dist.y < speed )
		{
			self.pos = home;
		}
		else
		{
			//pos += pos.direction(home) * speed;
		}
	}


	//todo
	void Attack(){}
	void Defend(){}
	void Spell(){}
	void Item(){}
	void Escape(){}

};




