//
// Created by ariel on 5/27/23.
//

#include "command.h"

std::vector<Command*>&
command_registry()
{
    static std::vector<Command*> registry;
    return registry;
}
