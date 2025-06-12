//
// Created by adifi on 05/02/2025.
//

#ifndef CREATEITEMWIDGET_H
#define CREATEITEMWIDGET_H


#include "MainWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include "FormWidget.h"

class MainWidget;
class FormWidget;

class Form : public QFrame {
    Q_OBJECT
public:
    explicit Form(unsigned int objectType,QWidget *parent = nullptr);

    MainWidget* getMainWidget() const;
    QVBoxLayout* getLayout() const;
private:
    MainWidget *main_wid;
    QVBoxLayout* mainLayout;
    FormWidget *currentForm;
    QPushButton* createItem;
};



#endif //CREATEITEMWIDGET_H
