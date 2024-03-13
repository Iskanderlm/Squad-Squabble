#include "cBattleScene.h"



void processEvents ( sf::RenderWindow& );
void resetRecentInput ();

cBattleScene::cBattleScene () 
	: m_bg_rect       ( cTextureRect ( sf::FloatRect ( 0.5f ,   0.5f,  1.0f,  1.0f ), "Assets/Textures/battle_bg.png",   false, cScaledElement::CENTER     ) )
	, m_enemy_squadler ( cTextureRect ( sf::FloatRect ( 0.55f, -0.03f,  0.7f,  0.7f ), "Assets/Textures/placeholder.png", true,  cScaledElement::TOP_RIGHT  ) )
	, m_player_squadler( cTextureRect ( sf::FloatRect ( 0.05f,   0.4f,  0.7f,  0.7f ), "Assets/Textures/placeholder.png", true,  cScaledElement::DOWN_LEFT  ) )
	, m_dialogue_text ( cLabel       ( sf::FloatRect ( 0.01f,  0.95f, 0.35f,  0.1f ), "test test test testes",           false, cScaledElement::DOWN_LEFT  ) )
	, m_run           ( cButton      ( sf::FloatRect ( 0.98f,  0.95f,  0.2f, 0.12f ), "RUN",                             false, cScaledElement::DOWN_RIGHT ) )
	, m_squadler       ( cButton      ( sf::FloatRect ( 0.77f,  0.95f,  0.2f, 0.12f ), "SQUADLERS",                         false, cScaledElement::DOWN_RIGHT ) )
	, m_bag           ( cButton      ( sf::FloatRect ( 0.98f,   0.8f,  0.2f, 0.12f ), "BAG",                             false, cScaledElement::DOWN_RIGHT ) )
	, m_fight         ( cButton      ( sf::FloatRect ( 0.77f,   0.8f,  0.2f, 0.12f ), "FIGHT",                           false, cScaledElement::DOWN_RIGHT ) )
	, m_back_button   ( cButton      ( sf::FloatRect ( 0.56f,  0.95f,  0.2f, 0.12f ), "BACK",                            false, cScaledElement::DOWN_RIGHT ) )
	, m_move_buttons{
		cButton ( sf::FloatRect ( 0.98f, 0.95f, 0.2f, 0.12f ), "M1", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.77f, 0.95f, 0.2f, 0.12f ), "M2", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.98f,  0.8f, 0.2f, 0.12f ), "M3", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.77f,  0.8f, 0.2f, 0.12f ), "M4", false, cScaledElement::DOWN_RIGHT ) }
	, m_squadler_buttons{
		cButton ( sf::FloatRect ( 0.98f, 0.95f, 0.2f, 0.12f ), "M1", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.77f, 0.95f, 0.2f, 0.12f ), "M2", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.98f,  0.8f, 0.2f, 0.12f ), "M3", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.77f,  0.8f, 0.2f, 0.12f ), "M4", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.98f, 0.65f, 0.2f, 0.12f ), "M5", false, cScaledElement::DOWN_RIGHT ),
		cButton ( sf::FloatRect ( 0.77f, 0.65f, 0.2f, 0.12f ), "M6", false, cScaledElement::DOWN_RIGHT ) }
	, m_hp_bar_1  ( sf::FloatRect ( 0.98f, 0.65f, 0.41f, 0.12f ), cScaledElement::DOWN_RIGHT )
	, m_hp_bar_2  ( sf::FloatRect ( 0.02f, 0.05f, 0.41f, 0.12f ), cScaledElement::TOP_LEFT   )
	, m_fade_rect ( sf::FloatRect (  0.0f,  0.0f,  1.0f,  1.0f ) )
	, m_spiral ( cTextureRect ( sf::FloatRect ( 0.5f , 0.5f , 1.0f , 1.0f ), "Assets/Textures/swirl.png", true, cScaledElement::CENTER ) )
{

	cSquadlerFactory::init ();

	m_enemy.m_name = ( rand () % 2 ) ? "Nicklas" : "Martin";

	m_player.m_name = "Player";

	m_player_squadler_starting_pos = m_player_squadler.m_uv_rect.getPosition ();
	m_enemy_squadler_starting_pos = m_enemy_squadler.m_uv_rect.getPosition ();

	cSquadlerFactory::setNewTeam ( m_player, m_enemy );

	m_move_buttons[ 0 ].m_on_press->hook< cBattleScene >( &cBattleScene::useMove1, *this );
	m_move_buttons[ 1 ].m_on_press->hook< cBattleScene >( &cBattleScene::useMove2, *this );
	m_move_buttons[ 2 ].m_on_press->hook< cBattleScene >( &cBattleScene::useMove3, *this );
	m_move_buttons[ 3 ].m_on_press->hook< cBattleScene >( &cBattleScene::useMove4, *this );

	m_squadler_buttons[ 0 ].m_on_press->hook< cBattleScene >( &cBattleScene::chooseSquadler1, *this );
	m_squadler_buttons[ 1 ].m_on_press->hook< cBattleScene >( &cBattleScene::chooseSquadler2, *this );
	m_squadler_buttons[ 2 ].m_on_press->hook< cBattleScene >( &cBattleScene::chooseSquadler3, *this );
	m_squadler_buttons[ 3 ].m_on_press->hook< cBattleScene >( &cBattleScene::chooseSquadler4, *this );
	m_squadler_buttons[ 4 ].m_on_press->hook< cBattleScene >( &cBattleScene::chooseSquadler5, *this );
	m_squadler_buttons[ 5 ].m_on_press->hook< cBattleScene >( &cBattleScene::chooseSquadler6, *this );

	m_enemy_squadler.m_sprite. setOrigin( m_enemy_squadler. m_sprite.getLocalBounds().getSize() / 2.0f );
	m_player_squadler.m_sprite.setOrigin( m_player_squadler.m_sprite.getLocalBounds().getSize() / 2.0f );

	m_spiral.m_sprite. setOrigin( m_spiral. m_sprite.getLocalBounds().getSize() / 2.0f );
	m_bg_rect.m_sprite.setOrigin( m_bg_rect.m_sprite.getLocalBounds().getSize() / 2.0f );


	m_dialogue_text.setFont( "Assets/Fonts/Boxy-Bold.ttf" );
	m_dialogue_text.setColor( sf::Color::Black );
	
	m_run.setColor( sf::Color::Black );
	m_run.setFont( "Assets/Fonts/Boxy-Bold.ttf" );
	m_run.assignStyle( cButton::DEFAULT, cUIRect::sRectStyle{ sf::Color( 64,   64, 255, 255 ), sf::Color( 255, 255, 255, 255 ), 1.5f } );
	m_run.assignStyle( cButton::PRESSED, cUIRect::sRectStyle{ sf::Color( 64,   64, 128, 255 ), sf::Color(  64,  64,  64, 255 ), 3.0f } );
	m_run.assignStyle( cButton::HOVERED, cUIRect::sRectStyle{ sf::Color( 128, 128, 255, 255 ), sf::Color( 128, 128, 255, 255 ), 3.0f } );

	m_squadler.setColor( sf::Color::Black );
	m_squadler.setFont( "Assets/Fonts/Boxy-Bold.ttf" );
	m_squadler.assignStyle( cButton::DEFAULT, cUIRect::sRectStyle{ sf::Color(  64, 255,  64, 255 ), sf::Color ( 255, 255, 255, 255 ), 1.5f } );
	m_squadler.assignStyle( cButton::PRESSED, cUIRect::sRectStyle{ sf::Color(  64, 128,  64, 255 ), sf::Color (  64,  64,  64, 255 ), 3.0f } );
	m_squadler.assignStyle( cButton::HOVERED, cUIRect::sRectStyle{ sf::Color( 128, 255, 128, 255 ), sf::Color ( 128, 255, 128, 255 ), 3.0f } );

	m_bag.setColor( sf::Color::Black );
	m_bag.setFont( "Assets/Fonts/Boxy-Bold.ttf" );
	m_bag.assignStyle( cButton::DEFAULT, cUIRect::sRectStyle{ sf::Color ( 200, 128, 64, 255 ), sf::Color ( 255, 255, 255, 255 ), 1.5f } );
	m_bag.assignStyle( cButton::PRESSED, cUIRect::sRectStyle{ sf::Color ( 128,  96, 64, 255 ), sf::Color (  64,  64,  64, 255 ), 3.0f } );
	m_bag.assignStyle( cButton::HOVERED, cUIRect::sRectStyle{ sf::Color ( 255, 128, 96, 255 ), sf::Color ( 255, 128,  96, 255 ), 3.0f } );

	m_fight.setColor( sf::Color::Black );
	m_fight.setFont( "Assets/Fonts/Boxy-Bold.ttf" );
	m_fight.assignStyle( cButton::DEFAULT, cUIRect::sRectStyle{ sf::Color( 255,  64,  64, 255 ), sf::Color ( 255, 255, 255, 255 ), 1.5f } );
	m_fight.assignStyle( cButton::PRESSED, cUIRect::sRectStyle{ sf::Color( 128,  64,  64, 255 ), sf::Color (  64,  64,  64, 255 ), 3.0f } );
	m_fight.assignStyle( cButton::HOVERED, cUIRect::sRectStyle{ sf::Color( 255, 128, 128, 255 ), sf::Color ( 255, 128, 128, 255 ), 3.0f } );


	m_back_button.setColor( sf::Color::Black );
	m_back_button.setFont( "Assets/Fonts/Boxy-Bold.ttf" );
	m_back_button.assignStyle( cButton::DEFAULT, cUIRect::sRectStyle{ sf::Color ( 128, 128, 128, 255 ), sf::Color( 255, 255, 255, 255 ), 1.5f } );
	m_back_button.assignStyle( cButton::PRESSED, cUIRect::sRectStyle{ sf::Color (  64,  64,  64, 255 ), sf::Color(  64,  64,  64, 255 ), 3.0f } );
	m_back_button.assignStyle( cButton::HOVERED, cUIRect::sRectStyle{ sf::Color ( 255, 255, 255, 255 ), sf::Color( 128, 128, 128, 255 ), 3.0f } );
	m_back_button.setVisible( false );
	m_back_button.m_active = false;

	m_back_button.m_on_press->hook< cBattleScene >( &cBattleScene::showHPBar1,         *this );
	m_back_button.m_on_press->hook< cBattleScene >( &cBattleScene::showMainButtons,    *this );
	m_back_button.m_on_press->hook< cBattleScene >( &cBattleScene::hideMoveButtons,    *this );
	m_back_button.m_on_press->hook< cBattleScene >( &cBattleScene::hideSquadlerButtons, *this );


	m_squadler.m_on_press->hook< cBattleScene >( &cBattleScene::hideHPBar1,                *this );
	m_squadler.m_on_press->hook< cBattleScene >( &cBattleScene::hideMainButtons,           *this );
	m_squadler.m_on_press->hook< cBattleScene >( &cBattleScene::updateSquadlerButtonLabels, *this );
	m_squadler.m_on_press->hook< cBattleScene >( &cBattleScene::showSquadlerButtons,        *this );



	m_fight.m_on_press->hook< cBattleScene >( &cBattleScene::hideMainButtons, *this );
	m_fight.m_on_press->hook< cBattleScene >( &cBattleScene::showMoveButtons, *this );

	m_run.m_on_press->hook< cBattleScene >( &cBattleScene::tryToRun, *this );


	for ( cButton& btn : m_move_buttons )
	{
		btn.setColor( sf::Color ( 0 , 0 , 0 , 255 ) );
		btn.setFont( "Assets/Fonts/Boxy-Bold.ttf" );
		btn.assignStyle( cButton::DEFAULT, cUIRect::sRectStyle{ sf::Color ( 128, 128, 128, 255 ), sf::Color( 255, 255, 255, 255 ), 1.5f } );
		btn.assignStyle( cButton::PRESSED, cUIRect::sRectStyle{ sf::Color (  64,  64,  64, 255 ), sf::Color(  64,  64,  64, 255 ), 3.0f } );
		btn.assignStyle( cButton::HOVERED, cUIRect::sRectStyle{ sf::Color ( 255, 255, 255, 255 ), sf::Color( 128, 128, 128, 255 ), 3.0f } );
		btn.setVisible( false );
		btn.m_active = false;
	}

	for ( cButton& btn : m_squadler_buttons )
	{
		btn.setColor ( sf::Color ( 0 , 0 , 0 , 255 ) );
		btn.setFont ( "Assets/Fonts/Boxy-Bold.ttf" );
		btn.assignStyle ( cButton::DEFAULT, cUIRect::sRectStyle{ sf::Color ( 128, 128, 128, 255 ), sf::Color( 255, 255, 255, 255 ), 1.5f } );
		btn.assignStyle ( cButton::PRESSED, cUIRect::sRectStyle{ sf::Color (  64,  64,  64, 255 ), sf::Color(  64,  64,  64, 255 ), 3.0f } );
		btn.assignStyle ( cButton::HOVERED, cUIRect::sRectStyle{ sf::Color ( 255, 255, 255, 255 ), sf::Color( 128, 128, 128, 255 ), 3.0f } );
		btn.setVisible ( false );
		btn.m_active = false;
	}


	selectSquadler( m_player, 0 );
	selectSquadler( m_enemy, 0 );
}

