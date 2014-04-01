
#pragma once


class HitData
{
	int hits = 0;
	int critical = 0;
};




int GetPlayerChanceToHitEnemy( LightWarrior@ source, FF1Enemy@ target )
{
	if( source is null or target is null )
		print( "Error: GetPlayerChanceToHitEnemy(): null instance passed as argument." );


	int base_chance = 168;
	int target_status = target.GetStatus();


	//Defender blind status modifier
	if( target.IsBlind() )
		base_chance += 40;

	//Elemental modifier
	if( target.HasElementalWeakness(source.GetElementalAttack()) )
	{
		base_chance += 40;
	}

	//Family modifier
	if( target.HasFamily(source.GetFamilyAttack()) )
	{
		base_chance += 40;
	}

	//Immobility check
	bool immobile = false;
	if( target.HasStatus(SLEEP) || target.HasStatus(PARALYZE) )
	{
		immobile = true;
		if( base_chance < 168 )
			base_chance = 168;
	}

	int result = base_chance + source.GetHit();

	//Check hit vs evasion
	if( !immobile )
		result -= target.GetEvade();

	//Finally, get the attacker blind status modifier
	if( source.HasStatus(BLIND) )
		result -= 40;

	return result;
}


// Calculate the number of hits against an enemy
HitData CalculateHits( Character@ source, Monster@ target )
{
	HitData data;

	critical_hits = 0;
	int hits_landed = 0;
	int number_of_hits = source.GetTotalNumberOfHits();
	int chance_to_hit = GetPlayerChanceToHitEnemy( source, target );

	for( int i = 0; i < number_of_hits; ++i )
	{
		int r = rand(0, 200);
		if( r <= chance_to_hit )
		{
			++hits_landed;

			// Zero is always critical
			if( r == 0 )
				++data.critical;
		}
	}

	// Calculate the amount of critical hits
	int crit_chance = source.GetCriticalHit();

	for( int i = 0; i < hits_landed; ++i )
	{
		if( probability(crit_chance) )
			if( critical_hits < hits_landed )
				++critical_hits;
	}

	data.hits = hits_landed;
	data.critical = critical_hits;

	return data;
}


// Main player->enemy attack damage function
int GetPhysicalAttackDamageOnEnemy( LightWarrior@ source, FF1Enemy@ target, int &out critical_hits )
{
	int num_hits = GetPlayerTotalNumberOfEnemyHits( source, target, critical_hits );

	//Zero is a miss since the minimum damage of a hit is 1
	if( num_hits == 0 )
		return 0;

	int base_attack_power = source.GetCombatAttackPower();
	int base_enemy_defense = target.defense;

	//Elemental modifier
	int elem_flags = target.GetElementalWeakness() & source.GetElementalAttack();
	for( int i = 1; i < ELEMENT_ALL; i <<= 1 )
	{
		if( elem_flags & i != 0 )
			base_attack_power += math.rand(2, 6);
	}

	//Family modifier
	int family_flags = target.GetFamily() & source.GetFamilyAttack();
	for( int i = 1; i < FAMILY_ALL; i <<= 1 )
	{
		if( family_flags & i != 0 )
			base_attack_power += math.rand(2, 6);
	}

	//If the target is asleep or paralyzed, add a damage multiplier
	if( target.GetStatus() & (SLEEP | PARALYZE) != 0 )
	{
		base_attack_power *= 1.25f;
	}

	int unprocesed_critical_hits = critical_hits;
	int total_damage = 0;
	for( int i = 0; i < num_hits; ++i )
	{
		int amount = base_attack_power + math.rand(0, base_attack_power) - base_enemy_defense;

		//Critical hits
		if( unprocesed_critical_hits > 0 )
		{
			--unprocesed_critical_hits;
			amount += base_attack_power + math.rand(0, base_attack_power);
		}

		amount = math.clamp( amount, 1, 99999 );
		total_damage += amount;
	}

	return total_damage;
}





