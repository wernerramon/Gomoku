#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "../IRenderWindow.hpp"
#include "./Sprite.hpp"
#include "./RectangleShape.hpp"
#include "./Text.hpp"

namespace GOM
{

  class RenderWindow : public IRenderWindow
  {
  public:
    RenderWindow();
    RenderWindow(unsigned int t_width, unsigned int t_height,
                 std::string t_title);
    ~RenderWindow();

    void draw(const GOM::ISprite *t_sprite) override;
    void draw(GOM::IRectangleShape *t_shape) override;
    void draw(const GOM::IText *t_text) override;
    void display() override;
    GOM::Vector2u getSize() const override;
    bool isOpen() override;
    void close() override;
    void clear(GOM::Color t_color) override;
    void setFramerateLimit(unsigned int t_fps) override;
    void create(unsigned int t_width, unsigned int t_height,
                std::string t_title) override;
    void create(unsigned int t_width, unsigned int t_height,
                std::string t_title, GOM::Style t_style) override;
    bool pollEvent(GOM::Event &t_event) override;

    sf::RenderWindow *getRenderWindow();

  private:
    sf::RenderWindow m_window;
    sf::Event m_event;
  };
} // namespace GOM

#endif // RENDERWINDOW_HPP
