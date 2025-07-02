//
// Created by ANDREA on 17/12/2024.
//

#include "Music.h"
#include <iomanip>
#include <iostream>

Music::Music(const std::string& tit,const std::string& des,const std::string& sing, unsigned int y, unsigned int t, const std::string& img_path): Item(tit, y, des, img_path), singer(sing),
    time(t) {
}
Music::~Music() {}

void Music::setSinger(std::string sing) { singer = sing;}

void Music::setTime(unsigned int durata) { time = durata;}

unsigned int Music::getTime() const{ return time;}

std::string Music::getSinger() const { return singer;}

unsigned int Music::getHours() const { return time / 3600;}

unsigned int Music::getMinutes() const { return (time % 3600) / 60;}

unsigned int Music::getSeconds() const { return time % 60;}

std::string Music::getExtendedLength() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << getHours() << ":"
        << std::setw(2) << std::setfill('0') << getMinutes() << ":"
        << std::setw(2) << std::setfill('0') << getSeconds();

    return oss.str();
}

void Music::accept(VisitorInterface *visitor) { visitor->visit(this); }

void Music::displayInfo() const {
    std::cout << "Music:" << std::endl
            << "\tID: " << getId() << std::endl
            << "\tTitle: " << getTitle() << std::endl
            << "\tSinger: " << getSinger() << std::endl
            << "\tTime(s): " << getTime() << std::endl
            << "\tDescription: " << getDescription() << std::endl;
}
