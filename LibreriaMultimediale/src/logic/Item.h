//
// Created by ANDREA on 15/12/2024.
//

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "VisitorInterface.h"

class Item {
public:
    explicit Item(const std::string& titolo, unsigned int year,const std::string& des);
    virtual ~Item() = default;

    std::string getTitle() const;
    std::string getDescription() const;
    unsigned int getYear() const;
    unsigned int getId() const;
    static unsigned int getIdCount();
    static void setIdCount(unsigned v);
    bool getStatus() const;

    void setTitle(std::string t);
    void setDescription(std::string d);
    void setYear(unsigned int y);
    void setId(unsigned int id);
    void setStatus(bool status);

    virtual void displayInfo() const = 0;

    virtual void accept(VisitorInterface *visitor) = 0;
private:
    std::string title;
    std::string description;
    unsigned int year;
    unsigned int id;
    static unsigned int idCount;
    bool isSaved = false;
};


#endif //ITEM_H
