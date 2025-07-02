//
// Created by adifi on 1/07/2025.
//

#include "ImageHandler.h"
#include <QFileDialog>

ImageHandler::ImageHandler(QWidget* parent) : QWidget(parent){}

QImage ImageHandler::scaleToFit(const QImage &src, int maxWidth, int maxHeight) {
    if (src.isNull()) return QImage();
    return src.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}


QString ImageHandler::addImage(){
    QString filePath = QFileDialog::getOpenFileName(this,
                        "Seleziona un'immagine",
                        QDir::homePath(),
                        "Immagini (*.png *.jpg *.jpeg *.bmp *.gif)");
    return filePath;
}

QString ImageHandler::generateUniqueFileName(const QString& dirPath, const QString& baseName) {
    QFileInfo fi(baseName);
    QString name = fi.completeBaseName();
    QString ext = fi.suffix();

    QString newName = baseName;
    int counter = 1;
    QDir dir(dirPath);

    while (dir.exists(newName)) {
        newName = QString("%1_%2.%3").arg(name).arg(counter).arg(ext);
        counter++;
    }

    return newName;
}

QString ImageHandler::copyImageToDestination(const QString& sourcePath, const QString& destFolder) {
    if (sourcePath.isEmpty()) return "";

    QFileInfo fi(sourcePath);
    QString fileName = fi.fileName();

    if (!QFile::exists(sourcePath)) {
        qWarning() << "File non trovato:" << sourcePath;
        return "";
    }

    QDir dir(destFolder);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString uniqueFileName = generateUniqueFileName(destFolder, fileName);
    QString destPath = dir.filePath(uniqueFileName);

    if (QFileInfo(sourcePath).absoluteFilePath() == QFileInfo(destPath).absoluteFilePath()) {
        qDebug() << "File già nella destinazione. Nessuna copia necessaria.";
        return destPath;
    }

    QImage img(sourcePath);
    if (img.isNull()) {
        qWarning() << "Impossibile caricare immagine da" << sourcePath;
        return "";
    }

    QImage processedImg = scaleToFit(img, 300, 300);

    if (!processedImg.save(destPath)) {
	qWarning() << "Errore nel salvataggio dell'immagine ridimensionata in" << destPath;
	return "";
        
    }
    destPath = "itemsCover/" + uniqueFileName;
    return destPath;
}
