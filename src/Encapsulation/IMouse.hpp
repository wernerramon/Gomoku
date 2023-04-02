#ifndef IMOUSE_HPP
#define IMOUSE_HPP

#include "./GraphicDataTypes.hpp"
#include "./IRenderWindow.hpp"

namespace GOM
{
    class IMouse
    {
    public:
        virtual ~IMouse() = default;

        virtual bool isLeftMouseButtonPressed() const = 0;
        virtual bool isRightMouseButtonPressed() const = 0;
        virtual bool isMouseXButton1Pressed() const = 0;
        virtual bool isMouseXButton2Pressed() const = 0;
        virtual bool isMouseMiddleButtonPressed() const = 0;
        virtual GOM::Vector2i
        getMousePosition(GOM::IRenderWindow *m_window) const = 0;
    };
} // namespace GOM

#endif // IMOUSE_HPP