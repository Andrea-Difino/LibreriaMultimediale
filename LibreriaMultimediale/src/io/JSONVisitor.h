//
// Created by ANDREA on 22/12/2024.
//

#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include <QJsonArray>
#include "../logic/VisitorInterface.h"
#include "../visual/ItemCard.h"
#include "../logic/Library.h"
#include "../logic/ObserverInterface.h"
#include "JSONFileHandler.h"
#include "../visual/MainWidget.h"

class MainWidget;

class JSONVisitor : public VisitorInterface{
    public:
        explicit JSONVisitor(Library* lib,MainWidget* p);
        ~JSONVisitor() override = default;

        void visit(Book* libro) override;
        void visit(Music* music) override;
        void visit(Film* film) override;

        void saveToFile();
        void removeItemById(int id);
        void loadFromFile(const QString& filename = "");
        void addJSONItemsToFile();
    private:
        Library* library;
        QJsonArray jsonArr;
        ObserverInterface* mainObserver{};

        void notifyAdd(QWidget* widget) const;
        void notifyRemove() const;
};



#endif //JSONVISITOR_H
