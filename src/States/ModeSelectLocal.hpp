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
    ModeSelectLocal(StateMachine &t_machine, GOM::IRenderWindow *t_window,
                    GOM::IGraphicLoader *t_graphic_loader, GOM::Vector2i t_size, bool t_replace = true);
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
    GOM::Vector2i m_size;

    void initSprites();
    void initText();
};

#endif /* !MODESELECTLOCAL_HPP_ */
