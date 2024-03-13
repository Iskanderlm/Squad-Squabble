#include "cButton.h"

#include "cResourceManager.h"

cButton::cButton ( const sf::FloatRect& _uv_rect , const sf::String& _string , const bool& _keep_aspect , const cScaledElement::eScaleTo& _scale_flag , const sRectStyle& _default_style , const sRectStyle& _hovered_style , const sRectStyle& _pressed_style ) :
	cUIRect ( _uv_rect , _keep_aspect , _scale_flag , _default_style ) ,
	cClickable ( sf::IntRect () ) ,
	cLabel ( _uv_rect , _string , _keep_aspect , _scale_flag ) ,
	m_is_hovered ( false ),
	m_is_pressed(false),
	m_curr_style ( eSelectedStyle::DEFAULT ),
	m_default_style( _default_style ),
	m_hovered_style(_hovered_style),
	m_pressed_style(_pressed_style)
{

	m_press_sound = cResourceManager::referenceSound( "Assets/Sounds/Button.wav" );
	m_on_press->hook<cButton> ( &cButton::buttonDown , *this );
	m_on_release->hook<cButton> ( &cButton::buttonUp , *this );

	cHoverNotifier::hook<cButton> ( *this , &cButton::hovered , &cButton::unHovered , &m_active , &m_rect );
}

cButton::~cButton ()
{
	cResourceManager::unReferenceSound( "Button.wav" );
}

void cButton::assignStyle ( const eSelectedStyle& _style , const sRectStyle& _new_style )
{
	switch ( _style )
	{
	case eSelectedStyle::DEFAULT:
		m_default_style = _new_style;
		break;
	case eSelectedStyle::HOVERED:
		m_hovered_style = _new_style;
		break;
	case eSelectedStyle::PRESSED:
		m_pressed_style = _new_style;
		break;
	}

	if ( _style == m_curr_style )
	{
		updateDispStyle ();
	}

}

void cButton::updateDispStyle ()
{
	switch ( m_curr_style )
	{
	case cButton::DEFAULT:
		setRectStyle ( m_default_style );
		break;
	case cButton::HOVERED:
		setRectStyle ( m_hovered_style );
		break;
	case cButton::PRESSED:
		setRectStyle ( m_pressed_style );
		break;
	}
}

void cButton::setVisible ( const bool& _visible )
{
	m_rect_visible = _visible;
	m_label_visible = _visible;
}

void cButton::setVisible ( void* _visible_ptr )
{
	bool visible = *( bool* ) _visible_ptr;
	m_rect_visible = visible;
	m_label_visible = visible;
}

void cButton::hideButton ( void* _null)
{
	m_rect_visible = false;
	m_label_visible = false;
}

void cButton::showButton ( void* _null )
{
	m_rect_visible = true;
	m_label_visible = true;
}

void cButton::deActivate ( void* _null )
{
	m_active = false;
}

void cButton::activate ( void* _null )
{
	m_active = true;
}


void cButton::resize ( void* _pointer_to_size )
{
	buttonResize ( cScaledElement::baseResize ( _pointer_to_size ) );
}

void cButton::buttonResize ( const sf::FloatRect& _new_rect )
{
	labelResize ( _new_rect );
	rectResize ( _new_rect );
	m_rect = (sf::IntRect) _new_rect;
}

void cButton::buttonDown ( void* _null )
{
	m_curr_style = PRESSED;
	m_is_pressed = true;
	m_press_sound.play();
	updateDispStyle ();
}

void cButton::buttonUp ( void* _null )
{
	m_is_pressed = false;
	if ( !m_is_hovered )
	{
		m_curr_style = DEFAULT;
	}
	else
	{
		m_curr_style = HOVERED;
	}
	updateDispStyle ();
}

void cButton::hovered (  )
{
	m_is_hovered = true;
	
	if ( !m_is_pressed )
	{
		m_curr_style = HOVERED;
		updateDispStyle ();
	}
}

void cButton::unHovered (  )
{
	m_is_hovered = false;
	if ( !m_is_pressed )
	{
		m_curr_style = DEFAULT;
		updateDispStyle ();
	}
}
