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
    get_instance();

    void
    start_bot() const;

private:
    BotInstance();
    //    BotInstance(const BotInstance&) = delete;
    void
    operator=(const BotInstance&) = delete;
};

#endif // NYC_DISCORD_BOT_BOT_INSTANCE_H
