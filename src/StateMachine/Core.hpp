/*
** EPITECH PROJECT, 2023
** Gomoku
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../Encapsulation/IRenderWindow.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"
#include "../Encapsulation/SFML/GraphicLoader.hpp"
#include "./StateMachine.hpp"
#include "../States/MainState.hpp"

class Core
{
public:
    Core();
    ~Core();
    void run();

private:
    GOM::IRenderWindow *m_window;
    GOM::IGraphicLoader *m_graphic_loader;
    StateMachine m_state_machine;
};

#endif /* !CORE_HPP_ */
