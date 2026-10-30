
# C++ Telegram Bot

A Telegram bot written in C++.

## Requirements

- C++ compiler
- libcurl
- nlohmann-json

On Arch Linux:

```bash
sudo pacman -S --needed base-devel curl nlohmann-json

export BOT_TOKEN="YOUR_BOT_TOKEN_HERE"
g++ -std=c++17 bot.cpp -o bot $(pkg-config --cflags --libs libcurl)

./bot