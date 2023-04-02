#include "GraphicLoader.hpp"

GOM::IFont *GOM::GraphicLoader::loadFont() { return new Font(); }

GOM::IMouse *GOM::GraphicLoader::loadMouse() { return new Mouse(); }

GOM::IRectangleShape *GOM::GraphicLoader::loadRectangleShape()
{
  return new RectangleShape();
}

GOM::IRenderWindow *GOM::GraphicLoader::loadRenderWindow()
{
  return new RenderWindow();
}

GOM::ISprite *GOM::GraphicLoader::loadSprite() { return new Sprite(); }

GOM::IText *GOM::GraphicLoader::loadText() { return new Text(); }

GOM::ITexture *GOM::GraphicLoader::loadTexture() { return new Texture(); }
