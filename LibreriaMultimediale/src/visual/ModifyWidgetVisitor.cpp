//
// Created by adifi on 28/03/2025.
//

#include "ModifyWidgetVisitor.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

#include "../logic/Book.h"
#include "../logic/Film.h"
#include "../logic/Music.h"

ModifyWidgetVisitor::ModifyWidgetVisitor(): modify(nullptr) {}

ModifyWidgetVisitor::~ModifyWidgetVisitor() {
    delete modify;
}

void ModifyWidgetVisitor::visit(Book *libro) {
    modify = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(modify);

    QWidget* imageWidget = new QWidget(modify);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* imageLayout = new QVBoxLayout(imageWidget);
    QLabel* image = new QLabel();
    QPixmap bookImage(":/assets/imgBookBig.png");
    image->setPixmap(bookImage.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLayout->addWidget(image);

    QWidget* rightWidget = new QWidget(modify);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* vLayout = new QVBoxLayout(rightWidget);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("TITOLO:");
    titleLabel->setObjectName("bookLabelsOverview");
    QLineEdit* titleField = new QLineEdit();
    titleField->setText(QString::fromStdString(libro->getTitle()));
    titleField->setMaxLength(40);
    titleField->setObjectName("formField");
    titleLabel->setFixedWidth(120);
    titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    titleLabel->setMargin(10);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleField);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *yearLabel = new QLabel("ANNO:");
    yearLabel->setObjectName("bookLabelsOverview");
    QSpinBox* yearSpinBox = new QSpinBox();
    yearSpinBox->setRange(1, QDate::currentDate().year());
    yearSpinBox->setValue(1);
    yearSpinBox->setValue(libro->getYear());
    yearLabel->setFixedWidth(120);
    yearLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yearLabel->setMargin(10);
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(yearSpinBox);

    QHBoxLayout *pagesLayout = new QHBoxLayout();
    QLabel *pagesLabel = new QLabel("PAGINE:");
    pagesLabel->setObjectName("bookLabelsOverview");
    QLineEdit* pagesField = new QLineEdit();
    pagesField->setObjectName("formField");
    QRegularExpression intregex("^[1-9]\\d*$");
    QRegularExpressionValidator *validatorIntero = new QRegularExpressionValidator(intregex, this);
    pagesField->setValidator(validatorIntero);
    pagesField->setText(QString::number(libro->getPages()));
    pagesLabel->setFixedWidth(120);
    pagesLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    pagesLabel->setMargin(10);
    pagesLayout->addWidget(pagesLabel);
    pagesLayout->addWidget(pagesField);

    QHBoxLayout *authorLayout = new QHBoxLayout();
    QLabel *authorLabel = new QLabel("AUTORE:");
    authorLabel->setObjectName("bookLabelsOverview");
    QLineEdit* authorField = new QLineEdit();
    authorField->setObjectName("formField");
    authorField->setText(QString::fromStdString(libro->getAuthor()));
    QRegularExpression regexNome("[A-Za-z ]+");
    QRegularExpressionValidator *validatorAuthor = new QRegularExpressionValidator(regexNome, this);
    authorField->setValidator(validatorAuthor);
    authorLabel->setFixedWidth(120);
    authorLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    authorLabel->setMargin(10);
    authorLayout->addWidget(authorLabel);
    authorLayout->addWidget(authorField);

    QHBoxLayout *genreLayout = new QHBoxLayout();
    QLabel *genreLabel = new QLabel("GENERE:");
    genreLabel->setObjectName("bookLabelsOverview");
    QComboBox* genreComboBox = new QComboBox();
    QStringList genreList;
    for (auto gen : Book::genres) {
        genreList.append(QString::fromStdString(gen));
    }
    genreComboBox->addItems(genreList);
    genreComboBox->setCurrentText(QString::fromStdString(libro->getGenre()));
    genreLabel->setFixedWidth(120);
    genreLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    genreLabel->setMargin(10);
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(genreComboBox);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE");
    description->setObjectName("bookLabelsOverview");
    QTextEdit* descriptionField = new QTextEdit();
    descriptionField->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionField->setMinimumHeight(85);
    descriptionField->setObjectName("formField");
    descriptionField->setText(QString::fromStdString(libro->getDescription()));
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(descriptionField);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QPushButton *save = new QPushButton("Salva");
    save->setObjectName("saveChanges");
    save->setCursor(Qt::PointingHandCursor);
    buttonsLayout->addWidget(save);

    QPushButton *close = new QPushButton("Chiudi");
    close->setObjectName("confirmSelection");
    close->setCursor(Qt::PointingHandCursor);
    buttonsLayout->addWidget(close);

    vLayout->addLayout(titleLayout);
    vLayout->addLayout(yearLayout);
    vLayout->addLayout(pagesLayout);
    vLayout->addLayout(authorLayout);
    vLayout->addLayout(genreLayout);
    vLayout->addLayout(descriptionLayout);
    vLayout->addLayout(buttonsLayout);

    connect(close, &QPushButton::clicked, [this] {
        emit closeModifyWidget();
    });

    connect(save, &QPushButton::clicked, [=] {
        if (areInputsValid()) {
            libro->setTitle(titleField->text().toStdString());
            libro->setAuthor(authorField->text().toStdString());
            libro->setGenre(genreComboBox->currentText().toStdString());
            libro->setPages(pagesField->text().toUInt());
            libro->setDescription(descriptionField->toPlainText().toStdString());
            libro->setYear(yearSpinBox->value());
            libro->setStatus(false);
            emit saveChanges(libro->getId(), titleField->text());
            emit closeModifyWidget();
        }
    });

    rightWidget->setLayout(vLayout);
    layout->addWidget(imageWidget,1,Qt::AlignCenter);
    layout->addWidget(rightWidget,1,Qt::AlignVCenter | Qt::AlignLeft);

    modify->setLayout(layout);
    emit modifyWidgetCreated(modify);
}

