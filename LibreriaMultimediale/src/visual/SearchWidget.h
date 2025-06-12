//
// Created by adifi on 01/02/2025.
//

#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H
#include <QLineEdit>
#include <QWidget>


class SearchWidget : public QWidget {
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = nullptr);

    QLineEdit* getSearchBar() const;
private:
    QLineEdit* searchBar;
};



#endif //SEARCHWIDGET_H
