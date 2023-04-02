#ifndef GRAPHICLOADER_HPP
#define GRAPHICLOADER_HPP

#include "../IGraphicLoader.hpp"

#include "./Font.hpp"
#include "./Mouse.hpp"
#include "./RectangleShape.hpp"
#include "./RenderWindow.hpp"
#include "./Sprite.hpp"
#include "./Text.hpp"
#include "./Texture.hpp"

namespace GOM
{
  class GraphicLoader : public IGraphicLoader
  {
  public:
    GraphicLoader() = default;
    ~GraphicLoader() override = default;

    IFont *loadFont() override;
    IMouse *loadMouse() override;
    IRectangleShape *loadRectangleShape() override;
    IRenderWindow *loadRenderWindow() override;
    ISprite *loadSprite() override;
    IText *loadText() override;
    ITexture *loadTexture() override;
  };
} // namespace GOM

#endif // GRAPHICLOADER_HPP
