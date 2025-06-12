//
// Created by adifi on 28/02/2025.
//

#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H
#include <QJsonObject>
#include "../logic/Item.h"
#include "../logic/VisitorInterface.h"

class JSONSerializer {
    public:
        static QJsonObject serialize(Book* libro);
        static QJsonObject serialize(Music* music);
        static QJsonObject serialize(Film* film);

        static Item *deserialize(const QJsonObject &obj);
};



#endif //JSONSERIALIZER_H
