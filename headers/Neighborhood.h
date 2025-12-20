#pragma once
#include <iostream>
#include <string>
#include "DCLL.h"
#include "Property.h"

using namespace std;

class Neighborhood {
private:
    string name;
    int propertyCount;
    double totalValue;
    // FIXED: Changed from pointer to direct object to avoid memory crashes
    DCLL<Property> properties;

public:
    Neighborhood(const string& neighborhoodName)
        : name(neighborhoodName), propertyCount(0), totalValue(0.0) {
    }

    // No manual delete needed anymore
    ~Neighborhood() {}

    const string& getName() const { return name; }
    int getPropertyCount() const { return propertyCount; }

    double getAveragePrice() const {
        return (propertyCount == 0) ? 0.0 : totalValue / propertyCount;
    }

    // Return reference to the internal list
    DCLL<Property>& getProperties() {
        return properties;
    }

    void addProperty(const Property& p) {
        properties.insert(p);
        totalValue += p.getPrice();
        propertyCount++;
    }

    void removeProperty(int propertyID) {
        try {
            Property* propToRemove = properties.search(propertyID);
            double priceToRemove = propToRemove->getPrice();
            properties.remove(propertyID);
            totalValue -= priceToRemove;
            propertyCount--;
        }
        catch (...) {
            throw runtime_error("Property ID not found in neighborhood");
        }
    }

    Property* searchProperty(int propertyID) {
        return properties.search(propertyID);
    }

    void displayProperties() const {
        cout << "\n--- Neighborhood: " << name << " ---" << endl;
        cout << "Property Count: " << propertyCount << endl;
        cout << "Average Price: $" << getAveragePrice() << endl;

        if (properties.isEmpty()) {
            cout << "  (No properties)" << endl;
        }
        else {
            properties.traverse([](const Property& p) {
                cout << "  ID: " << p.getPropertyID()
                    << ", Price: $" << p.getPrice() << endl;
                });
        }
    }
};
