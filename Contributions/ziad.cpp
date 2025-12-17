#pragma once
#include <iostream>
#include "DCLL.h"
#include "Property.h"
#include "Neighborhood.h"
#include "NeighborhoodIndex.h"
using  namespace std;
bool PropertyExists(DCLL<Property>& propertyList, int propertyID) {
    try
    {
        propertyList.search(propertyID);
        return true;
    }
    catch (...) {
        return false;
    }
}
bool IsvalidPropertyData(int propertyID, double price, const string& neighborhoodName)

{ 
if (propertyID <= 0)
return false;

if (price <= 0)
return false;
if (neighborhoodName == "")
return false;

return true;
}
void AddProperty(DCLL<Property>& propertyList, NeighborhoodIndex& neighborhoodIndex, int propertyID, double price,const string& neighborhoodName)
{
    if (!IsvalidPropertyData(propertyID, price, neighborhoodName)) {
        return;
    }
    if (PropertyExists(propertyList, propertyID)) {
        return;
    }
    Property newProperty(propertyID, price, neighborhoodName);
    propertyList.insert(newProperty);
    neighborhoodIndex.addPropertyToNeighborhood(newProperty);

 }
void RemoveProperty(DCLL<Property>& propertyList,NeighborhoodIndex& neighborhoodIndex,int propertyID) 
{
    if (!PropertyExists(propertyList, propertyID)) 
    {
        return;
    }
    Property*propertyToRemove = propertyList.search(propertyID);
    string neighborhoodName = propertyToRemove->getNeighborhoodName();
     propertyList.remove(propertyID);
     neighborhoodIndex.removePropertyFromNeighborhood(propertyID, neighborhoodName);

}
