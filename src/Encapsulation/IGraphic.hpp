#ifndef IGRAPHIC_HPP
#define IGRAPHIC_HPP

#include "GraphicDataTypes.hpp"
#include "SFML/RenderWindow.hpp"

namespace GOM
{
    class IGraphic
    {
    public:
        virtual ~IGraphic() = default;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void updateData() = 0;

    private:
        GOM::RenderWindow m_window;
    };
} // namespace GOM

#endif // IGRAPHIC_HPP