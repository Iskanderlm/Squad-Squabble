#include "cEvent.h"

cEvent::cEvent () :
	m_listeners ( std::list<cBaseHook*> () )
{

}

cEvent::~cEvent ()
{
	while ( m_listeners.size () > 0 )
	{
		delete m_listeners.back ();
		m_listeners.pop_back ();
	}
}





void cEvent::call ( void* _arg , int _size )
{
	if ( m_listeners.size () == 0 ) { return;  }

	std::list<cBaseHook*> to_remove = {};

	std::list<cBaseHook*>::iterator hook_itr = m_listeners.begin ();
	do
	{
		if ( ( *hook_itr )->m_flags & cEvent::eFlags::ONE_SHOT )
		{
			to_remove.push_back( *hook_itr );
		}
		callIndividual ( *hook_itr , _arg , _size , false , false );
		++hook_itr;
	} while ( hook_itr != m_listeners.end () );

	std::list<cBaseHook*>::iterator remove_itr = to_remove.end ();
	while ( to_remove.size () > 0 )
	{
		--remove_itr;
		m_listeners.remove ( *remove_itr );
		to_remove.pop_back ();
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  WIP
void cEvent::callIndividual ( cBaseHook* _hook , void* _arg , int _size , bool _end_of_frame , bool _next_frame )
{
	if ( ( _hook->m_flags & cEvent::eFlags::DEFERRED ) && !_next_frame )
	{
		if ( _size > 0 && _arg != nullptr )
		{
			void* stored_arg = new char[_size];

			memcpy ( stored_arg , _arg , _size );
		}
		//TODO Call next frame
		return;
	}
	if ( ( _hook->m_flags & cEvent::eFlags::END_OF_FRAME ) && !_end_of_frame )
	{
		if ( _size > 0 && _arg != nullptr && !_next_frame)
		{
			void* stored_arg = new char[ _size ];

			memcpy ( stored_arg , _arg , _size );
		}
		//TODO Call at end of frame
		return;
	}

	_hook->callFunction ( _arg );
	//func_pointer(_hook->m_func_pointer)(_arg);

	if ( _hook->m_flags & cEvent::eFlags::ONE_SHOT )
	{
		delete _hook;
	}
	if ( _end_of_frame || _next_frame )
	{
		delete[]  _arg;
	}
}