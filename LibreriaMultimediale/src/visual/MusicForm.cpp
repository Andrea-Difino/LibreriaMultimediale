//
// Created by adifi on 07/03/2025.
//

#include "MusicForm.h"

#include <qdir.h>
#include "ImageHandler.h"
#include "FormWidget.h"
#include <QLabel>
#include <QMessageBox>
#include "../logic/Music.h"

MusicForm::MusicForm(QWidget* parent) : FormWidget(parent) {
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *title = new QLabel("TITOLO");
    titleField = new QLineEdit();
    title->setFixedWidth(120);
    title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    title->setMargin(10);
    titleField->setMaxLength(40);
    titleField->setObjectName("formField");
    titleLayout->addWidget(title);
    titleLayout->addWidget(titleField);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *year = new QLabel("ANNO");
    yearSpinBox = new QSpinBox();
    year->setFixedWidth(120);
    year->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    year->setMargin(10);
    yearSpinBox->setRange(1300, QDate::currentDate().year());
    yearSpinBox->setValue(QDate::currentDate().year());
    yearLayout->addWidget(year);
    yearLayout->addWidget(yearSpinBox);

    QHBoxLayout *singerLayout = new QHBoxLayout();
    QLabel *singer = new QLabel("CANTANTE");
    singerField = new QLineEdit();
    singer->setFixedWidth(120);
    singer->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    singer->setMargin(10);
    singerField->setObjectName("formField");
    QRegularExpression regexNome("[A-Za-z0-9 ]+");
    QRegularExpressionValidator *validatorSinger = new QRegularExpressionValidator(regexNome, this);
    singerField->setValidator(validatorSinger);
    singerLayout->addWidget(singer);
    singerLayout->addWidget(singerField);

    QHBoxLayout *timeLayout = new QHBoxLayout();
    QLabel *time = new QLabel("DURATA");
    time->setFixedWidth(120);
    time->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    time->setMargin(10);
    QHBoxLayout *timeSelectionLayout = new QHBoxLayout();
    hoursSpinBox = new QSpinBox(this);
    hoursSpinBox->setRange(0, 23);          // Imposta l'intervallo per le ore (0-23)
    hoursSpinBox->setPrefix("Ore: ");       // Aggiungi un prefisso per chiarezza
    minutesSpinBox = new QSpinBox(this);
    minutesSpinBox->setRange(0, 59);        // Imposta l'intervallo per i minuti (0-59)
    minutesSpinBox->setPrefix("Minuti: ");  // Aggiungi un prefisso per chiarezza
    secondsSpinBox = new QSpinBox(this);
    secondsSpinBox->setRange(0, 59);        // Imposta l'intervallo per i secondi (0-59)
    secondsSpinBox->setPrefix("Secondi: ");
    timeSelectionLayout->addWidget(hoursSpinBox);
    timeSelectionLayout->addWidget(minutesSpinBox);
    timeSelectionLayout->addWidget(secondsSpinBox);
    timeLayout->addWidget(time);
    timeLayout->addLayout(timeSelectionLayout);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE");
    descriptionField = new QTextEdit();
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionField->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionField->setMinimumHeight(90);
    descriptionField->setObjectName("formField");
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(descriptionField);

    addImgButton = new QPushButton("Aggiungi Immagine", this);
    addImgButton->setCursor(Qt::PointingHandCursor);
    addImgButton->setObjectName("addImagesButton");

    ImageHandler* imageHand = new ImageHandler(this);
    connect(addImgButton, &QPushButton::clicked, this, [this, imageHand] () {
        image_path = imageHand->addImage();
        addImgButton->setText("Immagine Selezionata!");
    });

    createItem = new QPushButton("Crea Media", this);
    createItem->setObjectName("confirmSelection");
    createItem->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addImgButton);
    buttonsLayout->addWidget(createItem);
    buttonsLayout->setAlignment(Qt::AlignHCenter);

    form->getLayout()->addLayout(titleLayout);
    form->getLayout()->addLayout(yearLayout);
    form->getLayout()->addLayout(singerLayout);
    form->getLayout()->addLayout(timeLayout);
    form->getLayout()->addLayout(descriptionLayout);
    form->getLayout()->addLayout(buttonsLayout);

    connect(createItem, &QPushButton::clicked, [=] {
        if (titleField->text().isEmpty() || singerField->text().isEmpty()) {
            QMessageBox::warning(this, "Errore", "Tutti i campi, eccetto la descrizione e l'immagine, sono obbligatori.");
            return;
        }
        if (secondsSpinBox->value() == 0 && minutesSpinBox->value() == 0 && hoursSpinBox->value() == 0) {
            QMessageBox::warning(this, "Errore", "La durata deve essere maggiore di zero");
            return;
        }
        QString destFolder = QCoreApplication::applicationDirPath() + "/itemsCover";
        QString copiedPath = ImageHandler::copyImageToDestination(image_path, destFolder);
        if (!copiedPath.isEmpty()) {
            //qDebug() << "Immagine copiata in:" << copiedPath;
            addImgButton->setText("Aggiungi Immagine");
        }
        Music* newMusic = new Music(titleField->text().trimmed().toStdString(),descriptionField->toPlainText().toStdString(),singerField->text().toStdString(),yearSpinBox->value(),(secondsSpinBox->value() + minutesSpinBox->value() * 60 + hoursSpinBox->value() * 3600)%86400, copiedPath.toStdString());
        form->getMainWidget()->getLibrary()->addItem(newMusic);
        form->getMainWidget()->getLibrary()->setStatus(false);
        ItemCard* newItem = new ItemCard(titleField->text(),":/assets/imgMusic.png", newMusic,form->getMainWidget());
        form->getMainWidget()->addW_notification(newItem);

        clearFields();
        form->getMainWidget()->changePage();
    });
}

void MusicForm::clearFields() {
    titleField->clear();
    singerField->clear();
    yearSpinBox->clear();
    hoursSpinBox->setValue(0);
    minutesSpinBox->setValue(0);
    secondsSpinBox->setValue(0);
    descriptionField->clear();
    image_path = "";
}
