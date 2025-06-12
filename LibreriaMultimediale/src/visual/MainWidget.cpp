//
// Created by ANDREA on 19/12/2024.
//

#include "MainWidget.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QJsonDocument>
#include <QStandardPaths>
#include "../logic/Book.h"
#include "../logic/Music.h"
#include "../logic/Film.h"

QString desk_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

MainWidget::MainWidget(QWidget *parent) : QWidget(parent){
    this->resize(850,500);
    this->setMinimumSize(this->size());

    library = new Library();
    jsonVisitor = new JSONVisitor(library, this);
    overview_widget_ = new OverviewWidgetVisitor();
    modify_widget_visitor_ = new ModifyWidgetVisitor();

    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    topBar = new TopBar(this);
    topBar->setMinimumHeight(80);
    topBar->setMaximumHeight(100);
    topBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    filtersWidget = new QWidget(this);
    filtersWidget->setMinimumHeight(30);
    filtersWidget->setContentsMargins(20,0,0,0);

    QHBoxLayout *filtersLayout = new QHBoxLayout();
    filtersLayout->setAlignment(Qt::AlignHCenter);
    QLabel* music_label = new QLabel("Musica");
    QPushButton* selectMusic = new QPushButton();
    selectMusic->setCheckable(true);
    selectMusic->setCursor(QCursor(Qt::PointingHandCursor));
    selectMusic->setObjectName("filtersButtons");
    filtersLayout->addWidget(music_label);
    filtersLayout->addWidget(selectMusic);

    QLabel* film_label = new QLabel("Film");
    QPushButton* selectFilm = new QPushButton();
    selectFilm->setCheckable(true);
    selectFilm->setCursor(QCursor(Qt::PointingHandCursor));
    selectFilm->setObjectName("filtersButtons");
    filtersLayout->addWidget(film_label);
    filtersLayout->addWidget(selectFilm);

    QLabel* book_label = new QLabel("Libri");
    QPushButton* selectBook = new QPushButton();
    selectBook->setCheckable(true);
    selectBook->setCursor(QCursor(Qt::PointingHandCursor));
    selectBook->setObjectName("filtersButtons");
    filtersLayout->addWidget(book_label);
    filtersLayout->addWidget(selectBook);

    filtersWidget->setLayout(filtersLayout);

    connect(selectMusic, &QPushButton::clicked, [=] {
        filterItemsByType(selectBook,selectFilm,selectMusic);
    });
    connect(selectBook, &QPushButton::clicked, [=] {
        filterItemsByType(selectBook,selectFilm,selectMusic);
    });
    connect(selectFilm, &QPushButton::clicked, [=] {
        filterItemsByType(selectBook,selectFilm,selectMusic);
    });

    pagesStack = new QStackedWidget(this);
    pagesStack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(overview_widget_, &OverviewWidgetVisitor::overviewWidgetCreated, this, &MainWidget::addOverviewToLookAtPage);
    connect(overview_widget_, &OverviewWidgetVisitor::closeOverview, this, &MainWidget::changePage);

    connect(modify_widget_visitor_, &ModifyWidgetVisitor::modifyWidgetCreated, this, &MainWidget::addModifyToModifyPage);
    connect(modify_widget_visitor_, &ModifyWidgetVisitor::closeModifyWidget, this, &MainWidget::changePage);
    connect(modify_widget_visitor_, &ModifyWidgetVisitor::saveChanges, this, &MainWidget::changeItemCard);

    homePage = new QWidget(pagesStack);
    QWidget* homePageContainer = new QWidget(homePage);
    homePageContainer->setStyleSheet("background-color: white;");
    homePageContainer->setMinimumWidth(600);
    homePageContainer->setMinimumHeight(500);
    homePageContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    flowLayout = new QFlowLayout();
    homePageContainer->setLayout(flowLayout);
    flowLayout->setContentsMargins(10, 10, 10, 10);
    flowLayout->setSpacing(20);


    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(homePageContainer);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QVBoxLayout *homeLayout = new QVBoxLayout(homePage);
    homeLayout->setContentsMargins(30,30,30,30);
    homeLayout->addWidget(scrollArea);
    homePage->setLayout(homeLayout);

    addPage = new QWidget(pagesStack);
    QHBoxLayout *addPageLayout = new QHBoxLayout(addPage);
    addPageLayout->setContentsMargins(30,10,30,30);
    addPageLayout->setAlignment(Qt::AlignCenter);

    QWidget* comboBoxContainer = new QWidget(this);
    comboBoxContainer->setObjectName("comboBoxContainer");
    QVBoxLayout *comboBoxLayout = new QVBoxLayout();
    comboBoxLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    comboBoxLayout->setContentsMargins(20,30,20,30);
    comboBoxContainer->setLayout(comboBoxLayout);
    comboBoxContainer->setMaximumHeight(150);
    comboBoxContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    QLabel* comboBoxLabel = new QLabel("Cosa vuoi creare?");
    comboBoxLabel->setStyleSheet("border: none;");
    comboBoxLayout->addWidget(comboBoxLabel);

    QComboBox *comboBox = new QComboBox();
    comboBoxLayout->addWidget(comboBox);
    comboBox->addItem("Libro");
    comboBox->addItem("Musica");
    comboBox->addItem("Film");
    comboBox->setCurrentIndex(0);

    addPageLayout->addWidget(comboBoxContainer, 1, Qt::AlignCenter);

    currentForm = new Form(0, this); // 0 corrisponde all'indice del "Libro"
    addPageLayout->addWidget(currentForm, 1, Qt::AlignCenter);

    connect(comboBox, &QComboBox::currentIndexChanged, [addPageLayout, this](int index) {
        if (currentForm) {
            addPageLayout->removeWidget(currentForm);
            currentForm->deleteLater();
        }
        currentForm = new Form(index, this);
        addPageLayout->addWidget(currentForm, 1, Qt::AlignCenter);
    });

    lookAtPage = new QWidget(pagesStack);
    QHBoxLayout* lookAtPageLayout = new QHBoxLayout(lookAtPage);
    lookAtPageLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lookAtPage->setLayout(lookAtPageLayout);

    modifyPage = new QWidget(pagesStack);
    QHBoxLayout* modifyPageLayout = new QHBoxLayout(modifyPage);
    modifyPageLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    modifyPage->setLayout(modifyPageLayout);

    pagesStack->addWidget(homePage);
    pagesStack->addWidget(addPage);
    pagesStack->addWidget(lookAtPage);
    pagesStack->addWidget(modifyPage);

    mainLayout->addWidget(topBar);
    mainLayout->addWidget(filtersWidget,0,Qt::AlignLeft);
    mainLayout->addWidget(pagesStack);

    this->setLayout(mainLayout);
}

