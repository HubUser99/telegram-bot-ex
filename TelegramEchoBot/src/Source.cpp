#include <cstdio>
#include <string>

#include <tgbot/tgbot.h>

int main()
{
	TgBot::Bot bot("<YOUR_TELEGRAM_BOT_TOKEN_HERE>");
	bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
	{
		bot.getApi().sendMessage(message->chat->id, "Hi!");
	});
	bot.getEvents().onCommand("dick", [&bot](TgBot::Message::Ptr message)
	{
		const float randomSize = static_cast<float>(rand() % 21) + (static_cast<float>(rand() % 10 + 1) / 10.0f);
		char randomSizeCharArray[20];
		sprintf_s(randomSizeCharArray, "%.1f", randomSize);
		const std::string randomSizeString = randomSizeCharArray;
		bot.getApi().sendMessage(message->chat->id, "Your dick is " + randomSizeString + "cm");
	});

	bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message)
	{
		printf("User wrote %s\n", message->text.c_str());
		if (StringTools::startsWith(message->text, "/start"))
		{
			return;
		}
		if (StringTools::startsWith(message->text, "/dick"))
		{
			return;
		}
		bot.getApi().sendMessage(message->chat->id, ">>" + message->text, false, 0,
		                         std::make_shared<TgBot::InlineKeyboardMarkup>());
		bot.getApi().sendSticker(message->chat->id,
		                         "https://raw.githubusercontent.com/HubUser99/telegram-bot-ex/master/TelegramEchoBot/stickers/scuffed_brain.webp");
	});
	try
	{
		printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
		TgBot::TgLongPoll longPoll(bot);
		while (true)
		{
			printf("Long poll started\n");
			longPoll.start();
		}
	}
	catch (TgBot::TgException& e)
	{
		printf("error: %s\n", e.what());
	}
	return 0;
}
