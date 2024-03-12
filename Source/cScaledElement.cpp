#include "cScaledElement.h"

cEvent* cScaledElement::m_window_resize;

void cScaledElement::init()
{
	m_window_resize = new cEvent();
}

void cScaledElement::unInit()
{
	delete m_window_resize;
}

cScaledElement::cScaledElement(const sf::FloatRect& _uv_rect, const bool& _keep_aspect,const eScaleTo& _scale_flag ):
	m_keep_aspect( _keep_aspect ),
	m_scale_flag( _scale_flag ),
	m_uv_rect(_uv_rect)
	
{
	cScaledElement::m_window_resize->hook<cScaledElement>(&cScaledElement::resize, *this);
}

cScaledElement::~cScaledElement()
{
	cScaledElement::m_window_resize->unHook<cScaledElement>(&cScaledElement::resize, *this);
}


sf::FloatRect cScaledElement::baseResize( void* _pointer_to_size )
{
	sf::Vector2i size = *(sf::Vector2i*)_pointer_to_size;
	sf::Vector2f new_position{};
	sf::Vector2f new_size{};
	if ( m_keep_aspect )
	{
		new_size.x = fmin( size.x * m_uv_rect.width , (m_uv_rect.width / m_uv_rect.height) * m_uv_rect.height * size.y );
		new_size.y = fmin( size.y * m_uv_rect.height , (m_uv_rect.height / m_uv_rect.width) * m_uv_rect.width * size.x );
	}
	else
	{
		new_size.x = size.x * m_uv_rect.width;
		new_size.y = size.y * m_uv_rect.height;
	}

	switch ( m_scale_flag )
	{
	case cScaledElement::TOP_LEFT:
		new_position.x = size.x * m_uv_rect.left;
		new_position.y = size.y * m_uv_rect.top;
		break;
	
	case cScaledElement::LEFT:
		new_position.x = size.x * m_uv_rect.left;
		new_position.y = size.y * 0.5f - size.y * (0.5f - m_uv_rect.top) - (new_size.y / 2.0f);
		break;
	
	case cScaledElement::DOWN_LEFT:
		new_position.x = size.x * m_uv_rect.left;
		new_position.y = size.y - size.y * (1.0 - m_uv_rect.top) - new_size.y;
		break;
	
	case cScaledElement::DOWN:
		new_position.x = size.x * 0.5f - size.x * (0.5f - m_uv_rect.left) - (new_size.x / 2.0f);
		new_position.y = size.y - size.y * (1.0 - m_uv_rect.top) - new_size.y;
		break;
	
	case cScaledElement::DOWN_RIGHT:
		new_position.x = size.x - size.x * (1.0 - m_uv_rect.left) - new_size.x;
		new_position.y = size.y - size.y * (1.0 - m_uv_rect.top) - new_size.y;;
		break;
	
	case cScaledElement::RIGHT:
		new_position.x = size.x - size.x * (1.0 - m_uv_rect.left) - new_size.x;
		new_position.y = size.y * 0.5f - size.y * (0.5f - m_uv_rect.top) - (new_size.y / 2.0f);
		break;
	
	case cScaledElement::TOP_RIGHT:
		new_position.x = size.x - size.x * (1.0 - m_uv_rect.left) - new_size.x;
		new_position.y = size.y * m_uv_rect.top;
		break;
	
	case cScaledElement::TOP:
		new_position.x = size.x * 0.5f - size.x * (0.5f - m_uv_rect.left) - (new_size.x / 2.0f);
		new_position.y = size.y * m_uv_rect.top;
		break;
	
	case cScaledElement::CENTER:
		new_position.x = size.x * 0.5f - size.x * (0.5f - m_uv_rect.left) - (new_size.x / 2.0f);
		new_position.y = size.y * 0.5f - size.y * (0.5f - m_uv_rect.top) - (new_size.y / 2.0f);
		break;
	}

	return sf::FloatRect(new_position,new_size);
}