MainWidget::~MainWidget() {
    delete overview_widget_;
    delete modify_widget_visitor_;
    delete library;
}

void MainWidget::changePage() {
    if (pagesStack->currentIndex() == 0) {
        pagesStack->setCurrentIndex(1);
        topBar->getChangePageBtn()->setText("HOME");
        topBar->getSearchWidget()->hide();
        topBar->getSaveFile()->hide();
        topBar->getUploadFile()->hide();
        topBar->getCreateFile()->hide();
        filtersWidget->hide();
    }else if (pagesStack->currentIndex() == 1){
        pagesStack->setCurrentIndex(0);
        filtersWidget->show();
        topBar->getChangePageBtn()->setText("AGGIUNGI");
        topBar->getSearchWidget()->show();
        topBar->getSaveFile()->show();
        topBar->getCreateFile()->show();
        topBar->getUploadFile()->show();
    }else {
        pagesStack->setCurrentIndex(0);
        topBar->getSearchWidget()->show();
        topBar->getSaveFile()->show();
        topBar->getUploadFile()->show();
        topBar->getCreateFile()->show();
        topBar->getChangePageBtn()->show();
        filtersWidget->show();
        flowLayout->update();
    }
}

void MainWidget::handleSave() {
    checkFileExist();
    saveFile();
}

void MainWidget::saveFile() {
    if (library->getStatus()) {
        return;
    }
    library->applyVisitor(jsonVisitor);
    jsonVisitor->saveToFile();
    library->setStatus(true);
    QMessageBox::information(this, "Stato", "File Salvato Correttamente");
}

void MainWidget::checkFileExist() {
    if (JSONFileHandler::getLastDatabasePath().isEmpty()) {
        QString filePath;
        do {
            filePath = QFileDialog::getSaveFileName(this, "Crea Nuovo Database",
                QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                "JSON Files (*.json)", nullptr, QFileDialog::DontUseNativeDialog);
            if (filePath.isEmpty()) {
                return;
            }
            if (QFile::exists(filePath)) {
                QMessageBox::warning(this, "Errore", "Il file esiste già. Devi creare un nuovo database.");
            } else {
                break;
            }
        } while (true);
        if (!filePath.contains(".json")) {filePath = filePath + ".json";}
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            QJsonDocument emptyDoc{QJsonArray()};
            file.write(emptyDoc.toJson());
            file.close();
        } else {
            QMessageBox::critical(this, "Errore", "Impossibile creare il nuovo file JSON.");
            return;
        }
        JSONFileHandler::saveLastDatabasePath(filePath);
    }
}

