//
// Created by adifi on 07/03/2025.
//

#ifndef MUSICFORM_H
#define MUSICFORM_H

#include "FormWidget.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>

class FormWidget;

class MusicForm : public FormWidget {
    Q_OBJECT

private:
    QLineEdit* titleField;
    QSpinBox* yearSpinBox;
    QLineEdit* singerField;
    QSpinBox* hoursSpinBox;
    QSpinBox* minutesSpinBox;
    QSpinBox* secondsSpinBox;
    QTextEdit* descriptionField;

public:
    explicit MusicForm(QWidget* parent = nullptr);
    void clearFields() override;
};



#endif //MUSICFORM_H
