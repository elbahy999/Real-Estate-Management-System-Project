#pragma once

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
using namespace std;
template<typename Ty>
struct PropertyNode {
    Ty data;
    PropertyNode<Ty>* next;
    PropertyNode<Ty>* prev;

    PropertyNode(const Ty& prop) : data(prop), next(nullptr), prev(nullptr) {}
};
template <typename T>
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

        }
        else {
            newNode->next = tail->next;
            newNode->prev = tail;
            tail->next->prev = newNode;
            tail->next = newNode;
            tail = newNode;    // insert at end
        }

        count++;
    }

    void remove(int propertyID) {
        if (tail == nullptr)
            throw std::runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            if (current->data.getPropertyID() == propertyID) {

                if (count == 1) {
                    delete current;
                    tail = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;

                    if (current == tail)
                        tail = current->prev;

                    delete current;
                }

                count--;
                return;     // VERY IMPORTANT
            }

            current = current->next;

        } while (current != tail->next);

        throw std::runtime_error("Property ID not found");
    }

    T* search(int propertyID) const {
        if (tail == nullptr)
            throw std::runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            if (current->data.getPropertyID() == propertyID)
                return &(current->data);

            current = current->next;

        } while (current != tail->next);

        throw std::runtime_error("Property ID not found");
    }

    void traverse(void (*func)(const T&)) const {
        if (tail == nullptr)
            throw std::runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            func(current->data);
            current = current->next;

        } while (current != tail->next);
    }

    int get_Count() const {
        return count;
    }

    PropertyNode<T>* get_tail() {
        return tail;
    }
};

#pragma once

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
using namespace std;
template<typename Ty>
struct PropertyNode {
    Ty data;
    PropertyNode<Ty>* next;
    PropertyNode<Ty>* prev;

    PropertyNode(const Ty& prop) : data(prop), next(nullptr), prev(nullptr) {}
};
template <typename T>
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

        }
        else {
            newNode->next = tail->next;
            newNode->prev = tail;
            tail->next->prev = newNode;
            tail->next = newNode;
            tail = newNode;    // insert at end
        }

        count++;
    }

    void remove(int propertyID) {
        if (tail == nullptr)
            throw std::runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            if (current->data.getPropertyID() == propertyID) {

                if (count == 1) {
                    delete current;
                    tail = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;

                    if (current == tail)
                        tail = current->prev;

                    delete current;
                }

                count--;
                return;     // VERY IMPORTANT
            }

            current = current->next;

        } while (current != tail->next);

        throw std::runtime_error("Property ID not found");
    }

    T* search(int propertyID) const {
        if (tail == nullptr)
            throw std::runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            if (current->data.getPropertyID() == propertyID)
                return &(current->data);

            current = current->next;

        } while (current != tail->next);

        throw std::runtime_error("Property ID not found");
    }

    void traverse(void (*func)(const T&)) const {
        if (tail == nullptr)
            throw std::runtime_error("List is empty");

        PropertyNode<T>* current = tail->next;

        do {
            func(current->data);
            current = current->next;

        } while (current != tail->next);
    }

    int get_Count() const {
        return count;
    }

    PropertyNode<T>* get_tail() {
        return tail;
    }
};

