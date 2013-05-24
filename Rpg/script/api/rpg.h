
#pragma once

#ifndef __DEFINED__


/**
 * class that manages attribute values.
 */
class attributes;
{
	attributes();
	attributes(const attributes &);
	attributes& operator +=(const attributes &);
	attributes& operator -=(const attributes &);
	attributes operator +(const attributes &) const;
	attributes operator -(const attributes &) const;

	int get_max_param(int) const;
	int get_stat(int) const;
	int get_element(int);
	int get_status_atk(int);
	int get_status_def(int);

	void set_max_param(int, int) const;
	void set_stat(int, int) const;
	void set_element(int, int);
	void set_status_atk(int, int);
	void set_status_def(int, int);

};


/**
 * class that manages items and amount.
 */
class inventory
{
	inventory();
	inventory(const inventory &);

};



/**
 * class that manages equipped items.
 */
class equipment
{
	equipment();
	equipment(const equipment &);

};



/**
 * class that describes an enchantment
 * or temporary effect on an actor or entity.
 */
class buff
{
	buff();
	buff(const buff &);

};



/**
 * class that holds all basic information of a character
 */
class character_data
{
	string name;
	string script;
	string description;
	int id;
	int race_id;
	int class_id;
	int portrait_id;
	int map_spriteset_id;
	int battle_spriteset_id;
	int lv;
	int exp;
	int gold;
	attributes attributes;

};



/**
 * class that holds all basic information of a monster
 */
class monster_data
{
	string name;
	string script;
	string description;
	int id;
	int portrait_id;
	int map_spriteset_id;
	int battle_spriteset_id;
	int lv;
	int exp;
	int gold;
	attributes attributes;
	item_dropset item_dropset;

};


/**
 * class that is an instance of a character or monster class;
 */
class actor
{
	actor();
	actor(const actor &);

	string name;
	string script;
	int id;
	int portrait_id;
	int map_spriteset_id;
	int battle_spriteset_id;

	int get_lv() const;
	int get_exp() const;
	int get_gold() const;

	void set_lv(int) const;
	void set_exp(int) const;
	void set_gold(int) const;

	int get_param(int) const;
	int get_max_param(int) const;
	int get_base_max_param(int) const;
	int get_stat(int) const;
	int get_base_stat(int) const;
	int get_status_atk(int) const;
	int get_status_def(int) const;
	int get_base_status_atk(int) const;
	int get_base_status_def(int) const;

	void set_param(int, int) const;
	void set_base_max_param(int, int) const;
	void set_base_stat(int, int) const;
	void set_base_status_atk(int, int) const;
	void set_base_status_def(int, int) const;

	const attributes& get_attributes() const;
	const equipment& get_equipment() const;

};



/**
 * class entity that is a battle instance of, and 
 * holds a reference to, an actor.
 */
class combatant
{
	actor();
	actor(const actor &);

	actor@ get_actor() const;

	int get_param(int) const;
	int get_max_param(int) const;
	int get_base_max_param(int) const;
	int get_stat(int) const;
	int get_base_stat(int) const;
	int get_status_atk(int) const;
	int get_status_def(int) const;
	int get_base_status_atk(int) const;
	int get_base_status_def(int) const;

	void set_param(int, int) const;
	void set_base_max_param(int, int) const;
	void set_base_stat(int, int) const;
	void set_base_status_atk(int, int) const;
	void set_base_status_def(int, int) const;

	const attributes& get_attributes() const;
	const equipment& get_equipment() const;

};


/**
 * class that manages a list of current active and reserve
 * party members, as well as other information.
 */
class party
{
	party();
	party(const party &);

	int get_gold() const;
	int get_size() const;
	int get_active_size() const;
	int get_reserve_size() const;
	int get_max_size() const;
	int get_max_active_size() const;
	int get_active_member_id(int index) const;
	int get_reserve_member_id(int index) const;

	actor@ get_active_member(int index) const;
	actor@ get_reserve_member(int index) const;

	inventory& get_inventory();
	const inventory& get_inventory() const;

	void set_gold(int);
	void set_max_size(int);
	void set_max_active_size(int);

	void add_gold(int);
	void remove_gold(int);

	void add_member(int);
	void remove_member(int);

	bool has_member(int) const;
	bool is_member_active(int) const;
	bool is_member_in_reserve(int) const;
	bool is_full() const;

};


#endif
