//
// Created by adifi on 01/02/2025.
//

#include "TopBar.h"
#include "MainWidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QShortcut>

TopBar::TopBar(QWidget *parent) : QWidget(parent){

    QHBoxLayout *layout = new QHBoxLayout(this);

    saveFile = new QPushButton(this);
    saveFile->setCursor(Qt::PointingHandCursor);
    QIcon saveIcon(":/assets/save.png");
    saveFile->setIcon(saveIcon);
    saveFile->setObjectName("saveFileBtn");
    
    QShortcut* saveShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(saveShortcut, &QShortcut::activated, dynamic_cast<MainWidget*>(this->parent()), &MainWidget::handleSave);

    connect(saveFile, &QPushButton::clicked, dynamic_cast<MainWidget*>(this->parent()), &MainWidget::handleSave);

    uploadFile = new QPushButton(this);
    uploadFile->setCursor(Qt::PointingHandCursor);
    QIcon uploadIcon(":/assets/upload.png");
    uploadFile->setIcon(uploadIcon);
    uploadFile->setObjectName("UploadFileBtn");
    
    QShortcut* uploadShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(uploadShortcut, &QShortcut::activated, dynamic_cast<MainWidget*>(this->parent()), &MainWidget::loadJSONFile);

    connect(uploadFile, &QPushButton::clicked,dynamic_cast<MainWidget*>(this->parent()), &MainWidget::loadJSONFile);

    createFile = new QPushButton(this);
    createFile->setCursor(Qt::PointingHandCursor);
    QIcon createFileIcon(":/assets/createFile.png");
    createFile->setIcon(createFileIcon);
    createFile->setObjectName("createFileBtn");
    
    QShortcut* createShortcut = new QShortcut(QKeySequence("Ctrl+N"), this);
    connect(createShortcut, &QShortcut::activated, dynamic_cast<MainWidget*>(this->parent()), &MainWidget::createJSONFile);

    connect(createFile, &QPushButton::clicked,dynamic_cast<MainWidget*>(this->parent()), &MainWidget::createJSONFile);

    changePageBtn = new QPushButton(this);
    changePageBtn->setText("AGGIUNGI");
    changePageBtn->setObjectName("changePageBtn");
    changePageBtn->setCursor(Qt::PointingHandCursor);

    connect(changePageBtn, &QPushButton::clicked, dynamic_cast<MainWidget*>(this->parent()),&MainWidget::changePage);

    layout->addWidget(saveFile);
    layout->addWidget(uploadFile);
    layout->addWidget(createFile);
    layout->addStretch();

    searchBar = new SearchWidget(this);
    layout->addWidget(searchBar,1,Qt::AlignHCenter);
    
    connect(this, &TopBar::isSearching, dynamic_cast<MainWidget*>(parent), &MainWidget::filterLibraryByRegex);

    layout->addStretch();
    layout->addWidget(changePageBtn);
}

QPushButton * TopBar::getChangePageBtn() const {
    return changePageBtn;
}

SearchWidget * TopBar::getSearchWidget() const {
    return searchBar;
}

QPushButton * TopBar::getSaveFile() const {
    return saveFile;
}

QPushButton * TopBar::getUploadFile() const {
    return uploadFile;
}

QPushButton * TopBar::getCreateFile() const {
    return createFile;
}
