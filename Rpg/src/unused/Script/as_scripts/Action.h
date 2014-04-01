
#pragma once



/// @CombatActionState
/// Enumeration of possible CombatAction states.

enum CombatActionState
{
	Pending,		// Uninitialized state. 
	Preparing,		// Action is still queued and is preparing to be executed.
	Starting,		// Initial phase of execution.
	Advancing,		// Combatant moves into action position. (usually by walking forward)
	PreExecute,		// Pre-Execute Phase: Combatant begins executing this action.
	Executing,		// Action and all effects or animations are being executed.
	PostExecute,	// Post-Execute Phase: Combatant returns from executing this action
	Returning,		// Combatant returns from executing this action (usually by walking backward)
	Finishing,		// Any final steps before the action completes are done here.
	Complete		// Success! ~The action is completed.
};



/// @CombatAction
///
/// Base class that implements an action that a Combatant can perform
/// during battle.

class CombatAction
{
	// ~ CombatAction ~
	// * Base class is implemented through composite inheritence.
	action@ self;

	Combatant@ combatant;
	CombatActionState state;
	int time;

	CombatAction()
	{
		//self;
		state = CombatActionState::Pending;
	}

	bool finished
	{
		get const { return state == CombatActionState::Complete; }
		set
		{
			//
		}
	}

	//Combatant@ get_combatant
	//{
	//	return self.combatant.script;
	//}

	void Update()
	{
	}

	void UpdateState()
	{
		switch(state)
		{
			case CombatActionState::Preparing:
			{
				state = CombatActionState::Advancing;
			}
			break;

			case CombatActionState::Advancing:
			break;

			case CombatActionState::Executing:
			{
			}
			break;

			case CombatActionState::Returning:
			{
			}
			break;

			case CombatActionState::Finishing:
			{
			}
			break;

			case CombatActionState::Complete:
			{
			}
			break;
		}
	}


	/// @OnEnterState
	/// Called once every time this action changes to a new state .
	void OnEnterState()
	{
	}

};






/// @ActionAttack
///
/// Action performed by a player for all basic attacks during combat.

class ActionAttack : public CombatAction
{
	ActionAttack()
	{
	}

	void Update()
	{
	}

	void UpdateState()
	{
		switch(state)
		{
			case CombatActionState::Preparing:
			{
			}
			break;

			case CombatActionState::Advancing:
			{
				++time;
				if( time > 20 )
				{
					//combatant.MoveToAttackPosition();
					state = CombatActionState::PreExecute:
					time = 0;
				}
			}
			break;

			case CombatActionState::PreExecute:
			{
			}
			break;

			case CombatActionState::Executing:
			{
			}
			break;

			case CombatActionState::PostExecute:
			{
			}
			break;

			case CombatActionState::Returning:
			{
			}
			break;

			case CombatActionState::Finishing:
			{
			}
			break;

			case CombatActionState::Complete:
			{
			}
			break;
		}
	}

};



