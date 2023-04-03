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

#include "./ModeSelectLocal.hpp"
#include "./SettingsState.hpp"

class MainState final : public State
{
public:
    MainState(StateMachine &t_machine, GOM::IRenderWindow *t_window,
              GOM::IGraphicLoader *t_graphic_loader, GOM::Vector2i t_size, bool t_replace = true);
    ~MainState();
    void update() override;
    void draw() override;

private:
    GOM::ITexture *m_bg_t;
    GOM::ISprite *m_bg_s;
    GOM::IFont *m_font;
    GOM::IText *m_title;
    Button m_local;
    Button m_online;
    Button m_settings;
    Button m_exit;
    GOM::Vector2i m_size;

    void initSprites();
    void initText();
};

#endif //! MAINSTATE_HPP_