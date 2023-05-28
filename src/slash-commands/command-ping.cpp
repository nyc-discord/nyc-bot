//
// Created by ariel on 5/27/23.
//

#include "command-ping.h"

void
Ping::execute()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->on_slashcommand([](auto event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    std::cout << "Ping command listener executed\n";
}

void
Ping::initialize_command()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->global_command_create(dpp::slashcommand("ping", "Ping pong!", bot->me.id));
}
