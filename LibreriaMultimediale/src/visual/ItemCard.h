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
    
    protected:
    	void mouseDoubleClickEvent(QMouseEvent *event) override;
    	
    private:
        QLabel* titleLabel;
        QLabel* imageLabel;
        QLabel *favoriteIcon;
        QPushButton* lookBtn;
        QPushButton* editBtn;
        QPushButton* deleteBtn;
        Item* item;
        
        void updateFavoriteIcon();
        void animateFavoriteIcon(bool show);
        
    signals: 
    	void userDoubleClicked(unsigned int id);
};



#endif //ITEMCARD_H
