#include "cTextureRect.h"

cTextureRect::cTextureRect ( const sf::FloatRect& _uv_rect , const sf::String& _texture_path , const bool& _keep_aspect , const cScaledElement::eScaleTo& _scale_flag ) :
	cScaledElement ( _uv_rect , _keep_aspect , _scale_flag ),
	m_sprite(*cResourceManager::referenceTexture( _texture_path )),
	m_last_tex_path( _texture_path ),
	m_start_size( _uv_rect.getSize() ),
	m_tex_rect_visible(true)
{
	cRenderManager::m_draw_event->hook<cTextureRect> ( &cTextureRect::draw , *this );
}

cTextureRect::~cTextureRect ()
{
	cRenderManager::m_draw_event->unHook<cTextureRect> ( &cTextureRect::draw , *this );
	cResourceManager::unReferenceTexture ( m_last_tex_path );
}

void cTextureRect::resize ( void* _pointer_to_size )
{
	texRectResize ( baseResize ( _pointer_to_size ) );
}

void cTextureRect::setTexture ( const sf::String& _tex_path )
{


	sf::Texture* t_ptr = cResourceManager::referenceTexture ( _tex_path );
	if ( t_ptr == nullptr ) { return; }

	if ( m_last_tex_path != "" )
	{
		cResourceManager::unReferenceTexture ( m_last_tex_path );
	}

	m_last_tex_path = _tex_path;
	m_sprite.setTexture ( *t_ptr,true );

}

void cTextureRect::setScale ( const sf::Vector2f& _new_scale )
{
	m_uv_rect.width = _new_scale.x * m_start_size.x;
	m_uv_rect.height = _new_scale.y * m_start_size.y;
	texRectResize ( baseResize ( &cScaledElement::m_last_window_size ) );
}

void cTextureRect::texRectResize ( const sf::FloatRect& _new_rect )
{
	m_sprite.setScale ( sf::Vector2f(_new_rect.width / m_sprite.getTextureRect().width , _new_rect.height / m_sprite.getTextureRect ().height ));
}

void cTextureRect::draw ( void* _pointer_to_window )
{
	if(m_tex_rect_visible){
		m_sprite.setPosition (sf::Vector2f( m_uv_rect.left * cScaledElement::m_last_window_size.x, m_uv_rect.top * cScaledElement::m_last_window_size.y ));
		( ( sf::RenderWindow* ) _pointer_to_window )->draw ( m_sprite );
	}
	
}
