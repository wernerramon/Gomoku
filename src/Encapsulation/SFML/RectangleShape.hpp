#ifndef RECTANGLESHAPE_HPP
#define RECTANGLESHAPE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "../IRectangleShape.hpp"
#include "./Texture.hpp"

namespace GOM
{
  class RectangleShape : public IRectangleShape
  {
  public:
    RectangleShape() = default;
    ~RectangleShape() = default;

    void setFillColor(const GOM::Color &color) override;
    void setOutlineColor(const GOM::Color &color) override;
    void setOutlineThickness(float thickness) override;

    void setSize(const GOM::Vector2f &size) override;
    void setPosition(const GOM::Vector2f &position) override;
    void setTexture(const GOM::ITexture *texture) override;
    void setTextureRect(const GOM::IntRect &rect) override;
    void setRotation(float angle) override;
    void setScale(const GOM::Vector2f &factors) override;
    void setOrigin(const GOM::Vector2f &origin) override;
    void rotate(float angle) override;
    void scale(const GOM::Vector2f &factors) override;

    bool intersects(const GOM::FloatRect &rect) override;
    SIDE intersectsSide(const GOM::FloatRect &rect) override;

    const GOM::Vector2f &getSize() override;
    const GOM::Vector2f &getPosition() override;
    const GOM::FloatRect &getGlobalBounds() override;
    const GOM::IntRect &getTextureRect() override;
    float getRotation() const override;
    const GOM::Vector2f &getScale() override;
    const GOM::Vector2f &getOrigin() override;

    sf::RectangleShape &getRectangleShape();

  private:
    sf::RectangleShape m_shape;
    GOM::Vector2f m_size;
    GOM::Vector2f m_position;
    GOM::Vector2f m_scale;
    GOM::Vector2f m_origin;
    GOM::FloatRect m_globalBounds;
  };
} // namespace GOM

#endif // RECTANGLESHAPE_HPP
