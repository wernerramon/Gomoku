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
    m_icon_p1 = m_graphic_loader->loadSprite();
    m_icon_p2 = m_graphic_loader->loadSprite();
    m_bg_restart_s = m_graphic_loader->loadSprite();

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
        m_bg_restart_s->setTexture(m_bg_border_light_t, true);
    }
    else
    {
        m_bg_s->setTexture(m_bg_dark_t, true);
        m_top_border_s->setTexture(m_bg_border_dark_t, true);
        m_bot_border_s->setTexture(m_bg_border_dark_t, true);
        m_bg_restart_s->setTexture(m_bg_border_dark_t, true);
    }

    m_bot_border_s->setPosition({0, 845});
    m_bg_restart_s->setPosition({0, size_y / 2 - 25});
    m_bg_s->setScale({scale_x, scale_y});
    m_icon_p1->setTexture(m_cross_t, true);
    m_icon_p2->setTexture(m_circle_t, true);
    m_icon_p1->setScale({40.f / m_cross_t->getSize().x, 40.f / m_cross_t->getSize().y});
    m_icon_p2->setScale({40.f / m_cross_t->getSize().x, 40.f / m_cross_t->getSize().y});
    m_icon_p1->setColor(GOM::Blue);
    m_icon_p2->setColor(GOM::Red);
}

void GameState::initText()
{
    float size_x = m_window->getSize().x;
    float size_y = m_window->getSize().y;
    m_font = m_graphic_loader->loadFont();
    if (!m_font->loadFromFile("./assets/font/Roboto/Roboto-Black.ttf"))
    {
        throw std::runtime_error("Unable to load font.");
    }
    m_p1_name = m_graphic_loader->loadText();
    m_p2_name = m_graphic_loader->loadText();
    m_score = m_graphic_loader->loadText();
    m_move = m_graphic_loader->loadText();
    m_time_total_p1 = m_graphic_loader->loadText();
    m_time_turn_p1 = m_graphic_loader->loadText();
    m_time_total_p2 = m_graphic_loader->loadText();
    m_time_turn_p2 = m_graphic_loader->loadText();
    m_restart = m_graphic_loader->loadText();

    m_p1_name->setFont(m_font);
    m_p2_name->setFont(m_font);
    m_score->setFont(m_font);
    m_move->setFont(m_font);
    m_time_total_p1->setFont(m_font);
    m_time_turn_p1->setFont(m_font);
    m_time_total_p2->setFont(m_font);
    m_time_turn_p2->setFont(m_font);
    m_restart->setFont(m_font);

    m_p1_name->setCharacterSize(25);
    m_p2_name->setCharacterSize(25);
    m_score->setCharacterSize(25);
    m_move->setCharacterSize(25);
    m_time_total_p1->setCharacterSize(25);
    m_time_turn_p1->setCharacterSize(25);
    m_time_total_p2->setCharacterSize(25);
    m_time_turn_p2->setCharacterSize(25);
    m_restart->setCharacterSize(30);

    if (m_mode == 0 || m_mode == 1)
    {
        m_p1_name->setString("HUMAN");
        m_p2_name->setString("HUMAN");
    }
    else if (m_mode == 2)
    {
        m_p1_name->setString("HUMAN");
        m_p2_name->setString("AI");
    }
    else
    {
        m_p1_name->setString("AI");
        m_p2_name->setString("AI");
    }

    m_score->setString("SCORE " + std::to_string(m_score_p1) + ":" + std::to_string(m_score_p2));
    m_move->setString("MOVE " + std::to_string(m_move_count));
    m_time_total_p1->setString("0:00");
    m_time_turn_p1->setString("0.0");
    m_time_total_p2->setString("0:00");
    m_time_turn_p2->setString("0.0");
    m_restart->setString("PRESS 'ENTER' TO PLAY AGAIN!");

    m_time_total_p1->setPosition({10, 855});
    m_time_turn_p1->setPosition({10, 865 + m_time_total_p1->getLocalBounds().height});
    m_score->setPosition({size_x / 2 - (m_score->getLocalBounds().width / 2), 855});
    m_move->setPosition({size_x / 2 - (m_move->getLocalBounds().width / 2), 865 + m_score->getLocalBounds().height});
    m_time_total_p2->setPosition({size_x - 10 - m_time_total_p2->getLocalBounds().width, 855});
    m_time_turn_p2->setPosition({size_x - 10 - m_time_turn_p2->getLocalBounds().width, 865 + m_time_total_p2->getLocalBounds().height});
    m_p1_name->setPosition({size_x / 4 - (m_p1_name->getLocalBounds().width / 2), 855});
    m_p2_name->setPosition({(size_x * 0.75f) - (m_p2_name->getLocalBounds().width / 2), 855});
    m_restart->setPosition({size_x / 2 - (m_restart->getLocalBounds().width / 2), size_y / 2});
    m_restart->setColor(GOM::Red);
    m_icon_p1->setPosition({(size_x / 4) - 20, 865 + m_p1_name->getLocalBounds().height});
    m_icon_p2->setPosition({(size_x * 0.75f) - 20, 865 + m_p2_name->getLocalBounds().height});
}

