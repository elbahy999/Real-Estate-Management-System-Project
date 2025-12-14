#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "DCLL.h"
#include "Property.h"
using namespace std;

class FileManager {
public:
    static void saveProperties(DCLL<Property>& list, const string& filename) {
        fstream file(filename, ios::out | ios::trunc);
        if (!file.is_open()) {
            cerr << "Error opening file for writing!\n";
            return;
        }

        PropertyNode<Property>* tail = list.get_tail();
        if (!tail) return;

        PropertyNode<Property>* curr = tail->next;
        do {
            Property p = curr->data;

            file << p.get_Property_ID() << "|" << p.get_neighborhood_Name() << "|" << p.get_Price() << "\n";
            curr = curr->next;
        } while (curr != tail->next);

        file.close();
    }
    static void loadProperties(DCLL<Property>& list, const string& filename) {
        fstream file(filename, ios::in);
        if (!file.is_open()) {
            cerr << "Error opening file for reading!\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, priceStr;
            if (!getline(ss, idStr, '|')) continue;
            if (!getline(ss, name, '|')) continue;
            if (!getline(ss, priceStr)) continue;

            try {
                int id = stoi(idStr);
                double price = stod(priceStr);

                Property p(id, price, name);
                list.insert(p);
            }
            catch (exception& e) {
                cerr << "Error parsing line: " << line << " -> " << e.what() << endl;
                continue;
            }
        }

        file.close();
    }
};


