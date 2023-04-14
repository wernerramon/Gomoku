#ifndef SETTINGSSTATE_HPP_
#define SETTINGSSTATE_HPP_

#include <iostream>
#include <vector>

#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"

#include "../Components/Button.hpp"
#include "../Components/Textbox.hpp"

#include "../StateMachine/State.hpp"
#include "../StateMachine/StateMachine.hpp"

#include "./MainState.hpp"

class SettingsState final : public State
{
public:
    SettingsState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
                  GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace = true,
                  Host *t_host = nullptr, Client *t_client = nullptr);
    ~SettingsState();
    void update() override;
    void draw() override;

private:
    GOM::ITexture *m_bg_t;
    GOM::ITexture *m_bg_txt_t;
    GOM::ITexture *m_bg_txt_sel_t;
    GOM::ISprite *m_bg_s;
    GOM::ISprite *m_bg_size_s;
    GOM::ISprite *m_bg_txt_sel_s;
    GOM::IFont *m_font;
    GOM::IText *m_title;
    GOM::IText *m_instructions;
    GOM::IText *m_txt_size;
    Button m_home;
    int m_size;
    Textbox m_tb_size;
    std::size_t m_mode;

    void initSprites();
    void initText();
};

#endif /* !SETTINGSSTATE_HPP_ */