void MainWidget::loadJSONFile() {
    if (!library->getStatus()) {
        QMessageBox::StandardButton saveBeforeUpload = QMessageBox::question(this, "Libreria non salvata",
                                                                     "La libreria non è stata salvata. Vuoi salvare prima di uscire?",
                                                                     QMessageBox::Save | QMessageBox::Discard);
        if (saveBeforeUpload == QMessageBox::Save) {
            saveFile();
        }
    }

    QString filePath = QFileDialog::getOpenFileName(this, "Seleziona file JSON", desk_path, "JSON Files (*.json)",nullptr, QFileDialog::DontUseNativeDialog);
    if (filePath == JSONFileHandler::getLastDatabasePath()) return;
    if (!filePath.isEmpty()) {
        JSONFileHandler::saveLastDatabasePath(filePath);
        jsonVisitor->loadFromFile(filePath);
    }
}

void MainWidget::createJSONFile() {
    if (!library->getStatus()) {
        if (JSONFileHandler::getLastDatabasePath().isEmpty()) {
            QMessageBox::StandardButton saveCurrent = QMessageBox::question(
            this, "Salvataggio richiesto",
            "Hai modificato la libreria ma non è mai stata salvata. Vuoi salvarla prima di creare un nuovo database?",
            QMessageBox::Save | QMessageBox::Discard
            );

            if (saveCurrent == QMessageBox::Save) {

                QString savePath;
                do {
                    savePath = QFileDialog::getSaveFileName(
                        this, "Salva Libreria Corrente",
                        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                        "JSON Files (*.json)", nullptr, QFileDialog::DontUseNativeDialog
                    );

                    if (savePath.isEmpty()) return;

                    if (QFile::exists(savePath)) {
                        QMessageBox::warning(this, "Errore", "Il file esiste già. Scegli un nuovo nome.");
                    } else {
                        break;
                    }
                } while (true);

                if (!savePath.endsWith(".json")) {
                    savePath += ".json";
                }

                JSONFileHandler::saveLastDatabasePath(savePath);
                saveFile();
            }

            library->getVector().clear();
            JSONFileHandler::saveLastDatabasePath("");
        }else {
            library->getVector().clear();
            saveFile();
        }
    }

    QString filePath;
    do {
        filePath = QFileDialog::getSaveFileName(this, "Crea Nuovo Database",
            QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
            "JSON Files (*.json)", nullptr, QFileDialog::DontUseNativeDialog);

        if (filePath.isEmpty()) return;

        if (QFile::exists(filePath)) {
            QMessageBox::warning(this, "Errore", "Il file esiste già. Devi scegliere un nuovo nome.");
        } else {
            break;
        }
    } while (true);

    if (!filePath.endsWith(".json")) filePath += ".json";

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument emptyDoc{QJsonArray()};
        file.write(emptyDoc.toJson());
        file.close();
    } else {
        QMessageBox::critical(this, "Errore", "Impossibile creare il nuovo file JSON.");
        return;
    }

    jsonVisitor->loadFromFile(filePath);
    QMessageBox::information(this, "Database creato", "Nuovo database creato correttamente.");
}

void MainWidget::changeItemCard(unsigned int id, QString title) {
    for (auto itemCard : item_cards_) {
        if (itemCard->getItem()->getId() == id) {
            itemCard->setTitleLabel(title);
        }
    }
    library->setStatus(false);
    jsonVisitor->removeItemById(id); //mi serve per evitare duplicati nel DB.
}

void MainWidget::filterItemsByType(QPushButton* selectBook, QPushButton* selectFilm, QPushButton* selectMusic) {
    bool showBooks = selectBook->isChecked();
    bool showFilms = selectFilm->isChecked();
    bool showMusic = selectMusic->isChecked();

    for (auto item : item_cards_) {
        auto* itemPtr = item->getItem();
        bool isBook = dynamic_cast<Book*>(itemPtr) != nullptr;
        bool isFilm = dynamic_cast<Film*>(itemPtr) != nullptr;
        bool isMusic = dynamic_cast<Music*>(itemPtr) != nullptr;

        bool shouldShow = (!showBooks && !showFilms && !showMusic) ||
                          (showBooks && isBook) ||
                          (showFilms && isFilm) ||
                          (showMusic && isMusic);

        item->setVisible(shouldShow);
    }
    flowLayout->update();
}

