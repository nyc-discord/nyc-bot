//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_COMMAND_PING_H
#define NYC_DISCORD_BOT_COMMAND_PING_H

#include "bot-instance.h"
#include "command.h"

class Ping : public Command
{
public:
    Ping() { command_registry().push_back(this); }

    void
    execute() override
    {
        auto bot = this->bot_instance->bot_cluster.get();
        bot->on_slashcommand([](auto event) {
            if (event.command.get_command_name() == "ping")
            {
                event.reply("Pong!");
            }
        });

        std::cout << "my ping command executed\n";
    }

    void
    initialize_command() override
    {
        auto bot = this->bot_instance->bot_cluster.get();
        bot->global_command_create(dpp::slashcommand("ping", "Ping pong!", bot->me.id));
    }
};

REGISTER_COMMAND(Ping);

#endif // NYC_DISCORD_BOT_COMMAND_PING_H
