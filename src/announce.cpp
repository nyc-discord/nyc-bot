//
// Created by ariel on 5/27/23.
//

#include "slash-commands/announce.h"

const std::string COMMAND_NAME = "announce";
const std::string COMMAND_DESCRIPTION = "Announcement command";

void
Announce::execute()
{
    auto bot = this->bot_instance->bot_cluster.get();
    bot->on_slashcommand( [ &bot, this ]( const dpp::slashcommand_t& event ) {
        /* Check for our /dialog command */
        if ( event.command.get_command_name() == COMMAND_NAME ) {
            auto roles = event.command.member.roles;
            dpp::snowflake admin_role( 735306184860368967 );
            bool user_has_permission = false;

            for ( auto const& role : roles ) {
                if ( role == admin_role ) {
                    user_has_permission = true;
                    break;
                }
            }

            if ( !user_has_permission ) {
                return;
            }

            /* Instantiate an interaction_modal_response object */
            dpp::interaction_modal_response modal( "my_modal", "Fill out announcement form" );
            /* Add a text component */

            modal.add_component( dpp::component()
                                     .set_label( "Channel ID " )
                                     .set_id( "announcement_channel" )
                                     .set_type( dpp::cot_text )
                                     .set_placeholder( "Channel ID" )
                                     .set_min_length( 5 )
                                     .set_max_length( 50 )
                                     .set_text_style( dpp::text_short ) );
            modal.add_row();

            modal.add_component( dpp::component()
                                     .set_label( "Embed Color hex code" )
                                     .set_id( "embed_color" )
                                     .set_type( dpp::cot_text )
                                     .set_placeholder( "0xFF0000" )
                                     .set_min_length( 6 )
                                     .set_max_length( 6 )
                                     .set_text_style( dpp::text_short ) );
            modal.add_row();

            modal.add_component( dpp::component()
                                     .set_label( "Title" )
                                     .set_id( "announcement_title" )
                                     .set_type( dpp::cot_text )
                                     .set_placeholder( "Title" )
                                     .set_min_length( 5 )
                                     .set_max_length( 50 )
                                     .set_text_style( dpp::text_short ) );
            /* Add another text component in the next row, as required by Discord */
            modal.add_row();
            modal.add_component( dpp::component()
                                     .set_label( "Body" )
                                     .set_id( "announcement_body" )
                                     .set_type( dpp::cot_text )
                                     .set_placeholder( "Announcement Body" )
                                     .set_min_length( 1 )
                                     .set_max_length( 2000 )
                                     .set_text_style( dpp::text_paragraph ) );
            /* Trigger the dialog box. All dialog boxes are ephemeral */
            event.dialog( modal );
        }
    } );

    /* This event handles form submission for the modal dialog we create above */
    bot->on_form_submit( [ bot ]( const dpp::form_submit_t& event ) {
        /* For this simple example we know the first element of the first row ([0][0]) is value type string.
         * In the real world it may not be safe to make such assumptions!
         */
        std::string channel_id = std::get<std::string>( event.components[ 0 ].components[ 0 ].value );
        std::string hex_string = std::get<std::string>( event.components[ 1 ].components[ 0 ].value );
        uint32_t hex_color = std::stoul( hex_string, nullptr, 16 );
        std::string title = std::get<std::string>( event.components[ 2 ].components[ 0 ].value );
        std::string body_text = std::get<std::string>( event.components[ 3 ].components[ 0 ].value );

        dpp::message m;
        m.set_channel_id( channel_id );
        m.set_content( "Testing Announcements " + body_text ).set_flags( dpp::m_ephemeral );
        /* Emit a reply. Form submission is still an interaction and must generate some form of reply! */
        event.reply( m );

        // create the announcement embed
        dpp::embed embed = dpp::embed().set_color( hex_color ).set_title( title ).set_description( body_text );

        /* reply with the created embed */
        bot->message_create( dpp::message( channel_id, embed ).set_reference( event.custom_id ) );
    } );

    std::cout << "Announce command listener executed\n";
}

Announce::Announce( const std::string& command_name, const std::string& command_description )
    : SlashCommandRegistrar( command_name, command_description )
{
    command_registry().push_back( this );
}

REGISTER_COMMAND( Announce, COMMAND_NAME, COMMAND_DESCRIPTION );
