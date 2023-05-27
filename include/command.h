//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_COMMAND_H
#define NYC_DISCORD_BOT_COMMAND_H

#include "bot-instance.h"
#include <iostream>
#include <vector>

class Command
{
protected:
    BotInstance* bot_instance;

public:
    Command()
        : bot_instance(&BotInstance::get_instance())
    {
    }
    virtual void
    execute()
        = 0;
    virtual void
    initialize_command()
        = 0;
};

std::vector<Command*>&
command_registry();

#define REGISTER_COMMAND(CMD)                                                                                          \
    namespace                                                                                                          \
    {                                                                                                                  \
        CMD static_##CMD##_instance;                                                                                   \
    }
#endif // NYC_DISCORD_BOT_COMMAND_H
