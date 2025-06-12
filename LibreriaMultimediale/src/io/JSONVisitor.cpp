//
// Created by ANDREA on 22/12/2024.
//

#include "JSONVisitor.h"
#include <QString>
#include <QDebug>
#include "../logic/Film.h"
#include "../logic/Book.h"
#include "../logic/Music.h"
#include <QFileDialog>
#include <QJsonDocument>

#include "JSONSerializer.h"
#include "../visual/ItemCard.h"
#include "../visual/MainWidget.h"


JSONVisitor::JSONVisitor(Library *lib,MainWidget* p) : library(lib), mainObserver(p) {}

void JSONVisitor::visit(Book* libro) {
    jsonArr.append(JSONSerializer::serialize(libro));
}

void JSONVisitor::visit(Film* film) {
    jsonArr.append(JSONSerializer::serialize(film));
}

void JSONVisitor::visit(Music* music) {
    jsonArr.append(JSONSerializer::serialize(music));
}

void JSONVisitor::saveToFile(){
    JSONFileHandler::saveToFile(jsonArr, JSONFileHandler::getLastDatabasePath());
}

void JSONVisitor::removeItemById(const int id) {
    JSONFileHandler::removeItemById(id, jsonArr);
}

void JSONVisitor::loadFromFile(const QString& filename) {
    QString realpath = filename.isEmpty() ? JSONFileHandler::getLastDatabasePath() : filename;
    if (realpath.isEmpty()) {
        qDebug() << "Errore: Il percorso del database è vuoto!";
        return;
    }
    notifyRemove();

    if (library) {
        while (library->getSize() > 0) {
            library->removeLastItem();
        }
    }
    jsonArr = JSONFileHandler::loadFromFile(realpath);
    addJSONItemsToFile();
}

void JSONVisitor::addJSONItemsToFile() {
    Item::setIdCount(0);
    for (const QJsonValue &value : jsonArr) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        QString imagePath = (obj["type"].toString() == "Book") ? ":/assets/imgBook.png" :
                           (obj["type"].toString() == "Music") ? ":/assets/imgMusic.png" :
                           ":/assets/imgFilm.png";

        Item* item = JSONSerializer::deserialize(obj);
        ItemCard* widget = new ItemCard(obj["title"].toString(),imagePath,item, dynamic_cast<MainWidget*>(mainObserver));
        item->setStatus(true);
        library->addItem(item);
        notifyAdd(widget);
    }
    library->setStatus(true);
}

void JSONVisitor::notifyAdd(QWidget* widget) const {
    mainObserver->addW_notification(widget);
}

void JSONVisitor::notifyRemove() const{
    mainObserver->removeW_notification();
}






