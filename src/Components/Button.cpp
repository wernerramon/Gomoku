#include "./Button.hpp"

Button::Button(std::string t_path, GOM::Vector2f t_pos,
               GOM::Vector2f t_target_size,
               GOM::IGraphicLoader *t_graphic_loader, bool t_is_white)
    : m_is_white(t_is_white)
{
    m_btn_texture = t_graphic_loader->loadTexture();
    m_btn_sprite = t_graphic_loader->loadSprite();
    if (!m_btn_texture->loadFromFile(t_path))
    {
        throw std::runtime_error("Unable to load button texture.");
    }
    m_btn_sprite->setTexture(m_btn_texture, true);
    float scale_x = t_target_size.x / m_btn_texture->getSize().x;
    float scale_y = t_target_size.y / m_btn_texture->getSize().y;
    m_btn_sprite->setScale({scale_x, scale_y});
    m_btn_sprite->setPosition(t_pos);
}

bool Button::is_hovered(GOM::Vector2f t_mouse_pos)
{
    if (m_btn_sprite->contains(t_mouse_pos))
    {
        m_btn_sprite->setColor(GOM::Grey);
        return true;
    }
    if (m_is_white)
    {
        m_btn_sprite->setColor(GOM::EpiBlue);
    }
    else
    {
        m_btn_sprite->setColor(GOM::White);
    }
    return false;
}

bool Button::is_pressed(GOM::Vector2f t_mouse_pos)
{
    if (m_btn_sprite->contains(t_mouse_pos))
    {
        m_btn_sprite->setColor(GOM::Grey);
        return true;
    }
    if (m_is_white)
    {
        m_btn_sprite->setColor(GOM::EpiBlue);
    }
    else
    {
        m_btn_sprite->setColor(GOM::White);
    }
    return false;
}