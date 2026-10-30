Ruby Telegram Bot 🤖

Features

- Responds to Telegram messages
- Uses the Telegram Bot API
- Simple Ruby project structure
- Keeps the bot token in an environment variable

Requirements

- Ruby
- Bundler (optional, for managing dependencies)
- A Telegram bot token from "@BotFather" (https://t.me/BotFather)

Installation

Clone the repository:

git clone <URL>
cd ruby-telegram-bot

Install dependencies if your project has a "Gemfile":

gem install telegram-bot-ruby

bundle install

Configuration

Set your Telegram bot token as an environment variable:

export TELEGRAM_BOT_TOKEN="YOUR_BOT_TOKEN"

Replace "YOUR_BOT_TOKEN" with your actual token.



Run the Bot

Run the command that matches your main Ruby file. For example:

ruby main.rb

Or, if your entry point is named "bot.rb":

ruby bot.rb

Security

- Never publish your Telegram bot token.
- Do not commit ".env" files or other files containing secrets.
- If your token is exposed, revoke it through "@BotFather" (https://t.me/BotFather).

License

Choose a license for your project before distributing it. For example, MIT.
