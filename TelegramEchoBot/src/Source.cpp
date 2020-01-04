#include <cstdio>
#include <tgbot/tgbot.h>

int main() {
	TgBot::Bot bot("");
	bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Hi!");
		});
	bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
		printf("User wrote %s\n", message->text.c_str());
		if (StringTools::startsWith(message->text, "/start")) {
			return;
		}
		
		bot.getApi().sendMessage(message->chat->id, ">>" + message->text, false, 0, std::make_shared<TgBot::InlineKeyboardMarkup>());
		bot.getApi().sendSticker(message->chat->id, "https://github.com/TelegramBots/book/raw/master/src/docs/sticker-fred.webp");
		});
	try {
		printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
		TgBot::TgLongPoll longPoll(bot);
		while (true) {
			printf("Long poll started\n");
			longPoll.start();
		}
	}
	catch (TgBot::TgException & e) {
		printf("error: %s\n", e.what());
	}
	return 0;
}