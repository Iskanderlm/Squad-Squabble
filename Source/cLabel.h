#pragma once
#include "cScaledElement.h"
#include "cRenderManager.h"
#include "cResourceManager.h"

class cLabel : public cScaledElement
{
public:
	cLabel ( const sf::FloatRect& _uv_rect ,const sf::String& _string = "" ,  const bool& _keep_aspect = false , const cScaledElement::eScaleTo & _scale_flag = cScaledElement::TOP_LEFT);
	~cLabel ();

	void setString ( const sf::String& _string );

	void setFont ( const sf::String& _string );

	void setColor       ( const sf::Color& _color ) { m_text_obj->setFillColor        ( _color ); }
	void setOutlineColor( const sf::Color& _color ) { m_text_obj->setOutlineColor     ( _color ); }
	void setOutlineWidth( const float&     _width ) { m_text_obj->setOutlineThickness ( _width ); }


	bool m_label_visible;

	void  resize ( void* _pointer_to_size );

	void setLabelUVRect ( const sf::FloatRect& _new_uv_rect );

private:

	

	sf::Text* m_text_obj;
	sf::String m_last_font_path;

	void draw ( void* _pointer_to_window );

protected:
	void labelResize ( const sf::FloatRect& _new_rect );
};

