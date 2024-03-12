#pragma once

#include <list>


class cEvent
{
	class cBaseHook
	{
	public:
		virtual void callFunction ( void* _arg ) = 0;
		int m_flags = 0;
	};

	template<typename T>class cHook : cBaseHook
	{
	public:
		cHook ( void( T::* _func_ptr )( void* ) , T& _object , const int& _flags ) :
			m_func_pointer ( _func_ptr ) ,
			m_object ( _object )
		{

			m_flags = _flags;
		}

		void callFunction ( void* _arg ) { ( m_object.*m_func_pointer )( _arg ); }

		void( T::* m_func_pointer )( void* );
		T& m_object;

	};

public:

	cEvent ();
	~cEvent ();

	enum eFlags
	{
		DEFAULT      = 0 ,
		ONE_SHOT     = 1 ,
		DEFERRED     = 2 ,
		NO_ARG       = 4 ,
		END_OF_FRAME = 8 ,
		STATIC       = 16
	};

	std::list<cBaseHook*> m_listeners;

	template<typename T>void hook ( void( T::* _func_ptr )( void* ) , T& _object , int _flags = eFlags::DEFAULT )
	{
		if ( isHooked<T> ( _func_ptr , _object ) )
		{
			//TODO error stuff/////////////////////////////////////////////////////////////////////////////////////////

			return;
		}

		m_listeners.push_back ( ( cBaseHook* )new cHook<T>{ _func_ptr,_object ,_flags } );

	}

	template<typename T>void unHook ( void( T::* _func_ptr )( void* ) , T& _object )
	{
		if ( !isHooked<T> ( _func_ptr , _object ) )
		{
			//TODO error stuff/////////////////////////////////////////////////////////////////////////////////////////////
			return;
		}

		std::list< cBaseHook*> to_remove{};

		std::list<cBaseHook*>::iterator hook_itr = m_listeners.end ();
		do
		{
			--hook_itr;
			if ( ( ( cHook<T>* ) * hook_itr )->m_func_pointer == _func_ptr && ( &( ( cHook<T>* ) * hook_itr )->m_object == &_object ) )
			{
				to_remove.push_back ( *hook_itr );
			}


		} while ( hook_itr != m_listeners.begin () );

		while ( to_remove.size () > 0 )
		{
			delete( to_remove.back () );
			to_remove.pop_back ();
		}
	}



	template<typename T>bool isHooked ( void( T::* _func_ptr )( void* ) , T& _object )
	{
		if ( m_listeners.size () == 0 ) { return false; }

		std::list<cBaseHook*>::iterator hook_itr = m_listeners.begin ();
		do
		{
			if ( ( ( cHook<T>* ) * hook_itr )->m_func_pointer == _func_ptr && ( &( ( cHook<T>* ) * hook_itr )->m_object == &_object ) ) { return true; }

			++hook_itr;
		} while ( hook_itr != m_listeners.end () );

		return false;
	}

	void call ( void* _arg = nullptr , int _size = 0 );

private:

	void callIndividual ( cBaseHook* _hook , void* _arg , int _size , bool _end_of_frame , bool _next_frame );

};