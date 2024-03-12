#pragma once

#include <SFML/System/String.hpp>

struct sMove
{
	enum eDamageType
	{
		ATTACK = 0,
		SPECIAL_ATTACK = 1,
		HEAL = 2,
		BUFF = 3,
		DEBUFF = 4
	};

	sf::String m_name;

	int m_power;

	eDamageType m_damage_type;


};