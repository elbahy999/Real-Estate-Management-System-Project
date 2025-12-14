
#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "DCLL.h"
#include "Property.h"
#include "neighborhood.h"
using namespace std;

template <typename Ty>
class NeighborhoodIndex {
private:
    DCLL<Neighborhood<Ty>> index;

    Neighborhood<Ty>* findNeighborhood(const string& name) {
        if (index.get_Count() == 0) return nullptr;

        auto* current = index.get_tail();
        do {
            if (current->data.getName() == name) {
                return &current->data;
            }
            current = current->next;
        } while (current != index.get_tail());

        return nullptr;
    }

public:
    void insertNeighborhood(const string& name) {
        if (!findNeighborhood(name)) {
            index.insert(Neighborhood<Ty>(name));
        }
    }

    void addPropertyToNeighborhood(const Property<Ty>& p) {
        Neighborhood<Ty>* n = findNeighborhood(p.getNeighborhoodName());

        if (!n) {
            insertNeighborhood(p.getNeighborhoodName());
            n = findNeighborhood(p.getNeighborhoodName());
        }

        n->addProperty(p);
    }

    void removePropertyFromNeighborhood(int propertyID, const string& neighborhoodName) {
        Neighborhood<Ty>* n = findNeighborhood(neighborhoodName);
        if (!n) {
            throw runtime_error("No neighborhood found");
        }
        n->removeProperty(propertyID);
    }
};
