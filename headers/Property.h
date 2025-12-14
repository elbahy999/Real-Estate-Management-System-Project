#pragma once
#include <string>
#include <iostream>
using namespace std;
class Property {
private:
    double price;
    int id;
    string neighborhoodName;
public:
    Property(int id, double pr, const string& name) :price(pr), id(id), neighborhoodName(name) {}
    int get_Property_ID()const { return id; }
    double get_Price()const { return price; }
    string  get_neighborhood_Name() { return neighborhoodName; }
};

