#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <SFML/Graphics/Text.hpp>
#include <iostream>

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
    const GOM::IFont *getFont() override;
    unsigned int getCharacterSize() override;
    // const GOM::Color &getColor() const override;
    void setScale(const GOM::Vector2f &factor) override;
    const GOM::Vector2f &getPosition() override;
    const std::string &getString() override;
    GOM::FloatRect getLocalBounds() override;
    sf::Text &getText();

  private:
    sf::Text m_text;
    GOM::Vector2f m_position;
    std::string m_str;
  };
} // namespace GOM

#endif /* !TEXT_HPP_ */
