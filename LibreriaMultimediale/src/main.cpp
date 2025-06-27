#include <QApplication>
#include <QFileInfo>
#include <QFontDatabase>
#include "visual/MainWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName("Libreria Multimediale");
    a.setApplicationDisplayName("Libreria Multimediale");
    int id = QFontDatabase::addApplicationFont(":/font/mainFont.ttf");
    if (id != -1) {
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont font(family, 11);
        QApplication::setFont(font);
    } else {
        qDebug() << "Errore nel caricamento del font";
    }

    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Errore Impossibile caricare il file QSS.";
    }
    //Uso Mainwidget, classe derivata da QWidget, al posto di QMainWindow, per avere una finestra al 100% personalizzabile e leggera
    MainWidget mainFrame;
    mainFrame.show();

    return QApplication::exec();
}
