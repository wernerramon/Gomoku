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
}

MainState::MainState(StateMachine &t_machine, GOM::IRenderWindow *t_window,
                     GOM::IGraphicLoader *t_graphic_loader, const bool t_replace)
    : State(t_machine, t_window, t_graphic_loader, t_replace)
{
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
    m_window->display();
}