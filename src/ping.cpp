//
// Created by ariel on 5/27/23.
//

#include "slash-commands/ping.h"

const std::string COMMAND_NAME = "Ping";
const std::string COMMAND_DESCRIPTION = "Ping Pong Bing Bong";

void
Ping::execute()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->on_slashcommand( []( auto event ) {
        if ( event.command.get_command_name() == "ping" ) {
            event.reply( "Pong!" );
        }
    } );

    std::cout << "Ping command listener executed\n";
}

Ping::Ping( const std::string& command_name, const std::string& command_description )
    : SlashCommandRegistrar( command_name, command_description )
{
    command_registry().push_back( this );
}

REGISTER_COMMAND( Ping, COMMAND_NAME, COMMAND_DESCRIPTION );
