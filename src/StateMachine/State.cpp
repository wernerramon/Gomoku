#include "./State.hpp"

State::State(StateMachine &t_machine, GOM::IRenderWindow *t_window,
             GOM::IGraphicLoader *t_graphic_loader, const bool t_replace)
    : m_state_machine(t_machine), m_window(t_window), m_replace(t_replace)
{
    m_graphic_loader = t_graphic_loader;
    m_mouse = m_graphic_loader->loadMouse();
}
std::unique_ptr<State> State::next() { return std::move(m_next); }

const bool State::isReplacing() { return m_replace; }