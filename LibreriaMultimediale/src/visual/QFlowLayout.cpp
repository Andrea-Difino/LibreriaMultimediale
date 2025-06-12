//
// Created by adifi on 06/02/2025.
//

// Qflowlayout.cpp
#include "QFlowLayout.h"
#include <QWidget>

QFlowLayout::QFlowLayout(QWidget *parent, int margin, int spacing) : QLayout(parent) {
    setContentsMargins(margin, margin, margin, margin);
    QLayout::setSpacing(spacing);
}

QFlowLayout::~QFlowLayout() {
    while (!m_items.isEmpty()) {
        delete QFlowLayout::takeAt(0);
    }
}

void QFlowLayout::addItem(QLayoutItem *item) {
    m_items.append(item);
}

QSize QFlowLayout::sizeHint() const {
    return minimumSize();
}

QSize QFlowLayout::minimumSize() const {
    QSize size;
    for (QLayoutItem *item : m_items) {
        size = size.expandedTo(item->minimumSize());
    }

    const QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());

    if (parentWidget()) {
        size.setWidth(parentWidget()->width());
    }

    return size;
}

void QFlowLayout::setGeometry(const QRect &rect) {
    QLayout::setGeometry(rect);
    int newHeight = doLayout(rect);

    if (parentWidget()) {
        parentWidget()->setMinimumHeight(newHeight);
        parentWidget()->updateGeometry();
    }
}

int QFlowLayout::count() const {
    return m_items.size();
}

QLayoutItem *QFlowLayout::itemAt(int index) const {
    return m_items.value(index);
}

QLayoutItem *QFlowLayout::takeAt(int index) {
    return index >= 0 && index < m_items.size() ? m_items.takeAt(index) : nullptr;
}

int QFlowLayout::doLayout(const QRect &rect) const {
    int x = rect.x(), y = rect.y(), lineHeight = 0;

    for (QLayoutItem *item : m_items) {
        QWidget *widget = item->widget();
        if (widget && !widget->isVisible()) continue;
        int nextX = x + item->sizeHint().width() + spacing();
        if (nextX - spacing() > rect.right() && lineHeight > 0) {
            x = rect.x();
            y += lineHeight + spacing();
            nextX = x + item->sizeHint().width() + spacing();
            lineHeight = 0;
        }
        item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y();
}
