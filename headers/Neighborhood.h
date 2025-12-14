#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "DCLL.h"
#include "Property.h"

using namespace std;

/* ===================== Neighborhood ===================== */
template <typename Ty>
class Neighborhood {
private:
    string name;
    int propertyCount;
    double totalValue;
    DCLL<Property<Ty>> properties;

public:
    // Constructor
    Neighborhood(const string& neighborhoodName)
        : name(neighborhoodName), propertyCount(0), totalValue(0.0) {
    }

    // Getters
    const string& getName() const {
        return name;
    }

    int getPropertyCount() const {
        return propertyCount;
    }

    double getAveragePrice() const {
        return (propertyCount == 0) ? 0.0 : totalValue / propertyCount;
    }

    DCLL<Property<Ty>>& getProperties() {
        return properties;
    }

    /* ================= Add Property ================= */
    void addProperty(const Property<Ty>& p) {
        properties.insert(p);
        totalValue += p.getPrice();
        propertyCount++;
    }

    /* ================= Remove Property ================= */
    void removeProperty(int propertyID) {
        Property<Ty>* propToRemove = properties.search(propertyID);
        if (!propToRemove) {
            throw runtime_error("Property not found");
        }

        totalValue -= propToRemove->getPrice();
        properties.remove(propertyID);
        propertyCount--;
    }
};