void ModifyWidgetVisitor::visit(Music* music) {
    modify = new QWidget();

    QHBoxLayout* layout = new QHBoxLayout(modify);

    QWidget* imageWidget = new QWidget(modify);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* imageLayout = new QVBoxLayout(imageWidget);
    QLabel* image = new QLabel();
    QPixmap bookImage(":/assets/imgMusicBig.png");
    image->setPixmap(bookImage.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLayout->addWidget(image);

    QWidget* rightWidget = new QWidget(modify);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* vLayout = new QVBoxLayout(rightWidget);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("TITOLO:");
    titleLabel->setObjectName("musicLabelsOverview");
    QLineEdit* titleField = new QLineEdit();
    titleField->setMaxLength(40);
    titleField->setObjectName("formField");
    titleField->setText(QString::fromStdString(music->getTitle()));
    titleLabel->setFixedWidth(120);
    titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    titleLabel->setMargin(10);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleField);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *yearLabel = new QLabel("ANNO:");
    yearLabel->setObjectName("musicLabelsOverview");
    QSpinBox* yearSpinBox = new QSpinBox();
    yearLabel->setFixedWidth(120);
    yearLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yearLabel->setMargin(10);
    yearSpinBox->setRange(1300, QDate::currentDate().year());
    yearSpinBox->setValue(music->getYear());
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(yearSpinBox);

    QHBoxLayout *singerLayout = new QHBoxLayout();
    QLabel *singerLabel = new QLabel("CANTANTE:");
    singerLabel->setObjectName("musicLabelsOverview");
    QLineEdit* singerField = new QLineEdit();
    singerField->setObjectName("formField");
    QRegularExpression regexNome("[A-Za-z0-9 ]+");
    QRegularExpressionValidator *validatorSinger = new QRegularExpressionValidator(regexNome, this);
    singerField->setValidator(validatorSinger);
    singerField->setText(QString::fromStdString(music->getSinger()));
    singerLabel->setFixedWidth(120);
    singerLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    singerLabel->setMargin(10);
    singerLayout->addWidget(singerLabel);
    singerLayout->addWidget(singerField);

    QHBoxLayout *timeLayout = new QHBoxLayout();
    QLabel *timeLabel = new QLabel("DURATA:");
    timeLabel->setObjectName("musicLabelsOverview");
    timeLabel->setFixedWidth(120);
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    timeLabel->setMargin(10);
    QHBoxLayout *timeSelectionLayout = new QHBoxLayout();
    QSpinBox* hoursSpinBox = new QSpinBox();
    hoursSpinBox->setRange(0, 23);
    hoursSpinBox->setPrefix("Ore: ");
    hoursSpinBox->setValue(music->getHours());
    QSpinBox* minutesSpinBox = new QSpinBox();
    minutesSpinBox->setRange(0, 59);
    minutesSpinBox->setPrefix("Minuti: ");
    minutesSpinBox->setValue(music->getMinutes());
    QSpinBox* secondsSpinBox = new QSpinBox();
    secondsSpinBox->setRange(0, 59);
    secondsSpinBox->setPrefix("Secondi: ");
    secondsSpinBox->setValue(music->getSeconds());
    timeSelectionLayout->addWidget(hoursSpinBox);
    timeSelectionLayout->addWidget(minutesSpinBox);
    timeSelectionLayout->addWidget(secondsSpinBox);
    timeLayout->addWidget(timeLabel);
    timeLayout->addLayout(timeSelectionLayout);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE:");
    description->setObjectName("musicLabelsOverview");
    QTextEdit* descriptionField = new QTextEdit();
    descriptionField->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionField->setMinimumHeight(90);
    descriptionField->setObjectName("formField");
    descriptionField->setText(QString::fromStdString(music->getDescription()));
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(descriptionField);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QPushButton *save = new QPushButton("Salva");
    save->setObjectName("saveChanges");
    save->setCursor(Qt::PointingHandCursor);
    buttonsLayout->addWidget(save);

    QPushButton *close = new QPushButton("Chiudi");
    close->setObjectName("confirmSelection");
    close->setCursor(Qt::PointingHandCursor);
    buttonsLayout->addWidget(close);

    vLayout->addLayout(titleLayout);
    vLayout->addLayout(yearLayout);
    vLayout->addLayout(singerLayout);
    vLayout->addLayout(timeLayout);
    vLayout->addLayout(descriptionLayout);
    vLayout->addLayout(buttonsLayout);

    connect(close, &QPushButton::clicked, [this] {
        emit closeModifyWidget();
    });

    connect(save, &QPushButton::clicked, [=] {
        if (areInputsValid()) {
            music->setTitle(titleField->text().toStdString());
            music->setTime((secondsSpinBox->value() + minutesSpinBox->value() * 60 + hoursSpinBox->value() * 3600)%86400);
            music->setSinger(singerField->text().toStdString());
            music->setDescription(descriptionField->toPlainText().toStdString());
            music->setYear(yearSpinBox->value());
            music->setStatus(false);
            emit saveChanges(music->getId(), titleField->text());
            emit closeModifyWidget();
        }
    });

    rightWidget->setLayout(vLayout);
    layout->addWidget(imageWidget,1, Qt::AlignCenter);
    layout->addWidget(rightWidget,1,Qt::AlignVCenter | Qt::AlignLeft);
    modify->setLayout(layout);

    emit modifyWidgetCreated(modify);
}

