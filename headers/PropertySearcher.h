#pragma once
#include <stdexcept>
#include "NeighborhoodIndex.h"
#include "Property.h"
#include <string>
#include "DCLL.h" 

// 1. Removed "template <typename t>" because this class relies 
//    specifically on NeighborhoodIndex and Neighborhood structure.

class PropertySearcher {
private:
    NeighborhoodIndex* index;

public:
    PropertySearcher(NeighborhoodIndex* neighborhoodIndex)
        : index(neighborhoodIndex) {
    }

    // Function 1: Search Property by ID (Your existing code)
    Property* searchByID(int propertyID) {
        PropertyNode<Neighborhood>* tail = index->get_tail();

        if (tail == nullptr) {
            return nullptr;
        }

        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        // Check first neighborhood
        try {
            DCLL<Property>& properties = current->data.getProperties();
            Property* found = properties.search(propertyID);
            return found;
        }
        catch (const runtime_error&) {
            // Not in first neighborhood
        }
        current = current->next;

        // Search remaining neighborhoods
        while (current != start) {
            try {
                DCLL<Property>& properties = current->data.getProperties();
                Property* found = properties.search(propertyID);
                return found;
            }
            catch (const runtime_error&) {
                // Property not found in this neighborhood, continue
            }
            current = current->next;
        }
        return nullptr;
    }

    // Function 2: Search Properties by Neighborhood Name
    // Returns a pointer to the sub-list (DCLL) of properties
    DCLL<Property>* SearchPropertiesByNeighborhood(const string& neighborhoodName) {
        PropertyNode<Neighborhood>* tail = index->get_tail();

        if (tail == nullptr) {
            return nullptr;
        }

        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        // 1. Check first neighborhood manually (Same logic as searchByID)
        if (current->data.getName() == neighborhoodName) {
            // Return the address of the list so we don't make a copy
            return &(current->data.getProperties());
        }

        current = current->next;

        // 2. Loop through remaining neighborhoods (Same logic as searchByID)
        while (current != start) {
            if (current->data.getName() == neighborhoodName) {
                return &(current->data.getProperties());
            }
            current = current->next;
        }
        return nullptr; // Neighborhood not found
  }
     // Function 3: Search Properties by Price Range
    DCLL<Property>* searchByPriceRange(double minPrice, double maxPrice) {
        DCLL<Property>* results = new DCLL<Property>();

        if (index == nullptr) return results;

        // --- OUTER LOOP (Neighborhoods) ---
        PropertyNode<Neighborhood>* tail = index->get_tail();

        if (tail == nullptr) {
            return results;
        }

        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        do {
            DCLL<Property>& props = current->data.getProperties();

            // --- INNER LOOP (Properties) ---
            if (!props.isEmpty()) {
                // We declare new variables here with the SAME names. 
                // They only exist inside this 'if' block.
                PropertyNode<Property>* tail = props.get_tail();
                PropertyNode<Property>* start = tail->next;
                PropertyNode<Property>* current = start;

                do {
                    double price = current->data.getPrice();

                    if (price >= minPrice && price <= maxPrice) {
                        results->insert(current->data);
                    }
                    current = current->next;
                } while (current != start);
            }
            // Back in the outer loop, 'current' refers to the Neighborhood node again
            current = current->next;
        } while (current != start);

        return results;
    }

    void traverseAllProperties() {
        if (index == nullptr) return;
        PropertyNode<Neighborhood>* tail = index->get_tail();
        if (tail == nullptr) {
            cout << "No neighborhoods." << endl;
            return;
        }

        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        while (current != nullptr) {
            cout << "Neighborhood: " << current->data.getName() << endl;
            DCLL<Property>& props = current->data.getProperties();

            if (!props.isEmpty()) {
                PropertyNode<Property>* tail = props.get_tail();
                PropertyNode<Property>* start = tail->next;
                PropertyNode<Property>* current = start;

                while (current != nullptr) {
                    cout << "   ID: " << current->data.getPropertyID()
                        << ", Price: " << current->data.getPrice() << endl;

                    current = current->next;
                    if (current == start) break;
                }
            }
            else {
                cout << "   (No properties)" << endl;
            }

            current = current->next;
            if (current == start) break;
        }
    }
};
