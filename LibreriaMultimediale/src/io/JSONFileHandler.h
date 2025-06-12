//
// Created by adifi on 28/02/2025.
//

#ifndef JSONFILEHANDLER_H
#define JSONFILEHANDLER_H
#include <QJsonArray>
#include <QString>
#include "JSONVisitor.h"

class JSONVisitor;

class JSONFileHandler{
    public:
        explicit JSONFileHandler() = default;
        static void saveToFile(const QJsonArray& jsonArr, const QString& filePath);
        static void sortJsonArrayById(QJsonArray &jsonArray);
        static void removeItemById(int id,QJsonArray& array);
        static QJsonArray loadFromFile(const QString& filePath = "");

        static bool isValidJson(const QJsonArray &array);

        static void saveLastDatabasePath(const QString& path);
        static QString getLastDatabasePath();
    private:
        static QString lastPath;
        static bool modified;
};


#endif //JSONFILEHANDLER_H
