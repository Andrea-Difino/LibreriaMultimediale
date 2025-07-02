//
// Created by ANDREA on 17/12/2024.
//

#include "Film.h"

#include <iomanip>
#include <iostream>

Film::Film(const std::string& title,const std::string& des,const std::string& g, unsigned int year,unsigned int time, const std::string& img_path) : Item(title, year, des, img_path), genre(g), time(time) {}

std::string Film::getGenre() const{ return genre;}

unsigned int Film::getTime() const{ return time;}

unsigned int Film::getHours() const { return time / 3600;}

unsigned int Film::getMinutes() const { return (time % 3600) / 60;}

unsigned int Film::getSeconds() const { return time % 60;}

void Film::setGenre(const std::string &g) { genre = g;}

void Film::setTime(unsigned int seconds){ time = seconds;}

void Film::accept(VisitorInterface *visitor) { visitor->visit(this);}

std::string Film::getExtendedLength() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << getHours() << ":"
        << std::setw(2) << std::setfill('0') << getMinutes() << ":"
        << std::setw(2) << std::setfill('0') << getSeconds();

    return oss.str();
}

void Film::displayInfo() const {
    std::cout << "Film:" << std::endl
            << "\tID: " << getId() << std::endl
            << "\tTitle: " << getTitle() << std::endl
            << "\tGenre: " << getGenre() << std::endl
            << "\tTime(s): " << getTime() << std::endl
            << "\tDescription: " << getDescription() << std::endl;
}

std::vector<std::string> Film::tipology = {
    "Azione",
    "Avventura",
    "Animazione",
    "Biografico",
    "Commedia",
    "Crimine",
    "Documentario",
    "Drammatico",
    "Fantasy",
    "Storico",
    "Horror",
    "Musical",
    "Mistero",
    "Romantico",
    "Fantascienza",
    "Sportivo",
    "Thriller",
    "Guerra",
    "Western"
};
