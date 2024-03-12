#include "cHoverNotifier.h"


std::list<cHoverNotifier::cBaseHoverHook*> cHoverNotifier::m_hooks;

cHoverNotifier::~cHoverNotifier ()
{
	while ( m_hooks.size () > 0 )
	{
		delete m_hooks.back ();
		m_hooks.pop_back ();
	}

}

void cHoverNotifier::mouseMovedCheckHovered ( const sf::Vector2i& _mouse_pos )
{

	bool has_set_hover = false;

	std::list<cBaseHoverHook*>::iterator itr = m_hooks.begin ();

	while ( itr != m_hooks.end () )
	{
		cBaseHoverHook* obj = ( *itr );

		if ( !has_set_hover && *obj->m_is_active && obj->m_rect_ptr->contains ( _mouse_pos ) )
		{
			has_set_hover = true;
			if ( !obj->m_is_hovered )
			{
				obj->m_is_hovered = true;
				obj->callHover ();
			}
		}
		else if( obj->m_is_hovered )
		{
			obj->callUnHover ();
			obj->m_is_hovered = false;
		}
		++itr;
	}
	

}