void cBattleScene::hideMainButtons ( void* _null )
{
	m_run.deActivate( _null );
	m_bag.deActivate( _null );
	m_squadler.deActivate( _null );
	m_fight.deActivate( _null );

	m_run.hideButton( _null );
	m_bag.hideButton( _null );
	m_squadler.hideButton( _null );
	m_fight.hideButton( _null );
}

void cBattleScene::showMainButtons( void* _null )
{
	m_run.    activate( _null );
	m_bag.    activate( _null );
	m_squadler.activate( _null );
	m_fight.  activate( _null );

	m_run.    showButton( _null );
	m_bag.    showButton( _null );
	m_squadler.showButton( _null );
	m_fight.  showButton( _null );

}

void cBattleScene::hideSquadlerButtons( void* _null )
{
	for( cButton& btn : m_squadler_buttons )
	{
		btn.hideButton( _null );
		btn.deActivate( _null );
	}
	m_back_button.deActivate( _null );
	m_back_button.hideButton( _null );
}

void cBattleScene::showSquadlerButtons ( void* _null )
{
	for ( cButton& btn : m_squadler_buttons )
	{
		btn.showButton( _null );
		btn.activate( _null );
	}
	m_back_button.activate( _null );
	m_back_button.showButton( _null );
}

void cBattleScene::hideBackButton ( void* _null )
{
	m_back_button.deActivate( _null );
	m_back_button.hideButton( _null );
}

