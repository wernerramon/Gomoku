#include "GameState.hpp"

void GameState::initGrit()
{
    float pos_y = 100;
    float pos_x = 0;
    float size_x = 37 * m_size.x;
    float size_y = 37 * m_size.y;
    for (int i = 0; i <= m_size.y; i++)
    {
        GOM::ISprite *tmp_hor = m_graphic_loader->loadSprite();
        if (m_light_mode)
            tmp_hor->setTexture(m_line_light_hor_t, true);
        else
            tmp_hor->setTexture(m_line_dark_hor_t, true);
        tmp_hor->setScale({size_x / tmp_hor->getSize().x, 1});
        tmp_hor->setPosition({0, pos_y});
        pos_y += 37;
        m_lines_hor_s.push_back(tmp_hor);
    }
    for (int i = 0; i <= m_size.x; i++)
    {
        GOM::ISprite *tmp_ver = m_graphic_loader->loadSprite();
        if (m_light_mode)
            tmp_ver->setTexture(m_line_light_ver_t, true);
        else
            tmp_ver->setTexture(m_line_dark_ver_t, true);
        tmp_ver->setScale({1, (size_y + 5) / tmp_ver->getSize().y});
        tmp_ver->setPosition({pos_x, 100});
        pos_x += 37;
        m_lines_ver_s.push_back(tmp_ver);
    }
}

