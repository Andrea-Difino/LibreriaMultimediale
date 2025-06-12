//
// Created by adifi on 01/02/2025.
//

#include "SearchWidget.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QIcon>

#include "TopBar.h"

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);

    searchBar = new QLineEdit(this);
    searchBar->setObjectName("searchBar");
    searchBar->setFixedWidth(300);
    searchBar->setPlaceholderText("Cerca...");
    QIcon searchIcon(":/assets/search.png");
    searchBar->addAction(searchIcon, QLineEdit::LeadingPosition);

    connect(searchBar, &QLineEdit::textChanged,dynamic_cast<TopBar*>(parent),&TopBar::isSearching);

    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(spacer);
    layout->addWidget(searchBar);

    setLayout(layout);
}

QLineEdit * SearchWidget::getSearchBar() const {
    return searchBar;
}
