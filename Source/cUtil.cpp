#include "cUtil.h"

std::list<cUtil::cBaseLerpRequest*> cUtil::m_lerp_requests;
std::list<cUtil::cBaseDelayedCall*> cUtil::m_delayed_requests;

void cUtil::processLerps ( const float& _delta_time )
{
	if ( m_lerp_requests.size () != 0 )
	{

		std::list<cBaseLerpRequest*>::iterator itr = m_lerp_requests.begin ();

		std::list<cBaseLerpRequest*> to_remove{};

		while ( itr != m_lerp_requests.end () )
		{

			if ( ( *itr )->lerp ( _delta_time ) )
			{
				to_remove.push_back ( ( *itr ) );
			}

			++itr;
		}
		while ( to_remove.size () > 0 )
		{
			m_lerp_requests.remove ( to_remove.back () );

			delete to_remove.back ();

			to_remove.pop_back ();

		}
	}
	if ( m_delayed_requests.size () != 0 )
	{

		std::list<cBaseDelayedCall*>::iterator itr = m_delayed_requests.begin ();

		std::list<cBaseDelayedCall*> to_remove{};

		while ( itr != m_delayed_requests.end () )
		{
			( *itr )->m_remaining_time -= _delta_time;

			if ( ( *itr )->m_remaining_time <= 0 )
			{
				( *itr )->call ();
				to_remove.push_back ( ( *itr ) );
			}

			++itr;
		}
		while ( to_remove.size () > 0 )
		{
			m_delayed_requests.remove ( to_remove.back () );

			delete to_remove.back ();

			to_remove.pop_back ();

		}
	}

}
