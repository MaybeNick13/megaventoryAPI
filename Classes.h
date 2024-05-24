#ifndef CLASSES_H
#define CLASSES_H

#include <string>

struct Contact {
    std::string name;
    std::string email;
    std::string shippingAddress;
    std::string phone;
};

struct Supplier : public Contact {
};

struct Client : public Contact {
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
    Inventory location;
}

#endif // CLASSES_H
