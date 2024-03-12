#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "cInput.h"
#include "cClickable.h"
#include "cScaledElement.h"
#include "cRenderManager.h"
#include "cUIRect.h"
#include "cLabel.h"
#include "cButton.h"
#include "cHoverNotifier.h"
#include "cBattleScene.h"

void processEvents(sf::RenderWindow& _window)
{
	sf::Event event;

	while (_window.pollEvent(event))
	{

		switch (event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;


		case sf::Event::KeyPressed:
			cInput::pressedKey(event.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			cInput::pressedButton(event.mouseButton.button);
			break;


		case sf::Event::KeyReleased:
			cInput::releasedKey(event.key.code);
			break;
		case sf::Event::MouseButtonReleased:
			cInput::releasedButton(event.mouseButton.button);
			break;

		case sf::Event::MouseMoved:
			cHoverNotifier::mouseMovedCheckHovered ( sf::Vector2i ( event.mouseMove.x , event.mouseMove.y ) );
			cInput::mouseMoved(event.mouseMove.x, event.mouseMove.y);
			break;

		case sf::Event::Resized:
			sf::FloatRect tmp_rect(0, 0, event.size.width, event.size.height);
			_window.setView(sf::View(tmp_rect));
			cScaledElement::m_last_window_size.x = event.size.width;
			cScaledElement::m_last_window_size.y = event.size.height;
			cScaledElement::m_window_resize->call((void*)&event.size);
			break;

		}

	}

}

void resetRecentInput()
{
	cInput::resetPreFrameInput();
}

void initInputEvents()
{
	cInput::initInputEvents();
}

class cEventBinder {

public:
	void redirectClickEvent(void* _null)
	{
		cClickable::tryClickClickable();
	}
};





int main()
{


	cInput::resetInputMap();
	initInputEvents();
	cResourceManager::init ();
	cRenderManager::init();
	cScaledElement::init();
	cEventBinder event_binder = cEventBinder();
	cInput::hookToButtonPress <cEventBinder>(&cEventBinder::redirectClickEvent, event_binder, sf::Mouse::Left);


	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Testing");

	cScaledElement::m_last_window_size = (sf::Vector2i)window.getSize ();

	srand ( time ( 0 ) );

	cBattleScene bttl_scene = cBattleScene ();
	

	bttl_scene.init ( window );
	

	bttl_scene.unInit();

	cResourceManager::unInit ();
}