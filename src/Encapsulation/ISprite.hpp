#ifndef ISPRITE_HPP
#define ISPRITE_HPP

#include <string>

#include "./GraphicDataTypes.hpp"
#include "./ITexture.hpp"

namespace GOM
{
    class ISprite
    {
    public:
        virtual ~ISprite() = default;

        virtual void setTexture(GOM::ITexture *texture,
                                bool reset_rect = false) = 0;
        virtual void setTextureRect(const GOM::IntRect &rectangle) = 0;
        virtual void setPosition(const GOM::Vector2f &position) = 0;
        virtual void setScale(const GOM::Vector2f &factor) = 0;
        virtual void setRotation(float angle) = 0;
        virtual void setOrigin(const GOM::Vector2f &origin) = 0;
        virtual void setColor(const GOM::Color &color) = 0;
        virtual void move(const GOM::Vector2f &offset) = 0;
        virtual void rotate(float angle) = 0;
        virtual void scale(const GOM::Vector2f &factor) = 0;
        virtual GOM::Vector2u getSize() const = 0;
        virtual const GOM::ITexture *getTexture() const = 0;
        virtual GOM::FloatRect getLocalBounds() const = 0;
        virtual GOM::FloatRect getGlobalBounds() const = 0;

        virtual bool contains(const GOM::Vector2f &point) const = 0;
    };
} // namespace GOM

#endif // ISPRITE_HPP