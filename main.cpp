#include <dpp/dpp.h>
#include <iostream>

class react_collector : public dpp::reaction_collector
{
public:
    /* Collector will run for 20 seconds */
    react_collector(dpp::cluster* cl, dpp::snowflake id)
        : dpp::reaction_collector(cl, 5, id)
    {
    }

    /* On completion just output number of collected reactions to as a message. */
    void
    completed(const std::vector<dpp::collected_reaction>& list) override
    {
        std::cout << owner << std::endl;
        auto channelId = dpp::snowflake("1097992501438201897");
        //        if (!list.empty()) {
        owner->message_create(dpp::message(channelId, "I collected " + std::to_string(list.size()) + " reactions!"));
        //        } else {
        //            owner->message_create(dpp::message("... I got nothin'."));
        //        }
    }
};

int
main()
{
    dpp::cluster bot(std::getenv("token"), dpp::i_default_intents | dpp::i_message_content);

    bot.on_slashcommand([](auto event) {
        if (event.command.get_command_name() == "ping")
        {
            event.reply("Pong!");
        }
    });

    bot.on_slashcommand([](auto event) {
        if (event.command.get_command_name() == "about")
        {
            event.reply("This is a community driven bot, for more information go to the Github Page.");
        }
    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t & event) {
        /* Check which command they ran */
        if (event.command.get_command_name() == "copy") {
            /* Fetch a parameter value from the command parameters */
            std::string text = std::get<std::string>(event.get_parameter("text"));
            auto channel_id = dpp::snowflake(std::get<std::string>(event.get_parameter("channelID")));
            /* Reply to the command. There is an overloaded version of this
            * call that accepts a dpp::message so you can send embeds.
             */
//            event.dialog()
//            event.reply()
//            event.reply(std::string("copy: ") + text, channel_id);
            event.reply(std::string("copy: ") + text);
        }
    });

    bot.on_ready([&bot](auto event) {
        if (dpp::run_once<struct register_bot_commands>())
        {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("about", "About this bot.", bot.me.id));

            dpp::slashcommand copy_command("announce", "Make an announcement on a channel", bot.me.id);
            copy_command.set_type(dpp::ctxm_chat_input);
            copy_command.add_option(
                dpp::command_option(dpp::co_string, "channelID", "The ChannelID", true).
                add_option(dpp::command_option())
            );
            copy_command.add_option(
                dpp::command_option(dpp::co_string, "info", "Announcement Information", true).
                add_option(dpp::command_option())
            );
            bot.global_command_create(copy_command);
        }
    });



    react_collector* r = nullptr;

    bot.on_log(dpp::utility::cout_logger());

    /* Message handler */
    bot.on_message_create([&](const dpp::message_create_t& event) {
        /* If someone sends a message that has the text 'collect reactions!' start a reaction collector */
        if (event.msg.content == "collect reactions!" && r == nullptr)
        {
            /* Create a new reaction collector to collect reactions */
            r = new react_collector(&bot, event.msg.id);
        }
    });

    bot.start(dpp::st_wait);
}
