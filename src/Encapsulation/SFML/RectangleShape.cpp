#include "./RectangleShape.hpp"

void GOM::RectangleShape::setFillColor(const GOM::Color &color) {
  m_shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
}

void GOM::RectangleShape::setOutlineColor(const GOM::Color &color) {
  m_shape.setOutlineColor(sf::Color(color.r, color.g, color.b, color.a));
}

void GOM::RectangleShape::setOutlineThickness(float thickness) {
  m_shape.setOutlineThickness(thickness);
}

void GOM::RectangleShape::setSize(const GOM::Vector2f &size) {
  m_shape.setSize(sf::Vector2f(size.x, size.y));
}

void GOM::RectangleShape::setPosition(const GOM::Vector2f &position) {
  m_shape.setPosition(sf::Vector2f(position.x, position.y));
}

void GOM::RectangleShape::setTexture(const GOM::ITexture *texture) {
  GOM::ITexture *texture_cast = const_cast<GOM::ITexture *>(texture);
  m_shape.setTexture(
    dynamic_cast<GOM::Texture *>(texture_cast)->getTexture());
}

void GOM::RectangleShape::setTextureRect(const GOM::IntRect &rect) {
  m_shape.setTextureRect(
    sf::IntRect(rect.left, rect.top, rect.width, rect.height));
}

void GOM::RectangleShape::setRotation(float angle) {
  m_shape.setRotation(angle);
}

void GOM::RectangleShape::setScale(const GOM::Vector2f &factors) {
  m_shape.setScale(sf::Vector2f(factors.x, factors.y));
}

void GOM::RectangleShape::setOrigin(const GOM::Vector2f &origin) {
  m_shape.setOrigin(sf::Vector2f(origin.x, origin.y));
}

void GOM::RectangleShape::rotate(float angle) { m_shape.rotate(angle); }

void GOM::RectangleShape::scale(const GOM::Vector2f &factors) {
  m_shape.scale(sf::Vector2f(factors.x, factors.y));
}

bool GOM::RectangleShape::intersects(const GOM::FloatRect &rect) {
  return m_shape.getGlobalBounds().intersects(
    sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
}

GOM::IRectangleShape::SIDE
GOM::RectangleShape::intersectsSide(const GOM::FloatRect &rect) {
  sf::FloatRect shape_rect = m_shape.getGlobalBounds();
  shape_rect.width += shape_rect.left;
  shape_rect.height += shape_rect.top;
  sf::FloatRect obstacle_rect = sf::FloatRect(
    rect.left, rect.top, rect.width + rect.left, rect.height + rect.top);
  GOM::IRectangleShape::SIDE side = GOM::IRectangleShape::SIDE::NONE;

  if (m_shape.getGlobalBounds().intersects(
        sf::FloatRect(rect.left, rect.top, rect.width, rect.height))) {
    // left, top, right, bottom
    sf::FloatRect intersection_rect = {
      std::min(shape_rect.left, obstacle_rect.left),
      std::min(shape_rect.top, obstacle_rect.top),
      std::max(shape_rect.width, obstacle_rect.width),
      std::max(shape_rect.height, obstacle_rect.height)};
    float width = intersection_rect.width - intersection_rect.left;
    float height = intersection_rect.height - intersection_rect.top;

    if (intersection_rect.left == shape_rect.left && height > width) {
      side = GOM::IRectangleShape::SIDE::LEFT;
    } else if (intersection_rect.top == shape_rect.top && width > height) {
      side = GOM::IRectangleShape::SIDE::TOP;
    } else if (intersection_rect.width == shape_rect.width && height > width) {
      side = GOM::IRectangleShape::SIDE::RIGHT;
    } else if (intersection_rect.height == shape_rect.height &&
               width > height) {
      side = GOM::IRectangleShape::SIDE::BOTTOM;
    }
  };
  return side;
}

const GOM::Vector2f &GOM::RectangleShape::getSize() {
  sf::Vector2f sfml_vector = m_shape.getSize();
  m_size = {sfml_vector.x, sfml_vector.y};
  return m_size;
}

const GOM::Vector2f &GOM::RectangleShape::getPosition() {
  sf::Vector2f sfml_vector = m_shape.getPosition();
  m_position = {sfml_vector.x, sfml_vector.y};
  return m_position;
}

const GOM::FloatRect &GOM::RectangleShape::getGlobalBounds() {
  sf::FloatRect sfml_rect = m_shape.getGlobalBounds();
  m_globalBounds = {sfml_rect.left, sfml_rect.top, sfml_rect.width,
                    sfml_rect.height};
  return m_globalBounds;
}

const GOM::IntRect &GOM::RectangleShape::getTextureRect() {
  sf::IntRect sfml_rect = m_shape.getTextureRect();
  GOM::IntRect *m_textureRect = new GOM::IntRect{
    sfml_rect.left, sfml_rect.top, sfml_rect.width, sfml_rect.height};
  return *m_textureRect;
}

float GOM::RectangleShape::getRotation() const {
  return m_shape.getRotation();
}

const GOM::Vector2f &GOM::RectangleShape::getScale() {
  sf::Vector2f sfml_vector = m_shape.getScale();
  m_scale = {sfml_vector.x, sfml_vector.y};
  return m_scale;
}

const GOM::Vector2f &GOM::RectangleShape::getOrigin() {
  sf::Vector2f sfml_vector = m_shape.getOrigin();
  m_origin = {sfml_vector.x, sfml_vector.y};
  return m_origin;
}

sf::RectangleShape &GOM::RectangleShape::getRectangleShape() {
  return m_shape;
}
