#pragma once
#include <stdexcept>
#include "NeighborhoodIndex.h"
#include "Property.h"
#include <string>
#include "DCLL.h" 

class PropertySearcher {
private:
    NeighborhoodIndex* index;

public:
    PropertySearcher(NeighborhoodIndex* neighborhoodIndex)
        : index(neighborhoodIndex) {
    }

    // Function 1: Search Property by ID 
    Property* searchByID(int propertyID) {
        //f that takes a property ID & returns a pointer to a Property
        PropertyNode<Neighborhood>* tail = index->get_tail();
        //A pointer to a node that stores a Neighborhood.
        if (tail == nullptr) {
            return nullptr;
        }

        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        // Check first neighborhood
        try {
            DCLL<Property>& properties = current->data.getProperties();
            //refrance of property list
            
            Property* found = properties.search(propertyID);
            return found;
        }
        catch (const runtime_error&) {
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
            }
            current = current->next;
        }
        return nullptr;
    }

    // Returns a pointer to the list DCLL of properties
    //function 2
    DCLL<Property>* SearchPropertiesByNeighborhood(const string& neighborhoodName) {
        PropertyNode<Neighborhood>* tail = index->get_tail();

        if (tail == nullptr) {
            return nullptr;
        }

        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        if (current->data.getName() == neighborhoodName) {
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
        return nullptr; 
    }
    // Function 3: Search Properties by Price Range
    DCLL<Property>* searchByPriceRange(double minPrice, double maxPrice) {
        DCLL<Property>* results = new DCLL<Property>();

        if (index == nullptr) return results;

        //outerloop Neighborhoods 
        PropertyNode<Neighborhood>* tail = index->get_tail();

        if (tail == nullptr) {
            return results;
        }

        PropertyNode<Neighborhood>* start = tail->next;
        PropertyNode<Neighborhood>* current = start;

        do {
            DCLL<Property>& props = current->data.getProperties();

            // innerloop Properties
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
