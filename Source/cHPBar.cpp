#include "cHPBar.h"

cHPBar::cHPBar ( const sf::FloatRect& _uv_rect , const cScaledElement::eScaleTo& _scale_flag ) :
	m_bg_rect ( _uv_rect , false , _scale_flag ) ,
	m_name ( _uv_rect , "Name" , false , _scale_flag ) ,
	m_hp_text ( _uv_rect , "HP:    0/0" , false , _scale_flag ) ,
	m_lvl_text ( _uv_rect , "Lv 0" , false , _scale_flag ) ,
	m_hp_bg_rect( _uv_rect , false , _scale_flag ),
	m_hp_rect ( _uv_rect , false , _scale_flag)
{

	m_name.setFont ( "Assets/Fonts/Boxy-Bold.ttf" );
	m_hp_text.setFont ( "Assets/Fonts/Boxy-Bold.ttf" );
	m_lvl_text.setFont ( "Assets/Fonts/Boxy-Bold.ttf" );

	if ( _scale_flag == cScaledElement::TOP_LEFT)
	{
		m_lvl_text.setLabelUVRect ( sf::FloatRect ( _uv_rect.left + _uv_rect.width * 0.6f , _uv_rect.top, _uv_rect.width * 0.4f , _uv_rect.height * 0.4f ) );

		m_hp_text.setLabelUVRect ( sf::FloatRect ( _uv_rect.left + _uv_rect.width * 0.2f, _uv_rect.top + _uv_rect.height * 0.6f , _uv_rect.width * 0.8f , _uv_rect.height * 0.4f ) );
		
		m_name.setLabelUVRect ( sf::FloatRect ( _uv_rect.left, _uv_rect.top + _uv_rect.height * 0.05f , _uv_rect.width * 0.3f , _uv_rect.height * 0.4f ) );
		m_hp_rect.setRectUVRect(sf::FloatRect ( _uv_rect.left + _uv_rect.width * 0.39f , _uv_rect.top + _uv_rect.height * 0.45f , _uv_rect.width * 0.6f , _uv_rect.height * 0.15f ));
		m_hp_bg_rect.setRectUVRect ( sf::FloatRect ( _uv_rect.left + _uv_rect.width * 0.39f , _uv_rect.top + _uv_rect.height * 0.45f , _uv_rect.width * 0.6f , _uv_rect.height * 0.15f ) );
	}else{
		m_lvl_text.setLabelUVRect ( sf::FloatRect ( _uv_rect.left , _uv_rect.top - _uv_rect.height * 0.6f , _uv_rect.width * 0.4f , _uv_rect.height * 0.4f ) );
		
		m_hp_text.setLabelUVRect ( sf::FloatRect ( _uv_rect.left , _uv_rect.top, _uv_rect.width * 0.8f , _uv_rect.height * 0.4f ) );
		
		m_name.setLabelUVRect ( sf::FloatRect ( _uv_rect.left - _uv_rect.width * 0.7f , _uv_rect.top - _uv_rect.height * 0.55f , _uv_rect.width * 0.3f , _uv_rect.height * 0.4f ) );
		m_hp_rect.setRectUVRect ( sf::FloatRect ( _uv_rect.left - _uv_rect.width * 0.01f , _uv_rect.top - _uv_rect.height * 0.4f , _uv_rect.width * 0.6f , _uv_rect.height * 0.15f ) );
		m_hp_bg_rect.setRectUVRect ( sf::FloatRect ( _uv_rect.left - _uv_rect.width * 0.01f , _uv_rect.top - _uv_rect.height * 0.4f , _uv_rect.width * 0.6f , _uv_rect.height * 0.15f ) );
	}

	

	m_name.setColor ( sf::Color ( 0 , 0 , 0 , 255 ) );
	m_hp_text.setColor ( sf::Color ( 0 , 0 , 0 , 255 ) );
	m_lvl_text.setColor ( sf::Color ( 0 , 0 , 0 , 255 ) );

	m_hp_rect.setRectStyle ( cUIRect::sRectStyle{ sf::Color ( 96 , 255 , 128 , 255 ) , sf::Color ( 96 , 255 , 128 , 255 ) , 0.0f } );
	m_hp_bg_rect.setRectStyle ( cUIRect::sRectStyle{ sf::Color ( 96 , 96 , 96 , 255 ) , sf::Color ( 96 , 96 , 96 , 255 ) , 0.0f } );
}

void cHPBar::setHP ( const int& _hp , const int& _max_hp )
{
	std::stringstream s_stream;
	s_stream << _hp << "/" << _max_hp;
	std::string str;
	s_stream >> str;
	s_stream >> str;
	s_stream >> str;
	m_hp_text.setString (  sf::String("HP:   "+ str));

	float fill_amount = fmax ( 0.0 , _hp/fmax(1,_max_hp));

	if ( m_bg_rect.m_scale_flag == cScaledElement::TOP_LEFT )
	{
		m_hp_rect.setRectUVRect ( sf::FloatRect (
			m_bg_rect.m_uv_rect.left + m_bg_rect.m_uv_rect.width * 0.39f ,
			m_bg_rect.m_uv_rect.top + m_bg_rect.m_uv_rect.height * 0.45f ,
			m_bg_rect.m_uv_rect.width * 0.6f * fill_amount ,
			m_bg_rect.m_uv_rect.height * 0.15f ) );
	}
	else
	{
		m_hp_rect.setRectUVRect ( sf::FloatRect (
			m_bg_rect.m_uv_rect.left - m_bg_rect.m_uv_rect.width * 0.01f - ( m_bg_rect.m_uv_rect.width * 0.6f * (1.0f- fill_amount )) ,
			m_bg_rect.m_uv_rect.top - m_bg_rect.m_uv_rect.height * 0.4f ,
			m_bg_rect.m_uv_rect.width * 0.6f * fill_amount ,
			m_bg_rect.m_uv_rect.height * 0.15f ) );
	}

}

void cHPBar::setName ( const sf::String& _name )
{
	m_name.setString ( _name );
}

void cHPBar::setLevel ( const int& _lvl )
{
	std::stringstream s_stream;
	s_stream << _lvl;
	std::string str;
	s_stream >> str;
	m_lvl_text.setString ( sf::String ( "Lv " + str ) );
}

void cHPBar::setVisible ( const bool& _visible )
{
	m_bg_rect.m_rect_visible = _visible;
	m_hp_rect.m_rect_visible = _visible;
	m_hp_bg_rect.m_rect_visible = _visible;

	m_hp_text.m_label_visible = _visible;
	m_lvl_text.m_label_visible = _visible;
	m_name.m_label_visible = _visible;

}