void cBattleScene::showBackButton ( void* _null )
{
	m_back_button.activate( _null );
	m_back_button.showButton( _null );
}

void cBattleScene::hideMoveButtons ( void* _null )
{
	for ( cButton& btn : m_move_buttons )
	{
		btn.hideButton( _null );
		btn.deActivate( _null );
	}
	m_back_button.deActivate( _null );
	m_back_button.hideButton( _null );
}

void cBattleScene::showMoveButtons( void* _null )
{
	for ( cButton& btn : m_move_buttons )
	{
		btn.showButton( _null );
		btn.activate( _null );
	}
	m_back_button.activate( _null );
	m_back_button.showButton( _null );
}

void cBattleScene::hideHPBar1( void* _null )
{
	m_hp_bar_1.setVisible( false );
}

void cBattleScene::showHPBar1 ( void* _null )
{
	m_hp_bar_1.setVisible ( true );
}

void cBattleScene::hideHPBar2 ( void* _null )
{
	m_hp_bar_2.setVisible ( false );
}

void cBattleScene::showHPBar2 ( void* _null )
{
	m_hp_bar_2.setVisible ( true );
}

void cBattleScene::setFadeAlpha ( int _new_alpha )
{
	m_fade_rect.m_rectangle_shape.setFillColor ( sf::Color ( 0 , 0 , 0 , _new_alpha ) );
}

