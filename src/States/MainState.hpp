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

class MainState final : public State
{
public:
    MainState(StateMachine &t_machine, GOM::IRenderWindow *t_window,
              GOM::IGraphicLoader *t_graphic_loader, bool t_replace = true);
    ~MainState();
    std::string createLobbyCode();
    void update() override;
    void draw() override;

private:
    GOM::ITexture *m_bg_t;
    GOM::ISprite *m_bg_s;
    GOM::IFont *m_font;
    GOM::IText *m_title;
    std::size_t m_flag;
    Button m_local;
    Button m_online;
    Button m_settings;
    Button m_exit;

    void initSprites();
    void initText();
};

#endif //! MAINSTATE_HPP_