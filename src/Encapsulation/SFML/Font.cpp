#include "Font.hpp"

GOM::Font::Font() { m_font = new sf::Font(); }

GOM::Font::Font(const sf::Font &font) { m_font = new sf::Font(font); }

bool GOM::Font::loadFromFile(const std::string &filename)
{
  return m_font->loadFromFile(filename);
}

const sf::Font *GOM::Font::getFont() { return m_font; }
