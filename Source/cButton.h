#pragma once

#include "cClickable.h"
#include "cUIRect.h"
#include "cLabel.h"
#include "cHoverNotifier.h"

#include <SFML/Audio.hpp>

class cButton : public cUIRect ,public cLabel, public cClickable
{
	
public:
	enum eSelectedStyle
	{
		DEFAULT = 0 ,
		HOVERED = 1 ,
		PRESSED = 2
	};

	cButton ( const sf::FloatRect& _uv_rect , const sf::String& _string = "" , const bool& _keep_aspect = false , const cScaledElement::eScaleTo& _scale_flag = cScaledElement::TOP_LEFT , const sRectStyle& _default_style = sRectStyle () , const sRectStyle& _hovered_style = sRectStyle () , const sRectStyle& _pressed_style = sRectStyle () );
	
	~cButton ();

	void assignStyle ( const eSelectedStyle& _style, const sRectStyle& _new_style );

	void updateDispStyle ();

	bool m_is_hovered;
	bool m_is_pressed;

	void setVisible (const bool& _visible);

	void setVisible ( void* _visible_ptr );

	void hideButton ( void* _null );
	void showButton ( void* _null );

	void deActivate ( void* _null );
	void activate( void* _null );

protected:

	eSelectedStyle m_curr_style;

	sRectStyle m_default_style;
	sRectStyle m_hovered_style;
	sRectStyle m_pressed_style;

	void resize (void* _pointer_to_size );
	void buttonResize ( const sf::FloatRect& _new_rect );

	void buttonDown ( void* _null );
	void buttonUp ( void* _null );
	void hovered (  );
	void unHovered (  );

	sf::Sound m_press_sound;
};