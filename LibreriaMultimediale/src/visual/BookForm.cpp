//
// Created by adifi on 07/03/2025.
//

#include "BookForm.h"

#include <qdir.h>

#include "FormWidget.h"
#include <QMessageBox>
#include "Form.h"
#include "ImageHandler.h"
#include "../logic/Book.h"

BookForm::BookForm(QWidget* parent) : FormWidget(parent) {

    Form* form = dynamic_cast<Form*>(parent);
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
    yearSpinBox->setRange(0, QDate::currentDate().year());
    yearLayout->addWidget(year);
    yearLayout->addWidget(yearSpinBox);

    QHBoxLayout *pagesLayout = new QHBoxLayout();
    QLabel *pages = new QLabel("PAGINE");
    pagesField = new QLineEdit();
    pages->setFixedWidth(120);
    pages->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    pages->setMargin(10);
    pagesField->setObjectName("formField");
    QRegularExpression intregex("^[1-9]\\d*$");
    QRegularExpressionValidator *validatorIntero = new QRegularExpressionValidator(intregex, this);
    pagesField->setValidator(validatorIntero);
    pagesLayout->addWidget(pages);
    pagesLayout->addWidget(pagesField);

    QHBoxLayout *authorLayout = new QHBoxLayout();
    QLabel *author = new QLabel("AUTORE");
    authorField = new QLineEdit();
    author->setFixedWidth(120);
    author->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    author->setMargin(10);
    authorField->setObjectName("formField");
    QRegularExpression regexNome("[A-Za-z ]+");
    QRegularExpressionValidator *validatorAuthor = new QRegularExpressionValidator(regexNome, this);
    authorField->setValidator(validatorAuthor);
    authorLayout->addWidget(author);
    authorLayout->addWidget(authorField);

    QHBoxLayout *genreLayout = new QHBoxLayout();
    QLabel *genre = new QLabel("GENERE");
    genreComboBox = new QComboBox();
    genre->setFixedWidth(120);
    genre->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    genre->setMargin(10);
    QStringList genreList;
    for (auto gen : Book::genres) {
        genreList.append(QString::fromStdString(gen));
    }
    genreComboBox->addItems(genreList);
    genreLayout->addWidget(genre);
    genreLayout->addWidget(genreComboBox);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE");
    descriptionField = new QTextEdit();
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionField->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionField->setMinimumHeight(85);
    descriptionField->setObjectName("formField");
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(descriptionField);

    addImgButton = new QPushButton("Aggiungi Immagine", this);
    addImgButton->setCursor(Qt::PointingHandCursor);
    addImgButton->setObjectName("addImagesButton");

    ImageHandler* imageHand = new ImageHandler(this);
    connect(addImgButton, &QPushButton::clicked, this, [this,imageHand] () {
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
    form->getLayout()->addLayout(pagesLayout);
    form->getLayout()->addLayout(authorLayout);
    form->getLayout()->addLayout(genreLayout);
    form->getLayout()->addLayout(descriptionLayout);
    form->getLayout()->addLayout(buttonsLayout);

    connect(createItem, &QPushButton::clicked, [=] {
        if (titleField->text().isEmpty() || pagesField->text().isEmpty() || authorField->text().isEmpty()) {
            QMessageBox::warning(this, "Errore", "Tutti i campi, eccetto la descrizione e l'immagine, sono obbligatori");
            return;
        }
        QString destFolder = QCoreApplication::applicationDirPath() + "/itemsCover";
        QString copiedPath = ImageHandler::copyImageToDestination(image_path, destFolder);
        if (!copiedPath.isEmpty()) {
            addImgButton->setText("Aggiungi Immagine");
        }
        Book* newBook = new Book(titleField->text().trimmed().toStdString(),authorField->text().toStdString(),genreComboBox->currentText().toStdString(),pagesField->text().toInt(),yearSpinBox->value(),descriptionField->toPlainText().toStdString(), copiedPath.toStdString());
        form->getMainWidget()->getLibrary()->addItem(newBook);
        form->getMainWidget()->getLibrary()->setStatus(false);
        ItemCard* newItem = new ItemCard(titleField->text(),":/assets/imgBook.png",newBook, form->getMainWidget());
        form->getMainWidget()->addW_notification(newItem);

        clearFields();
        form->getMainWidget()->changePage();
    });
}


void BookForm::clearFields() {
    titleField->clear();
    authorField->clear();
    pagesField->clear();
    descriptionField->clear();
    image_path = "";
}
