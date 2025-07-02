//
// Created by ANDREA on 17/12/2024.
//

#include "Book.h"

#include <iostream>
#include <ostream>

Book::Book(const std::string &tit, const std::string &author, const std::string &gen, unsigned int p,
             unsigned int y, const std::string &des, const std::string& img_path) : Item(tit, y, des, img_path), author(author), pages(p), genre(gen){}

std::string Book::getAuthor() const { return author; }

unsigned int Book::getPages() const { return pages; }

std::string Book::getGenre() const { return genre; }

void Book::setAuthor(std::string auth) { this->author = auth; }

void Book::setGenre(std::string gen) { this->genre = gen; }

void Book::setPages(unsigned int p) { this->pages = p; }

void Book::accept(VisitorInterface *visitor) { visitor->visit(this); }

void Book::displayInfo() const {
    std::cout << "Libro:" << std::endl
            << "\tID: " << getId() << std::endl
            << "\tTitle: " << getTitle() << std::endl
            << "\tAuthor: " << getAuthor() << std::endl
            << "\tGenre: " << getGenre() << std::endl
            << "\tPages: " << getPages() << std::endl
            << "\tDescription: " << getDescription() << std::endl;
}

std::vector<std::string> Book::genres = {
    "Narrativa",
    "Giallo",
    "Fantascienza",
    "Fantasy",
    "Horror",
    "Romanzo Storico",
    "Saggio",
    "Poesia",
    "Teatro",
    "Biografia",
    "Avventura",
    "Thriller",
    "Young Adult",
    "Distopico",
    "Mitologia",
    "Romanzo",
    "Classico"
};