#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "DCLL.h"
#include "Property.h"
#include "Neighborhood.h"
#include "NeighborhoodIndex.h"

using namespace std;

class PropertyAnalytics {
public:

    // extraction and sorting
    vector<Property> getSortedProperties(DCLL<Property>& list, bool ascending) {
        vector<Property> vec;

        if (list.isEmpty()) {
            return vec;
        }

        PropertyNode<Property>* tail = list.get_tail();
        PropertyNode<Property>* start = tail->next; 
        PropertyNode<Property>* current = start;

        // extract data using a while loop
        bool finished = false;
        while (!finished) {
            vec.push_back(current->data);
            current = current->next;
            if (current == start) {
                finished = true;
            }
        }

        // manual bubble sort
        int n = vec.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                bool shouldSwap = false;
                if (ascending) {
                    if (vec[j].getPrice() > vec[j + 1].getPrice()) {
                        shouldSwap = true;
                    }
                }
                else {
                    if (vec[j].getPrice() < vec[j + 1].getPrice()) {
                        shouldSwap = true;
                    }
                }

                if (shouldSwap) {
                    Property temp = vec[j];
                    vec[j] = vec[j + 1];
                    vec[j + 1] = temp;
                }
            }
        }
        return vec;
    }

    // display sorted properties 
    void displaySortedProperties(DCLL<Property>& fullList, bool ascending) {
        cout << "\nproperties sorted by price ";
        if (ascending) {
            cout << "(ascending)" << endl;
        }
        else {
            cout << "(descending)" << endl;
        }

        vector<Property> sorted = getSortedProperties(fullList, ascending);

        if (sorted.empty()) {
            cout << "(no properties to display)" << endl;
            return;
        }

        for (int i = 0; i < sorted.size(); i++) {
            cout << "id: " << sorted[i].getPropertyID()
                << " price: $" << sorted[i].getPrice()
                << " area: " << sorted[i].getNeighborhoodName() << endl;
        }
        cout << "\ntotal properties: " << sorted.size() << endl;
    }

    // display by neighborhood
    void displayByNeighborhood(NeighborhoodIndex& index) {
        cout << "\nproperties by neighborhood" << endl;
        index.displayAll();
    }

    // neighborhood statistics
    void displayNeighborhoodStats(NeighborhoodIndex& index) {
        cout << "\nneighborhood statistics" << endl;

        if (index.isEmpty()) {
            cout << "no neighborhoods found." << endl;
            return;
        }

        DCLL<Neighborhood>& neighborhoods = index.getIndex();
        PropertyNode<Neighborhood>* tail = neighborhoods.get_tail();
        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        bool finished = false;
        while (!finished) {
            Neighborhood& n = current->data;
            cout << "\nneighborhood: " << n.getName() << endl;
            cout << "total properties: " << n.getPropertyCount() << endl;
            cout << "average price: $" << n.getAveragePrice() << endl;

            DCLL<Property>& props = n.getProperties();
            if (!props.isEmpty()) {
                // inner scope: using simplified names for properties
                PropertyNode<Property>* innerTail = props.get_tail();
                PropertyNode<Property>* innerStart = innerTail->next;
                PropertyNode<Property>* innerCurrent = innerStart;

                double maxPrice = innerCurrent->data.getPrice();
                double minPrice = innerCurrent->data.getPrice();

                bool innerFinished = false;
                while (!innerFinished) {
                    double price = innerCurrent->data.getPrice();
                    if (price > maxPrice) {
                        maxPrice = price;
                    }
                    if (price < minPrice) {
                        minPrice = price;
                    }
                    innerCurrent = innerCurrent->next;
                    if (innerCurrent == innerStart) {
                        innerFinished = true;
                    }
                }
                cout << "most expensive: $" << maxPrice << endl;
                cout << "least expensive: $" << minPrice << endl;
            }

            current = current->next;
            if (current == start) {
                finished = true;
            }
        }
    }

    // complete report
    void displayCompleteReport(DCLL<Property>& fullList, NeighborhoodIndex& index) {
        displaySortedProperties(fullList, true);
        displayByNeighborhood(index);

        cout << "\nsummary statistics " << endl;

        int totalProperties = fullList.get_Count();
        cout << "total properties in system: " << totalProperties << endl;

        if (totalProperties > 0) {
            vector<Property> allProps = getSortedProperties(fullList, true);

            double totalValue = 0;
            for (int i = 0; i < allProps.size(); i++) {
                totalValue += allProps[i].getPrice();
            }

            cout << "total market value: $" << totalValue << endl;
            cout << "average property price: $" << (totalValue / totalProperties) << endl;

            cout << "cheapest property: $" << allProps[0].getPrice();
            cout << " (id: " << allProps[0].getPropertyID() << ")" << endl;

            cout << "most expensive property: $" << allProps[totalProperties - 1].getPrice();
            cout << " (id: " << allProps[totalProperties - 1].getPropertyID() << ")" << endl;
        }
    }

    // display properties in price range
    void displayPropertiesInRange(DCLL<Property>& list, double minPrice, double maxPrice) {
        cout << "\nproperties in range $" << minPrice << " - $" << maxPrice << endl;

        if (list.isEmpty()) {
            cout << "(no properties)" << endl;
            return;
        }

        PropertyNode<Property>* tail = list.get_tail();
        PropertyNode<Property>* start = tail->next;
        PropertyNode<Property>* current = start;

        int count = 0;
        bool finished = false;
        while (!finished) {
            double price = current->data.getPrice();
            if (price >= minPrice) {
                if (price <= maxPrice) {
                    cout << "id: " << current->data.getPropertyID()
                        << " price: $" << price
                        << " area: " << current->data.getNeighborhoodName() << endl;
                    count++;
                }
            }
            current = current->next;
            if (current == start) {
                finished = true;
            }
        }
        cout << "\nproperties found: " << count << endl;
    }
};
