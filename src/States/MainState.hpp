#ifndef MAINSTATE_HPP_
#define MAINSTATE_HPP_

#include <iostream>

#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"

#include "../Components/Button.hpp"

#include "../StateMachine/State.hpp"
#include "../StateMachine/StateMachine.hpp"

#include "ModeSelectLocal.hpp"
#include "SettingsState.hpp"
#include "LobbyState.hpp"
#include "JoinLobbyState.hpp"

class MainState final : public State
{
public:
    MainState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
              GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace = true,
              Host *t_host = nullptr, Client *t_client = nullptr);
    ~MainState();
    void update() override;
    void draw() override;

private:
    GOM::ITexture *m_bg_t;
    GOM::ISprite *m_bg_s;
    GOM::IFont *m_font;
    GOM::IText *m_title;
    Button m_local;
    Button m_host;
    Button m_join;
    Button m_settings;
    Button m_exit;
    int m_size;
    std::size_t m_mode;

    void initSprites();
    void initText();
};

#endif //! MAINSTATE_HPP_