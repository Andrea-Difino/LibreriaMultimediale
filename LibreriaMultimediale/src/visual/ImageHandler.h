//
// Created by adifi on 1/07/2025.
//

#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QString>
#include <QImage>
#include <QWidget>

class ImageHandler : public QWidget{
    Q_OBJECT
    public: 
	ImageHandler(QWidget* parent = nullptr);
	~ImageHandler() = default;
	
	QString addImage();
	static QImage scaleToFit(const QImage &src, int maxWidth, int maxHeight);
	static QString generateUniqueFileName(const QString& dirPath, const QString& baseName);
	static QString copyImageToDestination(const QString& sourcePath, const QString& destFolder);

};


#endif //IMAGEHANDLER_H
