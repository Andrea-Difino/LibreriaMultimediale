//
// Created by adifi on 07/03/2025.
//

#include "FilmForm.h"

#include "FormWidget.h"
#include <QDate>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "ItemCard.h"
#include "../logic/Film.h"

FilmForm::FilmForm(QWidget* parent) : FormWidget(parent) {
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *title = new QLabel("TITOLO");
    titleField = new QLineEdit();
    title->setFixedWidth(120);
    title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    title->setMargin(10);
    titleField->setMaxLength(40);
    titleField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleField->setObjectName("formField");
    titleLayout->addWidget(title);
    titleLayout->addWidget(titleField);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *year = new QLabel("ANNO");
    yearSpinBox = new QSpinBox();
    year->setFixedWidth(120);
    year->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    year->setMargin(10);
    yearSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    yearSpinBox->setRange(1890, QDate::currentDate().year());
    yearSpinBox->setValue(1890);
    yearLayout->addWidget(year);
    yearLayout->addWidget(yearSpinBox);

    QHBoxLayout *timeLayout = new QHBoxLayout();
    QLabel *time = new QLabel("DURATA");
    time->setFixedWidth(120);
    time->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    time->setMargin(10);
    QHBoxLayout *timeSelectionLayout = new QHBoxLayout();
    hoursSpinBox = new QSpinBox(this);
    hoursSpinBox->setRange(0, 23);
    hoursSpinBox->setPrefix("Ore: ");
    minutesSpinBox = new QSpinBox(this);
    minutesSpinBox->setRange(0, 59);
    minutesSpinBox->setPrefix("Minuti: ");
    secondsSpinBox = new QSpinBox(this);
    secondsSpinBox->setRange(0, 59);
    secondsSpinBox->setPrefix("Secondi: ");
    hoursSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    minutesSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    secondsSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    timeSelectionLayout->addWidget(hoursSpinBox);
    timeSelectionLayout->addWidget(minutesSpinBox);
    timeSelectionLayout->addWidget(secondsSpinBox);
    timeLayout->addWidget(time);
    timeLayout->addLayout(timeSelectionLayout);

    QHBoxLayout *genreLayout = new QHBoxLayout();
    QLabel *genre = new QLabel("TIPOLOGIA");
    genre->setFixedWidth(120);
    genre->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    genre->setMargin(10);
    genreComboBox = new QComboBox();
    QStringList tipologyList;
    for (auto t : Film::tipology) {
        tipologyList.append(QString::fromStdString(t));
    }
    genreComboBox->addItems(tipologyList);
    genreComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    genreLayout->addWidget(genre);
    genreLayout->addWidget(genreComboBox);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE");
    descriptionField = new QTextEdit();
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionField->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionField->setMinimumHeight(90);
    descriptionField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    descriptionField->setObjectName("formField");
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(descriptionField);

    createItem = new QPushButton("Crea Media", this);
    createItem->setObjectName("confirmSelection");
    createItem->setCursor(Qt::PointingHandCursor);
    createItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    form->getLayout()->addLayout(titleLayout);
    form->getLayout()->addLayout(yearLayout);
    form->getLayout()->addLayout(timeLayout);
    form->getLayout()->addLayout(genreLayout);
    form->getLayout()->addLayout(descriptionLayout);
    form->getLayout()->addWidget(createItem,0,Qt::AlignHCenter);

    connect(createItem, &QPushButton::clicked, [=] {
        if (titleField->text().isEmpty()) {
            QMessageBox::warning(this, "Errore", "Tutti i campi, eccetto la descrizione, devono essere obbligatoriamente compilati.");
            return;
        }
        if (secondsSpinBox->value() == 0 && minutesSpinBox->value() == 0 && hoursSpinBox->value() == 0) {
            QMessageBox::warning(this, "Errore", "La durata deve essere maggiore di zero");
            return;
        }
        Film* newFilm = new Film(titleField->text().trimmed().toStdString(),descriptionField->toPlainText().toStdString(),genreComboBox->currentText().toStdString(),yearSpinBox->value(),(secondsSpinBox->value() + minutesSpinBox->value() * 60 + hoursSpinBox->value() * 3600)%86400);
        form->getMainWidget()->getLibrary()->addItem(newFilm);
        form->getMainWidget()->getLibrary()->setStatus(false);
        ItemCard* newItem = new ItemCard(titleField->text(),":/assets/imgFilm.png",newFilm, form->getMainWidget());
        form->getMainWidget()->addW_notification(newItem);

        clearFields();
        form->getMainWidget()->changePage();
    });
}

void FilmForm::clearFields() {
    titleField->clear();
    yearSpinBox->clear();
    hoursSpinBox->clear();
    minutesSpinBox->clear();
    secondsSpinBox->clear();
    descriptionField->clear();
}
