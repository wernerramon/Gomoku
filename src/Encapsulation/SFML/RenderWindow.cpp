#include "./RenderWindow.hpp"

GOM::RenderWindow::RenderWindow() {}

GOM::RenderWindow::RenderWindow(unsigned int t_width, unsigned int t_height,
                                  std::string t_title) {
  create(t_width, t_height, t_title);
}

GOM::RenderWindow::~RenderWindow() {}

void GOM::RenderWindow::draw(const GOM::ISprite *t_sprite) {
  GOM::ISprite *sprite = const_cast<GOM::ISprite *>(t_sprite);

  m_window.draw(dynamic_cast<GOM::Sprite *>(sprite)->getSprite());
}

void GOM::RenderWindow::draw(GOM::IRectangleShape *t_shape) {
  m_window.draw(
    dynamic_cast<GOM::RectangleShape *>(t_shape)->getRectangleShape());
}

void GOM::RenderWindow::draw(const GOM::IText *t_text) {
  GOM::IText *text = const_cast<GOM::IText *>(t_text);
  m_window.draw(dynamic_cast<GOM::Text *>(text)->getText());
}

void GOM::RenderWindow::display() { m_window.display(); }

GOM::Vector2u GOM::RenderWindow::getSize() const {
  return {m_window.getSize().x, m_window.getSize().y};
}

bool GOM::RenderWindow::isOpen() { return m_window.isOpen(); }

void GOM::RenderWindow::close() { m_window.close(); }

void GOM::RenderWindow::clear(GOM::Color t_color) {
  m_window.clear(sf::Color(t_color.r, t_color.g, t_color.b, t_color.a));
}

void GOM::RenderWindow::setFramerateLimit(unsigned int t_fps) {
  m_window.setFramerateLimit(t_fps);
}

void GOM::RenderWindow::create(unsigned int t_width, unsigned int t_height,
                                 std::string t_title) {
  m_window.create(sf::VideoMode(t_width, t_height), t_title);
}

void GOM::RenderWindow::create(unsigned int t_width, unsigned int t_height,
                                 std::string t_title, GOM::Style t_style) {
  m_window.create(sf::VideoMode(t_width, t_height), t_title, t_style);
}

bool GOM::RenderWindow::pollEvent(GOM::Event &t_event) {
  bool res = m_window.pollEvent(m_event);
  t_event.type = GOM::EventType(m_event.type);
  t_event.key = GOM::EventKey(m_event.key.code);
  return res;
}

sf::RenderWindow *GOM::RenderWindow::getRenderWindow() { return &m_window; }
