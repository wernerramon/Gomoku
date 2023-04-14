#include "SettingsState.hpp"

void SettingsState::initSprites()
{
    float size_x = m_window->getSize().x;
    float size_y = m_window->getSize().y;
    m_bg_t = m_graphic_loader->loadTexture();
    m_bg_s = m_graphic_loader->loadSprite();
    m_bg_txt_sel_t = m_graphic_loader->loadTexture();
    m_bg_txt_t = m_graphic_loader->loadTexture();
    m_bg_size_s = m_graphic_loader->loadSprite();
    m_bg_txt_sel_s = m_graphic_loader->loadSprite();
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
    m_bg_size_s->setTexture(m_bg_txt_t, true);
    m_bg_txt_sel_s->setTexture(m_bg_txt_sel_t, true);
}

void SettingsState::initText()
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
    m_title->setString("SETTINGS");
    m_title->setCharacterSize(50);
    m_title->setPosition(
        {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
    m_title->setColor(GOM::EpiBlue);
    m_instructions = m_graphic_loader->loadText();
    m_instructions->setFont(m_font);
    m_instructions->setString("Resize board (value has to be between 5 and 20):");
    m_instructions->setCharacterSize(30);
    m_instructions->setPosition(
        {(size_x / 2) - (m_instructions->getLocalBounds().width / 2), (size_y / 2) - 100});
    m_instructions->setColor(GOM::EpiBlue);
    m_txt_size = m_graphic_loader->loadText();
    m_txt_size->setFont(m_font);
    m_txt_size->setString("SIZE:");
    m_txt_size->setCharacterSize(30);
    m_txt_size->setPosition(
        {(size_x / 2) - (m_txt_size->getLocalBounds().width / 2), (size_y / 2)});
    m_txt_size->setColor(GOM::EpiBlue);
    m_tb_size.setLimit(true, 2);
    m_tb_size.setPosition({m_txt_size->getPosition().x + m_txt_size->getLocalBounds().width + 10, (size_y / 2)});

    m_bg_size_s->setScale({(m_txt_size->getLocalBounds().width + 64) / m_bg_txt_t->getSize().x, (m_txt_size->getLocalBounds().height + 20) / m_bg_txt_t->getSize().y});

    m_bg_size_s->setPosition({m_txt_size->getPosition().x - 10, (size_y / 2)});
}

SettingsState::SettingsState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
                             GOM::IGraphicLoader *t_graphic_loader, int t_size, bool t_replace,
                             Host *t_host, Client *t_client)
    : State(t_machine, t_window, t_graphic_loader, t_size, t_replace, t_host, t_client),
      m_home(Button("./assets/icons/home.png",
                    GOM::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                                  static_cast<float>(m_window->getSize().y - 74)},
                    GOM::Vector2f{64, 64}, t_graphic_loader, true)),
      m_tb_size(Textbox(30, GOM::EpiBlue, false, t_graphic_loader))
{
    m_size = t_size;
    m_mode = t_mode;
    initSprites();
    initText();
}

SettingsState::~SettingsState()
{
}

void SettingsState::update()
{
    for (auto event = GOM::Event{}; m_window->pollEvent(event);)
    {
        GOM::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
        GOM::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                  static_cast<float>(mouse_pos.y)};
        if (event.type == GOM::EventType::MouseMoved)
        {
            m_home.is_hovered(mouse_pos_f);
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
            if (m_bg_size_s->contains(mouse_pos_f) && !m_tb_size.getSelected())
            {
                std::cout << "size pressed" << std::endl;
                m_bg_txt_sel_s->setScale({(m_txt_size->getLocalBounds().width + 64) / m_bg_txt_t->getSize().x, (m_txt_size->getLocalBounds().height + 20) / m_bg_txt_t->getSize().y});
                m_bg_txt_sel_s->setPosition({m_txt_size->getPosition().x - 10, (size_y / 2)});
                m_tb_size.setSelected(true);
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
                if (m_tb_size.getSelected())
                {
                    int tmp_size = std::atoi(m_tb_size.getTextString().c_str());
                    if (tmp_size > 4 && tmp_size < 21)
                    {
                        m_size = tmp_size;
                    }
                    m_tb_size.setSelected(false);
                }
            default:
                break;
            }
            break;
        case GOM::EventType::TextEntered:
            if (m_tb_size.getSelected())
            {
                m_tb_size.typedOn(event);
            }
            break;
        default:
            break;
        }
    }
}

void SettingsState::draw()
{
    m_window->clear();
    m_window->draw(m_bg_s);
    m_window->draw(m_title);
    m_window->draw(m_instructions);
    if (m_tb_size.getSelected())
        m_window->draw(m_bg_txt_sel_s);
    else
        m_window->draw(m_bg_size_s);
    m_window->draw(m_tb_size.getText());
    m_window->draw(m_txt_size);
    m_window->draw(m_home.getSprite());
    m_window->display();
}