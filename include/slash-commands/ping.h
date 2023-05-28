//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_PING_H
#define NYC_DISCORD_BOT_PING_H

#include "bot-instance.h"
#include "slash_command_registrar.h"

class Ping : public SlashCommandRegistrar
{
public:
    Ping() { command_registry().push_back(this); }

    void
    execute() override;

    void
    initialize_command() override;
};

REGISTER_COMMAND(Ping);

#endif // NYC_DISCORD_BOT_PING_H