//
// Created by ariel on 5/27/23.
//

#include "slash-commands/slash_command_registrar.h"

std::vector<SlashCommandRegistrar*>&
command_registry()
{
    static std::vector<SlashCommandRegistrar*> registry;
    return registry;
}

void
SlashCommandRegistrar::initialize_command()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->global_command_create(dpp::slashcommand(this->command_name, this->command_description, bot->me.id));
}

SlashCommandRegistrar::SlashCommandRegistrar(const std::string& command_name, const std::string& command_description)
    : bot_instance(&BotInstance::get_instance())
{
    this->command_name = command_name;
    this->command_description = command_description;
}
