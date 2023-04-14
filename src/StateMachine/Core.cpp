#include "./Core.hpp"

Core::Core()
{
    m_graphic_loader = new GOM::GraphicLoader();
    m_window = m_graphic_loader->loadRenderWindow();
    m_window->create(
        745, 945, "GOMOKU",
        static_cast<GOM::Style>(GOM::Style::Titlebar | GOM::Style::Close));
    m_window->setFramerateLimit(60);
    srand(time(nullptr));
    m_state_machine.run(StateMachine::build<MainState>(
        m_state_machine, m_window, 0, m_graphic_loader, 20, true));
}

Core::~Core()
{
    if (m_graphic_loader)
        delete m_graphic_loader;
}

void Core::run()
{
    while (m_state_machine.running())
    {
        m_state_machine.nextState();
        m_state_machine.update();
        m_state_machine.draw();
    }
}