#ifndef LOBBYSTATE_HPP_
#define LOBBYSTATE_HPP_

#include <iostream>

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
// #include "GameStateMulti.hpp"

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
    Button m_start;
    Button m_home;
    int m_size;
    std::size_t m_mode;
    boost::asio::io_service m_io_service;

    void initSprites();
    void initText();
};

#endif /* !LOBBYSTATE_HPP_ */
