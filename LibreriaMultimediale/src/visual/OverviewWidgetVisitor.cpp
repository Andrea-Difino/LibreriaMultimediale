//
// Created by adifi on 06/03/2025.
//

#include "OverviewWidgetVisitor.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

#include "../logic/Book.h"
#include "../logic/Film.h"
#include "../logic/Music.h"

OverviewWidgetVisitor::OverviewWidgetVisitor(): overview(nullptr) {}

OverviewWidgetVisitor::~OverviewWidgetVisitor() {
    delete overview;
}

void OverviewWidgetVisitor::visit(Book *libro) {
    overview = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(overview);

    QWidget* imageWidget = new QWidget(overview);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* imageLayout = new QVBoxLayout(imageWidget);
    QLabel* image = new QLabel();
    QPixmap bookImage;

    if (libro->getImagePath() == "") {
        bookImage.load(":/assets/imgBookBig.png");
    } else {
        bookImage.load(QString::fromStdString(libro->getImagePath()));
    }

    image->setPixmap(bookImage);
    imageLayout->addWidget(image);

    QWidget* rightWidget = new QWidget(overview);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* vLayout = new QVBoxLayout(rightWidget);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("TITOLO:");
    titleLabel->setObjectName("bookLabelsOverview");
    QLabel* title = new QLabel(QString::fromStdString(libro->getTitle()));
    titleLabel->setFixedWidth(120);
    titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    titleLabel->setMargin(10);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(title);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *yearLabel = new QLabel("ANNO:");
    yearLabel->setObjectName("bookLabelsOverview");
    QLabel* year = new QLabel(QString::number(libro->getYear()));
    yearLabel->setFixedWidth(120);
    yearLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yearLabel->setMargin(10);
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(year);

    QHBoxLayout *pagesLayout = new QHBoxLayout();
    QLabel *pagesLabel = new QLabel("PAGINE:");
    pagesLabel->setObjectName("bookLabelsOverview");
    QLabel* pages = new QLabel(QString::number(libro->getPages()));
    pagesLabel->setFixedWidth(120);
    pagesLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    pagesLabel->setMargin(10);
    pagesLayout->addWidget(pagesLabel);
    pagesLayout->addWidget(pages);

    QHBoxLayout *authorLayout = new QHBoxLayout();
    QLabel *authorLabel = new QLabel("AUTORE:");
    authorLabel->setObjectName("bookLabelsOverview");
    QLabel* author = new QLabel(QString::fromStdString(libro->getAuthor()));
    authorLabel->setFixedWidth(120);
    authorLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    authorLabel->setMargin(10);
    authorLayout->addWidget(authorLabel);
    authorLayout->addWidget(author);

    QHBoxLayout *genreLayout = new QHBoxLayout();
    QLabel *genreLabel = new QLabel("GENERE:");
    genreLabel->setObjectName("bookLabelsOverview");
    QLabel* genre = new QLabel(QString::fromStdString(libro->getGenre()));
    genreLabel->setFixedWidth(120);
    genreLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    genreLabel->setMargin(10);
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(genre);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE");
    description->setObjectName("bookLabelsOverview");
    QLabel* descriptionField = new QLabel(QString::fromStdString(libro->getDescription()));
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionField->setWordWrap(true);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("background-color: white;");
    scrollArea->setWidget(descriptionField);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedHeight(100);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(scrollArea);

    QPushButton *close = new QPushButton("Chiudi");
    close->setObjectName("confirmSelection");
    close->setCursor(Qt::PointingHandCursor);

    vLayout->addLayout(titleLayout);
    vLayout->addLayout(yearLayout);
    vLayout->addLayout(pagesLayout);
    vLayout->addLayout(authorLayout);
    vLayout->addLayout(genreLayout);
    vLayout->addLayout(descriptionLayout);
    vLayout->addWidget(close,0,Qt::AlignHCenter);

    connect(close, &QPushButton::clicked, [this] {
        emit closeOverview();
    });

    rightWidget->setLayout(vLayout);
    layout->addWidget(imageWidget,1,Qt::AlignCenter);
    layout->addWidget(rightWidget,1,Qt::AlignVCenter | Qt::AlignLeft);

    overview->setLayout(layout);
    emit overviewWidgetCreated(overview);
}

