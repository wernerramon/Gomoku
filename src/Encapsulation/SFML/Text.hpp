#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <SFML/Graphics/Text.hpp>

#include "../IText.hpp"
#include "./Font.hpp"

namespace GOM
{
  class Text : public IText
  {
  public:
    Text() = default;
    ~Text() override = default;

    void setFont(GOM::IFont *font) override;
    void setPosition(const GOM::Vector2f &position) override;
    void setString(const std::string &string) override;
    void setCharacterSize(unsigned int size) override;
    void setColor(const GOM::Color &color) override;
    const GOM::IFont *getFont() const override;
    unsigned int getCharacterSize() const override;
    // const GOM::Color &getColor() const override;
    void setScale(const GOM::Vector2f &factor) override;
    const GOM::Vector2f &getPosition() const override;
    const std::string &getString() const override;
    GOM::FloatRect getLocalBounds() const override;
    sf::Text &getText();

  private:
    sf::Text m_text;
  };
} // namespace GOM

#endif /* !TEXT_HPP_ */