void GameState::initSprites()
{
    float size_x = m_window->getSize().x;
    float size_y = m_window->getSize().y;
    m_bg_dark_t = m_graphic_loader->loadTexture();
    m_bg_border_light_t = m_graphic_loader->loadTexture();
    m_bg_border_dark_t = m_graphic_loader->loadTexture();
    m_bg_light_t = m_graphic_loader->loadTexture();
    m_line_dark_hor_t = m_graphic_loader->loadTexture();
    m_line_light_hor_t = m_graphic_loader->loadTexture();
    m_line_dark_ver_t = m_graphic_loader->loadTexture();
    m_line_light_ver_t = m_graphic_loader->loadTexture();
    m_cross_t = m_graphic_loader->loadTexture();
    m_circle_t = m_graphic_loader->loadTexture();
    m_bg_s = m_graphic_loader->loadSprite();
    m_top_border_s = m_graphic_loader->loadSprite();
    m_bot_border_s = m_graphic_loader->loadSprite();
    if (!m_bg_dark_t->loadFromFile("./assets/sprites/bg_dark.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_bg_light_t->loadFromFile("./assets/sprites/bg_light.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_line_dark_hor_t->loadFromFile("./assets/sprites/line_dark_hor.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_line_light_hor_t->loadFromFile("./assets/sprites/line_light_hor.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_line_dark_ver_t->loadFromFile("./assets/sprites/line_dark_ver.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_line_light_ver_t->loadFromFile("./assets/sprites/line_light_ver.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_bg_border_light_t->loadFromFile("./assets/sprites/game_border_light.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_bg_border_dark_t->loadFromFile("./assets/sprites/game_border_dark.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_cross_t->loadFromFile("./assets/icons/cross.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    if (!m_circle_t->loadFromFile("./assets/icons/target.png"))
    {
        throw std::runtime_error("Unable to load image.");
    }
    float scale_x = size_x / m_bg_light_t->getSize().x;
    float scale_y = size_y / m_bg_light_t->getSize().y;
    float scale_hor_line = size_x / m_line_dark_hor_t->getSize().x;
    if (m_light_mode)
    {
        m_bg_s->setTexture(m_bg_light_t, true);
        m_top_border_s->setTexture(m_bg_border_light_t, true);
        m_bot_border_s->setTexture(m_bg_border_light_t, true);
    }
    else
    {
        m_bg_s->setTexture(m_bg_dark_t, true);
        m_top_border_s->setTexture(m_bg_border_dark_t, true);
        m_bot_border_s->setTexture(m_bg_border_dark_t, true);
    }

    m_bot_border_s->setPosition({0, 845});
    m_bg_s->setScale({scale_x, scale_y});
}

// void GameState::initText()
// {
//     float size_x = m_window->getSize().x;
//     float size_y = m_window->getSize().y;
//     m_font = m_graphic_loader->loadFont();
//     if (!m_font->loadFromFile("./assets/font/Roboto/Roboto-Black.ttf"))
//     {
//         throw std::runtime_error("Unable to load font.");
//     }
// }

GameState::GameState(StateMachine &t_machine, GOM::IRenderWindow *t_window,
                     GOM::IGraphicLoader *t_graphic_loader, GOM::Vector2i t_size, bool t_replace)
    : State(t_machine, t_window, t_graphic_loader, t_size, t_replace),
      m_home(Button("./assets/icons/home.png",
                    GOM::Vector2f{10, 10},
                    GOM::Vector2f{64, 64}, t_graphic_loader, true)),
      m_light((Button("./assets/icons/contrast.png",
                      GOM::Vector2f{84, 10},
                      GOM::Vector2f{64, 64}, t_graphic_loader, true)))
{
    m_size = t_size;
    m_light_mode = true;
    m_turn = true;
    initSprites();
    // initText();
    initGrit();
}

GameState::~GameState()
{
}

bool GameState::isEmpty(GOM::Vector2f t_pos)
{
    for (int i = 0; i < m_cross_s.size(); i++)
    {
        if (m_cross_s[i]->contains(t_pos))
        {
            return false;
        }
    }
    for (int i = 0; i < m_circle_s.size(); i++)
    {
        if (m_circle_s[i]->contains(t_pos))
        {
            return false;
        }
    }
    return true;
}

void GameState::createIcon(GOM::Vector2f t_mouse_pos)
{
    GOM::Vector2f pos = {0, 0};
    if (m_turn)
    {
        for (int i = 0; i < m_size.x; i++)
        {
            if (t_mouse_pos.x > i * 37 && t_mouse_pos.x < (i + 1) * 37)
            {
                pos.x = i * 37;
            }
        }
        for (int i = 0; i < m_size.y; i++)
        {
            if (t_mouse_pos.y > (i * 37) + 100 && t_mouse_pos.y < ((i + 1) * 37) + 100)
            {
                pos.y = (i * 37) + 100;
            }
        }
        GOM::ISprite *tmp = m_graphic_loader->loadSprite();
        tmp->setTexture(m_cross_t, true);
        tmp->setScale({32.f / m_cross_t->getSize().x, 32.f / m_cross_t->getSize().y});
        tmp->setPosition(pos);
        tmp->setColor(GOM::Blue);
        m_cross_s.push_back(tmp);
    }
    else
    {
        for (int i = 0; i < m_size.x; i++)
        {
            if (t_mouse_pos.x > i * 37 && t_mouse_pos.x < (i + 1) * 37)
            {
                pos.x = i * 37;
            }
        }
        for (int i = 0; i < m_size.y; i++)
        {
            if (t_mouse_pos.y > (i * 37) + 100 && t_mouse_pos.y < ((i + 1) * 37) + 100)
            {
                pos.y = (i * 37) + 100;
            }
        }
        GOM::ISprite *tmp = m_graphic_loader->loadSprite();
        tmp->setTexture(m_circle_t, true);
        tmp->setScale({32.f / m_cross_t->getSize().x, 32.f / m_cross_t->getSize().y});
        tmp->setPosition(pos);
        tmp->setColor(GOM::Red);
        m_circle_s.push_back(tmp);
    }
}

void GameState::update()
{
    for (auto event = GOM::Event{}; m_window->pollEvent(event);)
    {
        GOM::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
        GOM::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                  static_cast<float>(mouse_pos.y)};
        if (event.type == GOM::EventType::MouseMoved)
        {
            m_home.is_hovered(mouse_pos_f);
            m_light.is_hovered(mouse_pos_f);
        }
        if (m_mouse->isLeftMouseButtonPressed())
        {
            if (m_light.is_pressed(mouse_pos_f))
            {
                std::cout << "light btn pressed" << std::endl;
                if (m_light_mode)
                {
                    m_light_mode = false;
                    m_bg_s->setTexture(m_bg_dark_t, true);
                    m_top_border_s->setTexture(m_bg_border_dark_t, true);
                    m_bot_border_s->setTexture(m_bg_border_dark_t, true);
                    for (int i = 0; i < m_lines_hor_s.size(); i++)
                    {
                        m_lines_hor_s[i]->setTexture(m_line_dark_hor_t, true);
                    }
                    for (int i = 0; i < m_lines_ver_s.size(); i++)
                    {
                        m_lines_ver_s[i]->setTexture(m_line_dark_ver_t, true);
                    }
                }
                else
                {
                    m_light_mode = true;
                    m_bg_s->setTexture(m_bg_light_t, true);
                    m_top_border_s->setTexture(m_bg_border_light_t, true);
                    m_bot_border_s->setTexture(m_bg_border_light_t, true);
                    for (int i = 0; i < m_lines_hor_s.size(); i++)
                    {
                        m_lines_hor_s[i]->setTexture(m_line_light_hor_t, true);
                    }
                    for (int i = 0; i < m_lines_ver_s.size(); i++)
                    {
                        m_lines_ver_s[i]->setTexture(m_line_light_ver_t, true);
                    }
                }
            }
            if (m_home.is_pressed(mouse_pos_f))
            {
                std::cout << "home btn pressed" << std::endl;
                m_next = StateMachine::build<MainState>(
                    m_state_machine, m_window, m_graphic_loader, m_size, true);
            }
            if (mouse_pos_f.x > 0 && mouse_pos_f.x < m_size.x * 37 && mouse_pos_f.y > 100 && mouse_pos_f.y < m_size.y * 37 + 100)
            {
                if (isEmpty(mouse_pos_f))
                {
                    createIcon(mouse_pos_f);
                    if (m_turn)
                        m_turn = false;
                    else
                        m_turn = true;
                }
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

void GameState::draw()
{
    m_window->clear();
    m_window->draw(m_bg_s);
    m_window->draw(m_top_border_s);
    m_window->draw(m_bot_border_s);
    m_window->draw(m_light.getSprite());
    m_window->draw(m_home.getSprite());
    for (auto y = m_lines_hor_s.begin(); y != m_lines_hor_s.end(); ++y)
        m_window->draw(*y);
    for (auto x = m_lines_ver_s.begin(); x != m_lines_ver_s.end(); ++x)
        m_window->draw(*x);
    for (auto cross = m_cross_s.begin(); cross != m_cross_s.end(); ++cross)
        m_window->draw(*cross);
    for (auto circle = m_circle_s.begin(); circle != m_circle_s.end(); ++circle)
        m_window->draw(*circle);
    m_window->display();
}