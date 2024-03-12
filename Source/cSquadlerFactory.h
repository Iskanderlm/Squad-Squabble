#pragma once

#include "sSquadler.h"
#include "sTrainer.h"
#include "list"

class cSquadlerFactory
{

public:
	static void init ();
	static void unInit ();

	static sMove* getMove ( const sf::String& _move_name );

	static std::list < sMove* > m_all_moves;

	static std::list < sSquadler* > m_all_pokemon;


	static void setNewTeam (sTrainer& _trainer);
};