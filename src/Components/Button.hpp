#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <iostream>
#include <string>

#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"

class Button
{
public:
    Button(std::string t_path, GOM::Vector2f t_pos,
           GOM::Vector2f t_target_size, GOM::IGraphicLoader *t_graphic_loader,
           bool t_is_white);
    bool is_pressed(GOM::Vector2f t_mouse_pos);
    bool is_hovered(GOM::Vector2f t_mouse_pos);
    GOM::ISprite *getSprite() { return m_btn_sprite; };

private:
    bool m_is_white;
    GOM::ITexture *m_btn_texture;
    GOM::ISprite *m_btn_sprite;
};

#endif // !BUTTON_HPP_