//Contrbutions: Zyad Mahgoub
//DCLL Class Implementation: Implement the DoublyCircularLinkedList<Property> class completely from scratch, defining the internal PropertyNode structure with *prev and *next pointers.Fundamental Operations: Implement the core $O(1)$ insertion method (insert()) and the necessary $O(N)$ removal (remove(int propertyID)) and search (search(int propertyID)) operations required by other members.Circular and Doubly Logic: Ensure the list maintains the circular properties (tail connects to head, head connects to tail) and the doubly linked properties (*prev pointers are correct) during all insert and remove operations, handling edge cases such as empty lists, single-node lists, and multi-node lists.

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

template<typename T>
struct PropertyNode {
    T data;
    PropertyNode<T>* next;
    PropertyNode<T>* prev;

    PropertyNode(const T& prop) : data(prop), next(nullptr), prev(nullptr) {}
};

template<typename T>
class DCLL {
private:
    PropertyNode<T>* tail;
    int count;

public:
    DCLL() : tail(nullptr), count(0) {}
    ~DCLL() {}

    void insert(const T& newProperty) {
        PropertyNode<T>* newNode = new PropertyNode<T>(newProperty);

        if (tail == nullptr) {
            tail = newNode;
            tail->next = tail;
            tail->prev = tail;

        } else {
            newNode->next = tail->next;
            newNode->prev = tail;
            tail->next->prev = newNode;
            tail->next = newNode;
            tail = newNode;
        }

        count++;
    }

    void remove(int propertyID) {
        if (tail == nullptr)
            throw runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            if (current->data.getPropertyID() == propertyID) {

                if (count == 1) {
                    delete current;
                    tail = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;

                    if (current == tail)
                        tail = current->prev;

                    delete current;
                }

                count--;
                return;
            }

            current = current->next;

        } while (current != tail->next);

        throw runtime_error("Property ID not found");
    }

    T* search(int propertyID) const {
        if (tail == nullptr)
            throw runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            if (current->data.getPropertyID() == propertyID)
                return &(current->data);

            current = current->next;

        } while (current != tail->next);

        throw runtime_error("Property ID not found");
    }

    void traverse(void (*func)(const T&)) const {
        if (tail == nullptr)
            throw runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            func(current->data);
            current = current->next;

        } while (current != tail->next);
    }

    int getCount() const {
        return count;
    }
};