void MainWidget::addOverviewToLookAtPage(QWidget *widget) {
    addSpecialWidgetToPage(widget, lookAtPage, 2);
}

void MainWidget::addModifyToModifyPage(QWidget *widget) {
    addSpecialWidgetToPage(widget, modifyPage, 3);
}

void MainWidget::addSpecialWidgetToPage(QWidget *widget, QWidget *page, int pageIndex) {
    pagesStack->setCurrentIndex(pageIndex);

    topBar->getSearchWidget()->hide();
    topBar->getSaveFile()->hide();
    topBar->getUploadFile()->hide();
    topBar->getChangePageBtn()->hide();
    topBar->getCreateFile()->hide();
    filtersWidget->hide();

    QLayout* layout = page->layout();

    if (layout) {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
        layout->addWidget(widget);
    }
}

void MainWidget::filterLibraryByRegex(const QString& searchText) {
    QRegularExpression regex(searchText, QRegularExpression::CaseInsensitiveOption);
    for (auto item : item_cards_) {
        if (item) {
                QString title = QString::fromStdString(item->getItem()->getTitle());
                if (regex.match(title).hasMatch() || searchText.isEmpty()) {
                    item->show();
                } else {
                    item->hide();
                }
        }
    }
    flowLayout->update();
}

void MainWidget::deleteItem(QWidget* widget) {
    ItemCard* itemToRemove = dynamic_cast<ItemCard*>(widget);
    if (itemToRemove) {
        QMessageBox::StandardButton risposta = QMessageBox::question(this, "Eliminazione Item",
                                                                     "Sicuro di voler eliminare questo item?",
                                                                     QMessageBox::Yes | QMessageBox::No);
        if (risposta == QMessageBox::Yes) {
            for (int i = 0; i < flowLayout->count(); ++i) {
                QLayoutItem* item = flowLayout->itemAt(i);
                if (item && item->widget()) {
                    ItemCard* card = dynamic_cast<ItemCard*>(item->widget());
                    if (card && card->getItem()->getId() == itemToRemove->getItem()->getId()) {
                        library->removeItemById(card->getItem()->getId()); //rimuovo l'item dalla libreria
                        flowLayout->removeItem(item);
                        jsonVisitor->removeItemById(card->getItem()->getId()); //rimuovo l'item dal JsonArray
                        item_cards_.erase(item_cards_.begin() + i); //rimuovo l'item card dal vector

                        delete item->widget();
                        delete item;

                        flowLayout->update();
                        library->setStatus(false);
                        break;
                    }
                }
            }
        }
    }
}

void MainWidget::closeEvent(QCloseEvent *event) {
    if (!library->getStatus()) {
        QMessageBox::StandardButton risposta = QMessageBox::question(this, "Libreria non salvata",
                                                                     "La libreria non è stata salvata. Vuoi salvare prima di uscire?",
                                                                     QMessageBox::Save | QMessageBox::Discard |
                                                                     QMessageBox::Cancel,
                                                                     QMessageBox::Save);
        if (risposta == QMessageBox::Save) {
            saveFile();
            event->accept();
        } else if (risposta == QMessageBox::Discard) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}

void MainWidget::removeWidgetsFromUI() {
    while (QLayoutItem *item = this->flowLayout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    for (auto itemCard : item_cards_) {
        delete itemCard;
    }
    item_cards_.clear();
}

ModifyWidgetVisitor * MainWidget::getModifyWidgetVisitor() const {
    return modify_widget_visitor_;
}

OverviewWidgetVisitor * MainWidget::getOvervieWidget() const{
    return overview_widget_;
}

Library * MainWidget::getLibrary() const {
    return library;
}

void MainWidget::addW_notification(QWidget* widget) {
    addWidgetToUI(widget);
    item_cards_.push_back(dynamic_cast<ItemCard*>(widget));
    flowLayout->setGeometry(flowLayout->geometry());
}

void MainWidget::addWidgetToUI(QWidget* widget) {
    if (!flowLayout) return;
    flowLayout->addWidget(widget);
    flowLayout->invalidate();
    flowLayout->activate();
    update();
    repaint();
}


void MainWidget::removeW_notification() {
    removeWidgetsFromUI();
}

