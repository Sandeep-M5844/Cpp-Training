#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define MAX_ROWS 5 
#define MAX_COLS 5

class InventorySystem {
private:
    struct Item {
        string item_name;
        int item_quantity;
    };

    vector<vector<Item>> inventory;

public:
    InventorySystem() {
        inventory.resize(MAX_ROWS, vector<Item>(MAX_COLS));

        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                inventory[i][j].item_name = "";
                inventory[i][j].item_quantity = 0;
            }
        }
    }

    void addItem(int aisle, int bin, string name, int quantity) {
        if (aisle < 0 || aisle >= MAX_ROWS || bin < 0 || bin >= MAX_COLS) {
            cout << "Invalid location." << endl;
            return;
        }

        if (quantity <= 0) {
            cout << "Quantity must be positive and non-zero" << endl;
            return;
        }

        if (inventory[aisle][bin].item_name == "")
        {
            inventory[aisle][bin].item_name = name;  // this will create new name if not there
        }
        inventory[aisle][bin].item_quantity += quantity;

        cout << "Item " << name << " added at Aisle " << aisle << ", Bin " << bin
            << " with quantity " << inventory[aisle][bin].item_quantity << endl;
    }

    void removeItem(int aisle, int bin, int quantity) {
        if (aisle < 0 || aisle >= MAX_ROWS || bin < 0 || bin >= MAX_COLS) {
            cout << "Invalid location." << endl;
            return;
        }

        if (inventory[aisle][bin].item_quantity < quantity) {
            cout << "Not enough items to remove." << endl;
            return;
        }

        inventory[aisle][bin].item_quantity -= quantity;

        if (inventory[aisle][bin].item_quantity == 0) {
            inventory[aisle][bin].item_name = ""; // removing the name to empty string
        }

        cout << "Removed " << quantity << " items from Aisle " << aisle
            << ", Bin " << bin << endl;
    }

    void checkStock(int aisle, int bin)
    {
        if (aisle < 0 || aisle >= MAX_ROWS || bin < 0 || bin >= MAX_COLS)
        {
            cout << "Invalid  location." << endl;
            return;
        }

        if (inventory[aisle][bin].item_quantity > 0)
        {
            cout << "Stock at Aisle: " << aisle << ", Bin:: " << bin << ": "
                << "item name: " << inventory[aisle][bin].item_name
                << " Quantity - " << inventory[aisle][bin].item_quantity << endl;
        }
        else
        {
            cout << "No items at Aisle " << aisle << " Bin " << bin << endl;
        }
    }

    void displayInventory() {
        cout << "Displaying Inventory:" << endl;
        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                if (inventory[i][j].item_quantity > 0) {
                    cout << "Aisle " << i << ", Bin " << j << ": "
                        << "item_name: " << inventory[i][j].item_name << " - "
                        << "quantity:" << inventory[i][j].item_quantity << endl;
                }
            }
        }
    }

    void lowStockAlert(int threshold) {
        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                if (inventory[i][j].item_quantity > 0 && inventory[i][j].item_quantity < threshold) {
                    cout << "Low stock alert! Aisle " << i << ", Bin " << j << ": "
                        << "item: " << inventory[i][j].item_name << " - " << "quantity: "
                        << inventory[i][j].item_quantity << endl;
                }
            }
        }
    }

    void transferItem(int fromAisle, int fromBin, int toAisle, int toBin, int quantity)
    {
        if (fromAisle < 0 || fromAisle >= MAX_ROWS || fromBin < 0 || fromBin >= MAX_COLS ||
            toAisle < 0 || toAisle >= MAX_ROWS || toBin < 0 || toBin >= MAX_COLS)
        {
            cout << "Invalid  location." << endl;
            return;
        }

        if (inventory[fromAisle][fromBin].item_quantity < quantity)
        {
            cout << "Not enough stock to transfer." << endl;
            return;
        }

        string itemName = inventory[fromAisle][fromBin].item_name;
        inventory[fromAisle][fromBin].item_quantity -= quantity;

        if (inventory[fromAisle][fromBin].item_quantity == 0)
        {
            inventory[fromAisle][fromBin].item_name = "";
        }

        addItem(toAisle, toBin, itemName, quantity);
        cout << "Transferred " << quantity << " items from Aisle " << fromAisle
            << ", Bin " << fromBin << " to Aisle " << toAisle << ", Bin " << toBin << endl;
    }
    void get_item_location(string item)
    {
        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                if (inventory[i][j].item_name == item)
                {
                    cout << "the item is in " << i << "aile" << j << "bin";
                }
            }
        }
    }
};

// Menu to display choices
void displayMenu() {
    cout << endl<<"Inventory Management System" << endl;
    cout << "1. Add Item" << endl;
    cout << "2. Remove Item" << endl;
    cout << "3. Check Stock" << endl;
    cout << "4. Display Inventory" << endl;
    cout << "5. Transfer Item" << endl;
    cout << "6. Low Stock Alert" << endl;
    cout << "7. Exit" << endl;
    cout << "8. get item's alise and bin" << endl;
    cout << "Enter your choice: ";
}

// Main program
int main() {
    InventorySystem inv;
    int choice, quantity, threshold;
    string name,get_item_name;
    int aisle, bin, fromAisle, fromBin, toAisle, toBin;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter aisle (0 to " << MAX_ROWS - 1 << "): ";
            cin >> aisle;
            cout << "Enter bin (0 to " << MAX_COLS - 1 << "): ";
            cin >> bin;
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter quantity: ";
            cin >> quantity;
            inv.addItem(aisle, bin, name, quantity);
            break;

        case 2:
            cout << "Enter aisle (0 to " << MAX_ROWS - 1 << "): ";
            cin >> aisle;
            cout << "Enter bin (0 to " << MAX_COLS - 1 << "): ";
            cin >> bin;
            cout << "Enter quantity to remove: ";
            cin >> quantity;
            inv.removeItem(aisle, bin, quantity);
            break;

        case 3:
            cout << "Enter aisle (0 to " << MAX_ROWS - 1 << "): ";
            cin >> aisle;
            cout << "Enter bin (0 to " << MAX_COLS - 1 << "): ";
            cin >> bin;
            inv.checkStock(aisle, bin);
            break;

        case 4:
            inv.displayInventory();
            break;

        case 5:
            cout << "Enter from aisle (0 to " << MAX_ROWS - 1 << "): ";
            cin >> fromAisle;
            cout << "Enter from bin (0 to " << MAX_COLS - 1 << "): ";
            cin >> fromBin;
            cout << "Enter to aisle (0 to " << MAX_ROWS - 1 << "): ";
            cin >> toAisle;
            cout << "Enter to bin (0 to " << MAX_COLS - 1 << "): ";
            cin >> toBin;
            cout << "Enter quantity to transfer: ";
            cin >> quantity;
            inv.transferItem(fromAisle, fromBin, toAisle, toBin, quantity);
            break;

        case 6:
            cout << "Enter stock threshold: ";
            cin >> threshold;
            inv.lowStockAlert(threshold);
            break;

        case 7:
            cout << "Exiting the program." << endl;
            return 0;
        case 8:
            cout << "Enter item to get the alice and bin of particular item: ";
            cin >> get_item_name;
            inv.get_item_location(get_item_name);
            break;


        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
