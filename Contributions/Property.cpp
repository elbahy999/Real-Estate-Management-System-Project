
class Property {
private:
    int propertyID;
    double price;
    string neighborhoodName;

public:
    Property(int id, double pr, const std::string& name) 
        : propertyID(id), price(pr), neighborhoodName(name) {}

    int getPropertyID() const { return propertyID; }
    double getPrice() const { return price; }
    const string& getNeighborhoodName() const { return neighborhoodName; }

    void display() const {
        cout << "  [Property ID: " << propertyID 
                  << ", Price: $" << fixed << std::setprecision(2) << price << "]" << endl;
    }
};
