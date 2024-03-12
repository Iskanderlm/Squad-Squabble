#pragma once
#include "cEvent.h"

class cRenderManager {
public:

	static void init();
	static void unInit();

	static void draw( void* _pointer_to_window );

	static cEvent* m_draw_event;

};