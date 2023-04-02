#ifndef IGRAPHICLOADER_HPP
#define IGRAPHICLOADER_HPP

#include "IFont.hpp"
#include "IMouse.hpp"
#include "IRectangleShape.hpp"
#include "IRenderWindow.hpp"
#include "ISprite.hpp"
#include "IText.hpp"
#include "ITexture.hpp"

namespace GOM
{
    class IGraphicLoader
    {
    public:
        virtual ~IGraphicLoader() = default;

        virtual GOM::IFont *loadFont() = 0;
        virtual GOM::IMouse *loadMouse() = 0;
        virtual GOM::IRectangleShape *loadRectangleShape() = 0;
        virtual GOM::IRenderWindow *loadRenderWindow() = 0;
        virtual GOM::ISprite *loadSprite() = 0;
        virtual GOM::IText *loadText() = 0;
        virtual GOM::ITexture *loadTexture() = 0;
    };
} // namespace GOM

#endif // IGRAPHICLOADER_HPP