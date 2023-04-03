#include "Text.hpp"

void GOM::Text::setFont(GOM::IFont *font)
{
  m_text.setFont(*dynamic_cast<GOM::Font *>(font)->getFont());
}

void GOM::Text::setPosition(const GOM::Vector2f &position)
{
  m_text.setPosition(position.x, position.y);
}

void GOM::Text::setString(const std::string &string)
{
  m_text.setString(string);
}

void GOM::Text::setCharacterSize(unsigned int size)
{
  m_text.setCharacterSize(size);
}

void GOM::Text::setColor(const GOM::Color &color)
{
  sf::Color sfml_color(color.r, color.g, color.b, color.a);
  m_text.setFillColor(sfml_color);
}

const GOM::IFont *GOM::Text::getFont()
{
  const sf::Font *sfml_font = m_text.getFont();
  GOM::Font *font = new GOM::Font(*sfml_font);
  return font;
}

unsigned int GOM::Text::getCharacterSize()
{
  return m_text.getCharacterSize();
}

// const GOM::Color &GOM::Text::getColor() const {

// }

void GOM::Text::setScale(const GOM::Vector2f &factor)
{
  sf::Vector2f sfml_vector(factor.x, factor.y);
  m_text.setScale(sfml_vector);
}

const GOM::Vector2f &GOM::Text::getPosition()
{
  sf::Vector2f sfml_vector = m_text.getPosition();
  m_position = {sfml_vector.x, sfml_vector.y};
  return m_position;
}

const std::string &GOM::Text::getString()
{
  m_str = m_text.getString();
  return m_str;
}

GOM::FloatRect GOM::Text::getLocalBounds()
{
  sf::FloatRect sfml_bounds = m_text.getLocalBounds();
  return GOM::FloatRect{sfml_bounds.left, sfml_bounds.top, sfml_bounds.width,
                        sfml_bounds.height};
}

sf::Text &GOM::Text::getText() { return m_text; }