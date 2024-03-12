#pragma once

#include<list>
#include<SFML/Graphics.hpp>

class cResourceManager
{

	struct sFontInstance
	{
		sf::String m_path;
		int m_references = 0;
		sf::Font m_font;
	};

	struct sTextureInstance
	{
		sf::String m_path;
		int m_references = 0;
		sf::Texture m_texture;
	};
	
public:



	static sf::Font* referenceFont ( const sf::String& _path );
	static void unReferenceFont ( const sf::String& _path );

	static sf::Texture* referenceTexture ( const sf::String& _path );
	static void unReferenceTexture ( const sf::String& _path );


	friend int main ();
private:

	static std::list<sFontInstance*> m_font_instances;
	static std::list<sTextureInstance*> m_texture_instances;

	static std::list<sFontInstance*>::iterator findFontInstance ( const sf::String& _path );

	static std::list<sTextureInstance*>::iterator findTextureInstance ( const sf::String& _path );

protected:
	static void init ();
	static void unInit ();

};