void ModifyWidgetVisitor::visit(Film *film) {
    modify = new QWidget();

    QHBoxLayout* layout = new QHBoxLayout(modify);

    QWidget* imageWidget = new QWidget(modify);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* imageLayout = new QVBoxLayout(imageWidget);
    QLabel* image = new QLabel();
    QPixmap bookImage(":/assets/imgFilmBig.png");
    image->setPixmap(bookImage.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLayout->addWidget(image);

    QWidget* rightWidget = new QWidget(modify);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* vLayout = new QVBoxLayout(rightWidget);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("TITOLO:");
    titleLabel->setObjectName("filmLabelsOverview");
    QLineEdit* titleField = new QLineEdit();
    titleField->setMaxLength(40);
    titleField->setObjectName("formField");
    titleField->setText(QString::fromStdString(film->getTitle()));
    titleLabel->setFixedWidth(120);
    titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    titleLabel->setMargin(10);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleField);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *yearLabel = new QLabel("ANNO:");
    yearLabel->setObjectName("filmLabelsOverview");
    QSpinBox* yearSpinBox = new QSpinBox();
    yearLabel->setFixedWidth(120);
    yearLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yearLabel->setMargin(10);
    yearSpinBox->setRange(1300, QDate::currentDate().year());
    yearSpinBox->setValue(film->getYear());
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(yearSpinBox);

    QHBoxLayout *timeLayout = new QHBoxLayout();
    QLabel *timeLabel = new QLabel("DURATA:");
    timeLabel->setObjectName("filmLabelsOverview");
    timeLabel->setFixedWidth(120);
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    timeLabel->setMargin(10);
    QHBoxLayout *timeSelectionLayout = new QHBoxLayout();
    QSpinBox* hoursSpinBox = new QSpinBox();
    hoursSpinBox->setRange(0, 23);
    hoursSpinBox->setPrefix("Ore: ");
    hoursSpinBox->setValue(film->getHours());
    QSpinBox* minutesSpinBox = new QSpinBox();
    minutesSpinBox->setRange(0, 59);
    minutesSpinBox->setPrefix("Minuti: ");
    minutesSpinBox->setValue(film->getMinutes());
    QSpinBox* secondsSpinBox = new QSpinBox();
    secondsSpinBox->setRange(0, 59);
    secondsSpinBox->setPrefix("Secondi: ");
    secondsSpinBox->setValue(film->getSeconds());
    timeSelectionLayout->addWidget(hoursSpinBox);
    timeSelectionLayout->addWidget(minutesSpinBox);
    timeSelectionLayout->addWidget(secondsSpinBox);
    timeLayout->addWidget(timeLabel);
    timeLayout->addLayout(timeSelectionLayout);

    QHBoxLayout *genreLayout = new QHBoxLayout();
    QLabel *genreLabel = new QLabel("TIPOLOGIA:");
    QComboBox* genreComboBox = new QComboBox();
    QStringList tipologyList;
    for (auto t : Film::tipology) {
        tipologyList.append(QString::fromStdString(t));
    }
    genreComboBox->addItems(tipologyList);
    genreComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    genreComboBox->setCurrentText(QString::fromStdString(film->getGenre()));
    genreLabel->setObjectName("filmLabelsOverview");
    genreLabel->setFixedWidth(120);
    genreLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    genreLabel->setMargin(10);
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(genreComboBox);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE:");
    description->setObjectName("filmLabelsOverview");
    QTextEdit* descriptionField = new QTextEdit();
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionField->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionField->setMinimumHeight(90);
    descriptionField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    descriptionField->setObjectName("formField");
    descriptionField->setText(QString::fromStdString(film->getDescription()));
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(descriptionField);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QPushButton *save = new QPushButton("Salva");
    save->setObjectName("saveChanges");
    save->setCursor(Qt::PointingHandCursor);
    buttonsLayout->addWidget(save);

    QPushButton *close = new QPushButton("Chiudi");
    close->setObjectName("confirmSelection");
    close->setCursor(Qt::PointingHandCursor);
    buttonsLayout->addWidget(close);

    vLayout->addLayout(titleLayout);
    vLayout->addLayout(yearLayout);
    vLayout->addLayout(timeLayout);
    vLayout->addLayout(genreLayout);
    vLayout->addLayout(descriptionLayout);
    vLayout->addLayout(buttonsLayout);

    connect(close, &QPushButton::clicked, [this] {
        emit closeModifyWidget();
    });

    connect(save, &QPushButton::clicked, [=] {
        if (areInputsValid()) {
            film->setTitle(titleField->text().toStdString());
            film->setTime((secondsSpinBox->value() + minutesSpinBox->value() * 60 + hoursSpinBox->value() * 3600)%86400);
            film->setDescription(descriptionField->toPlainText().toStdString());
            film->setYear(yearSpinBox->value());
            film->setStatus(false);
            emit saveChanges(film->getId(), titleField->text());
            emit closeModifyWidget();
        }
    });

    rightWidget->setLayout(vLayout);
    layout->addWidget(imageWidget,1, Qt::AlignCenter);
    layout->addWidget(rightWidget,1,Qt::AlignVCenter | Qt::AlignLeft);
    modify->setLayout(layout);

    emit modifyWidgetCreated(modify);
}

QWidget * ModifyWidgetVisitor::getWidget() const{
    return modify;
}

bool ModifyWidgetVisitor::areInputsValid() const{
    QList<QWidget*> children = modify->findChildren<QWidget*>();

    for (QWidget* child : children) {
        if (QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(child)) {
            if (lineEdit->text().isEmpty()) {
                QMessageBox::warning(modify, "Errore", "I campi di testo non possono essere vuoti.");
                return false;
            }
        }
    }

    return true;
}
