//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_SLASH_COMMAND_REGISTRAR_H
#define NYC_DISCORD_BOT_SLASH_COMMAND_REGISTRAR_H

#include "bot-instance.h"
#include <iostream>
#include <vector>

class SlashCommandRegistrar
{
protected:
    BotInstance* bot_instance;
    std::string command_name;
    std::string command_description;

public:
    SlashCommandRegistrar(const std::string& command_name, const std::string& command_description);

    virtual void
    execute() = 0;

    virtual void
    initialize_command();
};

std::vector<SlashCommandRegistrar*>&
command_registry();

#define REGISTER_COMMAND(CMD, CMD_NAME, CMD_DESCRIPTION)        \
    namespace                                                   \
    {                                                           \
        CMD static_##CMD##_instance(CMD_NAME, CMD_DESCRIPTION); \
    }
#endif // NYC_DISCORD_BOT_SLASH_COMMAND_REGISTRAR_H
