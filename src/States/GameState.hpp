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
    GOM::ITexture *m_bg_border_light_t;
    GOM::ITexture *m_bg_border_dark_t;
    GOM::ITexture *m_bg_dark_t;
    GOM::ITexture *m_bg_light_t;
    GOM::ITexture *m_line_dark_hor_t;
    GOM::ITexture *m_line_light_hor_t;
    GOM::ITexture *m_line_dark_ver_t;
    GOM::ITexture *m_line_light_ver_t;
    GOM::ITexture *m_cross_t;
    GOM::ITexture *m_circle_t;
    GOM::ISprite *m_bg_s;
    GOM::ISprite *m_top_border_s;
    GOM::ISprite *m_bot_border_s;
    std::vector<GOM::ISprite *> m_lines_hor_s;
    std::vector<GOM::ISprite *> m_lines_ver_s;
    std::vector<GOM::ISprite *> m_cross_s;
    std::vector<GOM::ISprite *> m_circle_s;
    // GOM::IFont *m_font;
    GOM::Vector2i m_size;
    Button m_home;
    Button m_light;
    bool m_light_mode;
    bool m_turn;

    void initSprites();
    // void initText();
    void initGrit();
    void createIcon(GOM::Vector2f t_mouse_pos);
    bool isEmpty(GOM::Vector2f t_pos);
};

#endif /* !GAMESTATE_HPP_ */
