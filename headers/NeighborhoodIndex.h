#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "DCLL.h"
#include "Property.h"
#include "Neighborhood.h"

using namespace std;

class NeighborhoodIndex {
private:
    DCLL<Neighborhood> index;

    // Fixed: Added safety checks for empty list to prevent memory crash
    Neighborhood* findNeighborhood(const string& name) {
        if (index.isEmpty()) return nullptr;

        PropertyNode<Neighborhood>* tail = index.get_tail();
        if (tail == nullptr) return nullptr;

        PropertyNode<Neighborhood>* current = tail->next; // Start at the head
        PropertyNode<Neighborhood>* start = current;

        do {
            if (current->data.getName() == name) {
                return &(current->data);
            }
            current = current->next;
        } while (current != start);

        return nullptr;
    }

public:
    DCLL<Neighborhood>& getIndex() {
        return index;
    }

    bool isEmpty() const {
        return index.isEmpty();
    }

    PropertyNode<Neighborhood>* get_tail() const {
        return index.get_tail();
    }

    void insertNeighborhood(const string& name) {
        if (!findNeighborhood(name)) {
            Neighborhood newNeighborhood(name);
            index.insert(newNeighborhood);
            cout << "Neighborhood '" << name << "' created." << endl;
        }
        else {
            cout << "Neighborhood '" << name << "' already exists." << endl;
        }
    }

    void addPropertyToNeighborhood(const Property& p) {
        Neighborhood* n = findNeighborhood(p.getNeighborhoodName());

        // If neighborhood doesn't exist, create it automatically
        if (!n) {
            insertNeighborhood(p.getNeighborhoodName());
            n = findNeighborhood(p.getNeighborhoodName());
        }

        if (n) {
            n->addProperty(p);
            cout << "Property ID " << p.getPropertyID()
                << " added to '" << p.getNeighborhoodName() << "'." << endl;
        }
    }

    void removePropertyFromNeighborhood(int propertyID, const string& neighborhoodName) {
        Neighborhood* n = findNeighborhood(neighborhoodName);
        if (!n) {
            throw runtime_error("No neighborhood found: " + neighborhoodName);
        }
        n->removeProperty(propertyID);
        cout << "Property ID " << propertyID << " removed from '"
            << neighborhoodName << "'." << endl;
    }

    void displayAll() const {
        cout << "\n========================================" << endl;
        cout << "    ALL NEIGHBORHOODS" << endl;
        cout << "========================================" << endl;

        if (index.isEmpty()) {
            cout << "(No neighborhoods)" << endl;
            return;
        }

        index.traverse([](const Neighborhood& n) {
            n.displayProperties();
            });
    }

    void displayNeighborhood(const string& name) {
        Neighborhood* n = findNeighborhood(name);
        if (n) {
            n->displayProperties();
        }
        else {
            cout << "Neighborhood '" << name << "' not found." << endl;
        }
    }

    // Fixed: Added safety check for empty list
    Property* searchPropertyGlobal(int propertyID, string& foundInNeighborhood) {
        if (index.isEmpty()) return nullptr;

        PropertyNode<Neighborhood>* tail = index.get_tail();
        if (!tail) return nullptr;

        PropertyNode<Neighborhood>* current = tail->next;
        PropertyNode<Neighborhood>* start = current;

        do {
            try {
                Property* prop = current->data.searchProperty(propertyID);
                foundInNeighborhood = current->data.getName();
                return prop;
            }
            catch (const runtime_error&) {
                // Not in this neighborhood, keep looking
            }
            current = current->next;
        } while (current != start);

        return nullptr;
    }
};
