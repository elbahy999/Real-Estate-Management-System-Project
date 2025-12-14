#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include "DCLL.h"
#include "Property.h"
using namespace std;

class Neighborhood {
private:
    string name;
    int propertyCount;
    double totalValue;
    DCLL<Property>* properties;

public:
    Neighborhood(const string& neighborhoodName)
        : name(neighborhoodName), propertyCount(0), totalValue(0.0),
        properties(new DCLL<Property>()) {
    }

    ~Neighborhood() {
        delete properties;
    }

    const string& getName() const {
        return name;
    }

    int getPropertyCount() const {
        return propertyCount;
    }

    double getAveragePrice() const {
        return (propertyCount == 0) ? 0.0 : totalValue / propertyCount;
    }

    DCLL<Property>& getProperties() const {
        return *properties;
    }

    void addProperty(const Property& p) {
        properties->insert(p);
        totalValue += p.getPrice();
        propertyCount++;
    }

    void removeProperty(int propertyID) {
        Property* propToRemove = properties->search(propertyID);
        double priceToRemove = propToRemove->getPrice();
        properties->remove(propertyID);
        totalValue -= priceToRemove;
        propertyCount--;
    }

    Property* searchProperty(int propertyID) const {
        return properties->search(propertyID);
    }

    void displayProperties() const {
        cout << "\n--- Neighborhood: " << name << " ---" << endl;
        cout << "Property Count: " << propertyCount << endl;
        cout << "Average Price: $" << getAveragePrice() << endl;

        if (properties->isEmpty()) {
            cout << "  (No properties)" << endl;
        }
        else {
            properties->traverse([](const Property& p) {
                cout << "  ID: " << p.getPropertyID()
                    << ", Price: $" << p.getPrice() << endl;
                });
        }
    }

    int getPropertyID() const {
        return 0;
    }
};
