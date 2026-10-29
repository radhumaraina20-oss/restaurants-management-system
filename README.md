# Land of Spices — Restaurant Management System (C++)

A robust, console-based Fast Food Restaurant Management System written in standard C++. It provides an interactive portal for both administrators and customers to manage menu deals, place orders, and track deliveries.

---

## 📌 Features

### 👨‍💼 Admin Portal
- **Secure Authentication**: Protected by credentials (`username` / `password`).
- **Menu Management**:
  - Add new deals with custom items, categories, drink choices, fries, and pricing.
  - Remove existing deals from the menu.
- **Order Tracking & Fulfillment**:
  - View all customer orders placed across the system.
  - Update status of individual orders (`In Process`, `Dispatched`, `Delivered`, `Cancelled`).

### 🛍️ Customer Portal
- **Browse Menu**: View active deals with detailed descriptions, bundle items, and prices.
- **Place Orders**: Simple ordering flow collecting customer details and full delivery address.
- **Order Tracking**: Track current order status anytime using the unique auto-generated Order ID.

---

## 🔑 Default Credentials

| Role | Username | Password |
|---|---|---|
| **Admin** | `admin717` | `project` |

---

## 🏗️ Architecture & OOP Concepts

- **Inheritance**:
  - `Deal` inherits from `Item` to extend general food attributes with deal-specific details (bundle items, cold drinks, fries, and combo pricing).
- **Composition**:
  - `UserDetails` composes the `Address` class.
  - `OrderDetails` composes `UserDetails` and `Date` classes.
  - `FastFoodRestaurant` composes `Admin`, `Deal[]`, `OrderDetails[]`, and `Date`.
- **Encapsulation & Data Hiding**:
  - Private member variables protected by public accessors and mutators (`getters` / `setters`).
- **Memory Safety & Robust I/O**:
  - Pass-by-reference eliminates state loss across menu interactions.
  - Sanitized multi-word string reading via `std::getline` prevents buffer overflow and input choking.
  - Iterative menu loops prevent stack overflow recursion.

---

## 📂 Project Structure

```
restomanage.cp/
├── restaurant_management.cpp    # Complete C++ source code
└── README.md                    # Project documentation
```

---

## ⚙️ Compilation & Execution

### Prerequisites
- C++11 or higher (C++17 recommended)
- Any standard C++ compiler: GCC (MinGW for Windows), MSVC, or Clang

### 1. Using GCC / MinGW (g++)
```bash
g++ -std=c++17 restaurant_management.cpp -o restomanage.exe
./restomanage.exe
```

### 2. Using Microsoft Visual C++ (MSVC)
Open the **x64 Native Tools Command Prompt for VS**:
```cmd
cl /EHsc restaurant_management.cpp
restaurant_management.exe
```

### 3. Using Clang
```bash
clang++ -std=c++17 restaurant_management.cpp -o restomanage
./restomanage
```

---

## 📋 Sample Starter Menu Deals

When launched, the system comes pre-configured with 3 starter deals:
1. **Spicy Crunch Deal (Rs. 750.00)** — Zinger Burger, Pepsi 500ml, Regular Fries.
2. **Royal Pizza Feast (Rs. 1,450.00)** — Medium Tikka Pizza, 7Up 1.5L, Garlic Bread.
3. **Quick Bite Duo (Rs. 520.00)** — Chicken Shawarma Wrap, Mirinda Can, Spicy Wedges.

---

## 📄 License
This project is for educational and practical demonstration purposes. Feel free to modify and expand!

