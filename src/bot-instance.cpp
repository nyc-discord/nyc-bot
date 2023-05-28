//
// Created by ariel on 5/27/23.
//

#include "bot-instance.h"

BotInstance&
BotInstance::get_instance()
{
    static BotInstance instance;
    return instance;
}

void
BotInstance::start_bot() const
{
    this->bot_cluster->start( dpp::st_wait );
}

BotInstance::BotInstance()
{
    std::cout << "Initializing Bot" << std::endl;
    bot_cluster =
        std::make_unique<dpp::cluster>( std::getenv( "token" ), dpp::i_default_intents | dpp::i_message_content );
}
