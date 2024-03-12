#pragma once

#include "cEvent.h"


class cUtil
{

	class cBaseLerpRequest
	{
	public:
		virtual bool lerp (const float& _delta_time) = 0;
		
	};

	template <typename T> class cLerpRequest : public cBaseLerpRequest
	{
	public:

		cLerpRequest (T* _value_ptr,const T& _new_value,const float& _time, cEvent* _event_ptr = nullptr):
			m_on_done( _event_ptr ),
			m_duration( _time ),
			m_time_count (0.0f),
			m_value_ptr( _value_ptr ),
			m_new_value( _new_value ),
			m_start_value(*_value_ptr )
		{
		}

		bool lerp ( const float& _delta_time )
		{
			float l_factor = fmin(m_time_count += _delta_time, m_duration ) / m_duration;
			( *m_value_ptr ) = m_start_value + ( m_new_value - m_start_value ) * l_factor;

			if ( l_factor == 1.0 )
			{
				if ( m_on_done != nullptr )
				{
					m_on_done->call (nullptr);

					delete m_on_done;
					m_on_done = nullptr;
				}
				return true;
			}

			return false;
		}
		cEvent* m_on_done;
		float m_duration;

		float m_time_count;

		T* m_value_ptr;

		T m_new_value;

		T m_start_value;

	};

	template <typename T,typename D> class cCallLerpRequest : public cBaseLerpRequest
	{
	public:

		cCallLerpRequest ( void(D::*_func_pointer)(T) ,D& _obj ,const T& _start_value, const T& _new_value , const float& _time , cEvent* _event_ptr = nullptr) :
			m_on_done ( _event_ptr ) ,
			m_duration ( _time ) ,
			m_time_count ( 0.0f ) ,
			m_function_pointer ( _func_pointer ) ,
			m_object( _obj ),
			m_new_value ( _new_value ) ,
			m_start_value ( _start_value )
		{
		}

		bool lerp ( const float& _delta_time )
		{
			float l_factor = fmin ( m_time_count += _delta_time , m_duration ) / m_duration;
			(m_object.*m_function_pointer)( m_start_value + (T)(( m_new_value - m_start_value ) * l_factor));

			if ( l_factor == 1.0 )
			{
				if ( m_on_done != nullptr )
				{
					m_on_done->call ( nullptr );
					delete m_on_done;
				}
				return true;
			}

			return false;
		}
		cEvent* m_on_done;
		float m_duration;

		float m_time_count;

		void( D::* m_function_pointer )( T );

		D& m_object;

		T m_new_value;

		T m_start_value;

	};



	class cBaseDelayedCall
	{
	public:
		virtual void call () = 0;

		float m_remaining_time;

	};
	template<typename T> class cDelayedCall : public cBaseDelayedCall
	{
	public:
		cDelayedCall ( void( T::* _func_pointer )( ) , T& _object , const float& _time ):
			m_function_pointer( _func_pointer ),
			m_object( _object )
		{
			m_remaining_time = _time;
		}

		void call ()
		{
			( m_object.*m_function_pointer )( );
		}

		void( T::* m_function_pointer )( );
		T& m_object;
	};

public:
	static void processLerps ( const float& _delta_time );

	template<typename T> static void lerpValue ( T* _value_ptr , const T& _new_value , const float& _time)
	{
		m_lerp_requests.push_back ( ( cBaseLerpRequest* ) new cLerpRequest<T> ( _value_ptr , _new_value , _time ) );
	}

	template<typename T> static cEvent* lerpValueDoneEvent ( T* _value_ptr , const T& _new_value , const float& _time )
	{
		cEvent* event_ptr = new cEvent ();
		m_lerp_requests.push_back ( ( cBaseLerpRequest* ) new cLerpRequest<T> ( _value_ptr , _new_value , _time , event_ptr ) );
		return event_ptr;
	}

	template<typename T,typename D> static void functionLerpValue (void(D::*_func_ptr)(T),D& _object,const T& _start_value , const T& _new_value , const float& _time )
	{
		m_lerp_requests.push_back ( ( cBaseLerpRequest* ) new cCallLerpRequest<T , D> ( _func_ptr , _object , _start_value , _new_value , _time) );
	}

	template<typename T, typename D> static cEvent* functionLerpValueDoneEvent ( void( D::* _func_ptr )( T ),D& _object, const T& _start_value , const T& _new_value , const float& _time )
	{
		cEvent* event_ptr = new cEvent ();
		m_lerp_requests.push_back ( ( cBaseLerpRequest* ) new cCallLerpRequest<T,D> ( _func_ptr, _object, _start_value , _new_value , _time , event_ptr ) );
		return event_ptr;
	}

	template<typename T> static void callDelayed ( void( T::* _func_pointer )( ) , T& _object , const float& _time )
	{
		m_delayed_requests.push_back ( ( cBaseDelayedCall* ) new cDelayedCall<T> ( _func_pointer,_object , _time ) );
	}

private:
	static std::list<cBaseLerpRequest*> m_lerp_requests;
	static std::list<cBaseDelayedCall*> m_delayed_requests;


};