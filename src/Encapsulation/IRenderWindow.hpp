#ifndef IWINDOW_HPP
#define IWINDOW_HPP

#include <string>

#include "Event.hpp"
#include "GraphicDataTypes.hpp"
#include "IRectangleShape.hpp"
#include "ISprite.hpp"
#include "IText.hpp"

namespace GOM
{
    class IRenderWindow
    {
    public:
        ~IRenderWindow() = default;

        virtual void draw(const GOM::ISprite *t_sprite) = 0;
        virtual void draw(GOM::IRectangleShape *t_shape) = 0;
        virtual void draw(const GOM::IText *t_text) = 0;
        virtual void display() = 0;
        virtual GOM::Vector2u getSize() const = 0;
        virtual bool isOpen() = 0;
        virtual void close() = 0;
        virtual void clear(GOM::Color t_color = {0, 0, 0, 255}) = 0;
        virtual void setFramerateLimit(unsigned int t_fps) = 0;
        virtual void create(unsigned int t_width, unsigned int t_height,
                            std::string t_title) = 0;
        virtual void create(unsigned int t_width, unsigned int t_height,
                            std::string t_title, GOM::Style t_style) = 0;
        virtual bool pollEvent(GOM::Event &t_event) = 0;
        virtual void setSize(const GOM::Vector2u &t_size) = 0;
    };
} // namespace GOM

#endif // IWINDOW_HPP