void cBattleScene::setSwirl ( float _t )
{
	m_spiral.setScale ( sf::Vector2f ( 12.0f * ( 1.0f - _t ) + 1.5f , 12.0f * ( 1.0f - _t ) + 1.5f ) );
	m_spiral.m_sprite.setRotation ( -1440 * _t );
}

void cBattleScene::hideSwirl ( void* _null )
{
	m_spiral.m_tex_rect_visible = false;
}

void cBattleScene::useMove1 ( void* _null )
{
	if ( m_player.m_selected_squadler->m_moves[ 0 ] != nullptr )
	{
		m_cueued_move = m_player.m_selected_squadler->m_moves[ 0 ];
		turnSpeedCheck ();
	}
}

void cBattleScene::useMove2 ( void* _null )
{
	if ( m_player.m_selected_squadler->m_moves[ 1 ] != nullptr )
	{
		m_cueued_move = m_player.m_selected_squadler->m_moves[ 1 ];
		turnSpeedCheck ();
	}
}

void cBattleScene::useMove3 ( void* _null )
{
	if ( m_player.m_selected_squadler->m_moves[ 2 ] != nullptr )
	{
		m_cueued_move = m_player.m_selected_squadler->m_moves[ 2 ];
		turnSpeedCheck ();
	}
}

void cBattleScene::useMove4 ( void* _null )
{
	if ( m_player.m_selected_squadler->m_moves[ 3 ] != nullptr )
	{
		m_cueued_move = m_player.m_selected_squadler->m_moves[ 3 ];
		turnSpeedCheck ();
	}
}

