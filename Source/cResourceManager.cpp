#include "cResourceManager.h"

std::list<cResourceManager::sFontInstance*> cResourceManager::m_font_instances;
std::list<cResourceManager::sTextureInstance*> cResourceManager::m_texture_instances;

sf::Font* cResourceManager::referenceFont ( const sf::String& _path )
{
	std::list<sFontInstance*>::iterator itr = findFontInstance ( _path );

	if ( itr != m_font_instances.end () )
	{
		( *itr )->m_references++;
		return &( *itr )->m_font;
	}

	sFontInstance* f_instance = new sFontInstance ();


	f_instance->m_font = sf::Font ();
	if ( !f_instance->m_font.loadFromFile ( _path ) )
	{
		//TODO ERROR STUFF ////////////////////////////////////////////////////////////////////////////////////////////
		delete f_instance;
		return nullptr;
	}
	f_instance->m_references = 1;
	f_instance->m_path = _path;
	m_font_instances.push_back ( f_instance );
	return &( f_instance->m_font );
}

void cResourceManager::unReferenceFont ( const sf::String& _path )
{
	std::list<sFontInstance*>::iterator itr = findFontInstance ( _path );

	if ( itr != m_font_instances.end () )
	{
		sFontInstance* f_ptr = *itr;
		f_ptr->m_references--;
		if ( f_ptr->m_references == 0 )
		{
			m_font_instances.remove ( f_ptr );
			delete f_ptr;
		}
		return;
	}
}
void cResourceManager::unReferenceTexture ( const sf::String& _path )
{
	std::list<sTextureInstance*>::iterator itr = findTextureInstance ( _path );

	if ( itr != m_texture_instances.end () )
	{
		sTextureInstance* t_ptr = *itr;
		t_ptr->m_references--;
		if ( t_ptr->m_references == 0 )
		{
			m_texture_instances.remove ( t_ptr );
			delete t_ptr;
		}
		return;
	}
}

sf::Texture* cResourceManager::referenceTexture ( const sf::String& _path )
{
	std::list<cResourceManager::sTextureInstance*>::iterator itr = findTextureInstance ( _path );

	if ( itr != m_texture_instances.end () )
	{
		( *itr )->m_references++;
		return &( *itr )->m_texture;
	}

	sTextureInstance* t_instance = new sTextureInstance ();


	t_instance->m_texture = sf::Texture ();
	if ( !t_instance->m_texture.loadFromFile ( _path ) )
	{
		//TODO ERROR STUFF ////////////////////////////////////////////////////////////////////////////////////////////
		delete t_instance;
		return nullptr;
	}
	t_instance->m_references = 1;
	t_instance->m_path = _path;
	m_texture_instances.push_back ( t_instance );
	return &( t_instance->m_texture );
}

std::list<cResourceManager::sFontInstance*>::iterator cResourceManager::findFontInstance ( const sf::String& _path )
{
	std::list<cResourceManager::sFontInstance*>::iterator itr = m_font_instances.begin ();
	while ( itr != m_font_instances.end () )
	{
		if ( ( *itr )->m_path == _path )
		{
			return itr;
		}
		++itr;
	}
	return itr;
}

std::list<cResourceManager::sTextureInstance*>::iterator cResourceManager::findTextureInstance ( const sf::String& _path )
{
	std::list<cResourceManager::sTextureInstance*>::iterator itr = m_texture_instances.begin ();
	while ( itr != m_texture_instances.end () )
	{
		if ( ( *itr )->m_path == _path )
		{
			return itr;
		}
		++itr;
	}
	return itr;
}

void cResourceManager::init ()
{
	m_font_instances    = std::list< sFontInstance*    >();
	m_texture_instances = std::list< sTextureInstance* >();
}

void cResourceManager::unInit ()
{
	while ( m_font_instances.size () > 0 )
	{
		delete m_font_instances.back ();
		m_font_instances.pop_back ();
	}
	while ( m_texture_instances.size () > 0 )
	{
		delete m_texture_instances.back ();
		m_texture_instances.pop_back ();
	}
}
