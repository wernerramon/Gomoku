#ifndef IRECTANGLESHAPE_HPP
#define IRECTANGLESHAPE_HPP

#include "./GraphicDataTypes.hpp"
#include "./ITexture.hpp"

namespace GOM
{
    class IRectangleShape
    {
    public:
        enum SIDE
        {
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            NONE
        };
        virtual ~IRectangleShape() = default;

        virtual void setFillColor(const GOM::Color &) = 0;
        virtual void setOutlineColor(const GOM::Color &) = 0;
        virtual void setOutlineThickness(float) = 0;

        virtual void setSize(const GOM::Vector2f &) = 0;
        virtual void setPosition(const GOM::Vector2f &) = 0;
        virtual void setTexture(const GOM::ITexture *) = 0;
        virtual void setTextureRect(const GOM::IntRect &) = 0;
        virtual void setRotation(float) = 0;
        virtual void setScale(const GOM::Vector2f &) = 0;
        virtual void setOrigin(const GOM::Vector2f &) = 0;
        virtual void rotate(float) = 0;
        virtual void scale(const GOM::Vector2f &) = 0;

        virtual bool intersects(const GOM::FloatRect &) = 0;
        virtual SIDE intersectsSide(const GOM::FloatRect &) = 0;

        virtual const GOM::Vector2f &getSize() = 0;
        virtual const GOM::Vector2f &getPosition() = 0;
        virtual const GOM::FloatRect &getGlobalBounds() = 0;
        virtual const GOM::IntRect &getTextureRect() = 0;
        virtual float getRotation() const = 0;
        virtual const GOM::Vector2f &getScale() = 0;
        virtual const GOM::Vector2f &getOrigin() = 0;
    };
} // namespace GOM

#endif // IRECTANGLESHAPE_HPP