//
// Created by ANDREA on 26/12/2024.
//

#include "Library.h"
#include <iostream>

bool Library::isLibrarySaved = true;

Library::~Library() {
    for (Item* item : items) {
        delete item;
    }
}

void Library::addItem(Item *item) { items.push_back(item);}

void Library::removeLastItem() {
    delete items.back();
    items.pop_back();
}


void Library::removeItemById(const unsigned int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            items.erase(it);
            return;
        }
    }
}

Item* Library::getItem(const unsigned int id) const{
    for (Item* item : items) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}

void Library::applyVisitor(VisitorInterface *visitor) {
    for (Item* item : items) {
        if (!item->getStatus()) {
            item->accept(visitor);
        }
    }
}

bool Library::getStatus() const { return this->isLibrarySaved;}

void Library::setStatus(const bool status) { isLibrarySaved = status;}

int Library::getSize() const { return items.size();}

std::vector<Item *> & Library::getVector() { return items;}