GameState::GameState(StateMachine &t_machine, GOM::IRenderWindow *t_window, std::size_t t_mode,
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
    for (int y = 0; y < m_size.y; y++)
    {
        std::vector<int> tmp = {};
        for (int x = 0; x < m_size.x; x++)
        {
            tmp.push_back(0);
        }
        m_board.push_back(tmp);
    }
    m_light_mode = true;
    m_turn = true;
    m_mode = t_mode;
    m_score_p1 = 0;
    m_score_p2 = 0;
    m_move_count = 0;
    initSprites();
    initText();
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
    GOM::Vector2i coord = {0, 0};
    if (m_turn)
    {
        for (int i = 0; i < m_size.x; i++)
        {
            if (t_mouse_pos.x > i * 37 && t_mouse_pos.x < (i + 1) * 37)
            {
                pos.x = i * 37;
                coord.x = i;
            }
        }
        for (int i = 0; i < m_size.y; i++)
        {
            if (t_mouse_pos.y > (i * 37) + 100 && t_mouse_pos.y < ((i + 1) * 37) + 100)
            {
                pos.y = (i * 37) + 100;
                coord.y = i;
            }
        }
        GOM::ISprite *tmp = m_graphic_loader->loadSprite();
        tmp->setTexture(m_cross_t, true);
        tmp->setScale({40.f / m_cross_t->getSize().x, 40.f / m_cross_t->getSize().y});
        tmp->setPosition(pos);
        tmp->setColor(GOM::Blue);
        m_board[coord.y][coord.x] = 1;
        m_cross_s.push_back(tmp);
    }
    else
    {
        for (int i = 0; i < m_size.x; i++)
        {
            if (t_mouse_pos.x > i * 37 && t_mouse_pos.x < (i + 1) * 37)
            {
                pos.x = i * 37;
                coord.x = i;
            }
        }
        for (int i = 0; i < m_size.y; i++)
        {
            if (t_mouse_pos.y > (i * 37) + 100 && t_mouse_pos.y < ((i + 1) * 37) + 100)
            {
                pos.y = (i * 37) + 100;
                coord.y = i;
            }
        }
        GOM::ISprite *tmp = m_graphic_loader->loadSprite();
        tmp->setTexture(m_circle_t, true);
        tmp->setScale({40.f / m_cross_t->getSize().x, 40.f / m_cross_t->getSize().y});
        tmp->setPosition(pos);
        tmp->setColor(GOM::Red);
        m_board[coord.y][coord.x] = 2;
        m_circle_s.push_back(tmp);
    }
}

int GameState::check_win_or_draw(const std::vector<std::vector<int>> &board)
{
    // check horzontal win
    for (const auto &row : board)
    {
        int check = 0;
        for (int i = 0; i <= row.size() - 5; i++)
        {
            if (row[i] == 1 && row[i] == row[i + 1] && row[i] == row[i + 2] && row[i] == row[i + 3] && row[i] == row[i + 4])
            {
                return 1;
            }
            if (row[i] == 2 && row[i] == row[i + 1] && row[i] == row[i + 2] && row[i] == row[i + 3] && row[i] == row[i + 4])
            {
                return 2;
            }
        }
    }
    // check vertical win
    for (int col = 0; col < board[0].size(); col++)
    {
        for (int row = 0; row <= board.size() - 5; row++)
        {
            if (board[row][col] == 1 && board[row][col] == board[row + 1][col] && board[row][col] == board[row + 2][col] &&
                board[row][col] == board[row + 3][col] && board[row][col] == board[row + 4][col])
            {
                return 1;
            }
            if (board[row][col] == 2 && board[row][col] == board[row + 1][col] && board[row][col] == board[row + 2][col] &&
                board[row][col] == board[row + 3][col] && board[row][col] == board[row + 4][col])
            {
                return 2;
            }
        }
    }
    // Check for diagonal win (top-left to bottom-right)
    for (int row = 0; row <= board.size() - 5; row++)
    {
        for (int col = 0; col <= board[0].size() - 5; col++)
        {
            if (board[row][col] == 1 && board[row][col] == board[row + 1][col + 1] && board[row][col] == board[row + 2][col + 2] &&
                board[row][col] == board[row + 3][col + 3] && board[row][col] == board[row + 4][col + 4])
            {
                return 1;
            }
            if (board[row][col] == 2 && board[row][col] == board[row + 1][col + 1] && board[row][col] == board[row + 2][col + 2] &&
                board[row][col] == board[row + 3][col + 3] && board[row][col] == board[row + 4][col + 4])
            {
                return 2;
            }
        }
    }

    // Check for diagonal win (top-right to bottom-left)
    for (int row = 0; row <= board.size() - 5; row++)
    {
        for (int col = 4; col < board[0].size(); col++)
        {
            if (board[row][col] == 1 && board[row][col] == board[row + 1][col - 1] && board[row][col] == board[row + 2][col - 2] &&
                board[row][col] == board[row + 3][col - 3] && board[row][col] == board[row + 4][col - 4])
            {
                return 1;
            }
            if (board[row][col] == 2 && board[row][col] == board[row + 1][col - 1] && board[row][col] == board[row + 2][col - 2] &&
                board[row][col] == board[row + 3][col - 3] && board[row][col] == board[row + 4][col - 4])
            {
                return 2;
            }
        }
    }
    bool is_draw = true;
    for (const auto &row : board)
    {
        for (int cell : row)
        {
            if (cell == 0)
            {
                is_draw = false;
                break;
            }
        }
        if (!is_draw)
        {
            break;
        }
    }
    if (is_draw)
    {
        return 3; // Draw
    }
    return 0;
}

