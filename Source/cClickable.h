#pragma once

#include <list>
#include "cInput.h"

class cEventBinder;

class cClickable
{

	static std::list<cClickable*> m_clickables;


public:
	
	cClickable (sf::IntRect _rect);
	~cClickable ();


	bool m_active;
	
	cEvent* m_on_press;
	cEvent* m_on_release;

	sf::IntRect m_rect;

	void basePress ();

	void press () {};

	friend class cEventBinder;

protected:

	void release (void* _null);

	static void tryClickClickable ();
};