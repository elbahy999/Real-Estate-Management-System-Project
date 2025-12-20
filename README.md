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

## 🛠️ Detailed Architecture & Widgets

### 🧬 Class Hierarchy & Data Flow

The system is built on a hierarchical structure where the `NeighborhoodIndex` acts as the root controller, orchestrating interactions between the global property list and localized neighborhood data.

* **Global Access**: Every property is registered in a master `DCLL<Property>` for system-wide operations like range searches.
* **Localized Access**: Properties are simultaneously indexed within specific `Neighborhood` objects to allow for area-specific statistics.
* **Automatic Synchronization**: When a property is added, the `CRUD` logic handles the insertion into both the master list and the relevant neighborhood index automatically.

---

### ⏱️ Complexity Analysis

This project prioritizes memory efficiency and manual algorithmic implementation over standard library shortcuts.

| Operation | Data Structure |  Purpose |
| --- | --- | --- |
| **Search by ID** | DCLL | Linear traversal of the circular list. |
| **Insert Property** | DCLL | Constant time insertion at the tail. |
| **Price Sorting** | Vector (Bubble) | Stable manual sorting for reporting. |
| **Neighborhood Filter** | Index Map | Nested traversal of neighborhoods and properties. |

---

### 🧪 Implementation Details: The DCLL

The **Doubly Circular Linked List** is the heart of the project. Unlike a standard list, the `tail->next` points back to the `head`, and `head->prev` points to the `tail`, allowing for seamless infinite loops—perfect for a rotating real estate display.

```cpp
// Logic for Circular Traversal in the System
PropertyNode<T>* current = tail->next; // Start at Head
do {
    // Perform Operation (Display, Search, or Calculate)
    current = current->next;
} while (current != tail->next); // Stop when we return to Head

```
---

## 📋 What to Copy (Final Checklist)

To ensure your repository is perfect, copy these files exactly as follows:

1. **README.md**: Copy the entire text from my previous response and this response combined into a single file.
2. **The Headers**: Ensure all 8 headers (`DCLL.h`, `Neighborhood.h`, `NeighborhoodIndex.h`, `Property.h`, `FileManager.h`, `PropertySearcher.h`, `CRUD.h`, `PropertyAnalytics.h`) are in the root directory.
3. **The Main**: Copy the `main.cpp` code (the Controller and UI logic) into a file named `main.cpp` or `Source.cpp`.
4. **The Database**: You don't need to copy this; the program will create `database.txt` automatically the first time you save.

---
### 👥 Project Development Team

| Name | GitHub Handle | Header / Module Contribution |
| --- | --- | --- |
| **Zyad Akram** | @[Username1] | **(Base Data Structure & Templates)**: `DCLL.h` |
| **[Name 2]** | @[Username2] | **Data Modeler**: `Property.h` & `Neighborhood.h` |
| **[Name 3]** | @[Username3] | **Index Engineer**: `NeighborhoodIndex.h` |
| **Mohamed Ehab** | @[Username4] | **Persistence Specialist**: `FileManager.h` |
| **Ziad Mohamed** | @[Username4] | **Persistence Specialist**: `CRUD.h` |
| **Rodaina Agha** | @[Username5] | **Logic Controller**: `PropertySearcher.h` |
| **Ziad El-Bahy** | @elbahy999 | **Analytics & UI**: `PropertyAnalytics.h` & `main.cpp` |

---

### 🛠️ Technical Details Section

You can also add this section to describe the "Access Violation" fix we implemented, which shows high-level technical proficiency:

#### 🛡️ Memory Safety & Stability

During development, the team identified and resolved a critical **Access Violation (0xc0000005)** error.

* **The Challenge**: Using raw pointers for nested `DCLL` objects caused dangling pointers during object copying.
* **The Solution**: Transitioned the `Neighborhood` class to use direct object membership rather than heap-allocated pointers, ensuring automatic memory management and stack stability.

---

### ⚖️ MIT License

Create a file named `LICENSE` and paste the following, ensuring you update the year and name:

```text
MIT License

Copyright (c) 2025 [Your Team Name or Your Name]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

```

Would you like me to help you format a **"How to Run"** GIF or a screenshot placeholder for your final repository?
---
