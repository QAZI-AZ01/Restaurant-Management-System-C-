#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <limits> // For std::numeric_limits
#include <cstdlib> // For system("cls") or system("clear")
#include <conio.h> // For _getch() on Windows

using namespace std;

// Global variables
map<string, int> foodInventory;       // Stores food items and their stock
map<string, double> foodPrices;       // Stores food items and their prices
map<string, int> itemsSold;           // Tracks how many times each item was sold
vector<string> employees;             // Stores employee names
vector<double> sales;                 // Stores all sales records

const string ADMIN_PASSWORD = "0000"; // Admin password

// Function prototypes
void clearScreen();
string getPassword();
void displayMenu();
void customerSide();
void adminPanel();
void addFoodItem();
void updateFoodStock();
void viewFoodStock();
void addEmployee();
void viewEmployees();
void viewSalesTrends();
void viewItemsSold();

int main() {
    int choice;
    do {
        clearScreen();
        cout << "===== Restaurant Management System =====" << endl;
        cout << "1. Customer Side" << endl;
        cout << "2. Admin Panel" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                customerSide();
                break;
            case 2: {
                clearScreen();
                string password = getPassword();
                if (password == ADMIN_PASSWORD) {
                    clearScreen();
                    adminPanel();
                } else {
                    cout << "Incorrect password. Access denied." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    cin.get(); // Wait for user to press Enter
                }
                break;
            }
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
        }
    } while (choice != 3);

    return 0;
}

// Clear the terminal screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/Mac
#endif
}

// Get password with masking
string getPassword() {
    string password;
    char ch;
    cout << "Enter admin password: ";
    while ((ch = _getch()) != '\r') { // Use _getch() for Windows
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                password.erase(password.size() - 1); // Remove the last character
                cout << "\b \b"; // Move cursor back, overwrite with space, move back again
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl; // Move to the next line after password input
    return password;
}

// Display the restaurant menu
void displayMenu() {
    cout << "===== Restaurant Menu =====" << endl;
    for (map<string, double>::iterator it = foodPrices.begin(); it != foodPrices.end(); ++it) {
        cout << it->first << " - $" << fixed << setprecision(2) << it->second << " (Stock: " << foodInventory[it->first] << ")" << endl;
    }
    cout << "==========================" << endl;
}

// Customer side functionality
void customerSide() {
    int choice;
    double totalBill = 0.0;
    do {
        clearScreen();
        cout << "===== Customer Side =====" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. Place Order" << endl;
        cout << "3. Exit and Show Bill" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                displayMenu();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 2: {
                clearScreen();
                string item;
                int quantity;
                cout << "Enter the food item you want to order: ";
                cin >> item;
                cout << "Enter the quantity: ";
                cin >> quantity;

                // Check if the item exists in the inventory
                map<string, int>::iterator it = foodInventory.find(item);
                if (it != foodInventory.end() && it->second >= quantity) {
                    double total = foodPrices[item] * quantity;
                    totalBill += total;
                    foodInventory[item] -= quantity;
                    itemsSold[item] += quantity; // Track how many times the item was sold
                    sales.push_back(total);      // Record the sale
                    cout << "Added to your order: " << item << " x " << quantity << " = $" << fixed << setprecision(2) << total << endl;
                } else {
                    cout << "Item not available or insufficient stock." << endl;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            }
            case 3:
                clearScreen();
                cout << "===== Final Bill =====" << endl;
                cout << "Total Amount: $" << fixed << setprecision(2) << totalBill << endl;
                cout << "Thank you for visiting!" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 4:
                cout << "Returning to main menu..." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
        }
    } while (choice != 3 && choice != 4);
}

// Admin panel functionality
void adminPanel() {
    int choice;
    do {
        clearScreen();
        cout << "===== Admin Panel =====" << endl;
        cout << "1. Add Food Item" << endl;
        cout << "2. Update Food Stock" << endl;
        cout << "3. View Food Stock" << endl;
        cout << "4. Add Employee" << endl;
        cout << "5. View Employees" << endl;
        cout << "6. View Sales Trends" << endl;
        cout << "7. View Items Sold" << endl;
        cout << "8. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                addFoodItem();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 2:
                clearScreen();
                updateFoodStock();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 3:
                clearScreen();
                viewFoodStock();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 4:
                clearScreen();
                addEmployee();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 5:
                clearScreen();
                viewEmployees();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 6:
                clearScreen();
                viewSalesTrends();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 7:
                clearScreen();
                viewItemsSold();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            case 8:
                cout << "Returning to main menu..." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
        }
    } while (choice != 8);
}

// Add a new food item
void addFoodItem() {
    string item;
    double price;
    int stock;
    cout << "Enter the food item name: ";
    cin >> item;
    cout << "Enter the price: ";
    cin >> price;
    cout << "Enter the initial stock: ";
    cin >> stock;
    foodPrices[item] = price;
    foodInventory[item] = stock;
    cout << "Food item added successfully!" << endl;
}

// Update food stock
void updateFoodStock() {
    string item;
    int stock;
    cout << "Enter the food item name: ";
    cin >> item;
    cout << "Enter the new stock: ";
    cin >> stock;

    // Check if the item exists in the inventory
    map<string, int>::iterator it = foodInventory.find(item);
    if (it != foodInventory.end()) {
        foodInventory[item] = stock;
        cout << "Stock updated successfully!" << endl;
    } else {
        cout << "Item not found." << endl;
    }
}

// View current food stock
void viewFoodStock() {
    cout << "===== Food Stock =====" << endl;
    for (map<string, int>::iterator it = foodInventory.begin(); it != foodInventory.end(); ++it) {
        cout << it->first << " - " << it->second << " units" << endl;
    }
    cout << "======================" << endl;
}

// Add an employee
void addEmployee() {
    string name;
    cout << "Enter the employee name: ";
    cin >> name;
    employees.push_back(name);
    cout << "Employee added successfully!" << endl;
}

// View all employees
void viewEmployees() {
    cout << "===== Employees =====" << endl;
    for (size_t i = 0; i < employees.size(); i++) {
        cout << employees[i] << endl;
    }
    cout << "=====================" << endl;
}

// View sales trends
void viewSalesTrends() {
    cout << "===== Sales Trends =====" << endl;
    double totalSales = 0.0;
    for (size_t i = 0; i < sales.size(); i++) {
        cout << "Sale " << i + 1 << ": $" << fixed << setprecision(2) << sales[i] << endl;
        totalSales += sales[i];
    }
    cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    cout << "========================" << endl;
}

// View how many times each item was sold
void viewItemsSold() {
    cout << "===== Items Sold =====" << endl;
    for (map<string, int>::iterator it = itemsSold.begin(); it != itemsSold.end(); ++it) {
        cout << it->first << " - " << it->second << " times" << endl;
    }
    cout << "======================" << endl;
}
