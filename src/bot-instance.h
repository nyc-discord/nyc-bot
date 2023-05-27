//
// Created by ariel on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_BOT_INSTANCE_H
#define NYC_DISCORD_BOT_BOT_INSTANCE_H

#include "dpp/dpp.h"
#include <memory>

class BotInstance
{
public:
    std::shared_ptr<dpp::cluster> bot_cluster;

    static BotInstance&
    get_instance()
    {
        static BotInstance instance;
        return instance;
    }

    void
    start_bot()
    {
        this->bot_cluster->start(dpp::st_wait);
    }

private:
    BotInstance()
    {
        std::cout << "Initializing Bot" << std::endl;
        bot_cluster
            = std::make_unique<dpp::cluster>(std::getenv("token"), dpp::i_default_intents | dpp::i_message_content);
    };
//    BotInstance(const BotInstance&) = delete;
    void
    operator=(const BotInstance&)
        = delete;
};

#endif // NYC_DISCORD_BOT_BOT_INSTANCE_H
