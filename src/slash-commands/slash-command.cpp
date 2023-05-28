//
// Created by ariel on 5/27/23.
//

#include "slash-command.h"

std::vector<SlashCommand*>&
command_registry()
{
    static std::vector<SlashCommand*> registry;
    return registry;
}

void
SlashCommand::initialize_command()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->global_command_create(dpp::slashcommand(this->command_name, this->command_description, bot->me.id));
}
