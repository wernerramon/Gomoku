#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>

#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IRenderWindow.hpp"
#include "../Encapsulation/IMouse.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"

#include "../Networking/Host.hpp"
#include "../Networking/Client.hpp"

class StateMachine;

class State
{
public:
    State(StateMachine &t_machine, GOM::IRenderWindow *t_window,
          GOM::IGraphicLoader *t_graphic_loader, int t_size, const bool t_replace,
          Host *t_host = nullptr, Client *t_client = nullptr);

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
    Host *m_host = nullptr;
    Client *m_client = nullptr;
};

#endif // !STATE_HPP_