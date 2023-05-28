//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_COMMAND_ABOUT_H
#define NYC_DISCORD_BOT_COMMAND_ABOUT_H

#include "bot-instance.h"
#include "command.h"

class About : public Command
{
public:
    About() { command_registry().push_back(this); }

    void
    execute() override;

    void
    initialize_command() override;
};

REGISTER_COMMAND(About);

#endif // NYC_DISCORD_BOT_COMMAND_ABOUT_H
