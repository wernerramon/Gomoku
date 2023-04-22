#include "JoinLobbyState.hpp"

void JoinLobbyState::initSprites()
{
    float size_x = m_window->getSize().x;
    float size_y = m_window->getSize().y;
    m_bg_t = m_graphic_loader->loadTexture();
    m_bg_s = m_graphic_loader->loadSprite();
    m_bg_txt_t = m_graphic_loader->loadTexture();
    m_bg_txt_sel_t = m_graphic_loader->loadTexture();
    m_bg_txt_sel_s = m_graphic_loader->loadSprite();
    m_bg_port_s = m_graphic_loader->loadSprite();
    m_bg_ip_s = m_graphic_loader->loadSprite();
    if (!m_bg_t->loadFromFile("./assets/sprites/BG-Main.jpg"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_bg_txt_t->loadFromFile("./assets/sprites/game_border_light.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_bg_txt_sel_t->loadFromFile("./assets/sprites/box_selected.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    float scale_x = size_x / m_bg_t->getSize().x;
    float scale_y = size_y / m_bg_t->getSize().y;
    m_bg_s->setTexture(m_bg_t, true);
    m_bg_s->setScale({scale_x, scale_y});
    m_bg_txt_sel_s->setTexture(m_bg_txt_sel_t, true);
    m_bg_port_s->setTexture(m_bg_txt_t, true);
    m_bg_ip_s->setTexture(m_bg_txt_t, true);
}

void JoinLobbyState::initText()
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
    m_title->setString("JOIN LOBBY");
    m_title->setCharacterSize(50);
    m_title->setPosition(
        {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
    m_title->setColor(GOM::EpiBlue);

    m_title_ip = m_graphic_loader->loadText();
    m_title_ip->setFont(m_font);
    m_title_ip->setString("PLEASE ENTER HOST IP ADDRESS:");
    m_title_ip->setCharacterSize(25);
    m_title_ip->setPosition(
        {(size_x / 2) - 308.5f, (size_y / 4)});
    m_title_ip->setColor(GOM::EpiBlue);

    m_title_port = m_graphic_loader->loadText();
    m_title_port->setFont(m_font);
    m_title_port->setString("PLEASE ENTER HOST PORT:");
    m_title_port->setCharacterSize(25);
    m_title_port->setPosition(
        {(size_x / 2) - 211.f, (size_y / 2)});
    m_title_port->setColor(GOM::EpiBlue);

    m_tb_host_ip.setLimit(true, 15);
    m_tb_host_ip.setPosition({m_title_ip->getPosition().x + m_title_ip->getLocalBounds().width + 10, (size_y / 4)});
    m_bg_ip_s->setScale({(617.f / m_bg_txt_t->getSize().x), (m_title_ip->getLocalBounds().height + 20) / m_bg_txt_t->getSize().y});
    m_bg_ip_s->setPosition({m_title_ip->getPosition().x - 10, (size_y / 4)});

    m_tb_host_port.setLimit(true, 5);
    m_tb_host_port.setPosition({m_title_port->getPosition().x + m_title_port->getLocalBounds().width + 10, (size_y / 2)});
    m_bg_port_s->setScale({(422.f / m_bg_txt_t->getSize().x), (m_title_port->getLocalBounds().height + 20) / m_bg_txt_t->getSize().y});
    m_bg_port_s->setPosition({m_title_port->getPosition().x - 10, (size_y / 2)});
}

JoinLobbyState::JoinLobbyState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
                               GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace,
                               Host *t_host, Client *t_client)
    : State(t_machine, t_window, t_graphic_loader, t_size, t_replace, t_host, t_client),
      m_start(Button("./assets/sprites/BTN/button_join.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 75),
                                   static_cast<float>(m_window->getSize().y / 2 + 150)},
                     GOM::Vector2f{150, 50}, t_graphic_loader, false)),
      m_home((Button("./assets/icons/home.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                                   static_cast<float>(m_window->getSize().y - 100)},
                     GOM::Vector2f{64, 64}, t_graphic_loader, true))),
      m_tb_host_ip(Textbox(25, GOM::EpiBlue, false, t_graphic_loader)),
      m_tb_host_port(Textbox(25, GOM::EpiBlue, false, t_graphic_loader))
{
    m_btn_pressed = false;
    m_size = t_size;
    m_mode = t_mode;
    initSprites();
    initText();
}

JoinLobbyState::~JoinLobbyState()
{
}

void JoinLobbyState::update()
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
            float size_y = m_window->getSize().y;
            if (m_home.is_pressed(mouse_pos_f))
            {
                std::cout << "home btn pressed" << std::endl;
                m_next = StateMachine::build<MainState>(
                    m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
            }
            if (m_bg_ip_s->contains(mouse_pos_f) && !m_tb_host_port.getSelected())
            {
                std::cout << "ip pressed" << std::endl;
                m_bg_txt_sel_s->setScale({(617.f / m_bg_txt_t->getSize().x), (m_title_ip->getLocalBounds().height + 20) / m_bg_txt_t->getSize().y});
                m_bg_txt_sel_s->setPosition({m_title_ip->getPosition().x - 10, (size_y / 4)});
                m_tb_host_ip.setSelected(true);
            }
            if (m_bg_port_s->contains(mouse_pos_f) && !m_tb_host_ip.getSelected())
            {
                std::cout << "port pressed" << std::endl;
                m_bg_txt_sel_s->setScale({(422.f / m_bg_txt_t->getSize().x), (m_title_port->getLocalBounds().height + 20) / m_bg_txt_t->getSize().y});
                m_bg_txt_sel_s->setPosition({m_title_port->getPosition().x - 10, (size_y / 2)});
                m_tb_host_port.setSelected(true);
            }
            if (m_start.is_pressed(mouse_pos_f) && !m_btn_pressed)
            {
                std::cout << m_host_ip << std::endl;
                m_client = new Client(m_io_service, m_host_ip, static_cast<unsigned short>(std::stoi(m_host_port)));
                while (!m_client->isConnected())
                {
                    m_io_service.poll();
                }
                m_client->send_message("ok");
                m_btn_pressed = true;
            }
            if (m_client != nullptr)
            {
                std::cout << m_client->getStartGame() << std::endl;
                if (m_client->getStartGame())
                {
                    m_size = m_client->getBoardSize();
                    std::cout << m_size << std::endl;
                    m_next = StateMachine::build<GameStateMulti>(
                        m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true, nullptr, m_client);
                }
            }
        }

        switch (event.type)
        {
        case GOM::EventType::Closed:
            m_state_machine.quit();
            break;
        case GOM::EventType::KeyPressed:
            switch (event.key)
            {
            case GOM::EventKey::Enter:
                if (m_tb_host_ip.getSelected())
                {
                    m_host_ip = m_tb_host_ip.getTextString();
                    m_tb_host_ip.setSelected(false);
                }
                if (m_tb_host_port.getSelected())
                {
                    m_host_port = m_tb_host_port.getTextString();
                    m_tb_host_port.setSelected(false);
                }
            case GOM::EventKey::Space:
                if (m_client != nullptr)
                {
                    m_client->send_message("test from client");
                }
            default:
                break;
            }
            break;
        case GOM::EventType::TextEntered:
            if (m_tb_host_ip.getSelected())
            {
                m_tb_host_ip.typedOn(event);
            }
            else if (m_tb_host_port.getSelected())
            {
                m_tb_host_port.typedOn(event);
            }
            break;
        default:
            break;
        }
    }
}

void JoinLobbyState::draw()
{
    m_window->clear();
    m_window->draw(m_bg_s);
    m_window->draw(m_title);
    if (m_tb_host_ip.getSelected())
        m_window->draw(m_bg_txt_sel_s);
    else
        m_window->draw(m_bg_ip_s);
    m_window->draw(m_title_ip);
    m_window->draw(m_tb_host_ip.getText());
    if (m_tb_host_port.getSelected())
        m_window->draw(m_bg_txt_sel_s);
    else
        m_window->draw(m_bg_port_s);
    m_window->draw(m_title_port);
    m_window->draw(m_tb_host_port.getText());
    if (!m_host_ip.empty() && !m_host_port.empty())
        m_window->draw(m_start.getSprite());
    m_window->draw(m_home.getSprite());
    m_window->display();
}