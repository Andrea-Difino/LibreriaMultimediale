//
// Created by adifi on 05/02/2025.
//

#include "Form.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include "MainWidget.h"
#include <QTextEdit>
#include <QMessageBox>
#include "MusicForm.h"
#include "BookForm.h"
#include "FilmForm.h"


Form::Form(const unsigned int objectType, QWidget *parent) : QFrame(parent){
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    main_wid = dynamic_cast<MainWidget*>(this->parent());
    this->setMinimumSize(500,300);
    this->setMaximumSize(1000,500);
    this->setObjectName("form");
    this->setContentsMargins(10,5,10,5);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    switch (objectType) {
        case 0:
            currentForm = new BookForm(this);
        break;
        case 1:
            currentForm = new MusicForm(this);
        break;
        case 2:
            currentForm = new FilmForm(this);
        break;
        default:
            break;
    }

    if (currentForm) {
        mainLayout->addWidget(currentForm);
    }
}

MainWidget * Form::getMainWidget() const {
    return main_wid;
}

QVBoxLayout * Form::getLayout() const {
    return mainLayout;
}

