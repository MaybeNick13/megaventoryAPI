#include "MegaventoryAPI.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Classes.h"

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

void MegaventoryAPI::updateProduct(const Product& product) {
    json j;
    j["APIKEY"] = apiKey;
    j["mvProduct"] = {
        {"ProductSKU", product.SKU},
        {"ProductDescription", product.description},
        {"ProductSellingPrice", product.salesPrice},
        {"ProductPurchasePrice", product.purchasePrice}
    };

    std::string payload = j.dump();

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.megaventory.com/v2017a/Product/ProductUpdate");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        std::cout << "Response: " << response << std::endl;
    }
}

void MegaventoryAPI::updateContact(const Contact& contact) {
    json j;
    j["APIKEY"] = apiKey;
    j["mvSupplierClient"] = {
        {"SupplierClientName", contact.name},
        {"SupplierClientEmail", contact.email},
        {"SupplierClientShippingAddress1", contact.shippingAddress},
        {"SupplierClientPhone1", contact.phone}
    };

    std::string payload = j.dump();

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.megaventory.com/v2017a/SupplierClient/SupplierClientUpdate");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        std::cout << "Response: " << response << std::endl;
    }
}

void MegaventoryAPI::updateInventory(const Inventory& inventory) {
    json j;
    j["APIKEY"] = apiKey;
    j["mvInventoryLocation"] = {
        {"InventoryLocationAbbreviation", inventory.abbreviation},
        {"InventoryLocationName", inventory.name},
        {"InventoryLocationAddress", inventory.address}
    };

    std::string payload = j.dump();

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.megaventory.com/v2017a/InventoryLocation/InventoryLocationUpdate");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        std::cout << "Response: " << response << std::endl;
    }
}
