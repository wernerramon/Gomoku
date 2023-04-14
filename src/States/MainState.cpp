#include "./MainState.hpp"

void MainState::initSprites()
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

void MainState::initText()
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
    m_title->setString("GOMOKU");
    m_title->setCharacterSize(50);
    m_title->setPosition(
        {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
    m_title->setColor(GOM::EpiBlue);
}

MainState::MainState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
                     GOM::IGraphicLoader *t_graphic_loader, int t_size, const bool t_replace,
                     Host *t_host, Client *t_client)
    : State(t_machine, t_window, t_graphic_loader, t_size, t_replace, t_host, t_client),
      m_local(Button("./assets/sprites/BTN/button_local.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 250),
                                   static_cast<float>(m_window->getSize().y / 2 + 150)},
                     GOM::Vector2f{150, 50}, t_graphic_loader, false)),
      m_host((Button("./assets/sprites/BTN/button_host.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 100),
                                   static_cast<float>(m_window->getSize().y / 2 + 150)},
                     GOM::Vector2f{150, 50}, t_graphic_loader, false))),
      m_join((Button("./assets/sprites/BTN/button_join.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 100),
                                   static_cast<float>(m_window->getSize().y / 2 + 250)},
                     GOM::Vector2f{150, 50}, t_graphic_loader, false))),
      m_settings(Button("./assets/icons/gear.png",
                        GOM::Vector2f{static_cast<float>(m_window->getSize().x - 200),
                                      static_cast<float>(m_window->getSize().y - 100)},
                        GOM::Vector2f{64, 64}, t_graphic_loader, true)),
      m_exit((Button("./assets/icons/exit.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x - 100),
                                   static_cast<float>(m_window->getSize().y - 100)},
                     GOM::Vector2f{64, 64}, t_graphic_loader, true)))
{
    m_size = t_size;
    m_mode = t_mode;
    initSprites();
    initText();
}

MainState::~MainState()
{
    delete m_bg_t;
    delete m_bg_s;
}

void MainState::update()
{
    for (auto event = GOM::Event{}; m_window->pollEvent(event);)
    {
        GOM::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
        GOM::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                  static_cast<float>(mouse_pos.y)};
        if (event.type == GOM::EventType::MouseMoved)
        {
            m_local.is_hovered(mouse_pos_f);
            m_host.is_hovered(mouse_pos_f);
            m_join.is_hovered(mouse_pos_f);
            m_settings.is_hovered(mouse_pos_f);
            m_exit.is_hovered(mouse_pos_f);
        }
        if (m_mouse->isLeftMouseButtonPressed())
        {
            if (m_local.is_pressed(mouse_pos_f))
            {
                std::cout << "local btn pressed" << std::endl;
                m_next = StateMachine::build<ModeSelectLocal>(
                    m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
            }
            if (m_host.is_pressed(mouse_pos_f))
            {
                std::cout << "host btn pressed" << std::endl;
                m_next = StateMachine::build<LobbyState>(
                    m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
            }
            if (m_join.is_pressed(mouse_pos_f))
            {
                std::cout << "join btn pressed" << std::endl;
                m_next = StateMachine::build<JoinLobbyState>(
                    m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
            }
            if (m_settings.is_pressed(mouse_pos_f))
            {
                std::cout << "settings btn pressed" << std::endl;
                m_next = StateMachine::build<SettingsState>(
                    m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
            }
            if (m_exit.is_pressed(mouse_pos_f))
            {
                std::cout << "exit btn pressed" << std::endl;
                m_state_machine.quit();
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

void MainState::draw()
{
    m_window->clear();
    m_window->draw(m_bg_s);
    m_window->draw(m_title);
    m_window->draw(m_local.getSprite());
    m_window->draw(m_host.getSprite());
    m_window->draw(m_join.getSprite());
    m_window->draw(m_settings.getSprite());
    m_window->draw(m_exit.getSprite());
    m_window->display();
}