---

# 🏠 Real Estate Management System (C++)

A high-performance real estate management tool built entirely in C++ using custom **Doubly Circular Linked Lists (DCLL)**. This system allows users to manage properties across various neighborhoods, perform complex analytics, and persist data via a custom file management engine.

---

## 🚀 Key Features

* **Custom DCLL Implementation**: A robust, template-based Doubly Circular Linked List used for both global property storage and neighborhood organization.
* **Spatial Indexing**: Properties are logically grouped by neighborhoods using a `NeighborhoodIndex` for faster access and reporting.
* **Persistent Storage**: Full data persistence using `FileManager` to save and load property data from `database.txt`.
* **Real-time Analytics**: Built-in functions to calculate average prices, total market value, and price-sorted reports.
* **Safe Memory Management**: Optimized destructors and direct object management to prevent segmentation faults (Access Violations).

---

## 🏗️ System Architecture

The project is modularized into 8 core headers to maintain a clean separation of concerns:

| Header | Responsibility |
| --- | --- |
| **`DCLL.h`** | The foundational data structure (Doubly Circular Linked List). |
| **`Property.h`** | Defines the Property object attributes (ID, Price, Area). |
| **`Neighborhood.h`** | Manages a collection of properties within a specific area. |
| **`NeighborhoodIndex.h`** | High-level index for searching and organizing neighborhoods. |
| **`FileManager.h`** | Handles I/O operations and data persistence (`.txt` files). |
| **`PropertySearcher.h`** | Implements Global, Neighborhood-specific, and Range-based searches. |
| **`PropertyAnalytics.h`** | Provides sorting logic and summary statistics. |
| **`CRUD.h`** | Contains logic for Adding, Validating, and Removing properties safely. |

---

## 🛠️ Installation & Setup

### Without Terminal (Using IDE)

1. Download all `.h` files and the `main.cpp`.
2. Open your IDE (**Visual Studio**, **VS Code**, or **Code::Blocks**).
3. Create a new C++ Project.
4. Add all files to the project directory.
5. Click **Run** or press `F5`.

### Using Terminal (GCC)

```bash
# Clone the repository
git clone https://github.com/yourusername/RealEstateSystem.git

# Navigate to the folder
cd RealEstateSystem

# Compile the project
g++ main.cpp -o RealEstateApp

# Run the application
./RealEstateApp

```

---

## 📊 Data Management Logic

The system utilizes a **Manual Bubble Sort** within the `PropertyAnalytics` class to handle data extraction and sorting without relying on external libraries.

```cpp
// Example of the Analytics Sorting Logic
size_t n = vec.size();
for (size_t i = 0; i < n - 1; i++) {
    for (size_t j = 0; j < n - i - 1; j++) {
        if (vec[j].getPrice() > vec[j + 1].getPrice()) {
            // Swap logic
        }
    }
}

```

---

## 📂 File Format

Data is stored in `database.txt` using a pipe-delimited format:
`ID|NeighborhoodName|Price`

**Example:**

```text
1|Downtown|250000.00
2|EastArea|150000.00
3|Westside|420000.00

```

---

## 🛡️ Error Handling

The system includes protections against common C++ pitfalls:

* **Access Violations (`0xc0000005`)**: Resolved by using direct object references in the `Neighborhood` class.
* **Memory Leaks**: All `DCLL` nodes are recursively deleted upon list destruction.
* **Input Validation**: `CRUD.h` ensures that Property IDs and Prices are always positive values.

---

## 🤝 Contributing

1. Fork the Project.
2. Create your Feature Branch (`git checkout -b feature/NewFeature`).
3. Commit your Changes (`git commit -m 'Add some NewFeature'`).
4. Push to the Branch (`git push origin feature/NewFeature`).
5. Open a Pull Request.

---

**Developed as a Computer Science Project - 2025** 🎓
*This system demonstrates advanced data structure usage and object-oriented design in C++.*
