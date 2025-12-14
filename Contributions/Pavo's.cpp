//PAVO's code Main DCLL: A DCLL<Neighborhood> stores all unique neighborhood names within the system.
This serves as the primary index.Neighborhood Object: Each Neighborhood node contains a sub-DCLL, specifically a DCLL<Property>, 
which holds all the properties located in that specific area.Statistical Data: The Neighborhood class also tracks essential statistical data,
including the propertyCount and totalValue (sum of prices) to allow for $O(1)$ retrieval of the average property price within that neighborhood. 
template <typename Ty >
struct NeighborhoodNode {
    Ty data;
    NeighborhoodNode<Ty>* next;
    NeighborhoodNode<Ty>* prev;

    NeighborhoodNode(const Ty& neighborhood) : data(neighborhood), next(nullptr), prev(nullptr) {}
};
template <typename Ty1>
class Neighborhood {
private:
    string name;
    int propertyCount;
    double totalValue;
    vector<int> propertyIDs;
    DCLL<Property>* properties;
public:
    //consrtuctor 
    Neighborhood(const string& neighborhoodName)
        : name(neighborhoodName), propertyCount(0), totalValue(0.0) 
       , properties(new DCLL<Property>()) { }
   

    // destructor 
     ~Neighborhood() {
    delete properties;

     }
    //getter 
    const string& getName()const {
        return name;
    }

    int getPropertyCount()const {
        return propertyCount;
    }

    double getAvergePrice() const {
        return (propertyCount == 0) ? 0.0 : totalValue / propertyCount;
    }

    DCLL <Property>& getProperties()const {
        return *properties;
    }


    // ==================add
    void addproperty(const Property<Ty1>* p) {    // error  not reading the funcs
        properties.insert(p);
        totalValue += p.getPrice();
        propertyCount++;
        cout << p.getPropertyID();
    }
    //===================remove 
    void removeProperty(int propertyID) {
        Property<Ty1>* proptoremove = properties->search(propertyID);
        double pricetoremove = proptoremove->getPrice();
        properties->remove(propertyID);
        totalValue -= pricetoremove;
        propertyCount--;
        cout << propertyID;
    }
    //===================search
    bool search(NeighborhoodNode<Ty1>* head, int id) {
        NeighborhoodNode<Ty1>* current = head;
        int position = 0;
        while (current != nullptr && current->data != x) {
            position++;
            current = current->next;
            if (current == nullptr)
            {
                return false;
            }
            else {
                return true;
            }
        }
    }

    template <typename T>
    class NeighborhoodIndex {
    private:
        DCLL<Neighborhood>index;
        Neighborhood <T>* findNeighborhood(const string& name) {
            if (index.get_Count() == 0) {
                return nullptr;
            }PropertyNode<Neighborhood>* current = index.get_tail();
            do {
                if (current->data.getName() == name)  // error  not reading the funcs
                {
                    return current->data;
                }
                current = current->next;
            } while (current != index.tail->next) {
                return nullptr;
            }
        }
    public:
        void insertNeighborhood(const string & name) {
            if (findNeighborhood(name) == null) {
                Neighborhood newN(name);
                index.insert(newN);
            }
        }
        void addPropN(const Property <T>*  p ) {
            Neighborhood<T>* n = findNeighborhood(p.getneighborhoodName()); // error  not reading the funcs
            if (n == nullptr){
            
                insertNeighborhood(p.getneighborhoodName());
                n = findNeighborhood()
            }
            n->addproperty(p);
        }
    };

    //========== 
    void removepropfromNeighborhood(int propertyID, const string& neighborhoodName) {
        Neighborhood<T>* n = findNeighborhood(neighborhoodName());
        if (n == nullptr) {
            throw runtime_error(" No neighborhood found");
        } n->removeProperty(propertyID);
    }
};
