//
// Created by ANDREA on 19/12/2024.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include "TopBar.h"
#include <QStackedWidget>
#include <QComboBox>
#include "QFlowLayout.h"
#include "../logic/Library.h"
#include "Form.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include "OverviewWidgetVisitor.h"
#include <QScrollArea>
#include "../logic/ObserverInterface.h"
#include "../io/JSONVisitor.h"
#include "ItemCard.h"
#include "ModifyWidgetVisitor.h"

class Form;
class JSONVisitor;
class OverviewWidgetVisitor;
class ModifyWidgetVisitor;
class ItemCard;

class MainWidget: public QWidget, public ObserverInterface {
    Q_OBJECT
    public:
        explicit MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

        void addW_notification(QWidget* widget) override;
        void removeW_notification() override;

        void addWidgetToUI(QWidget* widget);
        void removeWidgetsFromUI();

        ModifyWidgetVisitor* getModifyWidgetVisitor() const;
        OverviewWidgetVisitor* getOvervieWidget() const;
        Library* getLibrary() const;
    private:
        JSONVisitor *jsonVisitor;
        QVBoxLayout* mainLayout;
        TopBar *topBar;
        QWidget* filtersWidget;
        QStackedWidget* pagesStack;
        QWidget* homePage;
        QFlowLayout *flowLayout;
        QWidget* addPage;
        Form* currentForm;
        QWidget* lookAtPage;
        QWidget* modifyPage;
        OverviewWidgetVisitor* overview_widget_;
        ModifyWidgetVisitor* modify_widget_visitor_;
        Library* library;
        std::vector<ItemCard*> item_cards_;
        void addSpecialWidgetToPage(QWidget *widget, QWidget *page, int pageIndex);
        void filterItems(QComboBox* typeCombo, QCheckBox* favCheckbox);
    protected:
        void closeEvent(QCloseEvent *event) override;
    public slots:
        void changePage();
        void loadJSONFile();
        void createJSONFile();
        void handleSave();
        void deleteItem(QWidget* widget);
        void filterLibraryByRegex(const QString& searchText);
    private slots:
        void saveFile();
        void checkFileExist();
        void addOverviewToLookAtPage(QWidget* widget);
        void addModifyToModifyPage(QWidget* widget);
        void changeItemCard(unsigned int id, QString title);
        void handleItemStatusChange(unsigned int id);
    signals: 
    	void itemStatusChanged(unsigned int id);
};



#endif //MAINWIDGET_H
