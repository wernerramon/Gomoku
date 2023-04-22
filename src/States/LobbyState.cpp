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
    m_txt_port = m_graphic_loader->loadText();
    m_txt_port->setFont(m_font);
    m_txt_port->setCharacterSize(35);
    m_txt_port->setColor(GOM::EpiBlue);
}

unsigned short find_open_port()
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0));
    auto port = acceptor.local_endpoint().port();
    acceptor.close();
    return port;
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
    m_btn_pressed = false;
    is_running = true;
    m_size = t_size;
    m_mode = t_mode;
    initSprites();
    initText();
    unsigned short port = find_open_port();
    std::cout << port << std::endl;
    m_txt_port->setString(std::to_string(port));
    m_txt_port->setPosition(
        {static_cast<float>(m_window->getSize().x / 2) - (m_txt_port->getLocalBounds().width / 2), 300});
    m_host = new Host(m_io_service, port);
    m_host->setBoardSize(m_size);
    m_host->setClientSymbol('O');
    m_host->setHostSymbol('X');
}

LobbyState::~LobbyState()
{
}

void LobbyState::update()
{
    while (is_running)
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
                    is_running = false;
                    m_next = StateMachine::build<MainState>(
                        m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
                }
                if (m_start.is_pressed(mouse_pos_f) && m_host->getGameStarted() && !m_btn_pressed)
                {
                    m_btn_pressed = true;
                    m_host->send_game_setup(1, 'X', 'O', m_size);
                    std::cout << "start btn pressed" << std::endl;
                    is_running = false;
                    m_next = StateMachine::build<GameStateMulti>(
                        m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true, m_host);
                }
            }
            switch (event.type)
            {
            case GOM::EventType::Closed:
                is_running = false;
                m_state_machine.quit();
                break;
            case GOM::EventType::KeyPressed:
                switch (event.key)
                {
                case GOM::EventKey::Enter:
                    std::cout << "pressed enter\n";
                    m_host->send_message("test from host");
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        draw();
    }
}

void LobbyState::draw()
{
    m_window->clear();
    m_window->draw(m_bg_s);
    m_window->draw(m_title);
    m_window->draw(m_txt_port);
    m_window->draw(m_home.getSprite());
    if (m_host->isReady())
        m_window->draw(m_start.getSprite());
    m_window->display();
}