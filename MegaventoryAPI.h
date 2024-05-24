#ifndef MEGAVENTORYAPI_H
#define MEGAVENTORYAPI_H

#include "Classes.h"
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>

class MegaventoryAPI {
private:
    std::string apiKey;
    double purchaseOrdersNo;
    double SaleOrdersNo;
    CURL *curl;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    void performRequest(const std::string& url, const std::string& payload, std::string& response);
    std::string prepareProductPayload(const Product& product, const std::string& action, const std::string& sourceApplication) const;
    std::string prepareContactPayload(const Contact& contact, const std::string& action, const std::string& sourceApplication) const;
    std::string prepareInventoryPayload(const Inventory& inventory, const std::string& action, const std::string& sourceApplication) const;
    std::string preparePurchaseOrderPayload(const Order& order, const std::string& action) const;
    std::string prepareSalesOrderPayload(const Order& order, const std::string& action) const;
    std::string prepareInventoryStockPayload(const Product& product, int quantity, const Inventory& inventory) const;
public:
    MegaventoryAPI(const std::string& key);
    ~MegaventoryAPI();
    void updateProduct(const Product& product,const std::string& action);
    void updateContact(const Contact& contact,const std::string& action);
    void updateInventory(const Inventory& inventory,const std::string& action);
    void createPurchaseOrder(const Order& order,const std::string& action) ;
    void createSalesOrder(const Order& order,const std::string& action) ;
    void updateInventoryStock(const Product& product, int quantity, const Inventory& inventory);
};

#endif // MEGAVENTORYAPI_H
