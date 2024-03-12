#include "cRenderManager.h"


cEvent* cRenderManager::m_draw_event;
void cRenderManager::init()
{
	m_draw_event = new cEvent();
}

void cRenderManager::unInit()
{
	delete m_draw_event;
}

void cRenderManager::draw(void* _pointer_to_window)
{
	cRenderManager::m_draw_event->call(_pointer_to_window);
}
