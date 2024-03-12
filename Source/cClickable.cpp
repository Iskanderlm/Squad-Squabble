#include "cClickable.h"

std::list<cClickable*> cClickable::m_clickables;

cClickable::cClickable ( sf::IntRect _rect ) :
	m_active ( true ) ,
	m_on_press ( new cEvent () ) ,
	m_on_release ( new cEvent () ) ,
	m_rect ( _rect )
{
	m_clickables.push_back ( this );
}

cClickable::~cClickable ()
{
	m_clickables.remove ( this );
	delete m_on_press;
	delete m_on_release;
}

void cClickable::release ( void* _null )
{
	m_on_release->call ();
}

void cClickable::basePress ()
{
	cInput::hookToButtonReleased <cClickable> ( &cClickable::release , *this , sf::Mouse::Left , cEvent::ONE_SHOT );
	press ();
	m_on_press->call ();
}

void cClickable::tryClickClickable ()
{
	cClickable* selected_ptr = nullptr;

	std::list<cClickable*>::iterator itr = m_clickables.begin ();

	while ( itr != m_clickables.end () )
	{
		if ( ( *itr )->m_rect.contains ( cInput::m_mousePos ) && ( *itr )->m_active )
		{
			selected_ptr = *itr;
			break;
		}

		++itr;
	}

	if ( selected_ptr != nullptr ) { selected_ptr->basePress (); }
}

