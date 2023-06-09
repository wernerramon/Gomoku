#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <algorithm>
#include <iostream>
#include <math.h>
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
    GameState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
              GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace = true,
              Host *t_host = nullptr, Client *t_client = nullptr);
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
    GOM::ISprite *m_bg_restart_s;
    std::vector<GOM::ISprite *> m_lines_hor_s;
    std::vector<GOM::ISprite *> m_lines_ver_s;
    std::vector<GOM::ISprite *> m_cross_s;
    std::vector<GOM::ISprite *> m_circle_s;

    GOM::ISprite *m_icon_p1;
    GOM::ISprite *m_icon_p2;

    std::vector<std::vector<int>> m_board;

    GOM::IFont *m_font;
    GOM::IText *m_p1_name;
    GOM::IText *m_p2_name;
    GOM::IText *m_score;
    GOM::IText *m_move;
    GOM::IText *m_time_total_p1;
    GOM::IText *m_time_turn_p1;
    GOM::IText *m_time_total_p2;
    GOM::IText *m_time_turn_p2;
    GOM::IText *m_restart;
    GOM::IText *m_winner;

    int m_size;
    Button m_home;
    Button m_light;
    Button m_swap;
    bool m_light_mode;
    bool m_turn;
    std::size_t m_mode;
    int m_score_p1;
    int m_score_p2;
    int m_move_count;

    bool m_is_host;

    void initSprites();
    void initText();
    void initGrit();
    void createIcon(GOM::Vector2f t_mouse_pos);
    bool isEmpty(GOM::Vector2f t_pos);
    int check_win_or_draw(const std::vector<std::vector<int>> &board);
};

#endif /* !GAMESTATE_HPP_ */
