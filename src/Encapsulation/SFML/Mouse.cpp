#include "Mouse.hpp"

GOM::Vector2i
GOM::Mouse::getMousePosition(GOM::IRenderWindow *m_window) const {
  sf::Vector2i mousePos = sf::Mouse::getPosition(
    *(dynamic_cast<GOM::RenderWindow *>(m_window))->getRenderWindow());
  return GOM::Vector2i{mousePos.x, mousePos.y};
}

bool GOM::Mouse::isLeftMouseButtonPressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool GOM::Mouse::isRightMouseButtonPressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

bool GOM::Mouse::isMouseXButton1Pressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::XButton1);
}

bool GOM::Mouse::isMouseXButton2Pressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::XButton2);
}

bool GOM::Mouse::isMouseMiddleButtonPressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
}
