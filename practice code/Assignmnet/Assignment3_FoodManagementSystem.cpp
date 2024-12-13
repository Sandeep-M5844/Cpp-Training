#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class ManageRestrunt
{
private:
    struct RestruntDetails
    {
        string R_name;
        string R_location;
    };

public:
    unordered_map<string, RestruntDetails> RestaurantData;

    void addDetails()
    {
        cout << "***** restrunt add details section*****" << endl;
        string name;
        string location;
        cout << "Enter the restaurant name: ";
        getline(cin, name);

        while (RestaurantData.find(name) != RestaurantData.end())
        {
            cout << "The restaurant " << name << " already exists. Please enter a new restaurant name: ";
            getline(cin, name);
        }

        cout << "Enter the location for " << name << ": ";
        getline(cin, location);

        RestaurantData[name].R_name = name;
        RestaurantData[name].R_location = location;

        cout << "Restaurant " << name << " added with location: " << location << endl;
    }

    void displayDetails()
    {
        cout << "***** restrunt Display details section*****" << endl;

        if (RestaurantData.empty())
        {
            cout << "No restaurant available." << endl;
            return;
        }

        cout << "Displaying all restaurant details:" << endl;
        for (const auto& data : RestaurantData)
        {
            cout << "Restaurant Name: " << data.second.R_name << endl;
            cout << "Location: " << data.second.R_location << endl;
        }
    }
};

class Menu
{
private:
    struct restaurantMenu
    {
        string ItemName;
        double price;
    };
public:

    unordered_map<string, vector<restaurantMenu>> menuData;

public:
    void addMenuItem(ManageRestrunt& manage)
    {
        cout << "***** restrunt menu details section*****" << endl;

        string restaurant_name, menu_item;
        double price;

        cout << "Enter the restaurant name to add menu item: ";
        getline(cin, restaurant_name);

        while (manage.RestaurantData.find(restaurant_name) == manage.RestaurantData.end())
        {
            cout << "Restaurant " << restaurant_name << " does not exist. Please enter a valid restaurant name: ";
            getline(cin, restaurant_name);
        }

        cout << "Enter the menu item: ";
        getline(cin, menu_item);
        cout << "Enter the price of the item: ";
        cin >> price;
        cin.ignore();

        restaurantMenu item;
        item.ItemName = menu_item;
        item.price = price;
        menuData[restaurant_name].push_back(item);

        cout << "Menu item: " << menu_item << " with price $" << price << " added to "
            << restaurant_name << "." << endl;
    }

    void removeMenuItem(ManageRestrunt& manage)
    {
        cout << "***** restrunt menu deletion details section*****" << endl;

        string restaurant_name, menu_item;
        cout << "Enter the restaurant name to remove menu item: ";
        getline(cin, restaurant_name);

        while (manage.RestaurantData.find(restaurant_name) == manage.RestaurantData.end())
        {
            cout << "Restaurant " << restaurant_name << " does not exist. Please enter a valid restaurant name: ";
            getline(cin, restaurant_name);
        }

        cout << "Enter the menu item name to remove: ";
        getline(cin, menu_item);

        bool item_found = false;
        for (auto it = menuData[restaurant_name].begin(); it != menuData[restaurant_name].end(); ++it)
        {
            if (it->ItemName == menu_item)
            {
                menuData[restaurant_name].erase(it);
                item_found = true;
                cout << "Item " << menu_item << " removed from " << restaurant_name << " menu." << endl;
                break;
            }
        }
        if (!item_found)
        {
            cout << "Item " << menu_item << " not found in the menu." << endl;
        }
    }
    

    void displayMenu(const string& restaurant_name)
    {
        cout << "***** Restaurant menu display details for perticular *****" << endl;

        if (menuData.find(restaurant_name) == menuData.end())
        {
            cout << "No menu available for " << restaurant_name << endl;
            return;
        }

        cout << "Menu for " << restaurant_name << ":" << endl;
        for (const auto& item : menuData[restaurant_name])
        {
            cout << item.ItemName << " - $" << item.price << endl;
        }
    }

    void displayAllRestaurantMenu()
    {
        if (menuData.empty())
        {
            cout << "No menus available." << endl;
            return;
        }

        for (const auto& restaurant : menuData)
        {
            cout << "Restaurant: " << restaurant.first << endl;
            for (const auto& item : restaurant.second)
            {
                cout << "* " << item.ItemName << " - $" << item.price << endl;
            }
            cout << endl;
        }
    }
};

class costumerinfo
{
public:
    string name;
    string contact_number;

    costumerinfo(string customer_name, string customer_contact)
    {
        name = customer_name;
        contact_number = customer_contact;
    }
};

