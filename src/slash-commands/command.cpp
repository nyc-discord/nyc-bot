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

void
Command::initialize_command()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->global_command_create(dpp::slashcommand(this->command_name, this->command_description, bot->me.id));
}