void cBattleScene::chooseSquadler1 ( void* _null )
{
	if ( m_player.m_squadlers[ 0 ] != nullptr )
	{
		if ( m_player.m_squadlers[ 0 ]->m_hp > 0 && m_player.m_squadlers[ 0 ] != m_player.m_selected_squadler )
		{
			selectSquadler ( m_player , 0 );
			startFlash ();
		}
	}
}

void cBattleScene::chooseSquadler2 ( void* _null )
{
	if ( m_player.m_squadlers[ 1 ] != nullptr )
	{
		if ( m_player.m_squadlers[ 1 ]->m_hp > 0 && m_player.m_squadlers[ 1 ] != m_player.m_selected_squadler )
		{
			selectSquadler ( m_player , 1 );
			startFlash ();
		}
	}
}

void cBattleScene::chooseSquadler3 ( void* _null )
{
	if ( m_player.m_squadlers[ 2 ] != nullptr )
	{
		if ( m_player.m_squadlers[ 2 ]->m_hp > 0 && m_player.m_squadlers[ 2 ] != m_player.m_selected_squadler )
		{
			selectSquadler ( m_player , 2 );
			startFlash ();
		}
	}
}

void cBattleScene::chooseSquadler4 ( void* _null )
{
	if ( m_player.m_squadlers[ 3 ] != nullptr )
	{
		if ( m_player.m_squadlers[ 3 ]->m_hp > 0 && m_player.m_squadlers[ 3 ] != m_player.m_selected_squadler )
		{
			selectSquadler ( m_player , 3 );
			startFlash ();
		}
	}
}

void cBattleScene::chooseSquadler5 ( void* _null )
{
	if ( m_player.m_squadlers[ 4 ] != nullptr )
	{
		if ( m_player.m_squadlers[ 4 ]->m_hp > 0 && m_player.m_squadlers[ 4 ] != m_player.m_selected_squadler )
		{
			selectSquadler ( m_player , 4 );
			startFlash ();
		}
	}
}

void cBattleScene::chooseSquadler6 ( void* _null )
{
	if ( m_player.m_squadlers[ 5 ] != nullptr )
	{
		if ( m_player.m_squadlers[ 5 ]->m_hp > 0 && m_player.m_squadlers[ 5 ] != m_player.m_selected_squadler )
		{
			selectSquadler ( m_player , 5 );
			startFlash ();
		}
	}
}

void cBattleScene::selectSquadler ( sTrainer& _trainer , const int& _squadler_index )
{
	bool end_player_turn = false;

	if ( &_trainer == &m_player )
	{
		if ( _trainer.m_selected_squadler != nullptr )
		{
			if ( _trainer.m_selected_squadler->m_hp > 0 )
			{
			end_player_turn = true;

			}
			else
			{
				hideSquadlerButtons (nullptr);
				showHPBar1 ( nullptr );
				showMainButtons ( nullptr );
			}
		}
	}

	_trainer.m_selected_squadler = _trainer.m_squadlers[ _squadler_index ];

	if ( &_trainer == &m_player )
	{
		m_player_squadler.setTexture ( _trainer.m_selected_squadler->m_back_texture_path );
		m_hp_bar_1.setLevel ( _trainer.m_selected_squadler->m_level );
		m_hp_bar_1.setName ( _trainer.m_selected_squadler->m_name );
		m_hp_bar_1.setHP ( _trainer.m_selected_squadler->m_hp , _trainer.m_selected_squadler->m_stats[ sSquadler::MAX_HP ] );

		for ( int i = 0; i < 4; i++ )
		{
			if ( _trainer.m_selected_squadler->m_moves[ i ] != nullptr )
			{
				m_move_buttons[ i ].setString ( _trainer.m_selected_squadler->m_moves[ i ]->m_name );
			}
			else
			{
				m_move_buttons[ i ].setString ( "" );
			}
		}


	}
	else
	{
		m_enemy_squadler.setTexture ( _trainer.m_selected_squadler->m_front_texture_path );
		m_hp_bar_2.setLevel ( _trainer.m_selected_squadler->m_level );
		m_hp_bar_2.setName ( _trainer.m_selected_squadler->m_name );
		m_hp_bar_2.setHP ( _trainer.m_selected_squadler->m_hp , _trainer.m_selected_squadler->m_stats[ sSquadler::MAX_HP ] );
	}
	if ( end_player_turn )
	{
		showHPBar1 (nullptr);
		hideSquadlerButtons (nullptr);
		enemyChoseMove ();
	}
}

