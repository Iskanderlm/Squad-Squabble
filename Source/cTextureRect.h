#pragma once


#include "cScaledElement.h"
#include "cResourceManager.h"
#include "cRenderManager.h"

class cTextureRect : public cScaledElement
{

public:
	cTextureRect ( const sf::FloatRect& _uv_rect ,const sf::String& _texture_path, const bool& _keep_aspect = true , const cScaledElement::eScaleTo& _scale_flag = cScaledElement::TOP_LEFT);
	~cTextureRect ();

	void  resize ( void* _pointer_to_size );
	sf::Sprite m_sprite;
	sf::String m_last_tex_path;
	sf::Vector2f m_start_size;
	bool m_tex_rect_visible;

	void setTexture ( const sf::String& _tex_path );

	void setScale ( const sf::Vector2f& _new_scale );

protected:
	void texRectResize ( const sf::FloatRect& _new_rect );
	void draw ( void* _pointer_to_window );
};