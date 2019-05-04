#include "fieldview.h"

#include <QDebug>

FieldView::FieldView()
{

}

void FieldView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "pressed";
    emit signalFieldPressed(1, 2);
}