void cBattleScene::updateHPbars ( void* _null )
{
	m_hp_bar_1.setHP ( m_player.m_selected_squadler->m_hp , m_player.m_selected_squadler->m_stats[ sSquadler::MAX_HP ] );
	m_hp_bar_2.setHP ( m_enemy.m_selected_squadler->m_hp , m_enemy.m_selected_squadler->m_stats[ sSquadler::MAX_HP ] );
}

cEvent* cBattleScene::useMove ( sMove& _move , sSquadler& _user , sSquadler& _not_user , const bool& _user_is_player )
{
	int damage;

	switch ( _move.m_damage_type )
	{
	case sMove::SPECIAL_ATTACK:
		damage = ( ( ( ( float ) _user.m_level * 2.0f ) / 5.0f + 2.0f ) * _move.m_power * ( ( float ) _user.m_stats[ sSquadler::SPECIAL_ATTACK ] / _not_user.m_stats[ sSquadler::SPECIAL_DEFENCE ] ) ) / 50.0 + 2;
		damage = fmax ( 1 , ( float ) damage * ( float ) ( ( rand () % 39 ) + 217 ) / 255.0f );
		_not_user.m_hp = fmax ( 0 , _not_user.m_hp - damage );
		updateHPbars ( nullptr );
		if ( _user_is_player )
		{
			startShakeEnemySquadler( nullptr );
			startJumpPlayerSquadler( nullptr );
		}
		else
		{
			startShakePlayerSquadler( nullptr );
			startJumpEnemySquadler( nullptr );
		}
		break;
	case sMove::ATTACK:
		damage = ( ( ( ( float ) _user.m_level * 2.0f ) / 5.0f + 2.0f ) * _move.m_power * ( ( float ) _user.m_stats[ sSquadler::ATTACK ] / _not_user.m_stats[ sSquadler::DEFENCE ] ) ) / 50.0 + 2;
		damage = fmax ( 1 , ( float ) damage * ( float ) ( ( rand () % 39 ) + 217 ) / 255.0f );
		_not_user.m_hp = fmax ( 0 , _not_user.m_hp - damage );
		updateHPbars ( nullptr );
		if ( _user_is_player )
		{
			startShakeEnemySquadler ( nullptr );
			startJumpPlayerSquadler ( nullptr );
		}
		else
		{
			startShakePlayerSquadler ( nullptr );
			startJumpEnemySquadler ( nullptr );
		}
		break;
	}
	return printDialogue ( _user.m_name + " used " + _move.m_name );
}

void cBattleScene::startShakePlayerSquadler ( void* null )
{
	cUtil::functionLerpValue< float, cBattleScene>( &cBattleScene::setShakePlayer , *this , 1.0f , 0.0f , 1.0f );
}



void cBattleScene::startShakeEnemySquadler ( void* null )
{
	cUtil::functionLerpValue<float , cBattleScene> ( &cBattleScene::setShakeEnemy , *this , 1.0f , 0.0f , 1.0f );
}

void cBattleScene::setShakePlayer ( float _t )
{
	m_player_squadler.m_uv_rect.left = m_player_squadler_starting_pos.x + ( sin ( 31.4f * _t ) * _t ) * 0.03;
}

void cBattleScene::setShakeEnemy ( float _t )
{
	m_enemy_squadler.m_uv_rect.left = m_enemy_squadler_starting_pos.x + ( sin ( 31.4f * _t ) * _t ) * 0.03;
}

void cBattleScene::startJumpPlayerSquadler ( void* null )
{
	cUtil::functionLerpValue<float , cBattleScene> ( &cBattleScene::setJumpPlayer , *this , 0.5f , -0.5f , 0.2f );
}

void cBattleScene::startJumpEnemySquadler ( void* null )
{
	cUtil::functionLerpValue<float , cBattleScene> ( &cBattleScene::setJumpEnemy , *this , 0.5f , -0.5f , 0.2f );
}

void cBattleScene::setJumpPlayer ( float _t )
{
	m_player_squadler.m_uv_rect.left = m_player_squadler_starting_pos.x + ( pow ( ( 0.5 - fabs ( _t ) ) + 1.0f , 2.0f ) - 1.0f ) * 0.15;
	m_player_squadler.m_uv_rect.top  = m_player_squadler_starting_pos.y - ( pow ( ( 0.5 - fabs ( _t ) ) + 1.0f , 2.0f ) - 1.0f ) * 0.15;
}

void cBattleScene::setJumpEnemy ( float _t )
{
	m_enemy_squadler.m_uv_rect.left = m_enemy_squadler_starting_pos.x - ( pow ( ( 0.5 - fabs ( _t ) ) + 1.0f , 2.0f ) - 1.0f ) * 0.15;
	m_enemy_squadler.m_uv_rect.top  = m_enemy_squadler_starting_pos.y + ( pow ( ( 0.5 - fabs ( _t ) ) + 1.0f , 2.0f ) - 1.0f ) * 0.15;
}

