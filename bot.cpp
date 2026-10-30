#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

size_t write_data(void* p, size_t s, size_t n, string* out) {
    out->append(static_cast<char*>(p), s * n);
    return s * n;
}

string request(const string& url) {
    CURL* c = curl_easy_init();
    string out;
    if (!c) return out;
    curl_easy_setopt(c, CURLOPT_URL, url.c_str());
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(c, CURLOPT_WRITEDATA, &out);
    curl_easy_setopt(c, CURLOPT_TIMEOUT, 40L);
    curl_easy_perform(c);
    curl_easy_cleanup(c);
    return out;
}

string encode(const string& s) {
    CURL* c = curl_easy_init();
    if (!c) return "";
    char* p = curl_easy_escape(c, s.c_str(), s.size());
    string out = p ? p : "";
    if (p) curl_free(p);
    curl_easy_cleanup(c);
    return out;
}

int main() {
    const char* t = getenv("BOT_TOKEN");
    if (!t) return 1;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    string base = string("https://api.telegram.org/bot") + t + "/";
    long long offset = 0;

    while (true) {
        try {
            json data = json::parse(request(
                base + "getUpdates?timeout=25&offset=" + to_string(offset)
            ));
            for (auto& u : data["result"]) {
                offset = u["update_id"].get<long long>() + 1;
                if (!u.contains("message")) continue;
                auto m = u["message"];
                if (!m.contains("text")) continue;
                auto id = m["chat"]["id"].get<long long>();
                string text = m["text"].get<string>();
                request(base + "sendMessage?chat_id=" + to_string(id) +
                    "&text=" + encode(text));
            }
        } catch (...) {
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}
