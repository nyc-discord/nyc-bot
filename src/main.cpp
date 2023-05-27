#include "bot-instance.h"
#include "commands.h"

int
main()
{
    auto bot_instance = BotInstance::get_instance();
    auto bot = bot_instance.bot_cluster.get();

    bot->on_ready([&bot](auto event) {
        if (dpp::run_once<struct register_bot_commands>())
        {
            for (auto command : command_registry())
            {
                command->execute();
                command->initialize_command();
            }
        }
    });

    bot->on_log(dpp::utility::cout_logger());
    bot_instance.start_bot();

    return 0;
}
