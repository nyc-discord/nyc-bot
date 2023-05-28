//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_SLASH_COMMAND_H
#define NYC_DISCORD_BOT_SLASH_COMMAND_H

#include "bot-instance.h"
#include <iostream>
#include <vector>

class SlashCommand
{
protected:
    BotInstance* bot_instance;
    std::string command_name;
    std::string command_description;

public:
    SlashCommand()
        : bot_instance(&BotInstance::get_instance())
    {
    }

    virtual void
    execute() = 0;

    virtual void
    initialize_command() = 0;
};

std::vector<SlashCommand*>&
command_registry();

#define REGISTER_COMMAND(CMD)        \
    namespace                        \
    {                                \
        CMD static_##CMD##_instance; \
    }
#endif // NYC_DISCORD_BOT_SLASH_COMMAND_H
