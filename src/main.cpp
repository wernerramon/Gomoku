#include "./StateMachine/Core.hpp"

int counter;

int action_counter;

int main(int ac, char *av[])
{
    Core core;
    core.run();
    return 0;
}