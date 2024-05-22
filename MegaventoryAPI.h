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
    std::string updateProduct(const Product& product);
    std::string updateClient(const Client& client);
    std::string updateSupplier(const Supplier& supplier);
    std::string updateInventoryLocation(const InventoryLocation& location);
    std::string createPurchaseOrder(const Product& product, const Supplier& supplier, int quantity);
    std::string createSalesOrder(const Product& product, const Client& client, int quantity);
    std::string updateInventory(const std::string& productSKU, int quantity);
};

#endif // MEGAVENTORYAPI_H