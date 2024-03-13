#include "cSquadlerFactory.h"


std::list< sMove* > cSquadlerFactory::m_all_moves;
std::list< sSquadler* > cSquadlerFactory::m_all_pokemon;
void cSquadlerFactory::init()
{
	m_all_moves.push_back( new sMove{ sf::String( "Gritpunch" ),40,sMove::SPECIAL_ATTACK } );
	m_all_moves.push_back( new sMove{ sf::String( "Quick Drill" ),40,sMove::ATTACK } );
	m_all_moves.push_back( new sMove{ sf::String( "Takeup" ),35,sMove::ATTACK } );
	m_all_moves.push_back( new sMove{ sf::String( "Tax Call" ),80,sMove::ATTACK } );

	m_all_moves.push_back( new sMove{ sf::String( "Bonk" ),65,sMove::ATTACK } );
	m_all_moves.push_back( new sMove{ sf::String( "Romper" ),40,sMove::SPECIAL_ATTACK } );
	m_all_moves.push_back( new sMove{ sf::String( "Slash" ),40,sMove::ATTACK } );
	m_all_moves.push_back( new sMove{ sf::String( "Goblin King" ),35,sMove::ATTACK } );


	m_all_pokemon.push_back( new sSquadler );
	m_all_pokemon.back()->m_name = sf::String( "Pitch" );
	m_all_pokemon.back()->m_back_texture_path = sf::String( "Assets/Textures/Back/Pitch.png" );
	m_all_pokemon.back()->m_front_texture_path = sf::String( "Assets/Textures/Front/Pitch.png" );
	m_all_pokemon.back()->m_level = 10;
	m_all_pokemon.back()->m_hp = 40;
	m_all_pokemon.back()->m_stats[sSquadler::MAX_HP] = 40;
	m_all_pokemon.back()->m_stats[sSquadler::ATTACK] = 45;
	m_all_pokemon.back()->m_stats[sSquadler::SPECIAL_ATTACK] = 35;
	m_all_pokemon.back()->m_stats[sSquadler::DEFENCE] = 40;
	m_all_pokemon.back()->m_stats[sSquadler::SPECIAL_DEFENCE] = 35;
	m_all_pokemon.back()->m_stats[sSquadler::SPEED] = 56;

	m_all_pokemon.back()->m_moves[0] = getMove( sf::String( "Gritpunch" ) );
	m_all_pokemon.back()->m_moves[1] = getMove( sf::String( "Quick Drill" ) );
	m_all_pokemon.back()->m_moves[2] = getMove( sf::String( "Takeup" ) );
	m_all_pokemon.back()->m_moves[3] = getMove( sf::String( "Tax Call" ) );


	m_all_pokemon.push_back( new sSquadler );
	m_all_pokemon.back()->m_name = sf::String( "Goblin" );
	m_all_pokemon.back()->m_back_texture_path = sf::String( "Assets/Textures/Back/Goblin.png" );
	m_all_pokemon.back()->m_front_texture_path = sf::String( "Assets/Textures/Front/Goblin.png" );
	m_all_pokemon.back()->m_level = 10;
	m_all_pokemon.back()->m_hp = 40;
	m_all_pokemon.back()->m_stats[sSquadler::MAX_HP] = 40;
	m_all_pokemon.back()->m_stats[sSquadler::ATTACK] = 45;
	m_all_pokemon.back()->m_stats[sSquadler::SPECIAL_ATTACK] = 35;
	m_all_pokemon.back()->m_stats[sSquadler::DEFENCE] = 40;
	m_all_pokemon.back()->m_stats[sSquadler::SPECIAL_DEFENCE] = 35;
	m_all_pokemon.back()->m_stats[sSquadler::SPEED] = 56;

	m_all_pokemon.back()->m_moves[0] = getMove( sf::String( "Bonk" ) );
	m_all_pokemon.back()->m_moves[1] = getMove( sf::String( "Romper" ) );
	m_all_pokemon.back()->m_moves[2] = getMove( sf::String( "Slash" ) );
	m_all_pokemon.back()->m_moves[3] = getMove( sf::String( "Goblin King" ) );

}

void cSquadlerFactory::unInit ()
{
}

sMove* cSquadlerFactory::getMove ( const sf::String& _move_name )
{
	std::list<sMove*>::iterator itr = m_all_moves.begin();

	while ( itr != m_all_moves.end () )
	{

		if ( ( *itr )->m_name == _move_name )
		{
			return ( *itr );
		}

		++itr;
	}

	return nullptr;
}


void cSquadlerFactory::setNewTeam ( sTrainer& _player, sTrainer& _opponent )
{
	std::list<sSquadler*> available_pokemon;
	
	std::list<sSquadler*>::iterator itr = m_all_pokemon.begin ();

	while ( itr != m_all_pokemon.end () )
	{
		available_pokemon.push_back ( new sSquadler(*(*itr)));

		++ itr;
	}

	for ( int i = 0; i < m_all_pokemon.size(); i++ )
	{

		if ( i > 11 )
			break;

		int rand_index = rand ()%available_pokemon.size();

		std::list<sSquadler*>::iterator tmp_itr = available_pokemon.begin ();

		std::advance ( tmp_itr , rand_index );

		sSquadler* pkm_ptr = ( *tmp_itr );

		available_pokemon.remove ( pkm_ptr );

		if(i % 2 == 0 )
			_player.m_squadlers[ i / 2 ] = pkm_ptr;
		else
			_opponent.m_squadlers[ i / 2 ] = pkm_ptr;

	}

	while ( available_pokemon.size () > 0 )
	{
		delete available_pokemon.back ();
		available_pokemon.pop_back ();
	}

}

