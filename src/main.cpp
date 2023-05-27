#include "bot-instance.h"
#include "commands.h"
#include <regex>

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

    /// custom code put this in a file
    bot->on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.content == "!select")
        {
            /* Create a message containing an action row, and a select menu within the action row. */
            dpp::message m(event.msg.channel_id, "Which borough are you from?");
            m.add_component(dpp::component().add_component(
                dpp::component()
                    .set_type(dpp::cot_selectmenu)
                    .set_placeholder("Pick a borough")
                    .add_select_option(dpp::select_option("Bronx", "bronx", "Land of rats").set_emoji("🐀"))
                    .add_select_option(dpp::select_option("Manhattan", "manhattan", "Best Borough").set_emoji("🤑"))
                    .add_select_option(dpp::select_option("Queens", "queens", "Who even lives here").set_emoji("👑"))
                    .add_select_option(
                        dpp::select_option("Brooklyn", "brooklyn", "Better be Williamsburg").set_emoji("☕️"))
                    .add_select_option(dpp::select_option("Staten Island", "statenisland", "Ok fed").set_emoji("🚔"))
                    .set_id("nyc_borough")));
            bot->message_create(m);
        }

        if (event.msg.content.starts_with("!dunce"))
        {
            // check that user is admin
            auto roles = event.msg.member.roles;
            dpp::snowflake admin_role(735306184860368967);
            bool user_has_permission = false;
            for (auto const& role : roles)
            {
                if (role == admin_role)
                {
                    user_has_permission = true;
                    break;
                }
            }

            if (!user_has_permission)
            {
                return;
            }

            std::regex mention_regex("<@!?([0-9]+)>");
            std::smatch matches;
            std::string content = event.msg.content;
            dpp::snowflake dunce_role_id("1112075408381325374");

            while (std::regex_search(content, matches, mention_regex))
            {
                dpp::snowflake user_id = std::stoull(matches[1].str());

                bot->guild_get_member(event.msg.guild_id, user_id, [&](auto data) {
                    const dpp::guild_member& member = data.template get<dpp::guild_member>();
                    bool has_dunce_role = false;
                    for (const auto& role : member.roles)
                    {
                        if (role == dunce_role_id)
                        {
                            has_dunce_role = true;
                            break;
                        }
                    }

                    if (has_dunce_role)
                    {
                        bot->guild_member_remove_role(event.msg.guild_id, user_id, dunce_role_id);
                    }
                    else
                    {
                        bot->guild_member_add_role(event.msg.guild_id, user_id, dunce_role_id);
                    }
                });

                content = matches.suffix().str();
            }
            std::cout << event.msg.content << std::endl;
        }
    });
    /* When a user clicks your select menu , the on_select_click event will fire,
     * containing the custom_id you defined in your select menu.
     */
    bot->on_select_click([&bot](const dpp::select_click_t& event) {
        /* Select clicks are still interactions, and must be replied to in some form to
         * prevent the "this interaction has failed" message from Discord to the user.
         */
        event.reply("You clicked " + event.custom_id + " and chose: " + event.values[0]);
    });

    /// end custom code

    bot->on_log(dpp::utility::cout_logger());
    bot_instance.start_bot();

    return 0;
}
