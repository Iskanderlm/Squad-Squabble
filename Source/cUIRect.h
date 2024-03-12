#pragma once
#include "cScaledElement.h"
#include "cRenderManager.h"

class cUIRect : public cScaledElement
{
public:
	struct sRectStyle
	{
		sf::Color m_fill_color = sf::Color{ 255,255,255,255 };
		sf::Color m_outline_color = sf::Color{ 0,0,0,255 };

		float m_outline_thickness = 0.0f;
	};

	cUIRect(const sf::FloatRect& _uv_rect,const bool& _keep_aspect = false,const cScaledElement::eScaleTo& _scale_flag = cScaledElement::TOP_LEFT, const sRectStyle& _style = sRectStyle());
	~cUIRect();

	void setRectStyle( const sRectStyle& _style );

	void setRectUVRect ( const sf::FloatRect& _new_uv_rect );

	void  resize(void* _pointer_to_size);
	sf::RectangleShape m_rectangle_shape;
	bool m_rect_visible;
protected:
	void rectResize ( const sf::FloatRect& _new_rect );
	void draw(void* _pointer_to_window);
};

