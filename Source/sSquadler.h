#pragma once

#include "sMove.h"



struct sSquadler
{

	enum eStat
	{
		ATTACK          = 0,
		SPECIAL_ATTACK  = 1,
		DEFENCE         = 2,
		SPECIAL_DEFENCE = 3,
		MAX_HP          = 4,
		SPEED           = 5,
		STAT_COUNT      = 6

	};

	sMove* m_moves[ 4 ];

	sf::String m_name;
	
	sf::String m_back_texture_path;
	sf::String m_front_texture_path;

	int m_level;
	int m_hp;
	int m_stats[ STAT_COUNT ];

	

};