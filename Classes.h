#ifndef CLASSES_H
#define CLASSES_H

#include <string>

struct Contact {
    std::string name;
    std::string email;
    std::string shippingAddress;
    std::string phone;
    std::string type;
};



struct Product {
    std::string SKU;
    std::string description;
    double salesPrice;
    double purchasePrice;
};

struct Inventory {
    std::string abbreviation;
    std::string name;
    std::string address;
};

struct Order {
    std::string status; 
    Product product;    
    int quantity; 
    Contact contact;
}

struct PurchaseOrder : public Order {
};

struct SalesOrder : public Order {
};
#endif // CLASSES_H
