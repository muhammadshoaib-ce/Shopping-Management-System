#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to print a star border.
void printStarBorder() {
    cout << string(50, '*') << endl;
}

// Function to display a checkout receipt.
void displayCheckoutReceipt(string products[], int cartCount, int cart[][3], int prices[]) {
    cout << "Checkout Receipt:" << endl;
    for (int i = 0; i < cartCount; i++) {
        cout << products[cart[i][0]] << " " << cart[i][2] << " x $" << cart[i][1]
            << " = $" << cart[i][1] * cart[i][2] << endl;
    }
}

// Function to display all available products.
void displayProducts(string products[], int productCount) {
    cout << "Available products:" << endl;
    for (int i = 0; i < productCount; i++) {
        cout << i + 1 << ". " << products[i] << endl;
    }
}

// Function to calculate the total price of the cart.
double calculateTotalPrice(int cartCount, int cart[][3], int prices[]) {
    double totalPrice = 0;
    for (int i = 0; i < cartCount; i++) {
        totalPrice += cart[i][1] * cart[i][2];
    }
    return totalPrice;
}

// Function to apply discounts on the total price.
double applyDiscounts(double totalPrice, double discounts[], int discountCount) {
    double discountedPrice = totalPrice;
    if (discountCount > 0) {
        cout << "discount: 15%" << endl;
        discountedPrice -= 0.15 * totalPrice;
    }
    return discountedPrice;
}

// Function to add a product to the cart.
void addToCart(string products[], int productCount, string product, int stock[], int& cartCount, int cart[][3], int prices[]) {
    bool found = false;
    for (int i = 0; i < productCount; i++) {
        if (products[i] == product) {
            found = true;
            cout << "Enter the number of units: ";
            int units;
            cin >> units;
            if (units > 0) {
                if (stock[i] >= units) {
                    cart[cartCount][0] = i;
                    cart[cartCount][1] = prices[i];
                    cart[cartCount][2] = units;
                    stock[i] -= units;
                    cartCount++;
                    cout << "Product '" << product << "' added to cart." << endl;
                }
                else {
                    cout << "Insufficient stock for product '" << product << "'." << endl;
                }
            }
            else {
                cout << "Invalid input. Please enter a positive number." << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << "Product '" << product << "' not found in the store." << endl;
    }
}

// Function to remove a product from the cart.
void removeFromCart(string products[], string name, int productCount, int& cartCount, int cart[][3], int stock[]) {
    bool found = false;
    for (int i = 0; i < cartCount; i++) {
        if (products[cart[i][0]] == name) {
            found = true;
            stock[cart[i][0]] += cart[i][2];
            cartCount--;
            for (int j = i; j < cartCount; j++) {
                cart[j][0] = cart[j + 1][0];
                cart[j][1] = cart[j + 1][1];
                cart[j][2] = cart[j + 1][2];
            }
            cout << "Product '" << name << "' removed from cart." << endl;
            break;
        }
    }
    if (!found) {
        cout << "The product '" << name << "' is not in the cart." << endl;
    }
}

// Function to view available stock.
void viewStock(string products[], int productCount, int stock[]) {
    cout << "Available stock:" << endl;
    for (int i = 0; i < productCount; i++) {
        cout << i + 1 << ". " << products[i] << ": " << stock[i] << endl;
    }
}

// Function to add stock for a product.
void addStock(string products[], int productCount, int stock[], string name, int units) {
    if (units > 0) {
        for (int i = 0; i < productCount; i++) {
            if (products[i] == name) {
                stock[i] += units;
                cout << "Stock updated successfully!" << endl;
                return;
            }
        }
        cout << "Product not found." << endl;
    }
    else {
        cout << "Invalid units." << endl;
    }
}

// Function to add a new product.
void addProduct(string products[], int& productCount, string name, int prices[], int price) {
    if (productCount >= 100) {
        cout << "Maximum number of products reached!" << endl;
        return;
    }
    products[productCount] = name;
    prices[productCount] = price;
    productCount++;
    cout << "Product added successfully!" << endl;
}

// Function to remove a product.
void removeProduct(string products[], int& productCount, string name, int prices[]) {
    int index = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i] == name) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Product not found!" << endl;
        return;
    }
    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
        prices[i] = prices[i + 1];
    }
    productCount--;
    cout << "Product removed successfully!" << endl;
}

