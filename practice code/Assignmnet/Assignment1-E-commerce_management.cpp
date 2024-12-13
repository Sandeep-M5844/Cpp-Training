#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Customer Class
class Customer {
public:
    int customer_id;
    string name;
    string email;

    Customer() {}

    void input_customer_details() {
        cout << "Enter customer ID: ";
        cin >> customer_id;

        cout << "Enter customer name: ";
        cin >> name;

        cout << "Enter customer email: ";
        cin >> email;
    }
};

class Product {
public:
    map<pair<int, string>, tuple<string, int, double>> product_inv;

    Product() {}
    void product_inventory()
    {
        cout << "Hello, please continue to add products to the inventory" << endl;
        int number_of_products;
        cout << "Enter number of products: ";
        cin >> number_of_products;

        for (int i = 0; i < number_of_products; i++) {
            int product_id;
            string product_name;
            string color;
            int quantity;
            double price;
            cout << "Product ID: ";
            cin >> product_id;

            cout << "Product Name: ";
            cin >> product_name;

            cout << "Color: ";
            cin >> color;

            cout << "Quantity: ";
            cin >> quantity;

            cout << "Price: ";
            cin >> price;

            product_inv[make_pair(product_id, product_name)] = make_tuple(color, quantity, price);
        }
    }

    void show_products() {
        for (auto& pro_detail : product_inv) {
            cout << endl << "Product Details for: " << pro_detail.first.second;
            cout << endl << "Product ID: " << pro_detail.first.first;
            cout << endl << "Name: " << pro_detail.first.second;
            cout << endl << "Color: " << get<0>(pro_detail.second);
            cout << endl << "Quantity: " << get<1>(pro_detail.second);
            cout << endl << "Price per unit: " << get<2>(pro_detail.second);
        }
    }

    ~Product() {}
};

class ShoppingCart : public Product, public Customer {
public:
    ShoppingCart() {}

    map<int, pair<double, int>> customer_cart; // product_id -> (price, quantity)


    void is_shopping() {
        bool interested;
        cout << endl << "Press 1 to buy the product, press 0 to exit: ";
        cin >> interested;
        if (interested) {
            input_customer_details();
            add_to_cart();
        }
        else {
            cout << endl << "Thanks for visiting Sandeep Mart! Please come again." << endl;
        }
    }

    void product_view_page() {
        cout << endl << "Welcome to the shopping section of Sandeep Mart!";
        cout << endl << "Please find the products available:";
        cout << endl << "-----------------------------------------";
        show_products();
        is_shopping();
    }

    void add_to_cart() {
        int purchase_product_id;
        cout << "Enter the product ID you want to purchase: ";
        cin >> purchase_product_id;

        int quantity;
        bool found_product = false;

        for (auto& pro_detail : product_inv) {
            if (pro_detail.first.first == purchase_product_id) {
                found_product = true;
                cout << "Enter the quantity required: ";
                cin >> quantity;
                int available_quantity = get<1>(pro_detail.second);

                if (available_quantity >= quantity) {
                    customer_cart[purchase_product_id] = make_pair(get<2>(pro_detail.second), quantity);
                    product_inv[pro_detail.first] = make_tuple(get<0>(pro_detail.second), available_quantity - quantity, get<2>(pro_detail.second));
                    cout << "Product added to cart!" << endl;
                }
                else
                {
                    cout << "Sorry, the quantity is not available. Please select a smaller quantity." << endl;
                }
                break;
            }
        }

        if (!found_product) {
            cout << "Product ID not found. Please try again." << endl;
        }

        is_shopping();
    }

    void view_cart() {
        cout << "Your Shopping Cart:" << endl;
        double total_price = 0;

        for (const auto& cart_item : customer_cart) {
            int product_id = cart_item.first;
            double price = cart_item.second.first;
            int quantity = cart_item.second.second;

            cout << "Product ID: " << product_id << " | Price: $" << price << " | Quantity: " << quantity << endl;
            total_price += price * quantity;
        }

        cout << "Total amount: $" << total_price << endl;
    }
};

int main()
{
    ShoppingCart s;
    while (true)
    {
        cout << endl << "Welcome to Sandeep Mart!";
        cout << endl << "*****************************";
        cout << endl << "Press 0 to open Employee page, Press 1 to open Customer page: ";
        int user;
        cin >> user;

        if (user == 1)
        {

            s.product_view_page();
        }
        else if (user == 0)
        {
            s.product_inventory();
            s.show_products();
        }
        else
        {
            cout << endl << "thank you ......";
            break;
        }

    }
    return 0;
}
