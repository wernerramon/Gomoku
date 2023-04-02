#include "Texture.hpp"

GOM::Texture::Texture() { m_texture = new sf::Texture(); }

GOM::Texture::Texture(const sf::Texture &texture) {
  m_texture = new sf::Texture(texture);
}

bool GOM::Texture::loadFromFile(const std::string &filename) {
  return m_texture->loadFromFile(filename);
}

bool GOM::Texture::loadFromFile(const std::string &filename,
                                  const IntRect &area) {
  sf::IntRect sfml_area(area.left, area.top, area.width, area.height);
  return m_texture->loadFromFile(filename, sfml_area);
}

GOM::Vector2u GOM::Texture::getSize() const {
  sf::Vector2u size = m_texture->getSize();
  return {size.x, size.y};
}

const sf::Texture *GOM::Texture::getTexture() { return m_texture; }
