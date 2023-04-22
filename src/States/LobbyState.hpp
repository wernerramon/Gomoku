#ifndef LOBBYSTATE_HPP_
#define LOBBYSTATE_HPP_

#include <iostream>
#include <cstdlib>

#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"

#include "../Components/Button.hpp"

#include "../StateMachine/State.hpp"
#include "../StateMachine/StateMachine.hpp"

#include "../Networking/Host.hpp"

#include "ModeSelectLocal.hpp"
#include "MainState.hpp"
#include "GameStateMulti.hpp"

class LobbyState final : public State
{
public:
    LobbyState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
               GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace = true,
               Host *t_host = nullptr, Client *t_client = nullptr);
    ~LobbyState();
    void update() override;
    void draw() override;

private:
    Host *m_host;

    GOM::ITexture *m_bg_t;
    GOM::ISprite *m_bg_s;

    GOM::IFont *m_font;
    GOM::IText *m_title;
    GOM::IText *m_txt_port;

    Button m_start;
    Button m_home;
    bool m_btn_pressed;

    int m_size;
    std::size_t m_mode;
    boost::asio::io_service m_io_service;

    bool is_running;
    void initSprites();
    void initText();
};

#endif /* !LOBBYSTATE_HPP_ */
