//
// Created by adifi on 28/03/2025.
//

#ifndef MODIFYWIDGETVISITOR_H
#define MODIFYWIDGETVISITOR_H

#include "MainWidget.h"
#include "../logic/VisitorInterface.h"

class ModifyWidgetVisitor: public QObject, public VisitorInterface{
    Q_OBJECT
    public:
        explicit ModifyWidgetVisitor();

        ~ModifyWidgetVisitor() override;

        void visit(Book* libro) override;
        void visit(Music* music) override;
        void visit(Film* film) override;

        QWidget* getWidget() const;

        bool areInputsValid() const;
    private:
        QWidget* modify;
    signals:
        void closeModifyWidget();
        void modifyWidgetCreated(QWidget* widget);
        void saveChanges(unsigned int id, QString title);
};



#endif //MODIFYWIDGETVISITOR_H
