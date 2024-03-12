#include "cSquadlerFactory.h"


std::list< sMove* > cSquadlerFactory::m_all_moves;
std::list< sSquadler* > cSquadlerFactory::m_all_pokemon;
void cSquadlerFactory::init ()
{
	m_all_moves.push_back ( new sMove{ sf::String("Gust"),40,sMove::SPECIAL_ATTACK});
	m_all_moves.push_back ( new sMove{ sf::String ( "Quick Attack" ),40,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Wing Attack" ),35,sMove::ATTACK } );

	m_all_moves.push_back ( new sMove{ sf::String ( "Crunch" ),80,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Ice Fang" ),65,sMove::ATTACK } );

	m_all_moves.push_back ( new sMove{ sf::String ( "Scratch" ),40,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Hydro Pump" ),120,sMove::SPECIAL_ATTACK } );

	m_all_moves.push_back ( new sMove{ sf::String ( "Mud-Slap" ),20,sMove::SPECIAL_ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Bulldoze" ),60,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Earth Power" ),90,sMove::SPECIAL_ATTACK } );

	m_all_moves.push_back ( new sMove{ sf::String ( "Tackle" ),40,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Snore" ),50,sMove::SPECIAL_ATTACK } );

	m_all_moves.push_back ( new sMove{ sf::String ( "Vine Whip" ),45,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Acid" ),40,sMove::SPECIAL_ATTACK } );

	m_all_moves.push_back ( new sMove{ sf::String ( "Lick" ),30,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Shadow Punch" ),60,sMove::ATTACK } );
	m_all_moves.push_back ( new sMove{ sf::String ( "Hex" ),65,sMove::SPECIAL_ATTACK } );

	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name                               = sf::String ( "Pidgey" );
	m_all_pokemon.back ()->m_back_texture_path                  = sf::String ( "Assets/Textures/Back/pidgey.png" );
	m_all_pokemon.back ()->m_front_texture_path                 = sf::String ( "Assets/Textures/Front/pidgey.png" );
	m_all_pokemon.back ()->m_level                              = 10;
	m_all_pokemon.back ()->m_hp                                 = 40;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ]          = 40;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ]          = 45;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ]  = 35;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ]         = 40;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 35;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ]           = 56;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Gust" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = getMove ( sf::String ( "Quick Attack" ) );
	m_all_pokemon.back ()->m_moves[ 2 ] = getMove ( sf::String ( "Wing Attack" ) );
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;


	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name = sf::String ( "Arbok" );
	m_all_pokemon.back ()->m_back_texture_path = sf::String ( "Assets/Textures/Back/arbok.png" );
	m_all_pokemon.back ()->m_front_texture_path = sf::String ( "Assets/Textures/Front/arbok.png" );
	m_all_pokemon.back ()->m_level = 22;
	m_all_pokemon.back ()->m_hp = 60;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ] = 60;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ] = 85;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ] = 65;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ] = 69;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 79;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ] = 80;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Crunch" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = getMove ( sf::String ( "Ice Fang" ) );
	m_all_pokemon.back ()->m_moves[ 2 ] = nullptr;
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;


	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name = sf::String ( "Kabuto" );
	m_all_pokemon.back ()->m_back_texture_path = sf::String ( "Assets/Textures/Back/kabuto.png" );
	m_all_pokemon.back ()->m_front_texture_path = sf::String ( "Assets/Textures/Front/kabuto.png" );
	m_all_pokemon.back ()->m_level = 5;
	m_all_pokemon.back ()->m_hp = 30;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ] = 30;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ] = 80;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ] = 55;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ] = 90;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 45;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ] = 55;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Scratch" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = getMove ( sf::String ( "Hydro Pump" ) );
	m_all_pokemon.back ()->m_moves[ 2 ] = nullptr;
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;


	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name = sf::String ( "Bellsprout" );
	m_all_pokemon.back ()->m_back_texture_path = sf::String ( "Assets/Textures/Back/bellsprout.png" );
	m_all_pokemon.back ()->m_front_texture_path = sf::String ( "Assets/Textures/Front/bellsprout.png" );
	m_all_pokemon.back ()->m_level = 21;
	m_all_pokemon.back ()->m_hp = 50;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ] = 50;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ] = 75;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ] = 70;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ] = 35;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 30;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ] = 40;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Vine Whip" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = getMove ( sf::String ( "Acid" ) );
	m_all_pokemon.back ()->m_moves[ 2 ] = nullptr;
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;


	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name = sf::String ( "Diglet" );
	m_all_pokemon.back ()->m_back_texture_path = sf::String ( "Assets/Textures/Back/diglet.png" );
	m_all_pokemon.back ()->m_front_texture_path = sf::String ( "Assets/Textures/Front/diglet.png" );
	m_all_pokemon.back ()->m_level = 10;
	m_all_pokemon.back ()->m_hp = 10;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ] = 10;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ] = 55;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ] = 35;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ] = 25;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 45;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ] = 95;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Bulldoze" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = getMove ( sf::String ( "Earth Power" ) );
	m_all_pokemon.back ()->m_moves[ 2 ] = getMove ( sf::String ( "Mud-Slap" ) );
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;


	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name = sf::String ( "Magikarp" );
	m_all_pokemon.back ()->m_back_texture_path = sf::String ( "Assets/Textures/Back/magikarp.png" );
	m_all_pokemon.back ()->m_front_texture_path = sf::String ( "Assets/Textures/Front/magikarp.png" );
	m_all_pokemon.back ()->m_level = 7;
	m_all_pokemon.back ()->m_hp = 20;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ] = 20;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ] = 10;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ] = 15;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ] = 55;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 20;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ] = 80;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Tackle" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = nullptr;
	m_all_pokemon.back ()->m_moves[ 2 ] = nullptr;
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;

	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name = sf::String ( "Snorlax" );
	m_all_pokemon.back ()->m_back_texture_path = sf::String ( "Assets/Textures/Back/snorlax.png" );
	m_all_pokemon.back ()->m_front_texture_path = sf::String ( "Assets/Textures/Front/snorlax.png" );
	m_all_pokemon.back ()->m_level = 30;
	m_all_pokemon.back ()->m_hp = 160;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ] = 160;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ] = 110;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ] = 65;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ] = 65;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 110;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ] = 30;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Tackle" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = getMove ( sf::String ( "Snore" ) );
	m_all_pokemon.back ()->m_moves[ 2 ] = nullptr;
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;
	

	m_all_pokemon.push_back ( new sSquadler );
	m_all_pokemon.back ()->m_name = sf::String ( "Haunter" );
	m_all_pokemon.back ()->m_back_texture_path = sf::String ( "Assets/Textures/Back/haunter.png" );
	m_all_pokemon.back ()->m_front_texture_path = sf::String ( "Assets/Textures/Front/haunter.png" );
	m_all_pokemon.back ()->m_level = 25;
	m_all_pokemon.back ()->m_hp = 45;
	m_all_pokemon.back ()->m_stats[ sSquadler::MAX_HP ] = 45;
	m_all_pokemon.back ()->m_stats[ sSquadler::ATTACK ] = 50;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_ATTACK ] = 115;
	m_all_pokemon.back ()->m_stats[ sSquadler::DEFENCE ] = 45;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPECIAL_DEFENCE ] = 55;
	m_all_pokemon.back ()->m_stats[ sSquadler::SPEED ] = 95;

	m_all_pokemon.back ()->m_moves[ 0 ] = getMove ( sf::String ( "Lick" ) );
	m_all_pokemon.back ()->m_moves[ 1 ] = getMove ( sf::String ( "Hex" ) );
	m_all_pokemon.back ()->m_moves[ 2 ] = getMove ( sf::String ( "Shadow Punch" ) );
	m_all_pokemon.back ()->m_moves[ 3 ] = nullptr;

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


void cSquadlerFactory::setNewTeam ( sTrainer& _trainer )
{
	std::list<sSquadler*> available_pokemon;
	
	std::list<sSquadler*>::iterator itr = m_all_pokemon.begin ();

	while ( itr != m_all_pokemon.end () )
	{
		available_pokemon.push_back ( new sSquadler(*(*itr)));

		++ itr;
	}

	for ( int i = 0; i < 6; i++ )
	{
		int rand_index = rand ()%available_pokemon.size();

		std::list<sSquadler*>::iterator tmp_itr = available_pokemon.begin ();

		std::advance ( tmp_itr , rand_index );

		sSquadler* pkm_ptr = ( *tmp_itr );

		available_pokemon.remove ( pkm_ptr );

		_trainer.m_squadlers[ i ] = pkm_ptr;

	}

	while ( available_pokemon.size () > 0 )
	{
		delete available_pokemon.back ();
		available_pokemon.pop_back ();
	}

}

