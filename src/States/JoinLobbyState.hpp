#ifndef JOINLOBBYSTATE_HPP_
#define JOINLOBBYSTATE_HPP_

#include <iostream>

#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"

#include "../Components/Button.hpp"
#include "../Components/Textbox.hpp"

#include "../StateMachine/State.hpp"
#include "../StateMachine/StateMachine.hpp"

#include "../Networking/Host.hpp"

#include "ModeSelectLocal.hpp"
#include "MainState.hpp"
#include "GameStateMulti.hpp"

class JoinLobbyState final : public State
{
public:
    JoinLobbyState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
                   GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace = true,
                   Host *t_host = nullptr, Client *t_client = nullptr);
    ~JoinLobbyState();
    void update() override;
    void draw() override;

private:
    Client *m_client = nullptr;

    GOM::ITexture *m_bg_t;
    GOM::ITexture *m_bg_txt_t;
    GOM::ITexture *m_bg_txt_sel_t;

    GOM::ISprite *m_bg_s;
    GOM::ISprite *m_bg_ip_s;
    GOM::ISprite *m_bg_port_s;
    GOM::ISprite *m_bg_txt_sel_s;

    GOM::IFont *m_font;

    GOM::IText *m_title;
    GOM::IText *m_title_ip;
    GOM::IText *m_title_port;

    Button m_start;
    Button m_home;

    int m_size;
    std::size_t m_mode;
    std::string m_host_ip;
    Textbox m_tb_host_ip;
    std::string m_host_port;
    Textbox m_tb_host_port;

    boost::asio::io_service m_io_service;

    void initSprites();
    void initText();
};

#endif /* !JOINLOBBYSTATE_HPP_ */
