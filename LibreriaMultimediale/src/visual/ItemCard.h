//
// Created by adifi on 02/02/2025.
//

#ifndef ITEMCARD_H
#define ITEMCARD_H
#include <QLabel>
#include "OverviewWidgetVisitor.h"

class OverviewWidgetVisitor;

class ItemCard : public QFrame{
    Q_OBJECT
    public:
        ItemCard(const QString &title, const QString &imagePath,Item* linked_obj, QWidget *parent);
        ~ItemCard() = default;

        Item* getItem() const;
        void setTitleLabel(QString title);
    private:
        QLabel* titleLabel;
        QLabel* imageLabel;
        QPushButton* lookBtn;
        QPushButton* editBtn;
        QPushButton* deleteBtn;
        Item* item;
};



#endif //ITEMCARD_H
