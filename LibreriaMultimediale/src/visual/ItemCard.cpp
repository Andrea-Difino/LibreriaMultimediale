//
// Created by adifi on 02/02/2025.
//

#include "ItemCard.h"
#include <QTimer>
#include <QVBoxLayout>
#include "../logic/Book.h"
#include "MainWidget.h"
#include "OverviewWidgetVisitor.h"


ItemCard::ItemCard(const QString &title, const QString &imagePath, Item *linked_obj, QWidget *parent) : QFrame(parent), item(linked_obj){
    setObjectName("createdWidget");
    setMinimumWidth(170);
    setMinimumHeight(210);
    setCursor(Qt::PointingHandCursor);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-weight:400;");
    titleLabel->setWordWrap(true);
    titleLabel->setFixedSize(140, 35);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel,0,Qt::AlignHCenter);


    imageLabel = new QLabel();
    QPixmap itemImage(imagePath);
    imageLabel->setPixmap(itemImage.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMargin(8);
    mainLayout->addWidget(imageLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    lookBtn = new QPushButton();
    QPixmap lookIcon(":/assets/guarda.png");
    lookBtn->setCursor(Qt::PointingHandCursor);
    lookBtn->setIcon(lookIcon);
    lookBtn->setIconSize(QSize(20,20));
    lookBtn->setFixedSize(25,25);

    connect(lookBtn, &QPushButton::clicked, [=] {
        item->accept(dynamic_cast<MainWidget*>(parent)->getOvervieWidget());
    });

    deleteBtn = new QPushButton();
    QPixmap deleteIcon(":/assets/delete.png");
    deleteBtn->setCursor(Qt::PointingHandCursor);
    deleteBtn->setIcon(deleteIcon);
    deleteBtn->setIconSize(QSize(20,20));
    deleteBtn->setFixedSize(25,25);

    connect(deleteBtn, &QPushButton::clicked, [this, parent] {
        dynamic_cast<MainWidget*>(parent)->deleteItem(this);
    });

    editBtn = new QPushButton();
    QPixmap editIcon(":/assets/modifica.png");
    editBtn->setCursor(Qt::PointingHandCursor);
    editBtn->setIcon(editIcon);
    editBtn->setIconSize(QSize(20,20));
    editBtn->setFixedSize(25,25);

    connect(editBtn, &QPushButton::clicked, [=] {
        item->accept(dynamic_cast<MainWidget*>(parent)->getModifyWidgetVisitor());
    });

    buttonLayout->addWidget(lookBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(editBtn);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

Item * ItemCard::getItem() const{
    return item;
}

void ItemCard::setTitleLabel(QString title) {
    titleLabel->setText(title);
}
