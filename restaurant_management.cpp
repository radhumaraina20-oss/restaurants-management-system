#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
// POSIX equivalent for _getch
inline int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

using namespace std;

// ==========================================
// Utility Functions
// ==========================================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseConsole(const string& message = "Press any key to continue...") {
    cout << "\n " << message << endl;
    _getch();
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string readLine(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

// ==========================================
// Class: Admin
// ==========================================
class Admin {
private:
    const string username = "admin717";
    const string password = "project";

public:
    Admin() = default;

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    bool authenticate(const string& user, const string& pass) const {
        return (username == user && password == pass);
    }
};

// ==========================================
// Class: Item
// ==========================================
class Item {
private:
    string name;
    string description;

public:
    Item(string n = "", string d = "") : name(n), description(d) {}

    void setItemName(const string& type) {
        cout << " Enter " << type << " Name: ";
        getline(cin, name);
    }

    void setItemDescription(const string& type) {
        cout << " Enter " << type << " Description: ";
        getline(cin, description);
    }

    string getItemName() const {
        return name;
    }

    string getItemDescription() const {
        return description;
    }

    void removeItem() {
        name.clear();
        description.clear();
    }
};

// ==========================================
// Class: Deal (Inherits from Item)
// ==========================================
class Deal : public Item {
private:
    string dealName;
    int dealItems;
    string coldDrink;
    string fries;
    double dealPrice;
    bool active;

public:
    Deal(string dn = "", int di = 0, string in = "", string id = "",
         string cd = "", string f = "", double dp = 0.0, bool act = false)
        : Item(in, id), dealName(dn), dealItems(di), coldDrink(cd), fries(f), dealPrice(dp), active(act) {}

    bool isActive() const {
        return active;
    }

    void setActive(bool act) {
        active = act;
    }

    void removeDeal() {
        dealName.clear();
        dealItems = 0;
        coldDrink.clear();
        fries.clear();
        dealPrice = 0.0;
        active = false;
        removeItem();
    }

    void showDeal() const {
        if (!active) return;
        cout << " ------------------------------------------" << endl;
        cout << "  Deal Name   : " << dealName << endl;
        cout << "  Items Count : " << dealItems << endl;
        cout << "  Main Item   : " << Item::getItemName() << endl;
        cout << "  Description : " << Item::getItemDescription() << endl;
        cout << "  Cold Drink  : " << coldDrink << endl;
        cout << "  Fries       : " << fries << endl;
        cout << "  Price       : Rs. " << fixed << setprecision(2) << dealPrice << endl;
        cout << " ------------------------------------------" << endl;
    }

    void inputDeal() {
        cout << " Enter Deal Name: ";
        getline(cin, dealName);

        cout << " Enter Number of Items: ";
        while (!(cin >> dealItems) || dealItems <= 0) {
            cout << " Invalid input. Please enter a valid number of items: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        string itemType;
        cout << " Enter Main Item Category (e.g. Burger/Pizza/Wrap): ";
        getline(cin, itemType);

        setItemName(itemType);
        setItemDescription(itemType);

        cout << " Enter Cold Drink (e.g. 500ml Coke / None): ";
        getline(cin, coldDrink);

        cout << " Enter Fries Type (e.g. Large Curly Fries / Regular / None): ";
        getline(cin, fries);

        cout << " Enter Deal Price: ";
        while (!(cin >> dealPrice) || dealPrice < 0) {
            cout << " Invalid price. Please enter a valid number: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        active = true;
    }

    string getDealName() const {
        return dealName;
    }

    int getDealItems() const {
        return dealItems;
    }

    string getColdDrink() const {
        return coldDrink;
    }

    string getFries() const {
        return fries;
    }

    double getDealPrice() const {
        return dealPrice;
    }
};

// ==========================================
// Class: Address
// ==========================================
class Address {
private:
    string societyName;
    string streetNumber;
    string houseNumber;

public:
    Address(string sn = "", string strn = "", string hn = "")
        : societyName(sn), streetNumber(strn), houseNumber(hn) {}

    void inputAddress() {
        cout << " Enter Society/Area Name : ";
        getline(cin, societyName);

        cout << " Enter Street/Lane Number: ";
        getline(cin, streetNumber);

        cout << " Enter House/Apartment No: ";
        getline(cin, houseNumber);
    }

    string getSocietyName() const { return societyName; }
    string getStreetNumber() const { return streetNumber; }
    string getHouseNumber() const { return houseNumber; }

    string getFullAddress() const {
        return "House #" + houseNumber + ", Street #" + streetNumber + ", " + societyName;
    }
};

// ==========================================
// Class: UserDetails
// ==========================================
class UserDetails {
private:
    string name;
    Address addressOfCustomer;
    string phoneNumber;

public:
    UserDetails(string n = "", string society = "", string street = "", string house = "", string pn = "")
        : name(n), addressOfCustomer(society, street, house), phoneNumber(pn) {}

    void inputDetails() {
        cout << " Enter your full name: ";
        getline(cin, name);

        cout << " Enter contact phone number: ";
        getline(cin, phoneNumber);

        cout << " --- Enter Delivery Address ---" << endl;
        addressOfCustomer.inputAddress();
    }

    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getFullAddress() const { return addressOfCustomer.getFullAddress(); }
};

// ==========================================
// Class: Date
// ==========================================
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}

    void setDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    string toString() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
};

// ==========================================
// Class: OrderDetails
// ==========================================
class OrderDetails {
private:
    int orderID;
    string dealName;
    double orderPrice;
    UserDetails customerDetails;
    Date orderDate;
    string orderStatus; // "In Process", "Dispatched", "Delivered", "Cancelled"
    bool active;

public:
    OrderDetails() : orderID(0), dealName(""), orderPrice(0.0), orderStatus("Pending"), active(false) {}

    void createOrder(int id, const string& dName, double price, const UserDetails& user, const Date& date) {
        orderID = id;
        dealName = dName;
        orderPrice = price;
        customerDetails = user;
        orderDate = date;
        orderStatus = "In Process";
        active = true;
    }

    bool isActive() const { return active; }

    void display() const {
        if (!active) return;
        cout << " ==========================================" << endl;
        cout << "  Order #" << orderID << "  [" << orderStatus << "]" << endl;
        cout << " ==========================================" << endl;
        cout << "  Deal Ordered  : " << dealName << endl;
        cout << "  Total Amount  : Rs. " << fixed << setprecision(2) << orderPrice << endl;
        cout << "  Order Date    : " << orderDate.toString() << endl;
        cout << "  Customer Name : " << customerDetails.getName() << endl;
        cout << "  Phone Number  : " << customerDetails.getPhoneNumber() << endl;
        cout << "  Delivery To   : " << customerDetails.getFullAddress() << endl;
        cout << " ------------------------------------------" << endl;
    }

    int getOrderID() const { return orderID; }
    string getDealName() const { return dealName; }
    string getOrderStatus() const { return orderStatus; }
    string getCustomerName() const { return customerDetails.getName(); }
    string getCustomerPhone() const { return customerDetails.getPhoneNumber(); }

    void setOrderStatus(const string& status) {
        orderStatus = status;
    }
};

// ==========================================
// Class: FastFoodRestaurant
// ==========================================
class FastFoodRestaurant {
private:
    string restaurantName;
    Admin administrator;
    static const int MAX_DEALS = 10;
    static const int MAX_ORDERS = 50;

    Deal deals[MAX_DEALS];
    int dealCount = 0;

    OrderDetails orders[MAX_ORDERS];
    int orderCount = 0;
    int nextOrderID = 1001;

    Date currentDate;

public:
    FastFoodRestaurant(string name = "Land of Spices") : restaurantName(name) {
        // Seed initial default menu deals
        deals[0] = Deal("Spicy Crunch Deal", 3, "Zinger Burger", "Crispy deep fried chicken thigh in bun",
                        "Pepsi 500ml", "Regular Fries", 750.0, true);
        deals[1] = Deal("Royal Pizza Feast", 4, "Medium Tikka Pizza", "Smoked chicken tikka with mozzarella",
                        "7Up 1.5L", "Garlic Bread", 1450.0, true);
        deals[2] = Deal("Quick Bite Duo", 2, "Chicken Shawarma Wrap", "Juicy spiced chicken wrapped with garlic mayo",
                        "Mirinda Can", "Spicy Wedges", 520.0, true);
        dealCount = 3;
    }

    void setRestaurantName(const string& name) {
        restaurantName = name;
    }

    string getRestaurantName() const {
        return restaurantName;
    }

    bool verifyAdmin(const string& u, const string& p) const {
        return administrator.authenticate(u, p);
    }

    void setupDate() {
        int d, m, y;
        cout << "\n Enter current system date:" << endl;
        cout << "  Enter Day (1-31)  : ";
        while (!(cin >> d) || d < 1 || d > 31) {
            cout << "  Invalid day. Re-enter: ";
            clearInputBuffer();
        }
        cout << "  Enter Month (1-12): ";
        while (!(cin >> m) || m < 1 || m > 12) {
            cout << "  Invalid month. Re-enter: ";
            clearInputBuffer();
        }
        cout << "  Enter Year (YYYY) : ";
        while (!(cin >> y) || y < 2000 || y > 2100) {
            cout << "  Invalid year. Re-enter: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        currentDate.setDate(d, m, y);
    }

    Date getDate() const {
        return currentDate;
    }

    // --- Deal Management ---
    void displayMenu() const {
        cout << "\n ==========================================" << endl;
        cout << "          " << restaurantName << " MENU" << endl;
        cout << " ==========================================" << endl;

        bool hasDeals = false;
        for (int i = 0; i < MAX_DEALS; i++) {
            if (deals[i].isActive()) {
                deals[i].showDeal();
                hasDeals = true;
            }
        }

        if (!hasDeals) {
            cout << "  No deals currently available in the menu." << endl;
        }
    }

    void addDeal() {
        if (dealCount >= MAX_DEALS) {
            cout << "\n Deal capacity reached (" << MAX_DEALS << " max). Remove a deal first!" << endl;
            return;
        }

        // Find available slot
        int slot = -1;
        for (int i = 0; i < MAX_DEALS; i++) {
            if (!deals[i].isActive()) {
                slot = i;
                break;
            }
        }

        if (slot == -1) {
            cout << "\n No empty deal slots available!" << endl;
            return;
        }

        cout << "\n --- Adding New Deal (Slot " << (slot + 1) << ") ---" << endl;
        deals[slot].inputDeal();
        dealCount++;
        cout << "\n Deal successfully added to the menu!" << endl;
    }

    void removeDeal() {
        displayMenu();
        string nameToRemove = readLine("\n Enter the exact Deal Name to remove: ");

        bool found = false;
        for (int i = 0; i < MAX_DEALS; i++) {
            if (deals[i].isActive() && deals[i].getDealName() == nameToRemove) {
                deals[i].removeDeal();
                dealCount--;
                found = true;
                cout << "\n Deal \"" << nameToRemove << "\" has been removed successfully!" << endl;
                break;
            }
        }

        if (!found) {
            cout << "\n Deal not found with name: " << nameToRemove << endl;
        }
    }

    // --- Order Management ---
    void placeOrder(int& lastCustomerOrderID) {
        if (orderCount >= MAX_ORDERS) {
            cout << "\n Sorry, maximum order capacity reached for today! Try again later." << endl;
            return;
        }

        displayMenu();
        string chosenDeal = readLine("\n Enter the Deal Name you wish to order: ");

        // Check if deal exists
        int dealIndex = -1;
        for (int i = 0; i < MAX_DEALS; i++) {
            if (deals[i].isActive() && deals[i].getDealName() == chosenDeal) {
                dealIndex = i;
                break;
            }
        }

        if (dealIndex == -1) {
            cout << "\n That deal is not currently offered on our menu." << endl;
            return;
        }

        cout << "\n --- Enter Your Information for Delivery ---" << endl;
        UserDetails customer;
        customer.inputDetails();

        // Find available slot for order
        int orderSlot = -1;
        for (int i = 0; i < MAX_ORDERS; i++) {
            if (!orders[i].isActive()) {
                orderSlot = i;
                break;
            }
        }

        int newId = nextOrderID++;
        orders[orderSlot].createOrder(newId, deals[dealIndex].getDealName(),
                                      deals[dealIndex].getDealPrice(), customer, currentDate);
        orderCount++;
        lastCustomerOrderID = newId;

        clearScreen();
        cout << "\n ================================================" << endl;
        cout << "  Congratulations! Your order has been placed!   " << endl;
        cout << "  Your Order ID is: #" << newId << endl;
        cout << "  Please save your Order ID to track its status. " << endl;
        cout << " ================================================" << endl;
        orders[orderSlot].display();
    }

    void viewAllOrders() const {
        cout << "\n ==========================================" << endl;
        cout << "           ALL RESTAURANT ORDERS           " << endl;
        cout << " ==========================================" << endl;

        bool hasOrders = false;
        for (int i = 0; i < MAX_ORDERS; i++) {
            if (orders[i].isActive()) {
                orders[i].display();
                hasOrders = true;
            }
        }

        if (!hasOrders) {
            cout << "  No active orders found." << endl;
        }
    }

    void updateOrderStatus() {
        viewAllOrders();
        cout << "\n Enter the Order ID to update status (or 0 to cancel): ";
        int targetId;
        if (!(cin >> targetId) || targetId == 0) {
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        int index = -1;
        for (int i = 0; i < MAX_ORDERS; i++) {
            if (orders[i].isActive() && orders[i].getOrderID() == targetId) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << " Order #" << targetId << " not found!" << endl;
            return;
        }

        cout << "\n Current Status: " << orders[index].getOrderStatus() << endl;
        cout << " Choose new status:" << endl;
        cout << "  1) In Process" << endl;
        cout << "  2) Dispatched / Out for Delivery" << endl;
        cout << "  3) Delivered" << endl;
        cout << "  4) Cancelled" << endl;
        cout << " Select option (1-4): ";

        int opt;
        if (cin >> opt) {
            clearInputBuffer();
            switch (opt) {
            case 1: orders[index].setOrderStatus("In Process"); break;
            case 2: orders[index].setOrderStatus("Dispatched"); break;
            case 3: orders[index].setOrderStatus("Delivered"); break;
            case 4: orders[index].setOrderStatus("Cancelled"); break;
            default: cout << " Invalid selection. Status untouched." << endl; return;
            }
            cout << " Order #" << targetId << " status updated to \"" << orders[index].getOrderStatus() << "\"!" << endl;
        } else {
            clearInputBuffer();
        }
    }

    void trackOrderByID(int customerLastOrderId) const {
        cout << "\n Track Your Order:" << endl;
        cout << " Enter your Order ID [Last placed: #" << (customerLastOrderId ? to_string(customerLastOrderId) : "None") << "]: ";
        int id;
        if (!(cin >> id)) {
            clearInputBuffer();
            cout << " Invalid Order ID." << endl;
            return;
        }
        clearInputBuffer();

        bool found = false;
        for (int i = 0; i < MAX_ORDERS; i++) {
            if (orders[i].isActive() && orders[i].getOrderID() == id) {
                orders[i].display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << " Order #" << id << " not found. Please check your ID and try again." << endl;
        }
    }
};

// ==========================================
// Function Prototypes for Clean Menu Loops
// ==========================================
void handleAdminSession(FastFoodRestaurant& restaurant);
void handleUserSession(FastFoodRestaurant& restaurant, int& lastCustomerOrderId);

// ==========================================
// Main Entry Point
// ==========================================
int main() {
    FastFoodRestaurant restaurant("Land of Spices");
    int lastCustomerOrderId = 0;

    clearScreen();
    cout << " ===============================================" << endl;
    cout << " |                                             |" << endl;
    cout << " |         Welcome to Land of Spices           |" << endl;
    cout << " |       Fast Food Management System           |" << endl;
    cout << " |                                             |" << endl;
    cout << " ===============================================" << endl;

    restaurant.setupDate();
    pauseConsole("Date configured. Press any key to enter main portal...");

    bool running = true;
    while (running) {
        clearScreen();
        cout << " ===============================================" << endl;
        cout << " |             LAND OF SPICES PORTAL           |" << endl;
        cout << " ===============================================" << endl;
        cout << " |  Date: " << setw(10) << left << restaurant.getDate().toString() << "                           |" << endl;
        cout << " |---------------------------------------------|" << endl;
        cout << " |  1) Admin Login                             |" << endl;
        cout << " |  2) Customer Portal                         |" << endl;
        cout << " |  3) Exit System                             |" << endl;
        cout << " ===============================================" << endl;
        cout << " Select option (1-3): ";

        int choice;
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << " Invalid option! Please enter 1, 2, or 3." << endl;
            pauseConsole();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1:
            handleAdminSession(restaurant);
            break;
        case 2:
            handleUserSession(restaurant, lastCustomerOrderId);
            break;
        case 3:
            running = false;
            clearScreen();
            cout << "\n ===============================================" << endl;
            cout << " |                                             |" << endl;
            cout << " |         Thank you for choosing              |" << endl;
            cout << " |             LAND OF SPICES!                 |" << endl;
            cout << " |              See you soon!                  |" << endl;
            cout << " |                                             |" << endl;
            cout << " ===============================================\n" << endl;
            break;
        default:
            cout << " Invalid choice. Please select 1, 2, or 3." << endl;
            pauseConsole();
            break;
        }
    }

    return 0;
}

// ==========================================
// Admin Session Handler
// ==========================================
void handleAdminSession(FastFoodRestaurant& restaurant) {
    clearScreen();
    cout << " ===============================================" << endl;
    cout << " |                 ADMIN LOGIN                 |" << endl;
    cout << " ===============================================" << endl;
    cout << " Default credentials: user: admin717 / pass: project" << endl;
    cout << " -----------------------------------------------" << endl;

    string user = readLine(" Username: ");
    string pass = readLine(" Password: ");

    if (!restaurant.verifyAdmin(user, pass)) {
        cout << "\n [!] Access Denied: Invalid username or password." << endl;
        pauseConsole();
        return;
    }

    bool adminLoggedIn = true;
    while (adminLoggedIn) {
        clearScreen();
        cout << " ===============================================" << endl;
        cout << " |             ADMIN CONTROL PANEL             |" << endl;
        cout << " ===============================================" << endl;
        cout << " |  1) View Menu Deals                         |" << endl;
        cout << " |  2) Add New Deal                            |" << endl;
        cout << " |  3) Remove Deal                             |" << endl;
        cout << " |  4) View All Customer Orders                |" << endl;
        cout << " |  5) Update Order Status                     |" << endl;
        cout << " |  6) Logout                                  |" << endl;
        cout << " ===============================================" << endl;
        cout << " Select an option (1-6): ";

        int option;
        if (!(cin >> option)) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (option) {
        case 1:
            clearScreen();
            restaurant.displayMenu();
            pauseConsole();
            break;
        case 2:
            clearScreen();
            restaurant.addDeal();
            pauseConsole();
            break;
        case 3:
            clearScreen();
            restaurant.removeDeal();
            pauseConsole();
            break;
        case 4:
            clearScreen();
            restaurant.viewAllOrders();
            pauseConsole();
            break;
        case 5:
            clearScreen();
            restaurant.updateOrderStatus();
            pauseConsole();
            break;
        case 6:
            adminLoggedIn = false;
            cout << "\n Logged out successfully." << endl;
            pauseConsole();
            break;
        default:
            cout << " Invalid option!" << endl;
            pauseConsole();
            break;
        }
    }
}

// ==========================================
// Customer Portal Session Handler
// ==========================================
void handleUserSession(FastFoodRestaurant& restaurant, int& lastCustomerOrderId) {
    bool userActive = true;
    while (userActive) {
        clearScreen();
        cout << " ===============================================" << endl;
        cout << " |               CUSTOMER PORTAL               |" << endl;
        cout << " ===============================================" << endl;
        cout << " |  1) View Food Menu                          |" << endl;
        cout << " |  2) Place an Order                          |" << endl;
        cout << " |  3) Track / View Order Status               |" << endl;
        cout << " |  4) Back to Main Portal                     |" << endl;
        cout << " ===============================================" << endl;
        cout << " Select an option (1-4): ";

        int option;
        if (!(cin >> option)) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (option) {
        case 1:
            clearScreen();
            restaurant.displayMenu();
            pauseConsole();
            break;
        case 2:
            clearScreen();
            restaurant.placeOrder(lastCustomerOrderId);
            pauseConsole();
            break;
        case 3:
            clearScreen();
            restaurant.trackOrderByID(lastCustomerOrderId);
            pauseConsole();
            break;
        case 4:
            userActive = false;
            break;
        default:
            cout << " Invalid option!" << endl;
            pauseConsole();
            break;
        }
    }
}
