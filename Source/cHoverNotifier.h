#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class cHoverNotifier
{

	class cBaseHoverHook
	{
	public:
		virtual void callHover () = 0;
		virtual void callUnHover () = 0;
		bool* m_is_active;
		bool m_is_hovered;
		sf::IntRect* m_rect_ptr;
	};

	template <typename T> class cHoverHook : cBaseHoverHook
	{

	public:
		cHoverHook ( T& _obj , void( T::* _hover_ptr )( void ) , void( T::* _un_hover_ptr )( void ) , bool* _is_active , sf::IntRect* _int_rect_ptr ) :
			m_object ( _obj ) ,
			m_hover_ptr ( _hover_ptr ) ,
			m_un_hover_ptr ( _un_hover_ptr )
		{
			m_is_active = _is_active;
			m_is_hovered = false;
			m_rect_ptr = _int_rect_ptr;
		}

		void callHover () { (m_object.*m_hover_ptr )(); }

		void callUnHover () { ( m_object.*m_un_hover_ptr )(  ); }


		T& m_object;
		void( T::* m_hover_ptr )( void );
		void( T::* m_un_hover_ptr )( void );
	};

public:
	static std::list< cBaseHoverHook*> m_hooks;

	template <typename T> static void hook ( T& _obj , void( T::* _hover_ptr )( void ) , void( T::* _un_hover_ptr )( void ) , bool* _is_active , sf::IntRect* _int_rect_ptr )
	{
		m_hooks.push_back ( ( cBaseHoverHook* )new cHoverHook<T> ( _obj , _hover_ptr , _un_hover_ptr , _is_active , _int_rect_ptr ) );
	}

	template <typename T>static void unHook ( T& _obj , void( T::* _hover_ptr )( void ) , void( T::* _un_hover_ptr )( void ) )
	{

		std::list< cBaseHoverHook*> to_remove{};
		std::list<cBaseHoverHook*>::iterator itr = m_hooks.begin ();
		while ( itr != m_hooks.end () )
		{
			cHoverHook <T>* obj = ( cHoverHook <T>* )( *itr );
			if ( obj->m_un_hover_ptr == _un_hover_ptr && obj->m_hover_ptr == _hover_ptr && obj->m_object == _obj )
			{
				to_remove.push_back ( obj );
			}
			++itr;
		}

		while ( to_remove.size () > 0 )
		{
			delete to_remove.back ();
			to_remove.pop_back ();
		}
	}

	~cHoverNotifier ();

	static void mouseMovedCheckHovered ( const sf::Vector2i& _mouse_pos );

};
