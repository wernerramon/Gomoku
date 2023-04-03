#include "ModeSelectLocal.hpp"

void ModeSelectLocal::initSprites()
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

void ModeSelectLocal::initText()
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
    m_title->setString("SELECT MODE");
    m_title->setCharacterSize(50);
    m_title->setPosition(
        {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
    m_title->setColor(GOM::EpiBlue);
}

ModeSelectLocal::ModeSelectLocal(StateMachine &t_machine, GOM::IRenderWindow *t_window,
                                 GOM::IGraphicLoader *t_graphic_loader, GOM::Vector2i t_size, bool t_replace)
    : State(t_machine, t_window, t_graphic_loader, t_size, t_replace),
      m_pvp(Button("./assets/sprites/BTN/button_p-vs-p.png",
                   GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 250),
                                 static_cast<float>(m_window->getSize().y / 2 + 150)},
                   GOM::Vector2f{150, 50}, t_graphic_loader, false)),
      m_pve((Button("./assets/sprites/BTN/button_p-vs-ai.png",
                    GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 100),
                                  static_cast<float>(m_window->getSize().y / 2 + 150)},
                    GOM::Vector2f{150, 50}, t_graphic_loader, false))),
      m_home((Button("./assets/icons/home.png",
                     GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                                   static_cast<float>(m_window->getSize().y - 100)},
                     GOM::Vector2f{64, 64}, t_graphic_loader, true)))
{
    m_size = t_size;
    initSprites();
    initText();
}

ModeSelectLocal::~ModeSelectLocal()
{
}

void ModeSelectLocal::update()
{
    for (auto event = GOM::Event{}; m_window->pollEvent(event);)
    {
        GOM::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
        GOM::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                  static_cast<float>(mouse_pos.y)};
        if (event.type == GOM::EventType::MouseMoved)
        {
            m_pvp.is_hovered(mouse_pos_f);
            m_pve.is_hovered(mouse_pos_f);
            m_home.is_hovered(mouse_pos_f);
        }
        if (m_mouse->isLeftMouseButtonPressed())
        {
            if (m_pvp.is_pressed(mouse_pos_f))
            {
                std::cout << "pvp btn pressed" << std::endl;
                m_next = StateMachine::build<GameState>(
                    m_state_machine, m_window, m_graphic_loader, m_size, true);
            }
            if (m_pve.is_pressed(mouse_pos_f))
            {
                std::cout << "pve btn pressed" << std::endl;
            }
            if (m_home.is_pressed(mouse_pos_f))
            {
                std::cout << "home btn pressed" << std::endl;
                m_next = StateMachine::build<MainState>(
                    m_state_machine, m_window, m_graphic_loader, m_size, true);
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

void ModeSelectLocal::draw()
{
    m_window->clear();
    m_window->draw(m_bg_s);
    m_window->draw(m_title);
    m_window->draw(m_pve.getSprite());
    m_window->draw(m_pvp.getSprite());
    m_window->draw(m_home.getSprite());
    m_window->display();
}