// Function to search for a product.
void searchProduct(string products[], int productCount, string name) {
    for (int i = 0; i < productCount; i++) {
        if (products[i] == name) {
            cout << "Product found!" << endl;
            return;
        }
    }
    cout << "Product not found!" << endl;
}

int main() {
    int productCount = 0;
    string products[100];
    int prices[100] = { 0 };
    int stock[100] = { 0 };

    // Load products from file.
    ifstream file("products.txt");
    if (file.is_open()) {
        while (file >> products[productCount] >> prices[productCount] >> stock[productCount]) {
            productCount++;
        }
        file.close();
    }

    int cartCount = 0;
    int cart[100][3] = { 0 }; // cart[i][0]: product index, cart[i][1]: price, cart[i][2]: quantity
    double discounts[] = { 0.15 };

    bool exit = false;
    do {
        int choice;
        printStarBorder();
        cout << "\tSHOPPING MANAGEMENT SYSTEM\n";
        printStarBorder();

        cout << "\nPRODUCT MANAGEMENT\n";
        cout << "------------------------------\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Search Product\n";
        cout << "4. View Stock\n";
        cout << "5. Add Stock\n";

        cout << "\nORDER PROCESSING\n";
        cout << "------------------------------\n";
        cout << "6. Add to Cart\n";
        cout << "7. Remove from Cart\n";
        cout << "8. View Cart\n";
        cout << "9. Checkout\n";

        cout << "------------------------------\n";
        cout << "10. Exit\n";

        printStarBorder();
        cout << "Enter your choice: ";

        cout << "Please enter your choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
        case 1: {
            cout << "Enter product name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            cout << "Enter product price: ";
            int price;
            cin >> price;
            addProduct(products, productCount, name, prices, price);
            break;
        }
        case 2: {
            cout << "Enter product name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            removeProduct(products, productCount, name, prices);
            break;
        }
        case 3: {
            cout << "Enter product name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            searchProduct(products, productCount, name);
            break;
        }
        case 4:
            viewStock(products, productCount, stock);
            break;
        case 5: {
            cout << "Enter product name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            cout << "Enter units to add: ";
            int units;
            cin >> units;
            addStock(products, productCount, stock, name, units);
            break;
        }
        case 6: {
            displayProducts(products, productCount);
            cout << "Enter product name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            addToCart(products, productCount, name, stock, cartCount, cart, prices);
            break;
        }
        case 7: {
            cout << "Enter product name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            removeFromCart(products, name, productCount, cartCount, cart, stock);
            break;
        }
        case 8: {
            cout << "Products in cart:" << endl;
            for (int i = 0; i < cartCount; i++) {
                cout << products[cart[i][0]] << " x " << cart[i][2] << " = $" << cart[i][1] * cart[i][2] << endl;
            }
            break;
        }
        case 9: {
            displayCheckoutReceipt(products, cartCount, cart, prices);
            double totalPrice = calculateTotalPrice(cartCount, cart, prices);
            double discountedPrice = applyDiscounts(totalPrice, discounts, 1);
            cout << "Total price after discount: $" << discountedPrice << endl;
            break;
        }
        case 10:
            cout << "\n=====================================\n";
            cout << "Thank you for using Shopping Management System\n";
            cout << "Developed by Muhammad Shoaib\n";
            cout << "=====================================\n";
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (!exit);

    // Save updated products to file.
    ofstream outfile("products.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < productCount; i++) {
            outfile << products[i] << " " << prices[i] << " " << stock[i] << endl;
        }
        outfile.close();
    }

    return 0;
}
