//
// Created by adifi on 02/02/2025.
//

#include "ItemCard.h"
#include <QTimer>
#include <QVBoxLayout>
#include "../logic/Book.h"
#include "MainWidget.h"
#include "OverviewWidgetVisitor.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>


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


    imageLabel = new QLabel(this);
    QPixmap itemImage(imagePath);
    imageLabel->setPixmap(itemImage.scaled(85, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMargin(8);
    imageLabel->lower();
    
    favoriteIcon = new QLabel(this);    
    favoriteIcon->setPixmap(QPixmap(":/assets/star.png").scaled(favoriteIcon->width()-5, favoriteIcon->height()-5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    favoriteIcon->resize(30, 30);
    favoriteIcon->setStyleSheet(
	    "QLabel { "
	    "background-color: white; "
	    "border-radius: 15px; "
	    "border: 2px solid #F9DB78; "         
	    "}"
    );
    int x = ((width() - favoriteIcon->width()) / 2)+30;
    int y = 55;
    favoriteIcon->move(x, y);
    favoriteIcon->setAlignment(Qt::AlignCenter);
    favoriteIcon->raise();
    favoriteIcon->hide(); 
    
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
    updateFavoriteIcon();
}

Item * ItemCard::getItem() const{
    return item;
}

void ItemCard::setTitleLabel(QString title) {
    titleLabel->setText(title);
}

void ItemCard::mouseDoubleClickEvent(QMouseEvent *event) {
    if (item) {
        item->setLiked(!item->isLiked());
        updateFavoriteIcon();
        item->setStatus(false);
        emit userDoubleClicked(item->getId());
    }
    QFrame::mouseDoubleClickEvent(event);
}

void ItemCard::updateFavoriteIcon() {
    if (item && item->isLiked()) {
        animateFavoriteIcon(true);
    } else {
        animateFavoriteIcon(false);
    }
}


void ItemCard::animateFavoriteIcon(bool show) {
    if (!favoriteIcon->graphicsEffect()) {
        auto* opacityEffect = new QGraphicsOpacityEffect(favoriteIcon);
        favoriteIcon->setGraphicsEffect(opacityEffect);
    }
    auto* effect = static_cast<QGraphicsOpacityEffect*>(favoriteIcon->graphicsEffect());

    const int iconWidth = 30;

    const int endX = ((width() - iconWidth) / 2) + 30;
    const int endY = 55;
    const QPoint targetPos(endX, endY);

    const QPoint startPos = show ? targetPos + QPoint(0, 10) : targetPos;
    const QPoint exitPos = targetPos + QPoint(0, 10);

    if (show) {
        favoriteIcon->move(startPos);
        favoriteIcon->setVisible(true);
    }

    QPropertyAnimation* moveAnim = new QPropertyAnimation(favoriteIcon, "pos");
    moveAnim->setDuration(300);
    moveAnim->setEasingCurve(QEasingCurve::OutCubic);
    moveAnim->setStartValue(show ? startPos : targetPos);
    moveAnim->setEndValue(show ? targetPos : exitPos);

    QPropertyAnimation* opacityAnim = new QPropertyAnimation(effect, "opacity");
    opacityAnim->setDuration(300);
    opacityAnim->setEasingCurve(QEasingCurve::OutCubic);
    opacityAnim->setStartValue(show ? 0.0 : 1.0);
    opacityAnim->setEndValue(show ? 1.0 : 0.0);

    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    group->addAnimation(moveAnim);
    group->addAnimation(opacityAnim);

    if (!show) {
        connect(group, &QParallelAnimationGroup::finished, [this]() {
            favoriteIcon->setVisible(false);
        });
    }

    group->start(QAbstractAnimation::DeleteWhenStopped);
}
