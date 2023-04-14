#include "./State.hpp"

State::State(StateMachine &t_machine, GOM::IRenderWindow *t_window,
             GOM::IGraphicLoader *t_graphic_loader, int t_size, const bool t_replace,
             Host *t_host, Client *t_client)
    : m_state_machine(t_machine), m_window(t_window), m_replace(t_replace)
{
    m_graphic_loader = t_graphic_loader;
    m_mouse = m_graphic_loader->loadMouse();
    m_host = t_host;
    m_client = t_client;
}
std::unique_ptr<State> State::next() { return std::move(m_next); }

const bool State::isReplacing() { return m_replace; }