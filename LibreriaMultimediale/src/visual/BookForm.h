//
// Created by adifi on 07/03/2025.
//

#ifndef BOOKFORM_H
#define BOOKFORM_H

#include "FormWidget.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>

class FormWidget;

class BookForm : public FormWidget {
    Q_OBJECT

private:
    QLineEdit* titleField;
    QLineEdit* authorField;
    QSpinBox *yearSpinBox;
    QLineEdit* pagesField;
    QComboBox *genreComboBox;
    QTextEdit *descriptionField;

public:
    explicit BookForm(QWidget* parent = nullptr);
    void clearFields() override;
};



#endif //BOOKFORM_H
