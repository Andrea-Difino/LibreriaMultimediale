//
// Created by ANDREA on 15/12/2024.
//

#include "Item.h"

unsigned int Item::idCount = 0;

Item::Item(const std::string& t, unsigned int y,const std::string& des = "", const std::string& img_path = ""): title(t), description(des.empty() ? "Nessuna Descrizione" : des), year(y), image_path(img_path){
    id = idCount++;
}

std::string Item::getTitle() const {return title;}

std::string Item::getDescription() const {return description;}

unsigned int Item::getYear() const {return year;}

void Item::setTitle(std::string t) {title = t;}

void Item::setDescription(std::string d) {description = d;}

void Item::setYear(unsigned int y) {year = y;}

unsigned int Item::getId() const {return id;}

unsigned int Item::getIdCount() {return idCount;}

void Item::setIdCount(unsigned int v) {idCount = v;}

void Item::setImagePath(std::string path) { this->image_path = path;}

void Item::setId(unsigned int id) {this->id = id;}

void Item::setStatus(bool status) {isSaved = status;}

bool Item::getStatus() const { return isSaved;}

void Item::setLiked(bool l) {is_liked = l;}

bool Item::isLiked() const {return is_liked;}

std::string Item::getImagePath() const { return image_path;}


