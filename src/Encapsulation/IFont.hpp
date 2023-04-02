#ifndef IFONT_HPP_
#define IFONT_HPP_

#include <string>

#include "./GraphicDataTypes.hpp"

namespace GOM
{
    class IFont
    {
    public:
        virtual ~IFont() = default;

        virtual bool loadFromFile(const std::string &filename) = 0;
    };
} // namespace GOM

#endif /* !IFONT_HPP_ */