#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <iostream>
#include <vector>

#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"

#include "../Components/Button.hpp"

#include "../StateMachine/State.hpp"
#include "../StateMachine/StateMachine.hpp"

#include "./MainState.hpp"

class GameState final : public State
{
public:
    GameState(StateMachine &t_machine, GOM::IRenderWindow *t_window,
              GOM::IGraphicLoader *t_graphic_loader, GOM::Vector2i t_size, bool t_replace = true);
    ~GameState();
    void update() override;
    void draw() override;

private:
    GOM::ITexture *m_bg_dark_t;
    GOM::ITexture *m_bg_light_t;
    GOM::ISprite *m_bg_s;
    GOM::ITexture *m_line_dark_hor_t;
    GOM::ITexture *m_line_light_hor_t;
    GOM::ISprite *m_line_hor_s;
    GOM::ITexture *m_line_dark_ver_t;
    GOM::ITexture *m_line_light_ver_t;
    GOM::ISprite *m_line_ver_s;
    // GOM::IFont *m_font;
    Button m_home;
    Button m_light;
    bool m_light_mode;
    GOM::Vector2i m_size;
    std::vector<GOM::ISprite *> m_lines_hor_s;
    std::vector<GOM::ISprite *> m_lines_ver_s;

    void initSprites();
    // void initText();
    void initGrit();
};

#endif /* !GAMESTATE_HPP_ */
