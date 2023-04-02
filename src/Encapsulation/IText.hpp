#ifndef ITEXT_HPP_
#define ITEXT_HPP_

#include <string>

#include "./GraphicDataTypes.hpp"
#include "./IFont.hpp"

namespace GOM
{
    class IText
    {
    public:
        virtual ~IText() = default;

        virtual void setFont(GOM::IFont *font) = 0;
        virtual void setPosition(const GOM::Vector2f &position) = 0;
        virtual void setString(const std::string &string) = 0;
        virtual void setCharacterSize(unsigned int size) = 0;
        virtual void setColor(const GOM::Color &color) = 0;
        virtual const GOM::IFont *getFont() const = 0;
        virtual unsigned int getCharacterSize() const = 0;
        virtual void setScale(const GOM::Vector2f &factor) = 0;
        virtual const GOM::Vector2f &getPosition() const = 0;
        virtual const std::string &getString() const = 0;
        virtual GOM::FloatRect getLocalBounds() const = 0;
    };
} // namespace GOM

#endif /* !ITEXT_HPP_ */