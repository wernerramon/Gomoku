#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <iostream>
#include <string>

#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"

class Sprite
{
public:
    Sprite(std::string t_path, GOM::Vector2f t_pos,
           GOM::IGraphicLoader *t_graphic_loader);
    ~Sprite();
    GOM::ISprite *getSprite();
    void setPos(float t_pos_x = 0, float t_pos_y = 0);
    GOM::ITexture *getTexture();
    void setPath(std::string t_path);
    std::string &getPath();

private:
    std::string m_path;
    GOM::ITexture *m_texture;
    GOM::ISprite *m_sprite;
    GOM::IGraphicLoader *m_graphic_loader;
};

#endif // !SPRITE_HPP_