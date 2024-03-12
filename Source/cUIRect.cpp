#include "cUIRect.h"

cUIRect::cUIRect( const sf::FloatRect& _uv_rect , const bool& _keep_aspect , const cScaledElement::eScaleTo& _scale_flag,const sRectStyle& _style ) :
	cScaledElement( _uv_rect , _keep_aspect, _scale_flag ) ,
	m_rectangle_shape( sf::RectangleShape( ) ),
	m_rect_visible(true)
{
	setRectStyle( _style );
	cRenderManager::m_draw_event->hook<cUIRect>( &cUIRect::draw , *this );
}

cUIRect::~cUIRect( )
{
	cRenderManager::m_draw_event->unHook<cUIRect>( &cUIRect::draw , *this );
}

void cUIRect::setRectStyle( const sRectStyle& _style )
{
	m_rectangle_shape.setFillColor( _style.m_fill_color );
	m_rectangle_shape.setOutlineColor( _style.m_outline_color );
	m_rectangle_shape.setOutlineThickness( _style.m_outline_thickness );
}

void cUIRect::setRectUVRect ( const sf::FloatRect& _new_uv_rect )
{
	m_uv_rect = _new_uv_rect;
	resize (&cScaledElement::m_last_window_size);
}

void cUIRect::resize( void* _pointer_to_size )
{
	rectResize ( baseResize( _pointer_to_size ) );

}

void cUIRect::rectResize ( const sf::FloatRect& _new_rect )
{
	m_rectangle_shape.setSize ( _new_rect.getSize () );
	m_rectangle_shape.setPosition ( _new_rect.getPosition () );
}

void cUIRect::draw( void* _pointer_to_window )
{
	if ( m_rect_visible )
	{
		( ( sf::RenderWindow* ) _pointer_to_window )->draw ( m_rectangle_shape );
	}
	
}
