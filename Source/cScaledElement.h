#pragma once
#include "cEvent.h"
#include <SFML/Graphics.hpp>

class cScaledElement
{
public:
	static void init();
	static void unInit();

	enum eScaleTo
	{
		TOP_LEFT   = 0,
		LEFT       = 1,
		DOWN_LEFT  = 2,
		DOWN       = 3,
		DOWN_RIGHT = 4,
		RIGHT      = 5,
		TOP_RIGHT  = 6,
		TOP        = 7,
		CENTER     = 8
	};

	cScaledElement( const sf::FloatRect& _uv_rect, const bool& _keep_aspect = false, const eScaleTo& _scale_flag = TOP_LEFT );
	~cScaledElement();

	static cEvent* m_window_resize;

	bool m_keep_aspect;
	eScaleTo m_scale_flag;
	sf::FloatRect m_uv_rect;
	friend void processEvents ( sf::RenderWindow& _window );
	friend int main ();
protected:
	static sf::Vector2i m_last_window_size;

	virtual void resize(void* _pointer_to_size) = 0;
	sf::FloatRect baseResize(void* _pointer_to_size );

	

};

