//
// Created by adifi on 28/02/2025.
//

#include "JSONSerializer.h"
#include <QJsonDocument>
#include "../logic/Book.h"
#include "../logic/Music.h"
#include "../logic/Film.h"
#include <QFile>

QJsonObject JSONSerializer::serialize(Book* libro) {
    libro->setStatus(true);
    QJsonObject libroJson;
    libroJson["type"] = "Book";
    libroJson["id"] = static_cast<int>(libro->getId());
    libroJson["title"] = QString::fromStdString(libro->getTitle());
    libroJson["author"] = QString::fromStdString(libro->getAuthor());
    libroJson["genre"] = QString::fromStdString(libro->getGenre());
    libroJson["pages"] = static_cast<int>(libro->getPages());
    libroJson["year"] = static_cast<int>(libro->getYear());
    libroJson["description"] = QString::fromStdString(libro->getDescription());
    return libroJson;
}

QJsonObject JSONSerializer::serialize(Music* music) {
    music->setStatus(true);
    QJsonObject musicaJson;
    musicaJson["type"] = "Music";
    musicaJson["id"] = static_cast<int>(music->getId());
    musicaJson["title"] = QString::fromStdString(music->getTitle());
    musicaJson["singer"] = QString::fromStdString(music->getSinger());
    musicaJson["durata"] = static_cast<int>(music->getTime());
    musicaJson["year"] = static_cast<int>(music->getYear());
    musicaJson["description"] = QString::fromStdString(music->getDescription());
    return musicaJson;
}

QJsonObject JSONSerializer::serialize(Film* film) {
    film->setStatus(true);
    QJsonObject filmJson;
    filmJson["type"] = "Film";
    filmJson["id"] = static_cast<int>(film->getId());
    filmJson["title"] = QString::fromStdString(film->getTitle());
    filmJson["genre"] = QString::fromStdString(film->getGenre());
    filmJson["durata"] = static_cast<int>(film->getTime());
    filmJson["year"] = static_cast<int>(film->getYear());
    filmJson["description"] = QString::fromStdString(film->getDescription());
    return filmJson;
}

Item* JSONSerializer::deserialize(const QJsonObject& obj) {
    if (obj["type"].toString() == "Book") {
        Book* book = new Book(obj["title"].toString().toStdString(), obj["author"].toString().toStdString(), obj["genre"].toString().toStdString(), obj["pages"].toInt(), obj["year"].toInt(), obj["description"].toString().toStdString());
        book->setId(obj["id"].toInt());
        Item::setIdCount(book->getId()+1);
        return book;
    }
    if (obj["type"].toString() == "Music") {
        Music* music = new Music(obj["title"].toString().toStdString(), obj["description"].toString().toStdString(), obj["singer"].toString().toStdString(), obj["year"].toInt(), obj["durata"].toInt());
        music->setId(obj["id"].toInt());
        Item::setIdCount(music->getId()+1);
        return music;
    }
    if (obj["type"].toString() == "Film") {
        Film* film = new Film(obj["title"].toString().toStdString(), obj["description"].toString().toStdString(), obj["genre"].toString().toStdString(), obj["year"].toInt(), obj["durata"].toInt());
        film->setId(obj["id"].toInt());
        Item::setIdCount(film->getId()+1);
        return film;
    }
    throw std::invalid_argument("Invalid JSON object");
}

