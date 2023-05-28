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
    Ping(const std::string& command_name, const std::string& command_description);

    void
    execute() override;
};
#endif // NYC_DISCORD_BOT_PING_H
