#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <iostream>
#include <string>

#include "../Encapsulation/GraphicDataTypes.hpp"
#include "./Sprite.hpp"

#define GRAY               \
    GOM::Color             \
    {                      \
        128, 128, 128, 255 \
    }

#define BLUE              \
    GOM::Color            \
    {                     \
        18, 107, 165, 255 \
    }

class Button : public Sprite
{
public:
    Button(std::string t_path, GOM::Vector2f t_pos,
           GOM::Vector2f t_target_size, GOM::IGraphicLoader *t_graphic_loader,
           bool t_is_white);
    bool is_pressed(GOM::Vector2f t_mouse_pos);
    bool is_hovered(GOM::Vector2f t_mouse_pos);

private:
    bool m_is_white;
};

#endif // !BUTTON_HPP_