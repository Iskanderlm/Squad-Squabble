#pragma once

#include "cScene.h"
#include "cButton.h"
#include "cHPBar.h"
#include "cUtil.h"
#include "cTextureRect.h"
#include "sTrainer.h"
#include "cSquadlerFactory.h"
#include <list>

class cBattleScene : public cScene
{

public:
	cBattleScene ();

	void init ( sf::RenderWindow& _window );
	void unInit ();


	void hideMainButtons ( void* _null);
	void showMainButtons ( void* _null );

	void hideSquadlerButtons ( void* _null );
	void showSquadlerButtons ( void* _null );

	void hideBackButton ( void* _null );
	void showBackButton ( void* _null );

	void hideMoveButtons ( void* _null );
	void showMoveButtons ( void* _null );

	void hideHPBar1 ( void* _null );
	void showHPBar1 ( void* _null );

	void hideHPBar2 ( void* _null );
	void showHPBar2 ( void* _null );

	void setFadeAlpha (int _new_alpha);

	void setSwirl ( float _t );

	void hideSwirl ( void* _null );


	void useMove1 ( void* _null );
	void useMove2 ( void* _null );
	void useMove3 ( void* _null );
	void useMove4 ( void* _null );

	void chooseSquadler1 ( void* _null );
	void chooseSquadler2 ( void* _null );
	void chooseSquadler3 ( void* _null );
	void chooseSquadler4 ( void* _null );
	void chooseSquadler5 ( void* _null );
	void chooseSquadler6 ( void* _null );

	void selectSquadler ( sTrainer& _trainer , const int& _squadler_index );

	void updateHPbars ( void* _null );

	cEvent* useMove ( sMove& _move , sSquadler& _user , sSquadler& _not_user , const bool& _user_is_player );

	void startShakePlayerSquadler ( void* null );
	void startShakeEnemySquadler ( void* null );

	void setShakePlayer ( float _t );
	void setShakeEnemy ( float _t );

	void startJumpPlayerSquadler ( void* null );
	void startJumpEnemySquadler ( void* null );

	void setJumpPlayer ( float _t );
	void setJumpEnemy ( float _t );

	cEvent* startFlash (void* _null = nullptr);

	void setFlash ( int _t );

	void updateSquadlerButtonLabels ( void* _null );

	void checkWinLose ( void* _null = nullptr );

	cEvent* printDialogue ( const sf::String& _string );

	void setNumDialogueChars ( int _i );

	void enemyChoseNewSquadler ( void* _null = nullptr );

	void tryUseCuedMove ( void* _null = nullptr );

	void enemyChoseMove ( void* _null = nullptr );

	void delayedUseQueuedMove ();

	void delayedEnemyChoseMove ();

	void turnSpeedCheck ();

	void tryToRun ( void* _null = nullptr );

	void failedToRun ( void* _null = nullptr );

	void delayedFailedToRun ();

	void win ();
	void lose ();

	cTextureRect m_bg_rect;

	cTextureRect m_enemy_squadler;
	cTextureRect m_player_squadler;

	sf::Vector2f m_player_squadler_starting_pos;
	sf::Vector2f m_enemy_squadler_starting_pos;

	cLabel m_dialogue_text;
	sf::String m_curr_dialogue;

	cButton m_run;
	cButton m_squadler;
	cButton m_bag;
	cButton m_fight;

	cButton m_back_button;

	cButton m_move_buttons[ 4 ];

	cButton m_squadler_buttons[ 6 ];

	cHPBar m_hp_bar_1;
	cHPBar m_hp_bar_2;

	cUIRect m_fade_rect;
	cTextureRect m_spiral;

	sTrainer m_player;
	sTrainer m_enemy;

	sMove* m_cueued_move = nullptr;
};