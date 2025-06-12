//
// Created by adifi on 06/02/2025.
//

#ifndef QFLOWLAYOUT_H
#define QFLOWLAYOUT_H

#include <QLayout>
#include <QRect>

class QFlowLayout : public QLayout {
public:
    explicit QFlowLayout(QWidget *parent = nullptr, int margin = 20, int spacing = -1);
    ~QFlowLayout() override;

    void addItem(QLayoutItem *item) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;

private:
    int doLayout(const QRect &rect) const;
    QList<QLayoutItem *> m_items;
};

#endif //QFLOWLAYOUT_H
