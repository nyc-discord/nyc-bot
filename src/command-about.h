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
    execute() override
    {
        auto bot = this->bot_instance->bot_cluster.get();
        bot->on_slashcommand([](auto event) {
            if (event.command.get_command_name() == "about")
            {
                event.reply(
                    "This is an open source bot. Please visit:\n "
                    "https://github.com/nyc-discord/nyc-bot/tree/main to "
                    "view the code and contribute!");
            }
        });

        std::cout << "About command listener executed\n";
    }

    void
    initialize_command() override
    {
        auto bot = this->bot_instance->bot_cluster.get();
        bot->global_command_create(dpp::slashcommand("about", "About this bot!", bot->me.id));
    }
};

REGISTER_COMMAND(About);

#endif // NYC_DISCORD_BOT_COMMAND_ABOUT_H