cEvent* cBattleScene::startFlash ( void* _null )
{
	return cUtil::functionLerpValueDoneEvent<int , cBattleScene> ( &cBattleScene::setFlash , *this , 255 , 0 , 0.1 );
}

void cBattleScene::setFlash ( int _t )
{
	m_fade_rect.m_rectangle_shape.setFillColor ( sf::Color ( 255 , 255 , 255 , _t ) );
}

void cBattleScene::updateSquadlerButtonLabels ( void* _null )
{
	for ( int i = 0; i < 6; i++ )
	{
		if ( m_player.m_squadlers[ i] != nullptr )
		{
			m_squadler_buttons[5 - i].setString( m_player.m_squadlers[i]->m_name );
		}
		else
		{
			m_squadler_buttons[5 - i].setString( "" );
		}
	}
}

void cBattleScene::checkWinLose ( void* _null )
{
	bool has_lost = true;
	for ( int i = 0; i < 6; i++ )
	{
		if ( m_player.m_squadlers[ i ] != nullptr )
		{
			if ( m_player.m_squadlers[ i ]->m_hp > 0 )
			{
				has_lost = false;
				break;
			}
		}
	}
	if ( has_lost )
	{
		lose ();
		return;
	}
	bool has_won = true;
	for ( int i = 0; i < 6; i++ )
	{
		if ( m_enemy.m_squadlers[ i ] != nullptr )
		{
			if ( m_enemy.m_squadlers[ i ]->m_hp > 0 )
			{
				has_won = false;
				break;
			}
		}
	}
	if ( has_won )
	{
		win ();
		return;
	}
}

cEvent* cBattleScene::printDialogue ( const sf::String& _string )
{
	m_dialogue_text.m_label_visible = true;
	m_dialogue_text.setString ( "" );
	m_curr_dialogue = _string;
	return cUtil::functionLerpValueDoneEvent<int , cBattleScene> ( &cBattleScene::setNumDialogueChars , *this , 0 , _string.getSize () , _string.getSize () * 0.05f );
}

void cBattleScene::setNumDialogueChars ( int _i )
{
	m_dialogue_text.setString ( m_curr_dialogue.substring ( 0 , _i ) );
}

void cBattleScene::enemyChoseNewSquadler ( void* _null )
{
	for ( int i = 0; i < 6; i++ )
	{
		if ( m_enemy.m_squadlers[ i ] != nullptr )
		{
			if ( m_enemy.m_squadlers[ i ]->m_hp > 0 )
			{
				selectSquadler ( m_enemy , i );
				startFlash ()->hook<cBattleScene> ( &cBattleScene::showMainButtons , *this );
				return;
			}
		}
	}
	checkWinLose ();
}

void cBattleScene::tryUseCuedMove ( void* _null )
{

	cUtil::callDelayed<cBattleScene> ( &cBattleScene::delayedUseQueuedMove , *this , 0.6f );

}

void cBattleScene::enemyChoseMove ( void* _null )
{
	if ( m_cueued_move != nullptr )
	{
		useMove ( *m_enemy.m_selected_squadler->m_moves[ 0 ] , *m_enemy.m_selected_squadler , *m_player.m_selected_squadler , false )->hook<cBattleScene> ( &cBattleScene::tryUseCuedMove , *this );
	}
	else
	{
		cUtil::callDelayed<cBattleScene> ( &cBattleScene::delayedEnemyChoseMove , *this , 0.6f );

	}



}

void cBattleScene::delayedUseQueuedMove ()
{
	if ( m_player.m_selected_squadler->m_hp > 0 )
	{
		cEvent* after_attack = useMove ( *m_cueued_move , *m_player.m_selected_squadler , *m_enemy.m_selected_squadler , true );
		if ( m_enemy.m_selected_squadler->m_hp > 0 )
		{
			after_attack->hook<cBattleScene> ( &cBattleScene::showMainButtons , *this );
		}
		else
		{
			after_attack->hook<cBattleScene> ( &cBattleScene::enemyChoseNewSquadler , *this );
		}
		m_cueued_move = nullptr;
	}
	else
	{
		updateSquadlerButtonLabels ( nullptr );
		hideHPBar1 ( nullptr );
		showSquadlerButtons ( nullptr );
		hideBackButton ( nullptr );
		checkWinLose ();
	}
}

