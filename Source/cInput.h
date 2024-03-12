#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include "cEvent.h"

class cInput
{


public:
	friend void processEvents ( sf::RenderWindow& _window );
	friend void resetRecentInput ();
	friend void initInputEvents ();

	static void clearAllInputs ();

	static void resetInputMap ();

	static bool isKeyJustPressed ( const sf::Keyboard::Key& _key );
	static bool isKeyPressed ( const sf::Keyboard::Key& _key );
	static bool isKeyJustReleased ( const sf::Keyboard::Key& _key );

	static bool isButtonJustPressed ( const sf::Mouse::Button& _button );
	static bool isButtonPressed ( const sf::Mouse::Button& _button );
	static bool isButtonJustReleased ( const sf::Mouse::Button& _button );

	template<typename T>static void hookToKeyPress ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Keyboard::Key& _key , const cEvent::eFlags& _flags = cEvent::eFlags::DEFAULT )
	{
		m_pressed_events[ _key ]->hook<T> ( _func_pointer , _object , _flags );
	}
	template<typename T>static void hookToKeyReleased ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Keyboard::Key& _key , const cEvent::eFlags& _flags = cEvent::eFlags::DEFAULT )
	{
		m_released_events[ _key ]->hook<T> ( _func_pointer , _object , _flags );
	}
	template<typename T>static void unHookFromKeyPress ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Keyboard::Key& _key )
	{
		m_pressed_events[ _key ]->unHook<T> ( _func_pointer , _object );
	}
	template<typename T>static void unHookFromKeyReleased ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Keyboard::Key& _key )
	{
		m_released_events[ _key ]->unHook<T> ( _func_pointer , _object );
	}
	template<typename T>static void hookToButtonPress ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Mouse::Button& _button , const cEvent::eFlags& _flags = cEvent::eFlags::DEFAULT )
	{
		int n_key = _button + sf::Keyboard::KeyCount;
		m_pressed_events[ n_key ]->hook<T> ( _func_pointer , _object , _flags );
	}
	template<typename T>static void hookToButtonReleased ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Mouse::Button& _button , const cEvent::eFlags& _flags = cEvent::eFlags::DEFAULT )
	{
		int n_key = _button + sf::Keyboard::KeyCount;
		m_released_events[ n_key ]->hook<T> ( _func_pointer , _object , _flags );
	}
	template<typename T>static void unHookFromButtonPress ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Mouse::Button& _button )
	{
		int n_key = _button + sf::Keyboard::KeyCount;
		m_pressed_events[ n_key ]->unHook<T> ( _func_pointer , _object );
	}
	template<typename T>static void unHookFromButtonReleased ( void( T::* _func_pointer )( void* ) , T& _object , const sf::Mouse::Button& _button )
	{
		int n_key = _button + sf::Keyboard::KeyCount;
		m_released_events[ n_key ]->unHook<T> ( _func_pointer , _object );
	}
	template<typename T> static void hookToAnyPress ( void( T::* _func_pointer )( void* ) , T& _object , const cEvent::eFlags& _flags = cEvent::eFlags::DEFAULT )
	{
		m_any_press_event.hook<T> ( _func_pointer , _object , _flags );
	}
	template<typename T> static void unHookFromAnyPress ( void( T::* _func_pointer )( void* ) , T& _object )
	{
		m_any_press_event.unHook<T> ( _func_pointer , _object );
	}

	static sf::Vector2i m_mousePos;

protected:

	static cEvent m_any_press_event;

	static void resetPreFrameInput ();

	static void initInputEvents ();

	static const int m_num_inputs = sf::Keyboard::KeyCount + sf::Mouse::Button::ButtonCount;

	static std::map<int , int> m_input_map;

	static cEvent* m_pressed_events[ m_num_inputs ];
	static cEvent* m_released_events[ m_num_inputs ];

	static bool m_just_pressed[ m_num_inputs ];
	static bool m_just_released[ m_num_inputs ];
	static bool m_is_pressed[ m_num_inputs ];

	static void mouseMoved ( const int& _x , const int& _y );

	static void pressedKey ( const sf::Keyboard::Key& _key );
	static void pressedButton ( const sf::Mouse::Button& _button );

	static void releasedKey ( const sf::Keyboard::Key& _key );
	static void releasedButton ( const sf::Mouse::Button& _button );

};