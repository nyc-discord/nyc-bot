//
// Created by Ariel Saldana on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_ANNOUNCE_H
#define NYC_DISCORD_BOT_ANNOUNCE_H

#include "bot-instance.h"
#include "slash_command_registrar.h"
#include <string>

/**
 * Be sure to call REGISTER_COMMAND(<class>); in the implementation files
 */
class Announce : public SlashCommandRegistrar
{
public:
    Announce( const std::string& command_name, const std::string& command_description );

    void
    execute() override;
};

#endif // NYC_DISCORD_BOT_ANNOUNCE_H
