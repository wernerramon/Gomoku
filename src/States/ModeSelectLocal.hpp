#ifndef MODESELECTLOCAL_HPP_
#define MODESELECTLOCAL_HPP_

#include <iostream>

#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"

#include "../Components/Button.hpp"

#include "../StateMachine/State.hpp"
#include "../StateMachine/StateMachine.hpp"

#include "./GameState.hpp"
#include "./MainState.hpp"

class ModeSelectLocal final : public State
{
public:
    ModeSelectLocal(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
                    GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace = true,
                    Host *t_host = nullptr, Client *t_client = nullptr);
    ~ModeSelectLocal();
    void update() override;
    void draw() override;

private:
    GOM::ITexture *m_bg_t;
    GOM::ISprite *m_bg_s;
    GOM::IFont *m_font;
    GOM::IText *m_title;
    Button m_pvp;
    Button m_pve;
    Button m_home;
    int m_size;
    std::size_t m_mode;

    void initSprites();
    void initText();
};

#endif /* !MODESELECTLOCAL_HPP_ */
