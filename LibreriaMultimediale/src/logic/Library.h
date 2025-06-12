//
// Created by ANDREA on 26/12/2024.
//

#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "Item.h"

class Library {
public:
    Library() = default;
    ~Library();

    void addItem(Item *item);
    void removeLastItem();
    void removeItemById(unsigned id);

    Item *getItem(unsigned int id) const;
    bool getStatus() const;
    int getSize() const;
    std::vector<Item*>& getVector();

    void setStatus(bool status);

    void applyVisitor(VisitorInterface *visitor);
private:
    std::vector<Item*> items;
    static bool isLibrarySaved;
};


#endif //LIBRARY_H
