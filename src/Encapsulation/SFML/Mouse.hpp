#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/Window/Mouse.hpp>

#include "../IMouse.hpp"
#include "./RenderWindow.hpp"

namespace GOM
{
  class Mouse : public IMouse
  {
  public:
    ~Mouse() override = default;

    bool isLeftMouseButtonPressed() const override;
    bool isRightMouseButtonPressed() const override;
    bool isMouseXButton1Pressed() const override;
    bool isMouseXButton2Pressed() const override;
    bool isMouseMiddleButtonPressed() const override;

    GOM::Vector2i
    getMousePosition(GOM::IRenderWindow *m_window) const override;
  };
} // namespace GOM

#endif // MOUSE_HPP
