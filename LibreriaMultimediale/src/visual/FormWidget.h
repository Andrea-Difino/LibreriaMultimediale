//
// Created by adifi on 07/03/2025.
//

#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include "Form.h"

class Form;

class FormWidget : public QWidget {
    Q_OBJECT

protected:
    Form* form;
    QPushButton* createItem;
public:
    explicit FormWidget(QWidget* parent = nullptr);
    virtual ~FormWidget() = default;

    virtual void clearFields() = 0;
};



#endif //FORMWIDGET_H
