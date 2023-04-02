#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "../ISprite.hpp"

#include <SFML/Graphics.hpp>

#include "./Texture.hpp"

namespace GOM
{
  class Sprite : public ISprite
  {
  public:
    Sprite() = default;
    ~Sprite() override = default;

    void setTexture(GOM::ITexture *texture, bool reset_rect) override;
    void setTextureRect(const GOM::IntRect &rectangle) override;
    void setPosition(const GOM::Vector2f &position) override;
    void setScale(const GOM::Vector2f &factor) override;
    void setRotation(float angle) override;
    void setOrigin(const GOM::Vector2f &origin) override;
    void setColor(const GOM::Color &color) override;
    void move(const GOM::Vector2f &offset) override;
    void rotate(float angle) override;
    void scale(const GOM::Vector2f &factor) override;
    GOM::Vector2u getSize() const override;
    const GOM::ITexture *getTexture() const override;
    GOM::FloatRect getLocalBounds() const override;
    GOM::FloatRect getGlobalBounds() const override;

    bool contains(const GOM::Vector2f &point) const override;

    sf::Sprite &getSprite();

  private:
    sf::Sprite m_sprite;
  };
} // namespace GOM

#endif // SPRITE_HPP
