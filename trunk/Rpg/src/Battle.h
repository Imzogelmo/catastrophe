
#pragma once


class BattleEvent
{
public:

};


class Battle
{
public:
	typedef fc::vector<BattleEvent*>	event_vec_type;

	Battle();
	~Battle();

	void AddEvent( BattleEvent* battleEvent );
	void AddOutroEvent( BattleEvent* battleEvent );

	//void SetMusic( Sound* sound );
	//Sound* GetMusic() const { return m_bgm; }

private:
	//MonsterTroop	m_monsterParty;
	//Party			m_party;...?

	event_vec_type		m_eventQueue;
	event_vec_type		m_outroEvents;

	//Sound*				m_bgm;
	//AnimatedSprite		m_background;

	//fc::vector<BattleAction*>	m_actions; //??

};


