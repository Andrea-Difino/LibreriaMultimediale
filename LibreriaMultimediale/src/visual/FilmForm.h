//
// Created by adifi on 07/03/2025.
//

#ifndef FILMFORM_H
#define FILMFORM_H


#include "FormWidget.h"
#include <QSpinBox>
#include <QTextEdit>

class FormWidget;

class FilmForm : public FormWidget {
    Q_OBJECT

private:
    QLineEdit* titleField;
    QSpinBox* yearSpinBox;
    QSpinBox* hoursSpinBox;
    QSpinBox* minutesSpinBox;
    QSpinBox* secondsSpinBox;
    QComboBox* genreComboBox;
    QTextEdit* descriptionField;
    QString image_path;
public:
    explicit FilmForm(QWidget* parent = nullptr);
    void clearFields() override;
};



#endif //FILMFORM_H
