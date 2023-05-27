//
// Created by Ariel Saldana on 5/27/23.
//

#ifndef NYC_DISCORD_BOT_COMMAND_ANNOUNCEMENT_H
#define NYC_DISCORD_BOT_COMMAND_ANNOUNCEMENT_H

#include "bot-instance.h"
#include "command.h"
#include <string>

class Announcement : public Command
{
public:
    Announcement() { command_registry().push_back(this); }
    std::string command_name = "announce";
    std::string command_description = "Announcement command";

    void
    execute() override
    {
        auto bot = this->bot_instance->bot_cluster.get();
        bot->on_slashcommand([&bot, this](const dpp::slashcommand_t& event) {
            /* Check for our /dialog command */
            if (event.command.get_command_name() == this->command_name) {

                auto roles = event.command.member.roles;
                dpp::snowflake admin_role(735306184860368967);
                bool user_has_permission = false;
                for (auto const& role : roles) {
                    if (role == admin_role) {
                        user_has_permission = true;
                        break;
                    }
                }

                if (!user_has_permission) {
                    return;
                }

                /* Instantiate an interaction_modal_response object */
                dpp::interaction_modal_response modal("my_modal", "Fill out announcement form");
                /* Add a text component */

                modal.add_component(dpp::component()
                                        .set_label("Channel ID ")
                                        .set_id("announcement_channel")
                                        .set_type(dpp::cot_text)
                                        .set_placeholder("Channel ID")
                                        .set_min_length(5)
                                        .set_max_length(50)
                                        .set_text_style(dpp::text_short));
                modal.add_row();

                modal.add_component(dpp::component()
                                        .set_label("Title")
                                        .set_id("announcement_title")
                                        .set_type(dpp::cot_text)
                                        .set_placeholder("Title")
                                        .set_min_length(5)
                                        .set_max_length(50)
                                        .set_text_style(dpp::text_short));
                /* Add another text component in the next row, as required by Discord */
                modal.add_row();
                modal.add_component(dpp::component()
                                        .set_label("Body")
                                        .set_id("announcement_body")
                                        .set_type(dpp::cot_text)
                                        .set_placeholder("Announcement Body")
                                        .set_min_length(1)
                                        .set_max_length(2000)
                                        .set_text_style(dpp::text_paragraph));
                /* Trigger the dialog box. All dialog boxes are ephemeral */
                event.dialog(modal);
            }
        });

        /* This event handles form submission for the modal dialog we create above */
        bot->on_form_submit([bot](const dpp::form_submit_t& event) {
            /* For this simple example we know the first element of the first row ([0][0]) is value type string.
             * In the real world it may not be safe to make such assumptions!
             */
            std::string channel_id = std::get<std::string>(event.components[0].components[0].value);
            std::string title = std::get<std::string>(event.components[1].components[0].value);
            std::string body_text = std::get<std::string>(event.components[2].components[0].value);

            dpp::message m;
            m.set_channel_id(channel_id);
            m.set_content("Testing Announcements " + body_text).set_flags(dpp::m_ephemeral);
            /* Emit a reply. Form submission is still an interaction and must generate some form of reply! */
            event.reply(m);

            // create the announcement embed
            dpp::embed embed
                = dpp::embed().set_color(dpp::colors::sti_blue).set_title(title).set_description(body_text);

            /* reply with the created embed */
            bot->message_create(dpp::message(channel_id, embed).set_reference(event.custom_id));
        });

        std::cout << "Announcement command listener executed\n";
    }

    void
    initialize_command() override
    {
        auto bot = this->bot_instance->bot_cluster.get();
        bot->global_command_create(dpp::slashcommand(this->command_name, this->command_description, bot->me.id));
    }
};

REGISTER_COMMAND(Announcement);

#endif // NYC_DISCORD_BOT_COMMAND_ANNOUNCEMENT_H
