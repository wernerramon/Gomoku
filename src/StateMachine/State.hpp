#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>

#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IRenderWindow.hpp"
#include "../Encapsulation/IMouse.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"

class StateMachine;

class State
{
public:
    State(StateMachine &t_machine, GOM::IRenderWindow *t_window,
          GOM::IGraphicLoader *t_graphic_loader, const bool t_replace);

    virtual ~State() = default;

    State(const State &) = delete;
    State &operator=(const State &) = delete;

    virtual void update() = 0;
    virtual void draw() = 0;

    std::unique_ptr<State> next();

    const bool isReplacing();

protected:
    StateMachine &m_state_machine;
    GOM::IRenderWindow *m_window;
    GOM::IMouse *m_mouse;
    bool m_replace;
    std::unique_ptr<State> m_next;
    GOM::IGraphicLoader *m_graphic_loader;
};

#endif // !STATE_HPP_