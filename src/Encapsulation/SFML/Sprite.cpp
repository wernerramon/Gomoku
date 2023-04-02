#include "Sprite.hpp"

void GOM::Sprite::setTexture(GOM::ITexture *texture, bool reset_rect) {
  m_sprite.setTexture(*dynamic_cast<GOM::Texture *>(texture)->getTexture(),
                      reset_rect);
}

void GOM::Sprite::setTextureRect(const GOM::IntRect &rectangle) {
  sf::IntRect sfml_rectangle(rectangle.left, rectangle.top, rectangle.width,
                             rectangle.height);
  m_sprite.setTextureRect(sfml_rectangle);
}

void GOM::Sprite::setPosition(const GOM::Vector2f &position) {
  m_sprite.setPosition(position.x, position.y);
}

void GOM::Sprite::setScale(const GOM::Vector2f &factor) {
  m_sprite.setScale(factor.x, factor.y);
}

void GOM::Sprite::setRotation(float angle) { m_sprite.setRotation(angle); }

void GOM::Sprite::setOrigin(const GOM::Vector2f &origin) {
  m_sprite.setOrigin(origin.x, origin.y);
}

void GOM::Sprite::setColor(const GOM::Color &color) {
  sf::Color sfml_color(color.r, color.g, color.b, color.a);
  m_sprite.setColor(sfml_color);
}

void GOM::Sprite::move(const GOM::Vector2f &offset) {
  m_sprite.move(offset.x, offset.y);
}

void GOM::Sprite::rotate(float angle) { m_sprite.rotate(angle); }

void GOM::Sprite::scale(const GOM::Vector2f &factor) {
  m_sprite.scale(factor.x, factor.y);
}

GOM::Vector2u GOM::Sprite::getSize() const {
  sf::Vector2u sfml_size = m_sprite.getTexture()->getSize();
  return GOM::Vector2u{sfml_size.x, sfml_size.y};
}

const GOM::ITexture *GOM::Sprite::getTexture() const {
  const sf::Texture *sfml_texture = m_sprite.getTexture();
  GOM::Texture *texture = new GOM::Texture(*sfml_texture);
  return texture;
}

GOM::FloatRect GOM::Sprite::getLocalBounds() const {
  sf::FloatRect sfml_bounds = m_sprite.getLocalBounds();
  return GOM::FloatRect{sfml_bounds.left, sfml_bounds.top, sfml_bounds.width,
                          sfml_bounds.height};
}

GOM::FloatRect GOM::Sprite::getGlobalBounds() const {
  sf::FloatRect sfml_bounds = m_sprite.getGlobalBounds();
  return GOM::FloatRect{sfml_bounds.left, sfml_bounds.top, sfml_bounds.width,
                          sfml_bounds.height};
}

bool GOM::Sprite::contains(const GOM::Vector2f &point) const {
  return m_sprite.getGlobalBounds().contains(point.x, point.y);
}

sf::Sprite &GOM::Sprite::getSprite() { return m_sprite; }
