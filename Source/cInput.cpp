#include "cInput.h"

void cInput::clearAllInputs ()
{
	memset ( cInput::m_is_pressed , 0 , m_num_inputs );
	memset ( cInput::m_just_pressed , 0 , m_num_inputs );
	memset ( cInput::m_just_released , 0 , m_num_inputs );
}

sf::Vector2i cInput::m_mousePos;
cEvent cInput::m_any_press_event;
std::map<int , int> cInput::m_input_map;
cEvent* cInput::m_pressed_events[ cInput::m_num_inputs ];
cEvent* cInput::m_released_events[ cInput::m_num_inputs ];

bool cInput::m_just_pressed[ cInput::m_num_inputs ];
bool cInput::m_just_released[ cInput::m_num_inputs ];
bool cInput::m_is_pressed[ cInput::m_num_inputs ];

void cInput::resetInputMap ()
{
	cInput::clearAllInputs ();
	cInput::m_input_map.clear ();

	for ( int i = 0; i < m_num_inputs; i++ )
	{
		m_input_map[ i ] = i;
	}
}


void cInput::resetPreFrameInput ()
{
	memset ( cInput::m_just_pressed , 0 , m_num_inputs );
	memset ( cInput::m_just_released , 0 , m_num_inputs );
}

void cInput::initInputEvents ()
{
	for ( int i = 0; i < m_num_inputs; i++ )
	{
		m_pressed_events[ i ] = new cEvent ();
		m_released_events[ i ] = new cEvent ();
	}
}


void cInput::pressedKey ( const sf::Keyboard::Key& _key )
{
	if ( !m_input_map.count ( _key ) ) { return; }

	int remapped_key = m_input_map[ _key ];

	if ( m_is_pressed[ remapped_key ] ) { return; }

	m_is_pressed[ remapped_key ] = true;
	m_just_pressed[ remapped_key ] = true;

	m_pressed_events[ remapped_key ]->call ();
	m_any_press_event.call ( &remapped_key,sizeof( int ));
}

void cInput::mouseMoved ( const int& _x , const int& _y )
{
	m_mousePos.x = _x;
	m_mousePos.y = _y;
}

void cInput::pressedButton ( const sf::Mouse::Button& _button )
{
	int n_key = _button + sf::Keyboard::KeyCount;

	if ( !m_input_map.count ( n_key ) ) { return; }

	int remapped_key = m_input_map[ n_key ];

	if ( m_is_pressed[ remapped_key ] ) { return; }

	m_is_pressed[ remapped_key ] = true;
	m_just_pressed[ remapped_key ] = true;

	m_pressed_events[ remapped_key ]->call ();
	m_any_press_event.call ( &remapped_key , sizeof ( int ) );
}


void cInput::releasedKey ( const sf::Keyboard::Key& _key )
{
	if ( !m_input_map.count ( _key ) ) { return; }

	int remapped_key = m_input_map[ _key ];

	if ( !m_is_pressed[ remapped_key ] ) { return; }

	m_is_pressed[ remapped_key ] = false;
	m_just_released[ remapped_key ] = true;

	m_released_events[ remapped_key ]->call ();
}

void cInput::releasedButton ( const sf::Mouse::Button& _button )
{
	int n_key = _button + sf::Keyboard::KeyCount;

	if ( !m_input_map.count ( n_key ) ) { return; }

	int remapped_key = m_input_map[ n_key ];

	if ( !m_is_pressed[ remapped_key ] ) { return; }

	m_is_pressed[ remapped_key ] = false;
	m_just_released[ remapped_key ] = true;

	m_released_events[ remapped_key ]->call ();

}




bool cInput::isKeyJustPressed ( const sf::Keyboard::Key& _key )
{
	return m_just_pressed[ _key ];
}

bool cInput::isKeyPressed ( const sf::Keyboard::Key& _key )
{
	return m_is_pressed[ _key ];
}

bool cInput::isKeyJustReleased ( const sf::Keyboard::Key& _key )
{
	return m_just_released[ _key ];
}



bool cInput::isButtonJustPressed ( const sf::Mouse::Button& _button )
{
	int n_key = _button + sf::Keyboard::KeyCount;
	return m_just_pressed[ n_key ];
}

bool cInput::isButtonPressed ( const sf::Mouse::Button& _button )
{
	int n_key = _button + sf::Keyboard::KeyCount;
	return m_is_pressed[ n_key ];
}

bool cInput::isButtonJustReleased ( const sf::Mouse::Button& _button )
{
	int n_key = _button + sf::Keyboard::KeyCount;
	return m_just_released[ n_key ];
}


typedef void( *func_pointer )( void* );




