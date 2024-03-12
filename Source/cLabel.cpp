#include "cLabel.h"

sf::Vector2i cScaledElement::m_last_window_size;
cLabel::cLabel ( const sf::FloatRect& _uv_rect , const sf::String& _string , const bool& _keep_aspect , const cScaledElement::eScaleTo& _scale_flag ):
	cScaledElement ( _uv_rect , _keep_aspect , _scale_flag ),
	m_label_visible(true)
{
	cRenderManager::m_draw_event->hook<cLabel> ( &cLabel::draw , *this );
	m_text_obj = new sf::Text ();
	m_text_obj->setString ( _string );
}

cLabel::~cLabel ()
{
	cRenderManager::m_draw_event->unHook<cLabel> ( &cLabel::draw , *this );
	if ( m_last_font_path != "" )
	{
		cResourceManager::unReferenceFont ( m_last_font_path );
	}
	
	delete m_text_obj;
}



void cLabel::setString ( const sf::String& _string )
{
	m_text_obj->setString ( _string );
	resize ( &cScaledElement::m_last_window_size );
}

void cLabel::setFont ( const sf::String& _string )
{

	sf::Font* f_ptr = cResourceManager::referenceFont ( _string );
	if ( f_ptr == nullptr ) { return; }

	if ( m_last_font_path != "" )
	{
		cResourceManager::unReferenceFont ( m_last_font_path );
	}

	m_last_font_path = _string;
	m_text_obj->setFont ( *f_ptr );

}

void cLabel::resize ( void* _pointer_to_size )
{
	labelResize ( baseResize( _pointer_to_size ) );
}

void cLabel::setLabelUVRect ( const sf::FloatRect& _new_uv_rect )
{
	m_uv_rect = _new_uv_rect;
	resize ( &cScaledElement::m_last_window_size );
}

void cLabel::labelResize ( const sf::FloatRect& _new_rect )
{

	float size_factor = fmin ( _new_rect.width / (m_text_obj->getLocalBounds ().width / 0.9f ), _new_rect.height / (m_text_obj->getLocalBounds ().height / 0.9f ) );

	m_text_obj->setCharacterSize ( fmax ( size_factor * m_text_obj->getCharacterSize () * 0.9f , 5 ) );

	m_text_obj->setPosition ( _new_rect.getPosition () + sf::Vector2f( (_new_rect.width - m_text_obj->getLocalBounds().width )/2.0f, ( _new_rect.height - m_text_obj->getLocalBounds().height ) / 2.0f ));
}

void cLabel::draw ( void* _pointer_to_window )
{
	if ( m_label_visible )
	{
		( ( sf::RenderWindow* ) _pointer_to_window )->draw ( ( *m_text_obj ) );
	}
	
}