void GameState::update()
{
    if (m_turn)
    {
        m_p1_name->setColor(GOM::EpiBlue);
        m_p2_name->setColor(GOM::White);
    }
    else
    {
        m_p2_name->setColor(GOM::EpiBlue);
        m_p1_name->setColor(GOM::White);
    }
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
                    m_bg_restart_s->setTexture(m_bg_border_dark_t, true);
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
                    m_bg_restart_s->setTexture(m_bg_border_light_t, true);
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
                    m_state_machine, m_window, m_mode, m_graphic_loader, m_size, true);
            }
            if (mouse_pos_f.x > 0 && mouse_pos_f.x < m_size.x * 37 && mouse_pos_f.y > 100 && mouse_pos_f.y < m_size.y * 37 + 100)
            {
                if (isEmpty(mouse_pos_f) && check_win_or_draw(m_board) == 0)
                {
                    createIcon(mouse_pos_f);
                    if (m_turn)
                        m_turn = false;
                    else
                        m_turn = true;
                    m_move_count++;
                    m_move->setString("MOVE " + std::to_string(m_move_count));
                    m_move->setPosition({m_window->getSize().x / 2 - (m_move->getLocalBounds().width / 2), 865 + m_score->getLocalBounds().height});
                    if (check_win_or_draw(m_board) == 1)
                    {
                        std::cout << "Player 1 won!" << std::endl;
                        m_score_p1++;
                        m_score->setString("SCORE " + std::to_string(m_score_p1) + ":" + std::to_string(m_score_p2));
                        m_score->setPosition({m_window->getSize().x / 2 - (m_score->getLocalBounds().width / 2), 855});
                    }
                    else if (check_win_or_draw(m_board) == 2)
                    {
                        std::cout << "Player 2 won!" << std::endl;
                        m_score_p2++;
                        m_score->setString("SCORE " + std::to_string(m_score_p1) + ":" + std::to_string(m_score_p2));
                        m_score->setPosition({m_window->getSize().x / 2 - (m_score->getLocalBounds().width / 2), 855});
                    }
                    else if (check_win_or_draw(m_board) == 3)
                    {
                        std::cout << "Draw!" << std::endl;
                    }
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
                m_move_count = 0;
                m_move->setString("MOVE " + std::to_string(m_move_count));
                m_move->setPosition({m_window->getSize().x / 2 - (m_move->getLocalBounds().width / 2), 865 + m_score->getLocalBounds().height});
                m_circle_s.clear();
                m_cross_s.clear();
                m_board.clear();
                for (int y = 0; y < m_size.y; y++)
                {
                    std::vector<int> tmp = {};
                    for (int x = 0; x < m_size.x; x++)
                    {
                        tmp.push_back(0);
                    }
                    m_board.push_back(tmp);
                }
            default:
                break;
            }
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
    if (check_win_or_draw(m_board) != 0)
    {
        m_window->draw(m_bg_restart_s);
        m_window->draw(m_restart);
    }
    m_window->draw(m_time_total_p1);
    m_window->draw(m_time_turn_p1);
    m_window->draw(m_p1_name);
    m_window->draw(m_score);
    m_window->draw(m_move);
    m_window->draw(m_p2_name);
    m_window->draw(m_time_total_p2);
    m_window->draw(m_time_turn_p2);
    m_window->draw(m_icon_p1);
    m_window->draw(m_icon_p2);
    m_window->display();
}