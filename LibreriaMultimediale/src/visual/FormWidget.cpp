//
// Created by adifi on 07/03/2025.
//

#include "FormWidget.h"

FormWidget::FormWidget(QWidget* parent) : QWidget(parent){
    form = dynamic_cast<Form*>(parent);
}