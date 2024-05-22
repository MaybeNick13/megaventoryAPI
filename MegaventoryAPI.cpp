#include "MegaventoryAPI.h"

using json = nlohmann::json;

MegaventoryAPI::MegaventoryAPI(const std::string& key) : apiKey(key) {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
}

MegaventoryAPI::~MegaventoryAPI() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

size_t MegaventoryAPI::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}