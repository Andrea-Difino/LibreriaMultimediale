//
// Created by ANDREA on 17/12/2024.
//

#ifndef LIBRO_H
#define LIBRO_H
#include "Item.h"
#include <vector>


class Book : public Item {
public:
    explicit Book(const std::string &tit, const std::string &author, const std::string &gen, unsigned int p
        ,unsigned int y, const std::string &des);
    ~Book() override = default;

    void setAuthor(std::string auth);
    void setPages(unsigned int p);
    void setGenre(std::string gen);

    std::string getAuthor() const;
    unsigned int getPages() const;
    std::string getGenre() const;

    void displayInfo() const override;
    void accept(VisitorInterface *visitor) override;

    static std::vector<std::string> genres;
private:
    std::string author;
    unsigned int pages;
    std::string genre;

};


#endif //LIBRO_H
