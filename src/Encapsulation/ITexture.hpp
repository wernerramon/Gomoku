#ifndef ITEXTURE_HPP
#define ITEXTURE_HPP

#include <string>

#include "./GraphicDataTypes.hpp"

namespace GOM
{
    class ITexture
    {
    public:
        virtual ~ITexture() = default;

        virtual bool loadFromFile(const std::string &filename) = 0;
        virtual bool loadFromFile(const std::string &filename,
                                  const IntRect &area) = 0;

        virtual GOM::Vector2u getSize() const = 0;
    };
} // namespace GOM

#endif // ITEXTURE_HPP