class order
{
    struct orderDetails
    {
        int oderID;
        string restaurant_name;
        string custumer_name;
        vector<string> menu_items;
        double total_cost = 0.0;
        orderDetails* next; // linked list for order details store 

    };
    orderDetails* head;
    orderDetails* current;
    int ordercounter;
    

public:
    order()
    {
        head = nullptr;
        current = nullptr;
    }

    void placeOrder(Menu& menuObj, ManageRestrunt& manage)
    {
        cout << "***** order section *****" << endl;
        string customer_name, customer_contact, restaurant_name;
        cout << "Enter your name: ";
        getline(cin, customer_name);
        cout << "Enter your contact number: ";
        getline(cin, customer_contact);

        // calling customer object to store the customer data
        costumerinfo customer(customer_name, customer_contact);

        cout << "Enter restaurant name to place an order: ";
        getline(cin, restaurant_name);

        // Checking if the restaurant exists or not
        while (manage.RestaurantData.find(restaurant_name) == manage.RestaurantData.end())
        {
            cout << "Restaurant " << restaurant_name << " does not exist. Please enter a valid restaurant name: ";
            getline(cin, restaurant_name);
        }

        // Display menu for the selected restaurant

        menuObj.displayMenu(restaurant_name);

        vector<string> order_items;
        double total_cost = 0.0;
        string menu_item;
        char continue_ordering = 'y';

        while (continue_ordering == 'y')
        {
            cout << "Enter menu item to order: ";
            getline(cin, menu_item);
            order_items.push_back(menu_item);

            bool item_found = false;
            for (const auto& item : menuObj.menuData[restaurant_name])
            {
                if (item.ItemName == menu_item)
                {
                    total_cost += item.price;
                    item_found = true;
                    break;
                }
            }
            if (!item_found)
            {
                cout << "Item not found on the menu!" << endl;
            }
            cout << "Do you want to add another item? (y/n): ";
            cin >> continue_ordering;
            cin.ignore();
        }
        ordercounter++;

        // if there is new order 

        orderDetails* new_order = new orderDetails;
        new_order->restaurant_name = restaurant_name;
        new_order->menu_items = order_items;
        new_order->total_cost = total_cost;
        new_order->custumer_name = customer_name;
        new_order->oderID = ordercounter;
        new_order->next = nullptr;

        if (head == nullptr) {
            head = new_order;
            current = new_order;  // If it's the first order, head and tail will be the same
        }
        else 
        {
            current->next = new_order;
            current = new_order;// moving the current to the new node 
        }
        cout<< "Order placed successfully! with ORDER ID :" <<new_order->oderID 
            <<"Total cost : $" << total_cost << endl;
    }

    void processOrder()
    {
        cout << "***** order processing*****" << endl;
        if (head == nullptr) {
            cout << "No orders to process." << endl;
            return;
        }

        orderDetails* order = head;// this order act as current node which intiall
        cout << "Processing order from " << order->restaurant_name <<"restaurant" << endl;
        cout << "customer name:" << order->custumer_name<<endl;
        cout << "order ID: " << order->oderID;
        cout << "Ordered Items: ";
        for (const auto& item : order->menu_items) {
            cout << item << " ";
        }
        cout << endl;
        cout << "Total cost: $" << order->total_cost << endl;

        // Move the head pointer to the next order in the list
        head = head->next;

        // Delete the processed order node
        delete order;
    }
};
    

int main()
{
    ManageRestrunt manage;
    Menu menuObj;
    order orderObj;
    int choice;

    do
    {
        cout << "SANDEEP CLOUD DELIVERY SYSTEM" << endl;
        cout << "*************************" << endl;
        cout << "1. Add Restaurant" << endl;
        cout << "2. Display Restaurant Details" << endl;
        cout << "3. Add Menu Item" << endl;
        cout << "4. Remove Menu Item" << endl; 
        cout << "5. Display Menu for a Restaurant" << endl;
        cout << "6. Display All Menus from all Restaurants" << endl;
        cout << "7. Place Order" << endl;
        cout << "8. Process and Deliver Orders" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  

        switch (choice)
        {
        case 1:
            manage.addDetails();
            break;
        case 2:
            manage.displayDetails();
            break;
        case 3:
            menuObj.addMenuItem(manage);
            break;
        case 4:
            menuObj.removeMenuItem(manage); 
            break;
        case 5:
        {
            string restaurant_name;
            cout << "Enter restaurant name to display menu: ";
            getline(cin, restaurant_name);
            menuObj.displayMenu(restaurant_name);
            break;
        }
        case 6:
            menuObj.displayAllRestaurantMenu();
            break;
        case 7:
            orderObj.placeOrder(menuObj, manage);
            break;
        case 8:
            orderObj.processOrder();
            break;
        case 9:
            cout << "Exiting the system..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice !=9);

    return 0;
}
