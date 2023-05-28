//
// Created by ariel on 5/27/23.
//

#include "slash-commands/about.h"

const std::string COMMAND_NAME = "announce";
const std::string COMMAND_DESCRIPTION = "Announcement command";

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

About::About(const std::string& command_name, const std::string& command_description)
    : SlashCommandRegistrar(command_name, command_description)
{
    command_registry().push_back(this);
}

REGISTER_COMMAND(About, COMMAND_NAME, COMMAND_DESCRIPTION);
