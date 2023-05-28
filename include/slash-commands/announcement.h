//
// Created by Ariel Saldana on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_ANNOUNCEMENT_H
#define NYC_DISCORD_BOT_ANNOUNCEMENT_H

#include "bot-instance.h"
#include "slash_command_registrar.h"
#include <string>

/**
 * Be sure to call REGISTER_COMMAND(<class>); in the implementation files
 */
class Announcement : public SlashCommandRegistrar
{
public:
    Announcement(const std::string& command_name, const std::string& command_description);

    void
    execute() override;

    void
    initialize_command() override;
};

#endif // NYC_DISCORD_BOT_ANNOUNCEMENT_H
