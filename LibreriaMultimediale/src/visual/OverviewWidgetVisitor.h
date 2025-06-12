//
// Created by adifi on 06/03/2025.
//

#ifndef OVERVIEWWIDGETVISITOR_H
#define OVERVIEWWIDGETVISITOR_H


#include "MainWidget.h"
#include "../logic/VisitorInterface.h"


class OverviewWidgetVisitor : public QObject, public VisitorInterface{
    Q_OBJECT
    public:
        explicit OverviewWidgetVisitor();

        ~OverviewWidgetVisitor() override;

        void visit(Book* libro) override;
        void visit(Music* music) override;
        void visit(Film* film) override;

        QWidget* getWidget() const;
    private:
        QWidget* overview;
    signals:
        void closeOverview();
        void overviewWidgetCreated(QWidget* widget);

};



#endif //OVERVIEWWIDGETVISITOR_H
