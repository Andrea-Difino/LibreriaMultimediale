//
// Created by adifi on 28/02/2025.
//

#include "JSONFileHandler.h"

#include <QJsonObject>
#include <QFileDialog>
#include <QJsonDocument>
#include "../visual/MainWidget.h"

QString JSONFileHandler::lastPath = "";
bool JSONFileHandler::modified = false;

void JSONFileHandler::saveToFile(const QJsonArray& jsonArr, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Errore nell'aprire il file per la scrittura:" << filePath;
        return;
    }
    file.write("");

    if (modified) sortJsonArrayById(const_cast<QJsonArray&>(jsonArr));

    QJsonArray data = QJsonArray{};
    for (const auto &item : jsonArr) {
        if (!item.isObject()) continue;
        QJsonObject itemObj = item.toObject();
        data.append(itemObj);
    }

    QJsonDocument doc(data);
    file.write(doc.toJson());
    file.close();
}

void JSONFileHandler::sortJsonArrayById(QJsonArray &jsonArray) {
    QVector<QJsonObject> jsonObjects;
    for (const auto &value : jsonArray) {
        if (value.isObject()) {
            jsonObjects.append(value.toObject());
        }
    }

    std::sort(jsonObjects.begin(), jsonObjects.end(), [](const QJsonObject &a, const QJsonObject &b) {
        return a["id"].toInt() < b["id"].toInt();
    });

    jsonArray = QJsonArray();
    for (const auto &obj : jsonObjects) {
        jsonArray.append(obj);
    }
}

void JSONFileHandler::removeItemById(int id,QJsonArray& array) {
    QJsonArray updatedArray;
    for (const auto& item : array) {
        QJsonObject itemObj = item.toObject();
        if (itemObj["id"].toInt() != id) {
            updatedArray.append(item);
        }
    }
    array = updatedArray;
    modified = true;
}

QJsonArray JSONFileHandler::loadFromFile(const QString& filePath) {
    if (filePath.isEmpty()) {
        qDebug() << "Errore: Percorso file vuoto!";
        return {};
    }

    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "Errore: Il file JSON non esiste!";
        return {};
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Errore nell'aprire il file per la lettura:" << filePath;
        return {};
    }

    QByteArray jsonData = file.readAll();
    file.close();

    if (jsonData.isEmpty()) {
        qDebug() << "Errore: Il file JSON è vuoto.";
        return {};
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (doc.isNull()) {
        qDebug() << "Errore di parsing JSON:" << parseError.errorString();
        return {};
    }

    if (!doc.isArray()) {
        qDebug() << "Errore: Il file JSON non contiene un array!";
        return {};
    }

    QJsonArray jsonArray = doc.array();

    if (!isValidJson(jsonArray)) {
        qDebug() << "Errore: Il JSON contiene dati non validi!";
        return {};
    }

    saveLastDatabasePath(filePath);
    return jsonArray;
}

bool JSONFileHandler::isValidJson(const QJsonArray &array) {
    QSet<QString> validTypes = {"Music", "Film", "Book"};
    QSet<int> ids;

    for (const QJsonValue &value : array) {
        if (!value.isObject()) {
            qDebug() << "Elemento non è un oggetto JSON valido.";
            return false;
        }

        QJsonObject obj = value.toObject();

        if (!obj.contains("id") || !obj["id"].isDouble()) {
            qDebug() << "Errore: Campo 'id' mancante o non valido.";
            return false;
        }
        int id = obj["id"].toInt();
        if (ids.contains(id)) {
            qDebug() << "Errore: ID duplicato:" << id;
            return false;
        }
        ids.insert(id);

        if (!obj.contains("title") || !obj["title"].isString()) {
            qDebug() << "Errore: Campo 'title' mancante o non valido.";
            return false;
        }
        if (!obj.contains("description") || !obj["description"].isString()) {
            qDebug() << "Errore: Campo 'description' mancante o non valido.";
            return false;
        }
        if (!obj.contains("year") || !obj["year"].isDouble()) {
            qDebug() << "Errore: Campo 'year' mancante o non valido.";
            return false;
        }

        QString type = obj["type"].toString();
        if (!validTypes.contains(type)) {
            qDebug() << "Errore: Tipo non riconosciuto:" << type;
            return false;
        }

        if (type == "Music") {
            if (!obj.contains("singer") || !obj["singer"].isString()) {
                qDebug() << "Errore: Campo 'singer' mancante o non valido per Music.";
                return false;
            }
            if (!obj.contains("durata") || !obj["durata"].isDouble()) {
                qDebug() << "Errore: Campo 'durata' mancante o non valido per Music.";
                return false;
            }
        } else if (type == "Film") {
            if (!obj.contains("genre") || !obj["genre"].isString()) {
                qDebug() << "Errore: Campo 'genre' mancante o non valido per Film.";
                return false;
            }
            if (!obj.contains("durata") || !obj["durata"].isDouble()) {
                qDebug() << "Errore: Campo 'durata' mancante o non valido per Film.";
                return false;
            }
        } else if (type == "Book") {
            if (!obj.contains("author") || !obj["author"].isString()) {
                qDebug() << "Errore: Campo 'author' mancante o non valido per Book.";
                return false;
            }
            if (!obj.contains("pages") || !obj["pages"].isDouble()) {
                qDebug() << "Errore: Campo 'pages' mancante o non valido per Book.";
                return false;
            }
        }
    }

    return true;
}

void JSONFileHandler::saveLastDatabasePath(const QString& path) {
    lastPath = path;
}

QString JSONFileHandler::getLastDatabasePath(){
    return lastPath;
}