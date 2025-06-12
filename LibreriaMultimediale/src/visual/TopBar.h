//
// Created by adifi on 01/02/2025.
//

#ifndef TOPBAR_H
#define TOPBAR_H
#include <QApplication>
#include <QPushButton>
#include "SearchWidget.h"

class TopBar : public QWidget{
    Q_OBJECT
private:
    SearchWidget* searchBar;
    QPushButton* saveFile;
    QPushButton* createFile;
    QPushButton* uploadFile;
    QPushButton* changePageBtn;
public:
    TopBar(QWidget *parent = nullptr);

    QPushButton* getChangePageBtn() const;
    QWidget* getSearchWidget() const;
    QPushButton* getSaveFile() const;
    QPushButton* getUploadFile() const;
    QPushButton *getCreateFile() const;

signals:
    void isSearching(const QString& searchText);
};



#endif //TOPBAR_H
