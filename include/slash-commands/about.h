//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_ABOUT_H
#define NYC_DISCORD_BOT_ABOUT_H

#include "bot-instance.h"
#include "slash_command_registrar.h"

class About : public SlashCommandRegistrar
{
public:
    About( const std::string& command_name, const std::string& command_description );

    void
    execute() override;
};

#endif // NYC_DISCORD_BOT_ABOUT_H
