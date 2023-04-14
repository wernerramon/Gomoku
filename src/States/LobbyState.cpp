/*
** EPITECH PROJECT, 2023
** Gomoku
** File description:
** LobbyState
*/

#include "LobbyState.hpp"

void LobbyState::initSprites()
{
    float size_x = m_window->getSize().x;
    float size_y = m_window->getSize().y;
    m_bg_t = m_graphic_loader->loadTexture();
    m_bg_s = m_graphic_loader->loadSprite();
    if (!m_bg_t->loadFromFile("./assets/sprites/BG-Main.jpg"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    float scale_x = size_x / m_bg_t->getSize().x;
    float scale_y = size_y / m_bg_t->getSize().y;
    m_bg_s->setTexture(m_bg_t, true);
    m_bg_s->setScale({scale_x, scale_y});
}

void LobbyState::initText()
{
    float size_x = m_window->getSize().x;
    float size_y = m_window->getSize().y;
    m_font = m_graphic_loader->loadFont();
    if (!m_font->loadFromFile("./assets/font/Roboto/Roboto-Black.ttf"))
    {
        throw std::runtime_error("Unable to load font.");
    }
    m_title = m_graphic_loader->loadText();
    m_title->setFont(m_font);
    m_title->setString("LOBBY");
    m_title->setCharacterSize(50);
    m_title->setPosition(
        {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
    m_title->setColor(GOM::EpiBlue);
}

LobbyState::LobbyState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
                       GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace,
                       Host *t_host, Client *t_client)
    : State(t_machine, t_window, t_graphic_loader, t_size, t_replace, t_host, t_client),
      m_start(Button("./assets/icons/buttonStart.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 50),
                                   static_cast<float>(m_window->getSize().y / 2 + 150)},
                     GOM::Vector2f{100, 100}, t_graphic_loader, true)),
      m_home((Button("./assets/icons/home.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                                   static_cast<float>(m_window->getSize().y - 100)},
                     GOM::Vector2f{64, 64}, t_graphic_loader, true)))
{
    m_size = t_size;
    m_mode = t_mode;
    initSprites();
    initText();
    m_host = new Host(m_io_service, 5555);
}

LobbyState::~LobbyState()
{
}

void LobbyState::update()
{
    for (auto event = GOM::Event{}; m_window->pollEvent(event);)
    {
        GOM::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
        GOM::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                  static_cast<float>(mouse_pos.y)};
        if (event.type == GOM::EventType::MouseMoved)
        {
            m_home.is_hovered(mouse_pos_f);
            m_start.is_hovered(mouse_pos_f);
        }
        if (m_mouse->isLeftMouseButtonPressed())
        {
            if (m_home.is_pressed(mouse_pos_f))
            {
                std::cout << "local btn pressed" << std::endl;
                m_next = StateMachine::build<MainState>(
                    m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
            }
            if (m_start.is_pressed(mouse_pos_f) && m_host->is_connected())
            {
                std::cout << "start btn pressed" << std::endl;
                // m_next = StateMachine::build<GameStateMulti>(
                //     m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true, m_host);
            }
        }
        switch (event.type)
        {
        case GOM::EventType::Closed:
            m_state_machine.quit();
            break;
        default:
            break;
        }
    }
}

void LobbyState::draw()
{
    m_window->clear();
    m_window->draw(m_bg_s);
    m_window->draw(m_title);
    m_window->draw(m_home.getSprite());
    if (m_host->is_connected())
        m_window->draw(m_start.getSprite());
    m_window->display();
}