#ifndef CLASSES_H
#define CLASSES_H

#include <string>

struct Contact {
    std::string Name;
    std::string Email;
    std::string ShippingAddress;
    std::string Phone;
};

struct Supplier : public Contact {
};

struct Client : public Contact {
};

struct Product {
    std::string SKU;
    std::string Description;
    double SalesPrice;
    double PurchasePrice;
};

struct InventoryLocation {
    std::string Abbreviation;
    std::string Name;
    std::string Address;
};

#endif // CLASSES_H
