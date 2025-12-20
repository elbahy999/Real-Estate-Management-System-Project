#include <iostream>
#include <string>
#include <limits>
#include "DCLL.h"
#include "Property.h"
#include "NeighborhoodIndex.h"
#include "FileManager.h"
#include "PropertySearcher.h"
#include "CRUD.h"
#include "PropertyAnalytics.h"

using namespace std;

// --- UI Function Declaration ---
void showMenu();
void handleUserInterface(DCLL<Property>& masterList, NeighborhoodIndex& index);

int main() {
    DCLL<Property> masterList;
    NeighborhoodIndex index;

    // 1. Initial Load: Automatically load data from file if it exists
    cout << "Initializing system..." << endl;
    FileManager::loadProperties(masterList, "database.txt");

    // Sync the master list into the Neighborhood Index
    if (!masterList.isEmpty()) {
        PropertyNode<Property>* tail = masterList.get_tail();
        PropertyNode<Property>* curr = tail->next;
        do {
            index.addPropertyToNeighborhood(curr->data);
            curr = curr->next;
        } while (curr != tail->next);
    }

    // 2. Launch UI
    handleUserInterface(masterList, index);

    // 3. Final Save: Save everything before closing
    cout << "Saving data and exiting..." << endl;
    FileManager::saveProperties(masterList, "database.txt");

    return 0;
}

void showMenu() {
    cout << "\n--- REAL ESTATE MANAGEMENT SYSTEM ---" << endl;
    cout << "1. Add New Property" << endl;
    cout << "2. Remove Property" << endl;
    cout << "3. Search Property by ID" << endl;
    cout << "4. Filter Properties by Price Range" << endl;
    cout << "5. Show Neighborhood Statistics" << endl;
    cout << "6. Display Complete Analytics Report" << endl;
    cout << "7. Save Current Data" << endl;
    cout << "0. Exit" << endl;
    cout << "Select an option: ";
}

void handleUserInterface(DCLL<Property>& masterList, NeighborhoodIndex& index) {
    PropertySearcher searcher(&index);
    PropertyAnalytics analytics;
    int choice;

    do {
        showMenu();
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number: ";
        }

        switch (choice) {
        case 1: { // ADD
            int id; double price; string neighborhood;
            cout << "Enter Property ID: "; cin >> id;
            cout << "Enter Price: "; cin >> price;
            cout << "Enter Neighborhood Name: ";
            cin.ignore(); getline(cin, neighborhood);
            AddProperty(masterList, index, id, price, neighborhood);
            break;
        }
        case 2: { // REMOVE
            int id;
            cout << "Enter Property ID to remove: "; cin >> id;
            RemoveProperty(masterList, index, id);
            break;
        }
        case 3: { // SEARCH ID
            int id;
            cout << "Enter ID to search: "; cin >> id;
            Property* p = searcher.searchByID(id);
            if (p) cout << "Found: " << p->getNeighborhoodName() << " - $" << p->getPrice() << endl;
            else cout << "Property not found." << endl;
            break;
        }
        case 4: { // RANGE
            double minP, maxP;
            cout << "Min price: "; cin >> minP;
            cout << "Max price: "; cin >> maxP;
            analytics.displayPropertiesInRange(masterList, minP, maxP);
            break;
        }
        case 5: { // STATS
            analytics.displayNeighborhoodStats(index);
            break;
        }
        case 6: { // FULL REPORT
            analytics.displayCompleteReport(masterList, index);
            break;
        }
        case 7: { // MANUAL SAVE
            FileManager::saveProperties(masterList, "database.txt");
            cout << "Data saved to database.txt" << endl;
            break;
        }
        }
    } while (choice != 0);
}
