#include "MegaventoryAPI.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Classes.h"

using json = nlohmann::json;


MegaventoryAPI::MegaventoryAPI(const std::string& key) : apiKey(key) {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    purchaseOrdersNo = 0;
    SaleOrdersNo = 0;
}

MegaventoryAPI::~MegaventoryAPI() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

size_t MegaventoryAPI::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void MegaventoryAPI::performRequest(const std::string& url, const std::string& payload, std::string& response) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        throw std::runtime_error("Request failed: " + std::string(curl_easy_strerror(res)));
    }
}

std::string MegaventoryAPI::prepareProductPayload(const Product& product,const std::string& action, const std::string& sourceApplication = "") const {
    json j;
    j["APIKEY"] = apiKey;
    j["mvProduct"] = {
        {"ProductSKU", product.SKU},
        {"ProductDescription", product.description},
        {"ProductSellingPrice", product.salesPrice},
        {"ProductPurchasePrice", product.purchasePrice}
    };
    j["mvRecordAction"] = action;
    if (!sourceApplication.empty()) {
        j["mvInsertUpdateDeleteSourceApplication"] = sourceApplication;
    }
    return j.dump();
}

std::string MegaventoryAPI::prepareContactPayload(const Contact& contact, const std::string& action, const std::string& sourceApplication = "") const {
    json j;
    j["APIKEY"] = apiKey;
    j["mvSupplierClient"] = {
        {"SupplierClientType", contact.type},
        {"SupplierClientName", contact.name},
        {"SupplierClientEmail", contact.email},
        {"SupplierClientShippingAddress1", contact.shippingAddress},
        {"SupplierClientPhone1", contact.phone}
    };
    j["mvRecordAction"] = action;
    if (!sourceApplication.empty()) {
        j["mvInsertUpdateDeleteSourceApplication"] = sourceApplication;
    }
    return j.dump();
}


std::string MegaventoryAPI::prepareInventoryPayload(const Inventory& inventory, const std::string& action, const std::string& sourceApplication = "") const {
    json j;
    j["APIKEY"] = apiKey;
    j["mvInventoryLocation"] = {
        {"InventoryLocationName", inventory.name},
        {"InventoryLocationAbbreviation", inventory.abbreviation}
    };
    j["mvRecordAction"] = action;
    if (!sourceApplication.empty()) {
        j["mvInsertUpdateDeleteSourceApplication"] = sourceApplication;
    }
    return j.dump();
}



std::string MegaventoryAPI::preparePurchaseOrderPayload(const Order& order, const std::string& action) const {
    json j;
    j["APIKEY"] = apiKey;
    j["mvPurchaseOrder"] = {
        {"PurchaseOrderSupplierName", order.contact.name},
        {"PurchaseOrderStatus", order.status},
        {"PurchaseOrderID", purchaseOrdersNo},
        {"PurchaseOrderNo", purchaseOrdersNo},
        {"PurchaseOrderDetails", json::array({
            {"PurchaseOrderRowProductSKU", order.product.SKU},
            {"PurchaseOrderRowQuantity", order.quantity}
        })}
    };
    j["mvRecordAction"] = action;
    return j.dump();
}

std::string MegaventoryAPI::prepareSalesOrderPayload(const Order& order, const std::string& action) const {
    json j;
    j["APIKEY"] = apiKey;
    j["mvSalesOrder"] = {
        {"SalesOrderSupplierName", order.contact.name},
        {"SalesOrderID", SaleOrdersNo},
        {"SalesOrderNo", SaleOrdersNo},
        {"SalesOrderStatus", order.status},
        {"SalesOrderDetails", json::array({
            {"SalesOrderRowProductSKU", order.product.SKU},
            {"SalesOrderRowQuantity", order.quantity}
        })}
    };
    j["mvRecordAction"] = action;
    return j.dump();
}


std::string MegaventoryAPI::prepareInventoryStockPayload(const Product& product, int quantity, const Inventory& inventory) const {
    json j;
    j["APIKEY"] = apiKey;
    j["mvProductStockUpdateList"] = json::array({
        {
            {"ProductSKU", product.SKU},
            {"ProductQuantity", quantity},
        }
    });
    return j.dump();
}


void MegaventoryAPI::updateProduct(const Product& product,const std::string& action) {
    std::string payload = prepareProductPayload(product,action);
    std::string response;
    performRequest("https://api.megaventory.com/v2017a/Product/ProductUpdate", payload, response);
    std::cout << "Response: " << response << std::endl;
}

void MegaventoryAPI::updateContact(const Contact& contact,const std::string& action) {
    std::string payload = prepareContactPayload(contact,action);
    std::string response;
    performRequest("https://api.megaventory.com/v2017a/SupplierClient/SupplierClientUpdate", payload, response);
    std::cout << "Response: " << response << std::endl;
}

void MegaventoryAPI::updateInventory(const Inventory& inventory,const std::string& action) {
    std::string payload = prepareInventoryPayload(inventory,action);
    std::string response;
    performRequest("https://api.megaventory.com/v2017a/InventoryLocation/InventoryLocationUpdate", payload, response);
    std::cout << "Response: " << response << std::endl;
}

void MegaventoryAPI::createPurchaseOrder(const Order& order,const std::string& action) {
    std::string payload = preparePurchaseOrderPayload(order,action);
    std::string response;
    performRequest("https://api.megaventory.com/v2017a/PurchaseOrder/PurchaseOrderUpdate", payload, response);
    std::cout << "Response: " << response << std::endl;
}

void MegaventoryAPI::createSalesOrder(const Order& order,const std::string& action) {
    std::string payload = prepareSalesOrderPayload(order,action);
    std::string response;
    performRequest("https://api.megaventory.com/v2017a/SalesOrder/SalesOrderUpdate", payload, response);
    std::cout << "Response: " << response << std::endl;
}

void MegaventoryAPI::updateInventoryStock(const Product& product, int quantity, const Inventory& inventory) {
    std::string payload = prepareInventoryStockPayload(product, quantity, inventory);
    std::string response;
    performRequest("https://api.megaventory.com/v2017a/InventoryLocationStock/ProductStockUpdate", payload, response);
    std::cout << "Response: " << response << std::endl;
}
