#ifndef MEGAVENTORYAPI_H
#define MEGAVENTORYAPI_H

#include "Classes.h"
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>

class MegaventoryAPI {
private:
    std::string apiKey;
    CURL *curl;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

public:
    MegaventoryAPI(const std::string& key);
    ~MegaventoryAPI();
    void updateProduct(const Product& product);
    void updateContact(const Contact& Contact);
    void updateInventory(const Inventory& inventory);
    void createPurchaseOrder(const Product& product, const Supplier& supplier, int quantity);
    void createSalesOrder(const Product& product, const Client& client, int quantity);
    void updateInventory(const std::string& productSKU, int quantity);
};

#endif // MEGAVENTORYAPI_H