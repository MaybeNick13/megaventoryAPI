#include <iostream>
#include "MegaventoryAPI.h"

int main() {
    try {
        std::string apiKey = "ec6d31f54d7b2a2c@m150644"; 
        MegaventoryAPI megaventory(apiKey);

        // Product 1
        Product product1;
        product1.SKU = "1112223";
        product1.description = "Puma sneakers";
        product1.salesPrice = 79.99;
        product1.purchasePrice = 35.99;

        // Product 2
        Product product2;
        product2.SKU = "1112299";
        product2.description = "New Balance sneakers";
        product2.salesPrice = 89.99;
        product2.purchasePrice = 39.99;

        // Client
        Contact client;
        client.name = "Achilles";
        client.email = "achilles@exampletest.com";
        client.shippingAddress = "Example 5, Athens";
        client.phone = "9876543210";
        client.type = "client";

        // Supplier
        Contact supplier;
        supplier.name = "Helen";
        supplier.email = "helen@exampletest.com";
        supplier.shippingAddress = "Example 6, Athens";
        supplier.phone = "9876543233";
        supplier.type = "supplier";

        // Inventory Location
        Inventory inventory;
        inventory.abbreviation = "Demo";
        inventory.name = "Demo Project Location";
        inventory.address = "Example 25, Athens";

        // Purchase Order
        Order Purchase;
        Purchase.status = "Pending";
        Purchase.product = product2;
        Purchase.quantity = 20;
        Purchase.contact = supplier;

         // Sales Order
        Order Sales;
        Sales.status = "Verified";
        Sales.product = product1;
        Sales.quantity = 10;
        Sales.contact = client;


        // Update Product
        megaventory.updateProduct(product1,"Insert");  // Assuming the default action is Update if not specified
        std::cout << "Updated Product 1: Puma sneakers" << std::endl;

        megaventory.updateProduct(product2,"Insert");  // Assuming the default action is Update if not specified
        std::cout << "Updated Product 2: New Balance sneakers" << std::endl;

        // Update Client and Supplier with specific actions
        megaventory.updateContact(client, "Insert");  // Action and source application specified
        std::cout << "Updated Client: Achilles" << std::endl;

        megaventory.updateContact(supplier, "Insert");  // Action and source application specified
        std::cout << "Updated Supplier: Helen" << std::endl;

        // Update Inventory with specific action
        megaventory.updateInventory(inventory, "Insert");  // Action and source application specified
        std::cout << "Updated Inventory Location: Demo Project Location" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
