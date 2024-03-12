#pragma once

#include "cUIRect.h"
#include "cLabel.h"
#include <sstream>

class cHPBar
{

public:
	cHPBar (const sf::FloatRect& _uv_rect,const cScaledElement::eScaleTo& _scale_flag = cScaledElement::TOP_LEFT);

	cUIRect m_bg_rect;
	cLabel m_name;
	cLabel m_hp_text;
	cLabel m_lvl_text;

	void setHP ( const int& _hp , const int& _max_hp );

	void setName ( const sf::String& _name );
	void setLevel ( const int& _lvl );

	void setVisible ( const bool& _visible );

	cUIRect m_hp_bg_rect;
	cUIRect m_hp_rect;


};