#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>

#include "../ITexture.hpp"

namespace GOM
{
  class Texture : public ITexture
  {
  public:
    Texture();
    Texture(const sf::Texture &texture);
    ~Texture() = default;

    bool loadFromFile(const std::string &filename) override;
    bool loadFromFile(const std::string &filename,
                      const IntRect &area = IntRect()) override;

    GOM::Vector2u getSize() const override;

    const sf::Texture *getTexture();

  private:
    sf::Texture *m_texture;
  };
} // namespace GOM

#endif // TEXTURE_HPP
