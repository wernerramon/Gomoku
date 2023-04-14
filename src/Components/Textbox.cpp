#include "Textbox.hpp"

Textbox::Textbox() {}

Textbox::Textbox(int t_size, GOM::Color t_color, bool t_sel,
                 GOM::IGraphicLoader *m_graphic_loader)
{
  m_textbox = m_graphic_loader->loadText();
  m_font = m_graphic_loader->loadFont();
  m_textbox->setCharacterSize(t_size);
  m_textbox->setColor(t_color);
  m_is_selected = t_sel;
  if (!m_font->loadFromFile("./assets/font/Roboto/Roboto-Black.ttf"))
  {
    throw std::runtime_error("Unable to load font.");
  }
  m_textbox->setFont(m_font);
  if (t_sel)
  {
    m_textbox->setString("_");
  }
  else
  {
    m_textbox->setString("");
  }
}

void Textbox::inputLogic(int t_char_typed)
{
  if (t_char_typed != DELETE_KEY && t_char_typed != ENTER_KEY &&
      t_char_typed != ESCAPE_KEY)
  {
    if (t_char_typed > 47 && t_char_typed < 58 || t_char_typed == 46)
    {
      m_text << static_cast<char>(t_char_typed);
    }
  }
  else if (t_char_typed == DELETE_KEY)
  {
    if (m_text.str().length() > 0)
    {
      deleteLastChar();
    }
  }
  m_textbox->setString(m_text.str());
}

void Textbox::deleteLastChar()
{
  std::string t = m_text.str();
  std::string new_t = "";
  for (int i = 0; i < t.length() - 1; i++)
  {
    new_t += t[i];
  }
  m_text.str("");
  m_text << new_t;
  m_textbox->setString(m_text.str());
}

void Textbox::setFont(GOM::IFont *t_font) { m_textbox->setFont(t_font); }

void Textbox::setPosition(const GOM::Vector2f &t_position)
{
  m_textbox->setPosition(t_position);
}

void Textbox::setLimit(bool t_has_limit) { m_has_limit = t_has_limit; }

void Textbox::setLimit(bool t_has_limit, int t_limit)
{
  m_has_limit = t_has_limit;
  m_limit = t_limit;
}

void Textbox::setSelected(bool t_sel)
{
  m_is_selected = t_sel;
  if (!t_sel)
  {
    std::string t = m_text.str();
    std::string new_t = "";
    for (int i = 0; i < t.length(); i++)
    {
      new_t += t[i];
    }
    m_textbox->setString(new_t);
  }
}

GOM::IText *Textbox::getText() { return m_textbox; }

void Textbox::typedOn(GOM::Event t_input)
{
  if (m_is_selected)
  {
    int char_typed = t_input.key;
    if (char_typed < 128)
    {
      if (m_has_limit)
      {
        if (m_text.str().length() + 1 < m_limit)
        {
          inputLogic(char_typed);
          m_textbox->setString(m_text.str() + "_");
        }
        else if (m_text.str().length() + 1 == m_limit)
        {
          inputLogic(char_typed);
          m_textbox->setString(m_text.str());
        }
        else if (m_text.str().length() + 1 > m_limit &&
                 char_typed == DELETE_KEY)
        {
          deleteLastChar();
          m_textbox->setString(m_text.str() + "_");
        }
      }
      else
      {
        inputLogic(char_typed);
        m_textbox->setString(m_text.str() + "_");
      }
    }
  }
}

int Textbox::getLength() { return m_text.str().length(); }

std::string Textbox::getTextString() const { return m_text.str().c_str(); }

bool Textbox::getSelected() { return m_is_selected; }

void Textbox::resetString()
{
  m_textbox->setString("_");
  m_text.str("");
  m_text.clear();
}