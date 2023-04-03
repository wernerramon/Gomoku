#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include <iostream>
#include <sstream>

#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"
#include "../Encapsulation/Event.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
public:
        Textbox();
        Textbox(int t_size, GOM::Color t_color, bool t_sel,
                GOM::IGraphicLoader *t_graphic_loader);

        void setFont(GOM::IFont *t_font);
        void setPosition(const GOM::Vector2f &t_position);
        void setLimit(bool t_has_limit);
        void setLimit(bool t_has_limit, int t_limit);
        void setSelected(bool t_sel);
        GOM::IText *getText();
        void typedOn(GOM::Event t_input);
        int getLength();
        std::string getTextString() const;
        bool getSelected();
        void resetString();

private:
        GOM::IFont *m_font;
        std::ostringstream m_text;
        GOM::IText *m_textbox;
        bool m_is_selected = false;
        bool m_has_limit = false;
        int m_limit;
        GOM::IGraphicLoader *m_graphic_loader;

        void inputLogic(int t_char_typed);
        void deleteLastChar();
};

#endif /* !TEXTBOX_HPP_ */
