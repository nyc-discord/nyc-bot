//
// Created by ariel on 5/27/23.
//

#include "slash-commands/about.h"

void
About::execute()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->on_slashcommand([](auto event) {
        if (event.command.get_command_name() == "about") {
            event.reply(
                "This is an open source bot. Please visit:\n "
                "https://github.com/nyc-discord/nyc-bot/tree/main to "
                "view the code and contribute!");
        }
    });

    std::cout << "About command listener executed\n";
}

void
About::initialize_command()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->global_command_create(dpp::slashcommand("about", "About this bot!", bot->me.id));
}
