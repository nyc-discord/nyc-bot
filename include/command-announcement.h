//
// Created by Ariel Saldana on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_COMMAND_ANNOUNCEMENT_H
#define NYC_DISCORD_BOT_COMMAND_ANNOUNCEMENT_H

#include "bot-instance.h"
#include "slash-command.h"
#include <string>

class Announcement : public SlashCommand
{
public:
    Announcement() { command_registry().push_back(this); }
    std::string command_name = "announce";
    std::string command_description = "Announcement command";

    void
    execute() override;

    void
    initialize_command() override;
};

REGISTER_COMMAND(Announcement);

#endif // NYC_DISCORD_BOT_COMMAND_ANNOUNCEMENT_H