void cBattleScene::delayedEnemyChoseMove ()
{
	if ( m_enemy.m_selected_squadler->m_hp > 0 )
	{

	cEvent* after_attack = useMove ( *m_enemy.m_selected_squadler->m_moves[ 0 ] , *m_enemy.m_selected_squadler , *m_player.m_selected_squadler , false );
	

	if ( m_player.m_selected_squadler->m_hp > 0 )
	{
		after_attack->hook<cBattleScene> ( &cBattleScene::showMainButtons , *this );
	}
	else
	{
		after_attack->hook<cBattleScene> ( &cBattleScene::updateSquadlerButtonLabels , *this );
		after_attack->hook<cBattleScene> ( &cBattleScene::hideHPBar1 , *this );
		after_attack->hook<cBattleScene> ( &cBattleScene::showSquadlerButtons , *this );
		after_attack->hook<cBattleScene> ( &cBattleScene::hideBackButton , *this );
		after_attack->hook<cBattleScene> ( &cBattleScene::checkWinLose , *this );

	}

	}
	else
	{
		enemyChoseNewSquadler ();
	}

}


void cBattleScene::turnSpeedCheck ()
{

	hideMoveButtons ( nullptr );
	if ( m_player.m_selected_squadler->m_stats[ sSquadler::SPEED ] > m_enemy.m_selected_squadler->m_stats[ sSquadler::SPEED ] )
	{
		useMove ( *m_cueued_move , *m_player.m_selected_squadler , *m_enemy.m_selected_squadler , true )->hook<cBattleScene> ( &cBattleScene::enemyChoseMove , *this );
		m_cueued_move = nullptr;
	}
	else if ( m_player.m_selected_squadler->m_stats[ sSquadler::SPEED ] < m_enemy.m_selected_squadler->m_stats[ sSquadler::SPEED ] )
	{
		enemyChoseMove ();
	}
	else
	{
		if ( rand () % 2 )
		{
			useMove ( *m_cueued_move , *m_player.m_selected_squadler , *m_enemy.m_selected_squadler , true )->hook<cBattleScene> ( &cBattleScene::enemyChoseMove , *this );
			m_cueued_move = nullptr;
		}
		else
		{
			enemyChoseMove ();
		}
	}

}

void cBattleScene::tryToRun ( void* _null )
{
	hideMainButtons ( nullptr );
	printDialogue ( "You try to run away..." )->hook<cBattleScene> ( &cBattleScene::failedToRun , *this );
}

void cBattleScene::failedToRun ( void* _null )
{
	cUtil::callDelayed<cBattleScene> ( &cBattleScene::delayedFailedToRun , *this , 0.7f );
}

void cBattleScene::delayedFailedToRun ()
{
	m_cueued_move = nullptr;
	printDialogue ( "You tripped on your own shoelaces..." )->hook<cBattleScene> ( &cBattleScene::enemyChoseMove , *this );
}

void cBattleScene::win ()
{
	hideMainButtons ( nullptr );
	printDialogue ( "You Have Defeated " + m_enemy.m_name +"!");
}

void cBattleScene::lose ()
{
	hideMainButtons ( nullptr );
	hideSquadlerButtons ( nullptr );
	showHPBar1 ( nullptr );
	printDialogue ( "You Lost To " + m_enemy.m_name + "!" );
}



void cBattleScene::init ( sf::RenderWindow& _window )
{
	{
		sf::Vector2i tmp_window_size = ( sf::Vector2i ) _window.getSize ();
		cScaledElement::m_window_resize->call ( &tmp_window_size );
	}

	printDialogue ( m_enemy.m_name + " Has Challenged You To A Fight To The Death!" );

	cUtil::functionLerpValue<int , cBattleScene> ( &cBattleScene::setFadeAlpha , *this , 255 , 0 , 0.5f );
	cUtil::functionLerpValueDoneEvent<float , cBattleScene> ( &cBattleScene::setSwirl , *this , 1.0f , 0.0f , 2.5f )->hook<cBattleScene> ( &cBattleScene::hideSwirl , *this );

	bool active_scene = true;

	sf::Clock delta_clock;

	while ( active_scene && _window.isOpen () )
	{
		float delta_time = delta_clock.restart ().asSeconds ();
		_window.clear ();
		resetRecentInput ();
		processEvents ( _window );

		cUtil::processLerps ( delta_time );

		cRenderManager::draw ( &_window );

		_window.display ();
	}

}

void cBattleScene::unInit ()
{

}