void OverviewWidgetVisitor::visit(Music* music) {
    overview = new QWidget();

    QHBoxLayout* layout = new QHBoxLayout(overview);

    QWidget* imageWidget = new QWidget(overview);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* imageLayout = new QVBoxLayout(imageWidget);
    QLabel* image = new QLabel();
    QPixmap musicImage;

    if (music->getImagePath() == "") {
        musicImage.load(":/assets/imgMusicBig.png");
    } else {
        musicImage.load(QString::fromStdString(music->getImagePath()));
    }
    image->setPixmap(musicImage);
    imageLayout->addWidget(image);

    QWidget* rightWidget = new QWidget(overview);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* vLayout = new QVBoxLayout(rightWidget);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("TITOLO:");
    titleLabel->setObjectName("musicLabelsOverview");
    QLabel* title = new QLabel(QString::fromStdString(music->getTitle()));
    titleLabel->setFixedWidth(120);
    titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    titleLabel->setMargin(10);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(title);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *yearLabel = new QLabel("ANNO:");
    yearLabel->setObjectName("musicLabelsOverview");
    QLabel* year = new QLabel(QString::number(music->getYear()));
    yearLabel->setFixedWidth(120);
    yearLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yearLabel->setMargin(10);
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(year);

    QHBoxLayout *singerLayout = new QHBoxLayout();
    QLabel *singerLabel = new QLabel("CANTANTE:");
    singerLabel->setObjectName("musicLabelsOverview");
    QLabel* singer = new QLabel(QString::fromStdString(music->getSinger()));
    singerLabel->setFixedWidth(120);
    singerLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    singerLabel->setMargin(10);
    singerLayout->addWidget(singerLabel);
    singerLayout->addWidget(singer);

    QHBoxLayout *timeLayout = new QHBoxLayout();
    QLabel *timeLabel = new QLabel("DURATA:");
    timeLabel->setObjectName("musicLabelsOverview");
    timeLabel->setFixedWidth(120);
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    timeLabel->setMargin(10);
    QLabel *time = new QLabel(QString::fromStdString(music->getExtendedLength()));
    timeLayout->addWidget(timeLabel);
    timeLayout->addWidget(time);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE:");
    description->setObjectName("musicLabelsOverview");
    QLabel* descriptionField = new QLabel(QString::fromStdString(music->getDescription()));
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionField->setWordWrap(true);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("background-color: white;");
    scrollArea->setWidget(descriptionField);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedHeight(100);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(scrollArea);

    QPushButton *close = new QPushButton("Chiudi");
    close->setObjectName("confirmSelection");
    close->setCursor(Qt::PointingHandCursor);

    vLayout->addLayout(titleLayout);
    vLayout->addLayout(yearLayout);
    vLayout->addLayout(singerLayout);
    vLayout->addLayout(timeLayout);
    vLayout->addLayout(descriptionLayout);
    vLayout->addWidget(close,0,Qt::AlignHCenter);

    connect(close, &QPushButton::clicked, [this] {
        emit closeOverview();
    });

    rightWidget->setLayout(vLayout);
    layout->addWidget(imageWidget,1, Qt::AlignCenter);
    layout->addWidget(rightWidget,1,Qt::AlignVCenter | Qt::AlignLeft);
    overview->setLayout(layout);

    emit overviewWidgetCreated(overview);
}

void OverviewWidgetVisitor::visit(Film *film) {
    overview = new QWidget();

    QHBoxLayout* layout = new QHBoxLayout(overview);

    QWidget* imageWidget = new QWidget(overview);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* imageLayout = new QVBoxLayout(imageWidget);
    QLabel* image = new QLabel();
    QPixmap filmImage;

    if (film->getImagePath() == "") {
        filmImage.load(":/assets/imgFilmBig.png");
    } else {
        filmImage.load(QString::fromStdString(film->getImagePath()));
    }
    image->setPixmap(filmImage);
    imageLayout->addWidget(image);

    QWidget* rightWidget = new QWidget(overview);
    rightWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* vLayout = new QVBoxLayout(rightWidget);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("TITOLO:");
    titleLabel->setObjectName("filmLabelsOverview");
    QLabel* title = new QLabel(QString::fromStdString(film->getTitle()));
    titleLabel->setFixedWidth(120);
    titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    titleLabel->setMargin(10);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(title);

    QHBoxLayout *yearLayout = new QHBoxLayout();
    QLabel *yearLabel = new QLabel("ANNO:");
    yearLabel->setObjectName("filmLabelsOverview");
    QLabel* year = new QLabel(QString::number(film->getYear()));
    yearLabel->setFixedWidth(120);
    yearLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    yearLabel->setMargin(10);
    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(year);

    QHBoxLayout *timeLayout = new QHBoxLayout();
    QLabel *timeLabel = new QLabel("DURATA:");
    timeLabel->setObjectName("filmLabelsOverview");
    timeLabel->setFixedWidth(120);
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    timeLabel->setMargin(10);
    QLabel *time = new QLabel(QString::fromStdString(film->getExtendedLength()));
    timeLayout->addWidget(timeLabel);
    timeLayout->addWidget(time);

    QHBoxLayout *genreLayout = new QHBoxLayout();
    QLabel *genreLabel = new QLabel("TIPOLOGIA:");
    QLabel *genre = new QLabel(QString::fromStdString(film->getGenre()));
    genreLabel->setObjectName("filmLabelsOverview");
    genreLabel->setFixedWidth(120);
    genreLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    genreLabel->setMargin(10);
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(genre);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    QLabel *description = new QLabel("DESCRIZIONE:");
    description->setObjectName("filmLabelsOverview");
    QLabel* descriptionField = new QLabel(QString::fromStdString(film->getDescription()));
    description->setFixedWidth(120);
    description->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    description->setMargin(10);
    descriptionField->setWordWrap(true);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("background-color: white;");
    scrollArea->setWidget(descriptionField);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedHeight(100);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    descriptionLayout->addWidget(description);
    descriptionLayout->addWidget(scrollArea);

    QPushButton *close = new QPushButton("Chiudi");
    close->setObjectName("confirmSelection");
    close->setCursor(Qt::PointingHandCursor);

    vLayout->addLayout(titleLayout);
    vLayout->addLayout(yearLayout);
    vLayout->addLayout(timeLayout);
    vLayout->addLayout(genreLayout);
    vLayout->addLayout(descriptionLayout);
    vLayout->addWidget(close,0,Qt::AlignHCenter);

    connect(close, &QPushButton::clicked, [this] {
        emit closeOverview();
    });

    rightWidget->setLayout(vLayout);
    layout->addWidget(imageWidget,1, Qt::AlignCenter);
    layout->addWidget(rightWidget,1,Qt::AlignVCenter | Qt::AlignLeft);
    overview->setLayout(layout);

    emit overviewWidgetCreated(overview);
}

QWidget * OverviewWidgetVisitor::getWidget() const{
    return overview;
}
